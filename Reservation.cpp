#include "Reservation.h"
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <ctime>

using namespace std;

Reservation::Reservation(int reservationId, string userId, int resourceId, string date,
                         string startTime, string endTime)
    : reservationId(reservationId), userId(move(userId)), resourceId(resourceId),
      date(move(date)), startTime(move(startTime)), endTime(move(endTime)) {}

//converts time string to minutes past midnight
int Reservation::toMinutes(const string& timeString) {
    tm parsed{};
    istringstream ss(timeString);
    ss >> get_time(&parsed, "%H:%M");
    if (ss.fail()) {
        throw invalid_argument("Invalid time format: " + timeString);
    }
    return parsed.tm_hour * 60 + parsed.tm_min;
}

//Determines if a reservation conflicts with another reservation by comparing
// the resource, date and start and end time of both reservations
bool Reservation::overlaps(const Reservation& other) const {
    if (resourceId != other.resourceId) return false;
    if (date != other.date) return false;

    int start = toMinutes(startTime);
    int end = toMinutes(endTime);
    int otherStart = toMinutes(other.startTime);
    int otherEnd = toMinutes(other.endTime);

    return start < otherEnd && otherStart < end;
}

void Reservation::display(ostream& out) const {
    out << "Reservation #" << reservationId << " | User: " << userId
        << " | Resource: " << resourceId
        << " | Date: " << date
        << " | " << startTime << "-" << endTime;
}
