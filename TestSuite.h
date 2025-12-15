#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include "ResourceManager.h"
#include "ReservationManager.h"
#include <string>

using namespace std;

class TestSuite {
public:
    // Run all tests
    static void runAllTests();
    
private:
    // Helper function to print test section separators
    static void printSeparator(const string& title);
    
    // Individual test functions
    static void testAddingResources(ResourceManager& rm);
    static void testCreatingReservations(ReservationManager& resMgr);
    static void testDetectingCollisions(ReservationManager& resMgr);
    static void testCancelingReservations(ReservationManager& resMgr);
    static void testModifyingReservations(ReservationManager& resMgr);
    static void testQueryingReservations(ReservationManager& resMgr);
    static void testSavingAndLoading(ResourceManager& rm, ReservationManager& resMgr);
};

#endif

