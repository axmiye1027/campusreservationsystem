#include "ReservationManager.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

bool ReservationManager::hasCollision(const Reservation& candidate) const {
    auto it = reservationsByResource.find(candidate.getResourceId());
    if (it == reservationsByResource.end()) return false;

    for (int existingId : it->second) {
        const auto& existing = reservationsById.at(existingId);
        if (candidate.overlaps(existing)) return true;
    }
    return false;
}

void ReservationManager::indexReservation(const Reservation& reservation) {
    reservationsByResource[reservation.getResourceId()].push_back(reservation.getId());
    reservationsByUser[reservation.getUserId()].push_back(reservation.getId());
}

void ReservationManager::unindexReservation(int reservationId) {
    auto found = reservationsById.find(reservationId);
    if (found == reservationsById.end()) return;
    const Reservation& res = found->second;

    auto& resVec = reservationsByResource[res.getResourceId()];
    resVec.erase(remove(resVec.begin(), resVec.end(), reservationId), resVec.end());

    auto& userVec = reservationsByUser[res.getUserId()];
    userVec.erase(remove(userVec.begin(), userVec.end(), reservationId), userVec.end());
}

bool ReservationManager::createReservation(const string& userId, int resourceId, const string& date,
                                           const string& startTime, const string& endTime,
                                           Reservation& created) {
    try {
        Reservation candidate(nextReservationId, userId, resourceId, date, startTime, endTime);
        // Validate time ordering
        if (Reservation::toMinutes(candidate.getStartTime()) >= Reservation::toMinutes(candidate.getEndTime())) {
            return false;
        }

        if (hasCollision(candidate)) {
            return false;
        }

        created = candidate;
        reservationsById[nextReservationId] = candidate;
        indexReservation(candidate);
        ++nextReservationId;
        return true;
    } catch (const exception&) {
        return false;
    }
}

bool ReservationManager::cancelReservation(int reservationId, const string& requestingUserId) {
    auto it = reservationsById.find(reservationId);
    if (it == reservationsById.end()) return false;

    if (it->second.getUserId() != requestingUserId) {
        return false;
    }

    unindexReservation(reservationId);
    reservationsById.erase(it);
    return true;
}

vector<Reservation> ReservationManager::getReservationsForUser(const string& userId) const {
    vector<Reservation> result;
    auto it = reservationsByUser.find(userId);
    if (it == reservationsByUser.end()) return result;
    for (int id : it->second) {
        result.push_back(reservationsById.at(id));
    }
    return result;
}

vector<Reservation> ReservationManager::getReservationsForResource(int resourceId) const {
    vector<Reservation> result;
    auto it = reservationsByResource.find(resourceId);
    if (it == reservationsByResource.end()) return result;
    for (int id : it->second) {
        result.push_back(reservationsById.at(id));
    }
    return result;
}

void ReservationManager::displayAll(ostream& out) const {
    for (const auto& entry : reservationsById) {
        entry.second.display(out);
        out << "\n";
    }
}

bool ReservationManager::loadFromFile(const string& path) {
    ifstream in(path);
    if (!in.is_open()) {
        return false;
    }

    reservationsById.clear();
    reservationsByResource.clear();
    reservationsByUser.clear();
    nextReservationId = 1;

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        if (tokens.size() != 6) continue;
        int reservationId = stoi(tokens[0]);
        Reservation res(reservationId, tokens[1], stoi(tokens[2]), tokens[3], tokens[4], tokens[5]);
        reservationsById[reservationId] = res;
        indexReservation(res);
        nextReservationId = max(nextReservationId, reservationId + 1);
    }
    return true;
}

bool ReservationManager::saveToFile(const string& path) const {
    ofstream out(path);
    if (!out.is_open()) return false;

    for (const auto& entry : reservationsById) {
        const auto& res = entry.second;
        out << res.getId() << ',' << res.getUserId() << ',' << res.getResourceId() << ','
            << res.getDate() << ',' << res.getStartTime() << ',' << res.getEndTime() << "\n";
    }
    return true;
}
