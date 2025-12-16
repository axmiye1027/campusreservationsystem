#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>
#include <iostream>

using namespace std;

class Reservation {
    int reservationId{};
    string userId;
    int resourceId{};
    string date;      // YYYY-MM-DD
    string startTime; // HH:MM (24h)
    string endTime;   // HH:MM (24h)

public:
    Reservation() = default;
    // Construct a reservation with all identifying fields filled in.
    Reservation(int reservationId, string userId, int resourceId, string date,
                string startTime, string endTime);

    //Getters
    int getId() const { return reservationId; }
    const string& getUserId() const { return userId; }
    int getResourceId() const { return resourceId; }
    const string& getDate() const { return date; }
    const string& getStartTime() const { return startTime; }
    const string& getEndTime() const { return endTime; }

    // Convert HH:MM into minutes past midnight for comparisons.
    static int toMinutes(const string& timeString);
    // Detect overlapping time ranges on the same resource/date.
    bool overlaps(const Reservation& other) const;
    // Print summary of the reservation.
    void display(ostream& out) const;
};

#endif
