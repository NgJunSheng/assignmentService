//// Data structure for Services details
//struct Services {
//    string serviceID;
//    string servicename;
//    double price;
//    int duration;
//};
//
//// Data structure for Booking details
//struct Bookings {
//    string bookingID;
//    string customerID;
//    string staffID;
//    string serviceID;
//    string date;
//    string time;
//    string status;//confirm, cancelled, completed
//};
//
//// Global ID counters
//int customerCounter = 1005;
//int staffCounter = 1011;
//
//const int MAX_SERVICES = 100;
//const int MAX_BOOKINGS = 100;
//
//int customerCount = 4;
//int staffCount = 10;
//void clearInput();
//
////Member booking
////Ng Jun Sheng Part
//void memberBookingMenu(const string& customerID);//main page for customer
//void viewServices();
//void searchBooking(const string& customerID);
//void addSingleBooking(const string& customerID);
//void addMultipleBooking(const string& customerID);
//void editBooking(const string& customerID);
//void cancelBooking(const string& customerID);
//void viewBooking(const string& customerID);
//void generateBookingSlip(const string& customerID);
//bool isDuplicateBooking(const Bookings& newBooking);
//bool validateBooking(const Bookings& booking);
//
////Staff Booking
//void staffBookingMenu();//main page for staff
//void addService();
//void deleteService();
//void editService();
//void searchService();
//void staffAddBooking();
//void staffViewBooking();
//void staffEditBooking();
//void rescheduleCancelBooking();
//void staffSearchBooking();
//void staffBookingValidation();
//
//Services servicesDB[MAX_SERVICES] = {
//    //Service ID, Service Name, Price, Duration
//    {"SI1001", "HairCut", 30.00, 30},
//    {"SI1002", "HairStyling", 50.00, 60},
//    {"SI1003", "Coolouring", 85.00, 90},
//    {"SI1004", "NailArt", 120.00, 90},
//    {"SI1005", "Skin Care Threatment ", 110.00, 90},
//};
//
//Bookings bookingDB[MAX_BOOKINGS];
//
//int servicecount = 5;
//int bookingCount = 0;
//
//int serviceCounter = 1006;
//int bookingCounter = 1001;
//// FIND SERVICE
//// FIND SERVICE
//int findServiceID(const string& serviceID) {
//
//    for (int i = 0; i < servicecount; i++) {
//        if (servicesDB[i].serviceID == serviceID) {
//            return i;
//        }
//    }
//    return -1;
//}
//
//// FIND STAFF
//int findStaffID(const string& staffID) {
//
//    for (int i = 0; i < staffCount; i++) {
//        if (staffDB[i].idStaff == staffID) {
//            return i;
//        }
//    }
//    return -1;
//}
//
//
//// FIND BOOKING
//int findBookingID(const string& bookingID) {
//
//    for (int i = 0; i < bookingCount; i++) {
//        if (bookingDB[i].bookingID == bookingID) {
//            return i;
//        }
//    }
//    return -1;
//}
// DATE VALIDATION
//bool ValidDate(const string& date) {
//
//    // DD/MM/YYYY
//    if (date.length() != 10) {
//        return false;
//    }
//
//    if (date[2] != '/' || date[5] != '/') {
//        return false;
//    }
//
//    for (int i = 0; i < date.length(); i++) {
//
//        if (i == 2 || i == 5) {
//            continue;
//        }
//
//        if (!isdigit(date[i])) {
//            return false;
//        }
//    }
//    return true;
//}
//
//// TIME VALIDATION
//bool ValidTime(const string& time) {
//
//    // Hour:Min
//    if (time.length() != 5) {
//        return false;
//    }
//
//    if (time[2] != ':') {
//        return false;
//    }
//
//    for (int i = 0; i < time.length(); i++) {
//
//        if (i == 2) {
//            continue;
//        }
//
//        if (!isdigit(time[i])) {
//            return false;
//        }
//    }
//
//    int hour = stoi(time.substr(0, 2));
//    int minute = stoi(time.substr(3, 2));
//
//    if (hour < 0 || hour > 23) {
//        return false;
//    }
//
//    if (minute < 0 || minute > 59) {
//        return false;
//    }
//
//    return true;
//}
//
//bool isDuplicateBooking(const Bookings& newBooking) {
//    for (int i = 0; i < bookingCount; i++) {
//        // Ignore cancelled bookings
//        if (bookingDB[i].status == "Cancelled") {
//            continue;
//        }
//
//        // Same customer + same date + same time
//        if (bookingDB[i].customerID == newBooking.customerID && bookingDB[i].date == newBooking.date && bookingDB[i].time == newBooking.time) {
//            cout << "cannot have same booking time, same date and same time\n";
//            return true;
//        }
//    }
//    return false;
//}
//// --- Member booking ---
//void memberBookingMenu(const string& customerID) {
//    int choice = 0;
//    while (true) {
//        cout << "\n----------------------------------------\n";
//        cout << "          MEMBER BOOKING SYSTEM \n";
//        cout << "----------------------------------------\n";
//        cout << "1. View Services\n";
//        cout << "2. Search Booking\n";
//        cout << "3. Add Single Booking\n";
//        cout << "4. Add Multiple Bookings\n";
//        cout << "5. Edit Booking\n";
//        cout << "6. Cancel Booking\n";
//        cout << "7. View My Bookings\n";
//        cout << "8. Generate Confirmation Slip\n";
//        cout << "9. Exit\n";
//        cout << "Select option (1-9): ";
//
//        if (!(cin >> choice)) {
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            cout << "Invalid input. Please enter a number from 1 to 9.\n";
//            continue;
//        }
//
//        switch (choice) {
//
//        case 1:
//            viewServices();
//            break;
//
//        case 2:
//            searchBooking(customerID);
//            break;
//
//        case 3:
//            addSingleBooking(customerID);
//            break;
//
//        case 4:
//            addMultipleBooking(customerID);
//            break;
//
//        case 5:
//            editBooking(customerID);
//            break;
//
//        case 6:
//            cancelBooking(customerID);
//            break;
//
//        case 7:
//            viewBooking(customerID);
//            break;
//
//        case 8:
//            generateBookingSlip(customerID);
//            break;
//
//        case 9:
//            return;
//
//        default:
//            cout << "[Error] Invalid selection.\n";
//        }
//    }
//}
//
////VIEW SERVICES
//void viewServices() {
//    cout << "\n========================================\n";
//    cout << right << setw(10) << "SERVICES\n";
//    cout << "========================================\n";
//    for (int i = 0; i < servicecount; i++) {
//        cout << "Service ID : " << servicesDB[i].serviceID << "\n";
//        cout << "Service    : " << servicesDB[i].servicename << "\n";
//        cout << "Price      : RM " << fixed << setprecision(2) << servicesDB[i].price << "\n";
//        cout << "Duration   : " << servicesDB[i].duration << " minutes\n";
//        cout << "----------------------------------------\n";
//    }
//}
//
////SEARCH BOOKING
//void searchBooking(const string& customerID) {
//    string bookid;
//    cout << "\nEnter Booking ID to search: ";
//    cin >> bookid;
//
//    int index = findBookingID(bookid);
//    if (index == -1) {
//        cout << "[Error] Booking not found.\n";
//        return;
//    }
//
//    if (bookingDB[index].customerID != customerID) {
//        cout << "[Error] You do not have permission to view this booking.\n";
//        return;
//    }
//
//    cout << "\n========== BOOKING FOUND ==========\n";
//    cout << "Booking ID : " << bookingDB[index].bookingID << "\n";
//    cout << "Customer ID: " << bookingDB[index].customerID << "\n";
//    cout << "Service ID : " << bookingDB[index].serviceID << "\n";
//    cout << "Staff ID   : " << bookingDB[index].staffID << "\n";
//    cout << "Date       : " << bookingDB[index].date << "\n";
//    cout << "Time       : " << bookingDB[index].time << "\n";
//    cout << "Status     : " << bookingDB[index].status << "\n";
//}
//
//// MEMBER - ADD SINGLE BOOKING
//void addSingleBooking(const string& customerID) {
//
//    if (bookingCount >= MAX_BOOKINGS) {
//        cout << "[Error] Booking database is full.\n";
//        return;
//    }
//
//    Bookings newBooking;
//    newBooking.customerID = customerID;
//    newBooking.status = "Confirmed";
//    cout << "\n========== AVAILABLE STAFF ==========\n";
//    for (int i = 0; i < staffCount; i++) {
//        cout << "[" << i + 1 << "] "
//            << staffDB[i].nameStaff
//            << " (" << staffDB[i].idStaff << ")"
//            << " - " << staffDB[i].positionStaff
//            << "\n";
//    }
//    cout << "\n========== ADD SINGLE BOOKING ==========\n";
//    viewServices();
//    cout << "Enter Service ID: ";
//    cin >> newBooking.serviceID;
//    if (findServiceID(newBooking.serviceID) == -1) {
//        cout << "[Error] Service ID not found.\n";
//        return;
//    }
//
//    cout << "Enter Staff ID: ";
//    cin >> newBooking.staffID;
//    if (findStaffID(newBooking.staffID) == -1) {
//        cout << "[Error] Staff ID not found.\n";
//        return;
//    }
//
//    cout << "Enter Date (DD/MM/YYYY): ";
//    cin >> newBooking.date;
//
//    cout << "Enter Time (HH:MM): ";
//    cin >> newBooking.time;
//
//    // Check normal validation first
//    if (!validateBooking(newBooking)) {
//        cout << "[Error] Wrong Input.\n";
//        return;
//    }
//
//    // Check duplicate booking
//    if (isDuplicateBooking(newBooking)) {
//        cout << "[Error] You already have a booking on " << newBooking.date << " at " << newBooking.time << ".\n";
//        cout << "You cannot make another booking at the same time.\n";
//        return;
//    }
//
//    newBooking.bookingID = "B" + to_string(bookingCounter++);
//    bookingDB[bookingCount] = newBooking;
//    bookingCount++;
//
//    cout << "\n[Success] Booking added successfully!\n";
//    cout << "Booking ID: " << newBooking.bookingID << "\n";
//}
//
//// MEMBER - ADD MULTIPLE BOOKINGS
//void addMultipleBooking(const string& customerID) {
//    char response;
//    cout << "\n========== ADD MULTIPLE BOOKINGS ==========\n";
//
//    do {
//        addSingleBooking(customerID);
//        cout << "\nAdd another booking? (Y/N): ";
//        cin >> response;
//        response = toupper(response);
//    } while (response == 'Y');
//    cout << "\nFinished adding multiple bookings.\n";
//}
//
//// MEMBER - EDIT BOOKING
//void editBooking(const string& customerID) {
//    string editid;
//    cout << "\nEnter Booking ID to edit: ";
//    cin >> editid;
//
//    int index = findBookingID(editid);
//    if (index == -1) {
//        cout << "[Error] Booking not found.\n";
//        return;
//    }
//
//    if (bookingDB[index].customerID != customerID) {
//        cout << "[Error] You cannot edit this booking.\n";
//        return;
//    }
//
//    if (bookingDB[index].status == "Cancelled") {
//        cout << "[Error] Cancelled booking cannot be edited.\n";
//        return;
//    }
//
//    string newDate;
//    string newTime;
//    cout << "\nEnter new date (DD/MM/YYYY): ";
//    cin >> newDate;
//
//    if (!ValidDate(newDate)) {
//        cout << "[Error] Invalid date format.\n";
//        return;
//    }
//
//    cout << "Enter new time (HH:MM): ";
//    cin >> newTime;
//    if (!ValidTime(newTime)) {
//        cout << "[Error] Invalid time format.\n";
//        return;
//    }
//
//    bookingDB[index].date = newDate;
//    bookingDB[index].time = newTime;
//    cout << "\n[Success] Booking updated successfully.\n";
//}
//
//// MEMBER - CANCEL BOOKING
//void cancelBooking(const string& customerID) {
//    string cancelid;
//    cout << "\nEnter Booking ID to cancel: ";
//    cin >> cancelid;
//
//    int index = findBookingID(cancelid);
//    if (index == -1) {
//        cout << "[Error] Booking not found.\n";
//        return;
//    }
//
//    if (bookingDB[index].customerID != customerID) {
//        cout << "[Error] You cannot cancel this booking.\n";
//        return;
//    }
//
//    if (bookingDB[index].status == "Cancelled") {
//        cout << "[Error] Booking is already cancelled.\n";
//        return;
//    }
//
//    bookingDB[index].status = "Cancelled";
//    cout << "\n[Success] Booking "
//        << cancelid
//        << " has been cancelled.\n";
//}
//
//// MEMBER - VIEW MY BOOKINGS
//void viewBooking(const string& customerID) {
//    bool found = false;
//    cout << "\n========== MY BOOKINGS ==========\n";
//    for (int i = 0; i < bookingCount; i++) {
//        if (bookingDB[i].customerID == customerID) {
//            found = true;
//            cout << "\nBooking ID : " << bookingDB[i].bookingID << "\n";
//            cout << "Service ID : " << bookingDB[i].serviceID << "\n";
//            cout << "Staff ID   : " << bookingDB[i].staffID << "\n";
//            cout << "Date       : " << bookingDB[i].date << "\n";
//            cout << "Time       : " << bookingDB[i].time << "\n";
//            cout << "Status     : " << bookingDB[i].status << "\n";
//            cout << "--------------------------------\n";
//        }
//    }
//
//    if (!found) {
//        cout << "No bookings found.\n";
//    }
//}
//
//// MEMBER - GENERATE BOOKING SLIP
//void generateBookingSlip(const string& customerID) {
//    string id;
//    cout << "\nEnter Booking ID: ";
//    cin >> id;
//
//    int index = findBookingID(id);
//    if (index == -1) {
//        cout << "[Error] Booking not found.\n";
//        return;
//    }
//
//    if (bookingDB[index].customerID != customerID) {
//        cout << "[Error] You cannot access this booking.\n";
//        return;
//    }
//
//    cout << "\n";
//    cout << "========================================\n";
//    cout << "       BOOKING CONFIRMATION SLIP        \n";
//    cout << "========================================\n";
//    cout << "Booking ID : " << bookingDB[index].bookingID << "\n";
//    cout << "Customer ID: " << bookingDB[index].customerID << "\n";
//    cout << "Service ID : " << bookingDB[index].serviceID << "\n";
//    cout << "Staff ID   : " << bookingDB[index].staffID << "\n";
//    cout << "Date       : " << bookingDB[index].date << "\n";
//    cout << "Time       : " << bookingDB[index].time << "\n";
//    cout << "Status     : " << bookingDB[index].status << "\n";
//    cout << "========================================\n";
//    cout << "       Thank you for your booking!      \n";
//    cout << "========================================\n";
//}
//
//// STAFF BOOKING MENU
//void staffBookingMenu() {
//    int choice;
//    while (true) {
//        cout << "\n----------------------------------------\n";
//        cout << "           STAFF BOOKING SYSTEM\n";
//        cout << "----------------------------------------\n";
//        cout << "1. Add Services\n";
//        cout << "2. View Services\n";
//        cout << "3. Delete Services\n";
//        cout << "4. Edit Services\n";
//        cout << "5. Search Services\n";
//        cout << "6. Add Booking\n";
//        cout << "7. View Booking\n";
//        cout << "8. Reschedule / Cancel Booking\n";
//        cout << "9. Edit Booking\n";
//        cout << "10. Search Booking\n";
//        cout << "11. Exit\n";
//        cout << "Select option: ";
//
//        if (!(cin >> choice)) {
//            cout << "[Error] Invalid input.\n";
//            continue;
//        }
//
//        switch (choice) {
//
//        case 1:
//            addService();
//            break;
//
//        case 2:
//            viewServices();
//            break;
//
//        case 3:
//            deleteService();
//            break;
//
//        case 4:
//            editService();
//            break;
//
//        case 5:
//            searchService();
//            break;
//
//        case 6:
//            staffAddBooking();
//            break;
//
//        case 7:
//            staffViewBooking();
//            break;
//
//        case 8:
//            rescheduleCancelBooking();
//            break;
//
//        case 9:
//            staffEditBooking();
//            break;
//
//        case 10:
//            staffSearchBooking();
//            break;
//
//        case 11:
//            return;
//
//        default:
//            cout << "[Error] Invalid selection.\n";
//        }
//    }
//}
//
//// STAFF - ADD SERVICES
//void addService() {
//
//    if (servicecount >= MAX_SERVICES) {
//        cout << "[Error] Service database is full.\n";
//        return;
//    }
//
//    Services newService;
//    newService.serviceID = "SI" + to_string(serviceCounter++);
//    cout << "\n========== ADD SERVICE ==========\n";
//    cout << "Service ID: " << newService.serviceID << "\n";
//
//    cout << "Enter Service Name: ";
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//    getline(cin, newService.servicename);
//
//    cout << "Enter Price: RM ";
//    cin >> newService.price;
//
//    cout << "Enter Duration (minutes): ";
//    cin >> newService.duration;
//
//    if (newService.servicename.empty() || newService.price <= 0 || newService.duration <= 0) {
//        cout << "[Error] Invalid service information.\n";
//        return;
//    }
//
//    servicesDB[servicecount] = newService;
//    servicecount++;
//
//    cout << "\n[Success] Service added successfully.\n";
//}
//
//// STAFF - VIEW SERVICES
//void viewAllServices() {
//    cout << "\n========== ALL SERVICES ==========\n";
//    for (int i = 0; i < servicecount; i++) {
//        cout << "\nService ID : "
//            << servicesDB[i].serviceID << "\n";
//
//        cout << "Name       : "
//            << servicesDB[i].servicename << "\n";
//
//        cout << "Price      : RM "
//            << fixed << setprecision(2)
//            << servicesDB[i].price << "\n";
//
//        cout << "Duration   : "
//            << servicesDB[i].duration
//            << " minutes\n";
//        cout << "----------------------------------\n";
//    }
//}
//
//// STAFF - DELETE SERVICE
//void deleteService() {
//    string id;
//
//    cout << "\nEnter Service ID to delete: ";
//    cin >> id;
//
//    int index = findServiceID(id);
//    if (index == -1) {
//        cout << "[Error] Service not found.\n";
//        return;
//    }
//
//    for (int i = index; i < servicecount - 1; i++) {
//        servicesDB[i] = servicesDB[i + 1];
//    }
//
//    servicecount--;
//    cout << "\n[Success] Service deleted successfully.\n";
//}
//
//// STAFF - EDIT SERVICE
//void editService() {
//    string id;
//    cout << "\nEnter Service ID to edit: ";
//    cin >> id;
//
//    int index = findServiceID(id);
//    if (index == -1) {
//        cout << "[Error] Service not found.\n";
//        return;
//    }
//
//    cout << "\nEnter new service name: ";
//    getline(cin, servicesDB[index].servicename);
//
//    cout << "Enter new price: RM ";
//    cin >> servicesDB[index].price;
//
//    cout << "Enter new duration: ";
//    cin >> servicesDB[index].duration;
//
//    if (servicesDB[index].price <= 0 || servicesDB[index].duration <= 0 || servicesDB[index].servicename.empty()) {
//        cout << "[Error] Invalid service information.\n";
//        return;
//    }
//
//    cout << "\n[Success] Service updated successfully.\n";
//}
//
//// STAFF - SEARCH SERVICE   
//void searchService() {
//    string id;
//    cout << "\nEnter Service ID to search: ";
//    cin >> id;
//
//    int index = findServiceID(id);
//    if (index == -1) {
//        cout << "[Error] Service not found.\n";
//        return;
//    }
//
//    cout << "\n========== SERVICE FOUND ==========\n";
//    cout << "Service ID : " << servicesDB[index].serviceID << "\n";
//    cout << "Service    : " << servicesDB[index].servicename << "\n";
//    cout << "Price      : RM " << fixed << setprecision(2) << servicesDB[index].price << "\n";
//    cout << "Duration   : " << servicesDB[index].duration << " minutes\n";
//}
//
//// STAFF - ADD BOOKING
//void staffAddBooking() {
//
//    if (bookingCount >= MAX_BOOKINGS) {
//        cout << "[Error] Booking database is full.\n";
//        return;
//    }
//
//    Bookings newBooking;
//    newBooking.bookingID = "B" + to_string(bookingCounter++);
//
//    cout << "\n========== STAFF ADD BOOKING ==========\n";
//
//    cout << "Generated Booking ID: "
//        << newBooking.bookingID << "\n";
//
//    cout << "Enter Customer ID: ";
//    cin >> newBooking.customerID;
//
//    viewAllServices();
//
//    cout << "Enter Service ID: ";
//    cin >> newBooking.serviceID;
//    if (findServiceID(newBooking.serviceID) == -1) {
//        cout << "[Error] Service not found.\n";
//        return;
//    }
//
//    cout << "\nAvailable Staff:\n";
//    for (int i = 0; i < staffCount; i++) {
//        cout << staffDB[i].idStaff << " - " << staffDB[i].nameStaff << "\n";
//    }
//
//    cout << "Enter Staff ID: ";
//    cin >> newBooking.staffID;
//    if (findStaffID(newBooking.staffID) == -1) {
//        cout << "[Error] Staff not found.\n";
//        return;
//    }
//
//    cout << "Enter Date (DD/MM/YYYY): ";
//    cin >> newBooking.date;
//
//    cout << "Enter Time (HH:MM): ";
//    cin >> newBooking.time;
//
//    newBooking.status = "Confirmed";
//
//    if (!validateBooking(newBooking)) {
//        cout << "[Error] Booking validation failed.\n";
//        return;
//    }
//
//    bookingDB[bookingCount] = newBooking;
//    bookingCount++;
//    cout << "\n[Success] Booking added successfully.\n";
//    cout << "Booking ID: "
//        << newBooking.bookingID << "\n";
//}
//
//// STAFF - VIEW BOOKING
//
//void staffViewBooking() {
//
//    if (bookingCount == 0) {
//        cout << "\nNo bookings available.\n";
//        return;
//    }
//
//    cout << "\n========== ALL BOOKINGS ==========\n";
//
//    for (int i = 0; i < bookingCount; i++) {
//        cout << "\nBooking ID : " << bookingDB[i].bookingID << "\n";
//        cout << "Customer ID: " << bookingDB[i].customerID << "\n";
//        cout << "Service ID : " << bookingDB[i].serviceID << "\n";
//        cout << "Staff ID   : " << bookingDB[i].staffID << "\n";
//        cout << "Date       : " << bookingDB[i].date << "\n";
//        cout << "Time       : " << bookingDB[i].time << "\n";
//        cout << "Status     : " << bookingDB[i].status << "\n";
//        cout << "----------------------------------\n";
//    }
//}
//
//// STAFF - RESCHEDULE / CANCEL BOOKING
//void rescheduleCancelBooking() {
//    string id;
//    int choice;
//    cout << "\nEnter Booking ID: ";
//    cin >> id;
//
//    int index = findBookingID(id);
//    if (index == -1) {
//        cout << "[Error] Booking not found.\n";
//        return;
//    }
//
//    cout << "\n1. Reschedule Booking\n";
//    cout << "2. Cancel Booking\n";
//    cout << "Select option: ";
//    cin >> choice;
//
//    if (choice == 1) {
//        string newDate;
//        string newTime;
//        cout << "Enter new date (DD/MM/YYYY): ";
//        cin >> newDate;
//
//        if (!ValidDate(newDate)) {
//            cout << "[Error] Invalid date format.\n";
//            return;
//        }
//
//        cout << "Enter new time (HH:MM): ";
//        cin >> newTime;
//
//        if (!ValidTime(newTime)) {
//            cout << "[Error] Invalid time format.\n";
//            return;
//        }
//
//        bookingDB[index].date = newDate;
//        bookingDB[index].time = newTime;
//        bookingDB[index].status = "Confirmed";
//        cout << "\n[Success] Booking rescheduled successfully.\n";
//    }
//
//    else if (choice == 2) {
//
//        if (bookingDB[index].status == "Cancelled") {
//            cout << "[Error] Booking already cancelled.\n";
//            return;
//        }
//
//        bookingDB[index].status = "Cancelled";
//        cout << "\n[Success] Booking cancelled successfully.\n";
//    }
//
//    else {
//        cout << "[Error] Invalid selection.\n";
//    }
//}
//
//// STAFF - EDIT BOOKING
//void staffEditBooking() {
//    string id;
//    cout << "\nEnter Booking ID to edit: ";
//    cin >> id;
//
//    int index = findBookingID(id);
//    if (index == -1) {
//        cout << "[Error] Booking not found.\n";
//        return;
//    }
//
//    if (bookingDB[index].status == "Cancelled") {
//        cout << "[Error] Cancelled booking cannot be edited.\n";
//        return;
//    }
//
//    cout << "\nCurrent Service ID: " << bookingDB[index].serviceID << "\n";
//
//    viewAllServices();
//    cout << "Enter new Service ID: ";
//    cin >> bookingDB[index].serviceID;
//
//    if (findServiceID(bookingDB[index].serviceID) == -1) {
//        cout << "[Error] Service not found.\n";
//        return;
//    }
//
//    cout << "\nAvailable Staff:\n";
//    for (int i = 0; i < staffCount; i++) {
//        cout << staffDB[i].idStaff
//            << " - "
//            << staffDB[i].nameStaff
//            << "\n";
//    }
//
//    cout << "Enter new Staff ID: ";
//    cin >> bookingDB[index].staffID;
//
//    if (findStaffID(bookingDB[index].staffID) == -1) {
//        cout << "[Error] Staff not found.\n";
//        return;
//    }
//    cout << "\n[Success] Booking edited successfully.\n";
//}
//
//// STAFF - SEARCH BOOKING
//void staffSearchBooking() {
//
//    string id;
//
//    cout << "\nEnter Booking ID to search: ";
//    cin >> id;
//
//    int index = findBookingID(id);
//    if (index == -1) {
//        cout << "[Error] Booking not found.\n";
//        return;
//    }
//
//    cout << "\n========== BOOKING FOUND ==========\n";
//    cout << "Booking ID : " << bookingDB[index].bookingID << "\n";
//    cout << "Customer ID: " << bookingDB[index].customerID << "\n";
//    cout << "Service ID : " << bookingDB[index].serviceID << "\n";
//    cout << "Staff ID   : " << bookingDB[index].staffID << "\n";
//    cout << "Date       : " << bookingDB[index].date << "\n";
//    cout << "Time       : " << bookingDB[index].time << "\n";
//    cout << "Status     : " << bookingDB[index].status << "\n";
//}
