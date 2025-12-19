/******************************************************************************
 * AUTHORS			: Paul S, Ryland L, Amy X, Cristal D, Elizabeth S
 * PROJECT #3		: Campus Reservation System
 * CLASS			: CS 1C
 * SECTION			: TTh 8a
 * DUE DATE			: 12/22/25
******************************************************************************/
#include "Menu.h"
#include "ResourceManager.h"
#include "ReservationManager.h"
#include "StudyRoom.h"
#include "LabEquipment.h"
#include "Reservation.h"
#include "TestSuite.h"
#include <iomanip>
#include <memory>
#include <vector>
#include <sstream>
#include <regex>
#include <stdexcept>

// Helper validation functions
namespace {
	/******************************************************************************
	 * FUNCTION - getValidInteger
	 * ----------------------------------------------------------------------------
	 * Prompts for an integer input and validates it. Handles cin failures.
	 * ----------------------------------------------------------------------------
	 * Returns true if valid integer was entered, false otherwise
	 *****************************************************************************/
	bool getValidInteger(int& value, const string& prompt) {
		string input;
		cout << prompt;
		getline(cin, input);
		
		istringstream iss(input);
		if (iss >> value && iss.eof()) {
			return true;
		}
		cout << "Invalid input. Please enter a valid integer.\n";
		return false;
	}
	
	/******************************************************************************
	 * FUNCTION - getValidPositiveInteger
	 * ----------------------------------------------------------------------------
	 * Prompts for a positive integer input and validates it.
	 * ----------------------------------------------------------------------------
	 * Returns true if valid positive integer was entered, false otherwise
	 *****************************************************************************/
	bool getValidPositiveInteger(int& value, const string& prompt) {
		if (!getValidInteger(value, prompt)) {
			return false;
		}
		if (value <= 0) {
			cout << "Please enter a positive integer.\n";
			return false;
		}
		return true;
	}
	
	/******************************************************************************
	 * FUNCTION - isValidDateFormat
	 * ----------------------------------------------------------------------------
	 * Validates that a date string is in YYYY-MM-DD format.
	 * ----------------------------------------------------------------------------
	 * Returns true if date format is valid, false otherwise
	 *****************************************************************************/
	bool isValidDateFormat(const string& date) {
		regex datePattern(R"(\d{4}-\d{2}-\d{2})");
		if (!regex_match(date, datePattern)) {
			return false;
		}
		
		// Additional validation: check if date components are reasonable
		istringstream iss(date);
		int year, month, day;
		char dash1, dash2;
		
		if (iss >> year >> dash1 >> month >> dash2 >> day) {
			if (dash1 == '-' && dash2 == '-' &&
				year >= 2000 && year <= 2100 &&
				month >= 1 && month <= 12 &&
				day >= 1 && day <= 31) {
				return true;
			}
		}
		return false;
	}
	
	/******************************************************************************
	 * FUNCTION - isValidTimeFormat
	 * ----------------------------------------------------------------------------
	 * Validates that a time string is in HH:MM format and has valid values.
	 * ----------------------------------------------------------------------------
	 * Returns true if time format is valid, false otherwise
	 *****************************************************************************/
	bool isValidTimeFormat(const string& time) {
		regex timePattern(R"(\d{2}:\d{2})");
		if (!regex_match(time, timePattern)) {
			return false;
		}
		
		// Additional validation: check if time components are valid
		istringstream iss(time);
		int hour, minute;
		char colon;
		
		if (iss >> hour >> colon >> minute) {
			if (colon == ':' &&
				hour >= 0 && hour <= 23 &&
				minute >= 0 && minute <= 59) {
				return true;
			}
		}
		return false;
	}
	
	/******************************************************************************
	 * FUNCTION - getValidDate
	 * ----------------------------------------------------------------------------
	 * Prompts for a date input and validates YYYY-MM-DD format.
	 * ----------------------------------------------------------------------------
	 * Returns true if valid date was entered, false otherwise
	 *****************************************************************************/
	bool getValidDate(string& date, const string& prompt) {
		cout << prompt;
		getline(cin, date);
		
		if (date.empty()) {
			cout << "Date cannot be empty.\n";
			return false;
		}
		
		if (!isValidDateFormat(date)) {
			cout << "Invalid date format. Please use YYYY-MM-DD (e.g., 2024-12-25).\n";
			return false;
		}
		return true;
	}
	
	/******************************************************************************
	 * FUNCTION - getValidTime
	 * ----------------------------------------------------------------------------
	 * Prompts for a time input and validates HH:MM format.
	 * ----------------------------------------------------------------------------
	 * Returns true if valid time was entered, false otherwise
	 *****************************************************************************/
	bool getValidTime(string& time, const string& prompt) {
		cout << prompt;
		getline(cin, time);
		
		if (time.empty()) {
			cout << "Time cannot be empty.\n";
			return false;
		}
		
		if (!isValidTimeFormat(time)) {
			cout << "Invalid time format. Please use HH:MM in 24-hour format (e.g., 14:30).\n";
			return false;
		}
		return true;
	}
	
	/******************************************************************************
	 * FUNCTION - getNonEmptyString
	 * ----------------------------------------------------------------------------
	 * Prompts for a string input and ensures it's not empty.
	 * ----------------------------------------------------------------------------
	 * Returns true if non-empty string was entered, false otherwise
	 *****************************************************************************/
	bool getNonEmptyString(string& value, const string& prompt) {
		cout << prompt;
		getline(cin, value);
		
		if (value.empty()) {
			cout << "This field cannot be empty.\n";
			return false;
		}
		return true;
	}
}

/******************************************************************************
 * FUNCTION - displayMenu
 * ----------------------------------------------------------------------------
 * Displays a menu for users. The menu displayed depends on whether the user
 * is logged in and if they are a student or admin.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 * 			BORDER_SIZE : size of a border; formatting
 *
 * 		THE ARGUMENTS FOR THE FOLLOWING PARAMETERS WILL BE MODIFIED.
 * 			Input read in the function will be stored in these parameters &
 * 			returned via the parameters.
 * 				u		: reference to a User object
 * ----------------------------------------------------------------------------
 * Returns nothing; outputs menu for users who are logged in
 *****************************************************************************/
void displayMenu(const int BORDER_SIZE, User &u)
{
	cout << left;
	cout << setfill('=') << setw(BORDER_SIZE) << "" << endl;


	if (!u.getIsLoggedIn())
	{
		cout << "SMART CAMPUS RESERVATION SYSTEM\n";
		cout << "0. Exit\n"
				"1. Create an account\n"
				"2. Login to your account\n";
	}
	else
	{
		cout << "SMART CAMPUS RESERVATION SYSTEM | " << u.getRole()
			 << ": " << u.getUsername() << endl;

		if (u.getRole() == "Student")
		{
			cout << "0. Logout\n"
					"1. Reserve campus resources\n"
					"2. Find campus resources\n"
					"3. View campus resources\n"
					"4. View my reservations\n"
					"5. Cancel a reservation\n";
		}
		else
		{
			cout << "0. Logout\n"
					"1. Find campus resources\n"
					"2. View campus resources\n"
					"3. Add campus resources\n"
					"4. Edit campus resources\n"
					"5. Delete campus resources\n"
					"6. Run all tests\n";
		}
	}
	cout << setfill('=') << setw(BORDER_SIZE) << "" << endl;
	cout << setfill(' ');
	cout << right;
}

/******************************************************************************
 * FUNCTION - getAndValidateMenuInput
 * ----------------------------------------------------------------------------
 * Prompts for initial user input and checks if it within the valid range
 * specified by LOWER_BOUND and UPPER_BOUND.
 *
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 * 				LOWER_BOUND	: lower bound for integer inputs, not included
 * 				UPPER_BOUND	: upper bound for integer inputs, not included
 *
 * 		THE ARGUMENTS FOR THE FOLLOWING PARAMETERS WILL BE MODIFIED.
 * 			Input read in the function will be stored in these parameters &
 * 			returned via the parameters.
 * 				input		: user input for an integer
 * ----------------------------------------------------------------------------
 * Returns nothing; alters the value of input
 *****************************************************************************/
void getAndValidateMenuInput(int& input,
							 const int LOWER_BOUND,
							 const int UPPER_BOUND)
{
	bool invalid = true;

	do
	{
		cout << "Enter selection: ";
		if (cin >> input) {
			cin.ignore(10000, '\n');
			if (input < LOWER_BOUND || input > UPPER_BOUND)
			{
				cout << "Invalid entry. Please enter a number between " 
					 << (LOWER_BOUND + 1) << " and " << UPPER_BOUND << ".\n";
			}
			else
			{
				invalid = false;
			}
		} else {
			cout << "Invalid input. Please enter a valid number.\n";
			cin.clear();
			cin.ignore(10000, '\n');
		}
	} while (invalid);
}

/******************************************************************************
 * FUNCTION - reserveResource
 * ----------------------------------------------------------------------------
 * Allows a student to reserve a campus resource.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 * 			BORDER_SIZE : size of a border; formatting
 * 			resourceManager : reference to ResourceManager
 * 			reservationManager : reference to ReservationManager
 * 			currentUser : reference to current User object
 * ----------------------------------------------------------------------------
 * Returns nothing; handles resource reservation
 *****************************************************************************/
void reserveResource(const int BORDER_SIZE, ResourceManager& resourceManager, 
                     ReservationManager& reservationManager, User& currentUser)
{
	cout << "\n" << string(BORDER_SIZE, '-') << "\n";
	cout << "RESERVE CAMPUS RESOURCES\n";
	cout << string(BORDER_SIZE, '-') << "\n";
	
	// Display available resources
	auto resources = resourceManager.listResources();
	if (resources.empty()) {
		cout << "No resources available.\n";
		return;
	}
	
	cout << "Available resources:\n";
	for (const auto& res : resources) {
		res->display(cout);
		cout << "\n";
	}
	
	int resourceId;
	if (!getValidPositiveInteger(resourceId, "Enter resource ID: ")) {
		return;
	}
	
	auto resource = resourceManager.findResource(resourceId);
	if (!resource) {
		cout << "Resource not found.\n";
		return;
	}
	
	string date;
	if (!getValidDate(date, "Enter date (YYYY-MM-DD): ")) {
		return;
	}
	
	string startTime;
	if (!getValidTime(startTime, "Enter start time (HH:MM): ")) {
		return;
	}
	
	string endTime;
	if (!getValidTime(endTime, "Enter end time (HH:MM): ")) {
		return;
	}
	
	// Validate that start time is before end time
	try {
		int startMinutes = Reservation::toMinutes(startTime);
		int endMinutes = Reservation::toMinutes(endTime);
		
		if (startMinutes >= endMinutes) {
			cout << "\nError: Start time must be before end time.\n";
			return;
		}
	} catch (const exception&) {
		cout << "\nError: Invalid time format.\n";
		return;
	}
	
	Reservation created;
	bool success = reservationManager.createReservation(
		currentUser.getUsername(), resourceId, date, startTime, endTime, created);
	
	if (success) {
		cout << "\nReservation created successfully!\n";
		created.display(cout);
		cout << "\n";
	} else {
		cout << "\nFailed to create reservation. Possible reasons:\n";
		cout << "- Time conflict with existing reservation\n";
		cout << "- Invalid time values\n";
		cout << "Please try again with different times.\n";
	}
}

/******************************************************************************
 * FUNCTION - findResources
 * ----------------------------------------------------------------------------
 * Allows users to find campus resources by name, category, or attribute.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 * 			BORDER_SIZE : size of a border; formatting
 * 			resourceManager : reference to ResourceManager
 * ----------------------------------------------------------------------------
 * Returns nothing; displays search results
 *****************************************************************************/
void findResources(const int BORDER_SIZE, ResourceManager& resourceManager)
{
	cout << "\n" << string(BORDER_SIZE, '-') << "\n";
	cout << "FIND CAMPUS RESOURCES\n";
	cout << string(BORDER_SIZE, '-') << "\n";
	cout << "Search by:\n";
	cout << "1. Name\n";
	cout << "2. Category\n";
	cout << "3. Attribute\n";
	
	int searchChoice;
	if (!getValidInteger(searchChoice, "Enter selection: ")) {
		return;
	}
	
	if (searchChoice < 1 || searchChoice > 3) {
		cout << "Invalid selection. Please enter 1, 2, or 3.\n";
		return;
	}
	
	vector<shared_ptr<Resource>> results;
	if (searchChoice == 1) {
		string name;
		if (!getNonEmptyString(name, "Enter name to search: ")) {
			return;
		}
		results = resourceManager.findByName(name);
	} else if (searchChoice == 2) {
		string category;
		if (!getNonEmptyString(category, "Enter category (StudyRoom or LabEquipment): ")) {
			return;
		}
		if (category != "StudyRoom" && category != "LabEquipment") {
			cout << "Invalid category. Please enter 'StudyRoom' or 'LabEquipment'.\n";
			return;
		}
		results = resourceManager.filterByCategory(category);
	} else if (searchChoice == 3) {
		string attr;
		if (!getNonEmptyString(attr, "Enter attribute name: ")) {
			return;
		}
		string value;
		if (!getNonEmptyString(value, "Enter attribute value: ")) {
			return;
		}
		results = resourceManager.filterByAttribute(attr, value);
	}
	
	if (results.empty()) {
		cout << "No resources found.\n";
	} else {
		cout << "\nFound " << results.size() << " resource(s):\n";
		for (const auto& res : results) {
			res->display(cout);
			cout << "\n";
		}
	}
}

/******************************************************************************
 * FUNCTION - viewResources
 * ----------------------------------------------------------------------------
 * Displays all campus resources.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 * 			BORDER_SIZE : size of a border; formatting
 * 			resourceManager : reference to ResourceManager
 * ----------------------------------------------------------------------------
 * Returns nothing; displays all resources
 *****************************************************************************/
void viewResources(const int BORDER_SIZE, ResourceManager& resourceManager)
{
	cout << "\n" << string(BORDER_SIZE, '-') << "\n";
	cout << "VIEW ALL CAMPUS RESOURCES\n";
	cout << string(BORDER_SIZE, '-') << "\n";
	
	auto resources = resourceManager.listResources();
	if (resources.empty()) {
		cout << "No resources available.\n";
	} else {
		cout << "Total resources: " << resources.size() << "\n\n";
		for (const auto& res : resources) {
			res->display(cout);
			cout << "\n";
		}
	}
}

/******************************************************************************
 * FUNCTION - viewMyReservations
 * ----------------------------------------------------------------------------
 * Displays all reservations for the current user.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 * 			BORDER_SIZE : size of a border; formatting
 * 			reservationManager : reference to ReservationManager
 * 			currentUser : reference to current User object
 * ----------------------------------------------------------------------------
 * Returns nothing; displays user's reservations
 *****************************************************************************/
void viewMyReservations(const int BORDER_SIZE, ReservationManager& reservationManager, 
                        User& currentUser)
{
	cout << "\n" << string(BORDER_SIZE, '-') << "\n";
	cout << "MY RESERVATIONS\n";
	cout << string(BORDER_SIZE, '-') << "\n";
	
	auto reservations = reservationManager.getReservationsForUser(currentUser.getUsername());
	if (reservations.empty()) {
		cout << "You have no reservations.\n";
	} else {
		cout << "You have " << reservations.size() << " reservation(s):\n\n";
		for (const auto& res : reservations) {
			res.display(cout);
			cout << "\n";
		}
	}
}

/******************************************************************************
 * FUNCTION - cancelReservation
 * ----------------------------------------------------------------------------
 * Allows a student to cancel one of their reservations.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 * 			BORDER_SIZE : size of a border; formatting
 * 			reservationManager : reference to ReservationManager
 * 			currentUser : reference to current User object
 * ----------------------------------------------------------------------------
 * Returns nothing; handles reservation cancellation
 *****************************************************************************/
void cancelReservation(const int BORDER_SIZE, ReservationManager& reservationManager, 
                       User& currentUser)
{
	cout << "\n" << string(BORDER_SIZE, '-') << "\n";
	cout << "CANCEL A RESERVATION\n";
	cout << string(BORDER_SIZE, '-') << "\n";
	
	auto reservations = reservationManager.getReservationsForUser(currentUser.getUsername());
	if (reservations.empty()) {
		cout << "You have no reservations to cancel.\n";
		return;
	}
	
	cout << "Your reservations:\n";
	for (const auto& res : reservations) {
		res.display(cout);
		cout << "\n";
	}
	
	int resId;
	if (!getValidPositiveInteger(resId, "\nEnter reservation ID to cancel: ")) {
		return;
	}
	
	if (reservationManager.cancelReservation(resId, currentUser.getUsername())) {
		cout << "\nReservation cancelled successfully!\n";
	} else {
		cout << "\nFailed to cancel reservation. It may not exist or you don't have permission.\n";
	}
}

/******************************************************************************
 * FUNCTION - addResource
 * ----------------------------------------------------------------------------
 * Allows an admin to add a new campus resource (Study Room or Lab Equipment).
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 * 			BORDER_SIZE : size of a border; formatting
 * 			resourceManager : reference to ResourceManager
 * ----------------------------------------------------------------------------
 * Returns nothing; handles resource addition
 *****************************************************************************/
void addResource(const int BORDER_SIZE, ResourceManager& resourceManager)
{
	cout << "\n" << string(BORDER_SIZE, '-') << "\n";
	cout << "ADD CAMPUS RESOURCES\n";
	cout << string(BORDER_SIZE, '-') << "\n";
	cout << "Resource type:\n";
	cout << "1. Study Room\n";
	cout << "2. Lab Equipment\n";
	
	int typeChoice;
	if (!getValidInteger(typeChoice, "Enter selection: ")) {
		return;
	}
	
	if (typeChoice < 1 || typeChoice > 2) {
		cout << "Invalid selection. Please enter 1 or 2.\n";
		return;
	}
	
	if (typeChoice == 1) {
		int id;
		if (!getValidPositiveInteger(id, "Enter resource ID: ")) {
			return;
		}
		
		string name;
		if (!getNonEmptyString(name, "Enter name: ")) {
			return;
		}
		
		int capacity;
		if (!getValidPositiveInteger(capacity, "Enter capacity: ")) {
			return;
		}
		
		string location;
		if (!getNonEmptyString(location, "Enter location: ")) {
			return;
		}
		
		string hours;
		if (!getNonEmptyString(hours, "Enter availability hours (e.g., 08:00-22:00): ")) {
			return;
		}
		
		auto studyRoom = make_shared<StudyRoom>(id, name, capacity, location, hours);
		if (resourceManager.addResource(studyRoom)) {
			cout << "\nStudy room added successfully!\n";
		} else {
			cout << "\nFailed to add study room. ID may already exist.\n";
		}
	} else if (typeChoice == 2) {
		int id;
		if (!getValidPositiveInteger(id, "Enter resource ID: ")) {
			return;
		}
		
		string name;
		if (!getNonEmptyString(name, "Enter name: ")) {
			return;
		}
		
		string equipmentType;
		if (!getNonEmptyString(equipmentType, "Enter equipment type: ")) {
			return;
		}
		
		string fragileStr;
		if (!getNonEmptyString(fragileStr, "Is fragile? (true/false): ")) {
			return;
		}
		
		if (fragileStr != "true" && fragileStr != "false") {
			cout << "Invalid input. Please enter 'true' or 'false'.\n";
			return;
		}
		bool fragile = (fragileStr == "true");
		
		auto labEquipment = make_shared<LabEquipment>(id, name, equipmentType, fragile);
		if (resourceManager.addResource(labEquipment)) {
			cout << "\nLab equipment added successfully!\n";
		} else {
			cout << "\nFailed to add lab equipment. ID may already exist.\n";
		}
	} else {
		cout << "Invalid selection.\n";
	}
}

/******************************************************************************
 * FUNCTION - editResource
 * ----------------------------------------------------------------------------
 * Allows an admin to edit an existing campus resource.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 * 			BORDER_SIZE : size of a border; formatting
 * 			resourceManager : reference to ResourceManager
 * ----------------------------------------------------------------------------
 * Returns nothing; handles resource editing
 *****************************************************************************/
void editResource(const int BORDER_SIZE, ResourceManager& resourceManager)
{
	cout << "\n" << string(BORDER_SIZE, '-') << "\n";
	cout << "EDIT CAMPUS RESOURCES\n";
	cout << string(BORDER_SIZE, '-') << "\n";
	
	int id;
	if (!getValidPositiveInteger(id, "Enter resource ID to edit: ")) {
		return;
	}
	
	auto resource = resourceManager.findResource(id);
	if (!resource) {
		cout << "Resource not found.\n";
		return;
	}
	
	cout << "Current resource:\n";
	resource->display(cout);
	cout << "\n\n";
	
	string category = resource->getCategory();
	if (category == "StudyRoom") {
		auto studyRoom = dynamic_pointer_cast<StudyRoom>(resource);
		if (studyRoom) {
			cout << "Enter new name (or press Enter to keep current): ";
			string name;
			getline(cin, name);
			if (!name.empty()) {
				studyRoom->setName(name);
			}
			
			int capacity;
			if (getValidInteger(capacity, "Enter new capacity (or -1 to keep current): ")) {
				if (capacity >= 0) {
					studyRoom->setCapacity(capacity);
				}
			}
			
			cout << "Enter new location (or press Enter to keep current): ";
			string location;
			getline(cin, location);
			if (!location.empty()) {
				studyRoom->setLocation(location);
			}
			
			cout << "Enter new availability hours (or press Enter to keep current): ";
			string hours;
			getline(cin, hours);
			if (!hours.empty()) {
				studyRoom->setAvailabilityHours(hours);
			}
			
			cout << "\nResource updated successfully!\n";
		}
	} else if (category == "LabEquipment") {
		auto labEquipment = dynamic_pointer_cast<LabEquipment>(resource);
		if (labEquipment) {
			cout << "Enter new name (or press Enter to keep current): ";
			string name;
			getline(cin, name);
			if (!name.empty()) {
				labEquipment->setName(name);
			}
			
			cout << "Enter new equipment type (or press Enter to keep current): ";
			string type;
			getline(cin, type);
			if (!type.empty()) {
				labEquipment->setEquipmentType(type);
			}
			
			string fragileStr;
			cout << "Enter fragile status (true/false, or press Enter to keep current): ";
			getline(cin, fragileStr);
			if (!fragileStr.empty()) {
				if (fragileStr == "true" || fragileStr == "false") {
					labEquipment->setFragile(fragileStr == "true");
				} else {
					cout << "Invalid input. Please enter 'true' or 'false'.\n";
				}
			}
			
			cout << "\nResource updated successfully!\n";
		}
	}
}

/******************************************************************************
 * FUNCTION - deleteResource
 * ----------------------------------------------------------------------------
 * Allows an admin to delete a campus resource and cancel all its reservations.
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 * 			BORDER_SIZE : size of a border; formatting
 * 			resourceManager : reference to ResourceManager
 * 			reservationManager : reference to ReservationManager
 * ----------------------------------------------------------------------------
 * Returns nothing; handles resource deletion
 *****************************************************************************/
void deleteResource(const int BORDER_SIZE, ResourceManager& resourceManager, 
                    ReservationManager& reservationManager)
{
	cout << "\n" << string(BORDER_SIZE, '-') << "\n";
	cout << "DELETE CAMPUS RESOURCES\n";
	cout << string(BORDER_SIZE, '-') << "\n";
	
	int id;
	if (!getValidPositiveInteger(id, "Enter resource ID to delete: ")) {
		return;
	}
	
	auto resource = resourceManager.findResource(id);
	if (!resource) {
		cout << "Resource not found.\n";
		return;
	}
	
	cout << "Resource to delete:\n";
	resource->display(cout);
	cout << "\nAre you sure you want to delete this resource? (yes/no): ";
	string confirm;
	getline(cin, confirm);
	
	if (confirm == "yes") {
		// Also cancel all reservations for this resource
		auto reservations = reservationManager.getReservationsForResource(id);
		for (const auto& res : reservations) {
			reservationManager.cancelReservation(res.getId(), res.getUserId());
		}
		
		if (resourceManager.removeResource(id)) {
			cout << "\nResource deleted successfully!\n";
		} else {
			cout << "\nFailed to delete resource.\n";
		}
	} else {
		cout << "Deletion cancelled.\n";
	}
}

/******************************************************************************
 * FUNCTION - runAllTests
 * ----------------------------------------------------------------------------
 * Runs all tests in the TestSuite (admin only).
 * ----------------------------------------------------------------------------
 * PRE-CONDITIONS
 * 		The following need a defined value passed in:
 * 			BORDER_SIZE : size of a border; formatting
 * ----------------------------------------------------------------------------
 * Returns nothing; runs test suite
 *****************************************************************************/
void runAllTests(const int BORDER_SIZE)
{
	cout << "\n" << string(BORDER_SIZE, '-') << "\n";
	cout << "RUNNING ALL TESTS\n";
	cout << string(BORDER_SIZE, '-') << "\n";
	TestSuite::runAllTests();
	cout << "\n" << string(BORDER_SIZE, '-') << "\n";
	cout << "Tests completed.\n";
}
