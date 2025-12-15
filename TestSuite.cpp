#include "TestSuite.h"
#include "StudyRoom.h"
#include "LabEquipment.h"
#include "Reservation.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

void TestSuite::printSeparator(const string& title) {
    cout << "\n" << string(60, '=') << "\n";
    cout << title << "\n";
    cout << string(60, '=') << "\n";
}

void TestSuite::testAddingResources(ResourceManager& rm) {
    printSeparator("TEST 1: Adding Resources");
    
    // Add study rooms
    auto room1 = make_shared<StudyRoom>(1, "Library Study Room A", 4, "Library 2nd Floor", "08:00-22:00");
    auto room2 = make_shared<StudyRoom>(2, "Science Building Room 101", 6, "Science Building", "09:00-21:00");
    auto room3 = make_shared<StudyRoom>(3, "Quiet Study Room B", 2, "Library 3rd Floor", "07:00-23:00");
    
    rm.addResource(room1);
    rm.addResource(room2);
    rm.addResource(room3);
    
    // Add lab equipment
    auto equipment1 = make_shared<LabEquipment>(4, "Microscope Alpha", "Microscope", true);
    auto equipment2 = make_shared<LabEquipment>(5, "Oscilloscope Beta", "Oscilloscope", false);
    auto equipment3 = make_shared<LabEquipment>(6, "Centrifuge Gamma", "Centrifuge", true);
    
    rm.addResource(equipment1);
    rm.addResource(equipment2);
    rm.addResource(equipment3);
    
    cout << "Added " << rm.listResources().size() << " resources:\n";
    for (const auto& resource : rm.listResources()) {
        resource->display(cout);
        cout << "\n";
    }
    
    // Test finding resources
    auto found = rm.findResource(1);
    if (found) {
        cout << "\n✓ Successfully found resource ID 1: " << found->getName() << "\n";
    } else {
        cout << "\n✗ Failed to find resource ID 1\n";
    }
}

void TestSuite::testCreatingReservations(ReservationManager& resMgr) {
    printSeparator("TEST 2: Creating Reservations");
    
    Reservation created;
    
    // Create valid reservations
    bool success1 = resMgr.createReservation("Alice", 1, "2024-03-15", "10:00", "12:00", created);
    if (success1) {
        cout << "✓ Created reservation #" << created.getId() << " for user Alice\n";
        created.display(cout);
        cout << "\n";
    } else {
        cout << "✗ Failed to create reservation for Alice\n";
    }
    
    bool success2 = resMgr.createReservation("Bob", 1, "2024-03-15", "13:00", "15:00", created);
    if (success2) {
        cout << "✓ Created reservation #" << created.getId() << " for user Bob\n";
        created.display(cout);
        cout << "\n";
    } else {
        cout << "✗ Failed to create reservation for Bob\n";
    }
    
    bool success3 = resMgr.createReservation("Charlie", 2, "2024-03-15", "09:00", "11:00", created);
    if (success3) {
        cout << "✓ Created reservation #" << created.getId() << " for user Charlie\n";
        created.display(cout);
        cout << "\n";
    } else {
        cout << "✗ Failed to create reservation for Charlie\n";
    }
    
    bool success4 = resMgr.createReservation("Diana", 4, "2024-03-16", "14:00", "16:00", created);
    if (success4) {
        cout << "✓ Created reservation #" << created.getId() << " for user Diana\n";
        created.display(cout);
        cout << "\n";
    } else {
        cout << "✗ Failed to create reservation for Diana\n";
    }
    
    // Test invalid time ordering (start >= end)
    bool invalid1 = resMgr.createReservation("Eve", 3, "2024-03-15", "15:00", "15:00", created);
    if (!invalid1) {
        cout << "✓ Correctly rejected reservation with start time >= end time\n";
    } else {
        cout << "✗ Should have rejected invalid time ordering\n";
    }
    
    cout << "\nAll reservations:\n";
    resMgr.displayAll(cout);
}

void TestSuite::testDetectingCollisions(ReservationManager& resMgr) {
    printSeparator("TEST 3: Detecting Collisions");
    
    Reservation created;
    
    // Try to create overlapping reservation (should fail)
    bool collision1 = resMgr.createReservation("Frank", 1, "2024-03-15", "11:00", "13:00", created);
    if (!collision1) {
        cout << "✓ Correctly detected collision: 11:00-13:00 overlaps with existing 10:00-12:00\n";
    } else {
        cout << "✗ Should have detected collision\n";
    }
    
    // Try to create reservation that starts exactly when another ends (should succeed - no overlap)
    bool noCollision1 = resMgr.createReservation("Grace", 1, "2024-03-15", "12:00", "12:30", created);
    if (noCollision1) {
        cout << "✓ Correctly allowed non-overlapping reservation: 12:00-12:30 (adjacent to 10:00-12:00)\n";
        created.display(cout);
        cout << "\n";
    } else {
        cout << "✗ Should have allowed non-overlapping reservation\n";
    }
    
    // Try to create reservation on same resource, same date, overlapping time
    bool collision2 = resMgr.createReservation("Henry", 1, "2024-03-15", "14:00", "16:00", created);
    if (!collision2) {
        cout << "✓ Correctly detected collision: 14:00-16:00 overlaps with existing 13:00-15:00\n";
    } else {
        cout << "✗ Should have detected collision\n";
    }
    
    // Try to create reservation on same resource, different date (should succeed)
    bool noCollision2 = resMgr.createReservation("Iris", 1, "2024-03-16", "10:00", "12:00", created);
    if (noCollision2) {
        cout << "✓ Correctly allowed reservation on different date: 2024-03-16\n";
        created.display(cout);
        cout << "\n";
    } else {
        cout << "✗ Should have allowed reservation on different date\n";
    }
    
    // Try to create reservation on different resource, same date/time (should succeed)
    bool noCollision3 = resMgr.createReservation("Jack", 2, "2024-03-15", "10:00", "12:00", created);
    if (noCollision3) {
        cout << "✓ Correctly allowed reservation on different resource: Resource 2\n";
        created.display(cout);
        cout << "\n";
    } else {
        cout << "✗ Should have allowed reservation on different resource\n";
    }
}

void TestSuite::testCancelingReservations(ReservationManager& resMgr) {
    printSeparator("TEST 4: Canceling Reservations");
    
    // Get initial count
    vector<Reservation> allReservations;
    // We'll need to check by getting reservations for a user
    auto aliceReservations = resMgr.getReservationsForUser("Alice");
    cout << "Initial reservations for Alice: " << aliceReservations.size() << "\n";
    
    // Cancel a valid reservation (Alice's first reservation should be ID 1)
    if (!aliceReservations.empty()) {
        int reservationId = aliceReservations[0].getId();
        bool canceled = resMgr.cancelReservation(reservationId, "Alice");
        if (canceled) {
            cout << "✓ Successfully canceled reservation #" << reservationId << " for Alice\n";
        } else {
            cout << "✗ Failed to cancel reservation\n";
        }
        
        // Verify it's gone
        aliceReservations = resMgr.getReservationsForUser("Alice");
        cout << "Remaining reservations for Alice: " << aliceReservations.size() << "\n";
    }
    
    // Try to cancel someone else's reservation (should fail)
    auto bobReservations = resMgr.getReservationsForUser("Bob");
    if (!bobReservations.empty()) {
        int bobReservationId = bobReservations[0].getId();
        bool unauthorizedCancel = resMgr.cancelReservation(bobReservationId, "Alice");
        if (!unauthorizedCancel) {
            cout << "✓ Correctly prevented Alice from canceling Bob's reservation\n";
        } else {
            cout << "✗ Should have prevented unauthorized cancellation\n";
        }
    }
    
    // Try to cancel non-existent reservation
    bool invalidCancel = resMgr.cancelReservation(9999, "Alice");
    if (!invalidCancel) {
        cout << "✓ Correctly handled cancellation of non-existent reservation\n";
    } else {
        cout << "✗ Should have failed to cancel non-existent reservation\n";
    }
    
    cout << "\nRemaining reservations after cancellations:\n";
    resMgr.displayAll(cout);
}

void TestSuite::testModifyingReservations(ReservationManager& resMgr) {
    printSeparator("TEST 5: Modifying Reservations");
    
    // Modification is done by canceling and creating a new one
    auto charlieReservations = resMgr.getReservationsForUser("Charlie");
    if (!charlieReservations.empty()) {
        int oldReservationId = charlieReservations[0].getId();
        int resourceId = charlieReservations[0].getResourceId();
        string date = charlieReservations[0].getDate();
        
        cout << "Original reservation:\n";
        charlieReservations[0].display(cout);
        cout << "\n";
        
        // Cancel the old reservation
        bool canceled = resMgr.cancelReservation(oldReservationId, "Charlie");
        if (canceled) {
            cout << "✓ Canceled old reservation #" << oldReservationId << "\n";
            
            // Create new reservation with modified time
            Reservation modified;
            bool created = resMgr.createReservation("Charlie", resourceId, date, "10:00", "12:00", modified);
            if (created) {
                cout << "✓ Created modified reservation:\n";
                modified.display(cout);
                cout << "\n";
            } else {
                cout << "✗ Failed to create modified reservation (may have collision)\n";
            }
        } else {
            cout << "✗ Failed to cancel old reservation for modification\n";
        }
    }
}

void TestSuite::testQueryingReservations(ReservationManager& resMgr) {
    printSeparator("TEST 7: Querying Reservations");
    
    // Get reservations for a user
    auto userReservations = resMgr.getReservationsForUser("Bob");
    cout << "Reservations for user 'Bob': " << userReservations.size() << "\n";
    for (const auto& res : userReservations) {
        res.display(cout);
        cout << "\n";
    }
    
    // Get reservations for a resource
    auto resourceReservations = resMgr.getReservationsForResource(1);
    cout << "\nReservations for resource ID 1: " << resourceReservations.size() << "\n";
    for (const auto& res : resourceReservations) {
        res.display(cout);
        cout << "\n";
    }
    
    // Get reservations for another resource
    auto resource2Reservations = resMgr.getReservationsForResource(2);
    cout << "\nReservations for resource ID 2: " << resource2Reservations.size() << "\n";
    for (const auto& res : resource2Reservations) {
        res.display(cout);
        cout << "\n";
    }
}

void TestSuite::testSavingAndLoading(ResourceManager& rm, ReservationManager& resMgr) {
    printSeparator("TEST 6: Saving and Loading Data");
    
    // Save resources
    bool savedResources = rm.saveToFile("resources.txt");
    if (savedResources) {
        cout << "✓ Successfully saved resources to resources.txt\n";
    } else {
        cout << "✗ Failed to save resources\n";
    }
    
    // Save reservations
    bool savedReservations = resMgr.saveToFile("reservations.txt");
    if (savedReservations) {
        cout << "✓ Successfully saved reservations to reservations.txt\n";
    } else {
        cout << "✗ Failed to save reservations\n";
    }
    
    // Create a new manager to test loading
    ReservationManager loadedResMgr;
    bool loaded = loadedResMgr.loadFromFile("reservations.txt");
    if (loaded) {
        cout << "✓ Successfully loaded reservations from file\n";
        cout << "\nLoaded reservations:\n";
        loadedResMgr.displayAll(cout);
        
        // Verify data integrity
        auto loadedAliceReservations = loadedResMgr.getReservationsForUser("Alice");
        auto loadedBobReservations = loadedResMgr.getReservationsForUser("Bob");
        
        cout << "\nVerification:\n";
        cout << "Loaded reservations for Alice: " << loadedAliceReservations.size() << "\n";
        cout << "Loaded reservations for Bob: " << loadedBobReservations.size() << "\n";
        
        if (!loadedBobReservations.empty()) {
            cout << "Sample loaded reservation:\n";
            loadedBobReservations[0].display(cout);
            cout << "\n";
        }
    } else {
        cout << "✗ Failed to load reservations from file\n";
    }
    
    // Test loading non-existent file
    ReservationManager emptyMgr;
    bool loadFailed = emptyMgr.loadFromFile("nonexistent.txt");
    if (!loadFailed) {
        cout << "✓ Correctly handled loading non-existent file\n";
    } else {
        cout << "✗ Should have failed to load non-existent file\n";
    }
}

void TestSuite::runAllTests() {
    cout << "Campus Reservation System - Test Suite\n";
    cout << "======================================\n";
    
    ResourceManager rm;
    ReservationManager resMgr;
    
    // Run all test cases
    testAddingResources(rm);
    testCreatingReservations(resMgr);
    testDetectingCollisions(resMgr);
    testCancelingReservations(resMgr);
    testModifyingReservations(resMgr);
    testQueryingReservations(resMgr);
    testSavingAndLoading(rm, resMgr);
    
    printSeparator("All Tests Complete.");
    cout << "Files created: resources.txt, reservations.txt\n";
}

