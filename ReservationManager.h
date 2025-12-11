#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include "Reservation.h"
#include "ResourceManager.h"
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class ReservationManager {
    unordered_map<int, Reservation> reservationsById;
    unordered_map<int, vector<int>> reservationsByResource;
    unordered_map<string, vector<int>> reservationsByUser;
    int nextReservationId{1};

    // Check if the candidate reservation conflicts with an existing one.
    bool hasCollision(const Reservation& candidate) const;
    // Index reservation into resource and user lookup tables.
    void indexReservation(const Reservation& reservation);
    // Remove reservation from lookup tables.
    void unindexReservation(int reservationId);

public:
    // Create reservation if times are valid and no overlap occurs.
    bool createReservation(const string& userId, int resourceId, const string& date,
                           const string& startTime, const string& endTime, Reservation& created);

    // Cancel reservation if it exists and the requesting user owns it.
    bool cancelReservation(int reservationId, const string& requestingUserId);

    // Fetch all reservations tied to a user or resource.
    vector<Reservation> getReservationsForUser(const string& userId) const;
    vector<Reservation> getReservationsForResource(int resourceId) const;

    // Print all known reservations.
    void displayAll(ostream& out) const;

    // CSV persistence helper methods.
    bool loadFromFile(const string& path);
    bool saveToFile(const string& path) const;
};

#endif
