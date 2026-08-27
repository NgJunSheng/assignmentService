#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits> 
#include <cctype>
#include <algorithm>
#include <utility>
#include <ctime>

using namespace std;

// Data structure for Customer details
struct Customer {
    string idCustomer;
    string nameCustomer;
    string genderCustomer;
    string phoneCustomer;
    string emailCustomer;
    string passwordCustomer;
};

// Data structure for Member details
struct Member {
    string idMember;
    string nameMember;
    string genderMember;
    string phoneMember;
    string emailMember;
    string passwordMember;
};

// Data structure for Salon Staff details
struct Staff {
    string idStaff;
    string nameStaff;
    string genderStaff;
    string phoneStaff;
    string emailStaff;
    string passwordStaff;
    string positionStaff;
};

// Define timeslot set
struct Timeslot {
    int id;
    string time;
    bool isBooked;
    string bookingID;
    string staffID;
    string staffName;
    string customerID;
    string customerName;
    string service;
    string status;
};

// Data structure for Services details
struct Services {
    string serviceID;
    string servicename;
    double price;
    int duration;
};

// Data structure for Booking details
struct Bookings {
    string bookingID;
    string customerID;
    string staffID;
    string serviceID;
    string date;
    string time;
    string status;//confirm, cancelled, completed
};

void clearInput();
//Member booking
void memberBookingMenu(const string& customerID);//main page for customer
void viewServices();
void searchBooking(const string& customerID);
void addSingleBooking(const string& customerID);
void addMultipleBooking(const string& customerID);
void editBooking(const string& customerID);
void cancelBooking(const string& customerID);
void viewBooking(const string& customerID);
void generateBookingSlip(const string& customerID);

//Staff Booking
void staffBookingMenu();//main page for staff
void addService();
void deleteService();
void editService();
void searchService();
void staffAddBooking();
void staffViewBooking();
void staffEditBooking();
void rescheduleCancelBooking();
void staffSearchBooking();
void staffBookingValidation();

// Function Declarations
void logo();
void mainMenu();
void customerPortal();
void registerCustomer();
void registerMember();
void customerMemberLogin();
void staffPortal();
void registerStaff();
void staffLogin();
void showCustomerMemberUI(const string& userId, const string& accountType);
void memberCustomerProfile(const string& userId, const string& accountType);
void viewProfile(const string& userId, const string& accountType);
void editProfileCMUI(const string& userId, const string& accountType);
void showStaffUI(const string& username);
void memberManagement();
void staffManagement();
void showStaffList();
void showMemberCustomerList();
void clearInput();
bool isValidEmail(const string& email);
bool isValidPassword(const string& pass);
bool isValidPhoneNumber(const string& phone);
bool isValidName(const string& name);
void AppointmentManagement();
void ViewAllAppointment(const Timeslot schedule[], int size, string filterStaffID = "");
void getCurrentSystemTime(int& year, int& month, int& day, int& hour);
void CreateAppointmentStaff();
void initMonthlySchedule();
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
// Global ID counters
int customerCounter = 1005;
int memberCounter = 1005;
int staffCounter = 1011;
int servicecount = 5;
int serviceCounter = 1006;
int bookingCounter = 1001;

const int MAX_CUSTOMERS = 100;
const int MAX_MEMBERS = 100;
const int MAX_STAFF = 100;
const int MAX_SERVICES = 100;

int customerCount = 4;
int memberCount = 4;
int staffCount = 10;

// Total slots and days in month
const int TOTAL_SLOTS = 7;
const int DAYS_IN_MONTH = 31;

Services servicesDB[MAX_SERVICES] = {
    //Service ID, Service Name, Price, Duration
    {"SI1001", "HairCut", 30.00, 30},
    {"SI1002", "HairStyling", 50.00, 60},
    {"SI1003", "Coolouring", 85.00, 90},
    {"SI1004", "NailArt", 120.00, 90},
    {"SI1005", "Skin Care Threatment ", 110.00, 90},
};

Timeslot defaultDaySlots[TOTAL_SLOTS] = {
    {1, "09:00 AM - 11:00 AM", false, "", "", "", "", "", "", ""},
    {2, "11:00 AM - 01:00 PM", false, "", "", "", "", "", "", ""},
    {3, "01:00 PM - 03:00 PM", false, "", "", "", "", "", "", ""},
    {4, "03:00 PM - 05:00 PM", false, "", "", "", "", "", "", ""},
    {5, "05:00 PM - 07:00 PM", false, "", "", "", "", "", "", ""},
    {6, "07:00 PM - 09:00 PM", false, "", "", "", "", "", "", ""},
    {7, "09:00 PM - 11:00 PM", false, "", "", "", "", "", "", ""}
};

Timeslot schedule[DAYS_IN_MONTH][TOTAL_SLOTS];

// Color word for appointment
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";

Customer customerDB[MAX_CUSTOMERS] = {
    {"C1001", "Viknesh a/l Vijayan", "Male", "013-5678901", "viknesh129@gmail.com", "SolarPower2026!"},
    {"C1002", "Priya a/p Anbalagan", "Female", "014-6789012", "priya59@gmail.com", "Bikoma72!q"},
    {"C1003", "Teo Bao Bin", "Male", "016-7890123", "bb520go@gmail.com", "k8n9vp2m5x"},
    {"C1004", "Lily Yee", "Female", "017-8901234", "lilyisflower43@gmail.com", "K0N9VP2M5Z"}
};

Member memberDB[MAX_MEMBERS] = {
    {"M1001", "Eren Chew", "Male", "017-6543210", "erenono097@gmail.com", "k8N9vP2mX5"},
    {"M1002", "Tan Shin Nang", "Male", "018-2345678", "startan67@gmail.com", "b9M3zP7wR#"},
    {"M1003", "Noor Siti", "Female", "011-12345678", "siti945@gmail.com", "TungtSahur345"},
    {"M1004", "Alice Low", "Female", "019-5678901", "alicelow@gmail.com", "76WhatheDogDoing//"}
};

Staff staffDB[MAX_STAFF] = {
    {"STF1001", "Kim Ji Soo", "Female", "011-2233445", "jisookim123@gmail.com", "k8N9vP2m!", "Hair Stylist"},
    {"STF1002", "Sarah Jenkins", "Female", "017-8899001", "sarah36@gmail.com", "r9W!z2#k&", "Hair Color Stylist"},
    {"STF1003", "Sim Jia Yih", "Female", "011-10546505", "jiayih@gmail.com", "j7N5qW8mX2z%", "Hair Color Stylist"},
    {"STF1004", "Lim Xiao Qing", "Female", "018-9032655", "xiaoqing@gmail.com", "w9K4zM2pR!", "Nail Technician"},
    {"STF1005", "Lim Cai Xuan", "Female", "012-6125939", "caixuan@gmail.com", "t3X8qP5mL9#", "Receptionist"},
    {"STF1006", "Lee Hao Zheng", "Male", "016-5011218", "haozheng@gmail.com", "y8M2!zR9#vW@", "Nail Technician"},
    {"STF1007", "Ng Jun Sheng", "Male", "017-3746889", "junsheng@gmail.com", "h3N9!qX5$k&", "Receptionist"},
    {"STF1008", "Lao Teh", "Male", "017-88990012", "laoteh@gmail.com", "c9P5!xT2$w@", "Skincare Specialist"},
    {"STF1009", "Noor Shahirah", "Female", "010-86043225", "shahirah@gmail.com", "k6P3#wT8$mL&", "Skincare Specialist"},
    {"STF1010", "Roslizawati", "Female", "017-88378451", "rosealwaysrosie@gmail.com", "But860//wt=", "Hair Stylist"}
};


// FIND SERVICE
int findServiceID(const string& serviceID) {

    for (int i = 0; i < servicecount; i++) {
        if (servicesDB[i].serviceID == serviceID) {
            return i;
        }
    }
    return -1;
}

// FIND STAFF
int findStaffID(const string& staffID) {

    for (int i = 0; i < staffCount; i++) {
        if (staffDB[i].idStaff == staffID) {
            return i;
        }
    }
    return -1;
}


// FIND BOOKING
bool findBookingID(const string& bookingID, int& dayIndex, int& slotIndex) {
    for (int day = 0; day < DAYS_IN_MONTH; day++) {
        for (int slot = 0; slot < TOTAL_SLOTS; slot++) {
            if (schedule[day][slot].bookingID == bookingID) {
                dayIndex = day;
                slotIndex = slot;
                return true;
            }
        }
    }
    return false;
}

// DATE VALIDATION
bool ValidDate(const string& date) {

    // DD/MM/YYYY
    if (date.length() != 10) {
        return false;
    }

    if (date[2] != '/' || date[5] != '/') {
        return false;
    }

    for (int i = 0; i < date.length(); i++) {

        if (i == 2 || i == 5) {
            continue;
        }

        if (!isdigit(date[i])) {
            return false;
        }
    }
    return true;
}

// TIME VALIDATION
bool ValidTime(const string& time) {

    // Hour:Min
    if (time.length() != 5) {
        return false;
    }

    if (time[2] != ':') {
        return false;
    }

    for (int i = 0; i < time.length(); i++) {

        if (i == 2) {
            continue;
        }

        if (!isdigit(time[i])) {
            return false;
        }
    }

    int hour = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(3, 2));

    if (hour < 0 || hour > 23) {
        return false;
    }

    if (minute < 0 || minute > 59) {
        return false;
    }

    return true;
}

//BOOKING DUPLICATE
bool isDuplicateBooking(const string& customerID, int dayIndex, int slotIndex) {
    for (int slot = 0; slot < TOTAL_SLOTS; slot++) {
        if (schedule[dayIndex][slot].isBooked &&
            schedule[dayIndex][slot].customerID == customerID) {
            if (slot == slotIndex) {
                return true;
            }
        }
    }
    return false;
}

// BOOKING VALIDATION
bool validateBooking(const Bookings& booking) {

    // Customer ID cannot be empty
    if (booking.customerID.empty()) {
        return false;
    }

    // Service must exist
    if (findServiceID(booking.serviceID) == -1) {
        return false;
    }

    // Staff must exist
    if (findStaffID(booking.staffID) == -1) {
        return false;
    }

    // Date cannot be empty
    if (booking.date.empty()) {
        return false;
    }

    // Date format
    if (!ValidDate(booking.date)) {
        return false;
    }

    // Time cannot be empty
    if (booking.time.empty()) {
        return false;
    }

    // Time format
    if (!ValidTime(booking.time)) {
        return false;
    }

    // Status cannot be empty
    if (booking.status.empty()) {
        return false;
    }

    return true;
}

int main() {
    initMonthlySchedule(); // FIXED: Initialized schedule here so bookings persist
    logo();
    mainMenu();
    return 0;
}

int findCustomerIndex(const string& id) {
    for (int i = 0; i < customerCount; ++i) {
        if (customerDB[i].idCustomer == id) return i;
    }
    return -1;
}

int findMemberIndex(const string& id) {
    for (int i = 0; i < memberCount; ++i) {
        if (memberDB[i].idMember == id) return i;
    }
    return -1;
}

int findStaffIndex(const string& id) {
    string searchID = id;
    transform(searchID.begin(), searchID.end(), searchID.begin(), ::toupper);

    for (int i = 0; i < staffCount; ++i) {
        string dbID = staffDB[i].idStaff;
        transform(dbID.begin(), dbID.end(), dbID.begin(), ::toupper);

        if (dbID == searchID) return i;
    }
    return -1;
}

bool isValidName(const string& name) {
    if (name.empty()) return false;
    for (char c : name) {
        if (isdigit(c)) return false;
        if (!isalpha(c) && !isspace(c) && c != '\'' && c != '-') return false;
    }
    return true;
}

bool isValidPhoneNumber(const string& phone) {
    if (phone.empty()) return false;
    if (phone.find('-') == string::npos) return false;
    for (char c : phone) {
        if (!isdigit(c) && c != '-' && !isspace(c)) return false;
    }
    return true;
}

bool isValidEmail(const string& email) {
    string domain = "@gmail.com";
    if (email.length() < domain.length()) return false;
    return email.compare(email.length() - domain.length(), domain.length(), domain) == 0;
}

bool isValidPassword(const string& pass) {
    if (pass.length() < 8) return false;
    bool hasLetter = false;
    bool hasDigit = false;
    for (char c : pass) {
        if (isalpha(c)) hasLetter = true;
        if (isdigit(c)) hasDigit = true;
    }
    return hasLetter && hasDigit;
}

void logo() {
    cout << R"(
##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### #####  
 ######    ######       ######     ###    ##        #######  ##    ##    
##    ##  ##    ##     ##    ##   ## ##   ##       ##     ## ###   ##    
##        ##           ##        ##   ##  ##       ##     ## ####  ##    
##   #### ##   ####     ######  ##     ## ##       ##     ## ## ## ##    
##    ##  ##    ##           ## ######### ##       ##     ## ##  ####    
##    ##  ##    ##     ##    ## ##     ## ##       ##     ## ##   ###    
 ######    ######       ######  ##     ## ########  #######  ##    ##    
##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### #####  
)" << endl;
}

void mainMenu() {
    int choice = 0;
    while (true) {
        cout << "--------------MAIN SYSTEM MENU--------------\n";
        cout << "[ 1 ] Customer / Member\n";
        cout << "[ 2 ] Staff\n";
        cout << "[ 3 ] Exit System\n";
        cout << "Select option (1-3): ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
        case 1:
            customerPortal();
            break;
        case 2:
            staffPortal();
            break;
        case 3:
            cout << "Exiting application. Goodbye!\n";
            return;
        default:
            cout << "Invalid selection. Please enter 1, 2, or 3.\n";
        }
    }
}

void customerPortal() {
    int choice = 0;
    while (true) {
        cout << "============ CUSTOMER/MEMBER PORTAL ============\n";
        cout << "[ 1 ] Customer Registration\n";
        cout << "[ 2 ] Member Registration\n";
        cout << "[ 3 ] Customer / Member Login\n";
        cout << "[ 4 ] Exit (Return to Main Menu)\n";
        cout << "Select option (1-4): ";

        if (!(cin >> choice)) {
            clearInput();
            continue;
        }
        switch (choice) {
        case 1:
            registerCustomer();
            break;
        case 2:
            registerMember();
            break;
        case 3:
            customerMemberLogin();
            break;
        case 4:
            cout << "Returning to Main Menu...\n";
            return;
        default:
            cout << "Invalid option. Try again.\n";
        }
    }
}

void registerCustomer() {
    if (customerCount >= MAX_CUSTOMERS) {
        cout << "[Error] Customer database capacity reached!\n";
        return;
    }

    Customer newCustomer;
    cout << "\n--- NEW CUSTOMER REGISTRATION ---\n";
    string customerGeneratedID = "C" + to_string(customerCounter++);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "Enter Full Name: ";
        getline(cin, newCustomer.nameCustomer);
        if (isValidName(newCustomer.nameCustomer)) break;
        cout << "[Error] Invalid name! Only can use alphabet. Try again.\n";
    }

    string genderInput;
    while (true) {
        cout << "Enter Gender (m/f): ";
        cin >> genderInput;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (genderInput == "m" || genderInput == "M") {
            newCustomer.genderCustomer = "Male";
            break;
        }
        else if (genderInput == "f" || genderInput == "F") {
            newCustomer.genderCustomer = "Female";
            break;
        }
        else {
            cout << "[Error] Invalid gender! Please enter 'm' for Male or 'f' for Female.\n";
        }
    }

    while (true) {
        cout << "Enter Phone Number (e.g.: xxx-xxxxxxxx): ";
        cin >> newCustomer.phoneCustomer;
        if (isValidPhoneNumber(newCustomer.phoneCustomer)) break;
        cout << "[Error] Invalid phone number! Only can use digit and must at '-' . Try again.\n";
    }

    while (true) {
        cout << "Enter Email Address (must end with @gmail.com): ";
        cin >> newCustomer.emailCustomer;
        if (isValidEmail(newCustomer.emailCustomer)) break;
        cout << "[Error] Invalid email! Must end with '@gmail.com'. Try again.\n";
    }

    while (true) {
        cout << "Enter Password (min 8 chars, must contain letters & digits): ";
        cin >> newCustomer.passwordCustomer;
        if (isValidPassword(newCustomer.passwordCustomer)) break;
        cout << "[Error] Password must be at least 8 characters long and contain both letters and digits. Try again.\n";
    }
    newCustomer.idCustomer = customerGeneratedID;
    customerDB[customerCount++] = newCustomer;

    cout << "\n[Success] Customer registration completed!\n";
    cout << "============================================\n";
    cout << " Assigned Customer ID : " << customerGeneratedID << "\n";
    cout << " Name                 : " << newCustomer.nameCustomer << "\n";
    cout << " Phone                : " << newCustomer.phoneCustomer << "\n";
    cout << " Email                : " << newCustomer.emailCustomer << "\n";
    cout << "============================================\n";
    cout << "Please keep your Customer ID to log in.\n";
}

void registerMember() {
    if (memberCount >= MAX_MEMBERS) {
        cout << "[Error] Member database capacity reached!\n";
        return;
    }
    char response;
    Member newMember;
    cout << "\n--- NEW MEMBER REGISTRATION ---\n";

    cout << "Do you already pay the Member Fee ? (Y=yes,N=no): ";
    cin >> response;
    response = toupper(response);

    if (response == 'Y') {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (true) {
            cout << "Enter Full Name: ";
            getline(cin, newMember.nameMember);
            if (isValidName(newMember.nameMember)) break;
            cout << "[Error] Invalid name! Only can use alphabet. Try again.\n";
        }

        string genderInput;
        while (true) {
            cout << "Enter Gender (m/f): ";
            cin >> genderInput;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (genderInput == "m" || genderInput == "M") {
                newMember.genderMember = "Male";
                break;
            }
            else if (genderInput == "f" || genderInput == "F") {
                newMember.genderMember = "Female";
                break;
            }
            else {
                cout << "[Error] Invalid gender! Please enter 'm' for Male or 'f' for Female.\n";
            }
        }

        while (true) {
            cout << "Enter Phone Number (e.g.: xxx-xxxxxxxx): ";
            cin >> newMember.phoneMember;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (isValidPhoneNumber(newMember.phoneMember)) break;
            cout << "[Error] Invalid phone number! Only can use digit and must at '-' . Try again.\n";
        }

        while (true) {
            cout << "Enter Email Address (must end with @gmail.com): ";
            cin >> newMember.emailMember;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (isValidEmail(newMember.emailMember)) break;
            cout << "[Error] Invalid email! Must end with '@gmail.com'. Try again.\n";
        }

        while (true) {
            cout << "Enter Password (min 8 chars, must contain letters & digits): ";
            cin >> newMember.passwordMember;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (isValidPassword(newMember.passwordMember)) break;
            cout << "[Error] Password must be at least 8 characters long and contain both letters and digits. Try again.\n";
        }

        string memberGeneratedID = "M" + to_string(memberCounter++);
        newMember.idMember = memberGeneratedID;
        memberDB[memberCount++] = newMember;

        cout << "\n[Success] Member registration completed!\n";
        cout << "================================================\n";
        cout << " Assigned Member ID : " << memberGeneratedID << "\n";
        cout << " Name               : " << newMember.nameMember << "\n";
        cout << " Phone              : " << newMember.phoneMember << "\n";
        cout << " Email              : " << newMember.emailMember << "\n";
        cout << "=================================================\n";
        cout << "Please keep your Member ID to log in.\n";
    }
    else {
        cout << "Please pay Member Fee first at the counter." << endl;
    }
}

void customerMemberLogin() {
    string idCustomerMember, passCustomerMember;
    cout << "\n--- CUSTOMER / MEMBER LOGIN ---\n";
    cout << "Customer ID / Member ID: ";
    cin >> idCustomerMember;
    cout << "Password: ";
    cin >> passCustomerMember;

    int memIdx = findMemberIndex(idCustomerMember);
    if (memIdx != -1 && memberDB[memIdx].passwordMember == passCustomerMember) {
        cout << "\nMember login successful!\n";
        showCustomerMemberUI(idCustomerMember, "Member");
        return;
    }

    int custIdx = findCustomerIndex(idCustomerMember);
    if (custIdx != -1 && customerDB[custIdx].passwordCustomer == passCustomerMember) {
        cout << "\nCustomer login successful!\n";
        showCustomerMemberUI(idCustomerMember, "Customer");
        return;
    }

    cout << "\n[Error] Invalid Customer/Member ID or Password.\n";
}

void showCustomerMemberUI(const string& userId, const string& accountType) {
    int choice = 0;
    string name;
    if (accountType == "Member") {
        int idx = findMemberIndex(userId);
        name = memberDB[idx].nameMember;
    }
    else {
        int idx = findCustomerIndex(userId);
        name = customerDB[idx].nameCustomer;
    }
    while (true) {
        cout << "\n************************************************\n";
        cout << "           CUSTOMER/MEMBER DASHBOARD           \n";
        cout << " Welcome: " << name << " (" << accountType << " - " << userId << ")\n";
        cout << "**************************************************\n";
        cout << "[ 1 ] Your Profile\n";
        cout << "[ 2 ] Service\n";
        cout << "[ 3 ] Appointment\n";
        cout << "[ 4 ] Billing\n";
        cout << "[ 5 ] Logout\n";
        cout << "Select action: ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input.\n";
            continue;
        }
        if (choice == 5) {
            cout << "Logging out of Customer Dashboard...\n";
            break;
        }
        switch (choice) {
        case 1:
            memberCustomerProfile(userId, accountType);
            break;
        case 2:
            memberBookingMenu(userId);
            break;
        case 3:
            cout << "\n-> [Customer UI] Appointment module selected.\n";
            break;
        case 4:
            cout << "\n-> [Customer UI] Billing module selected.\n";
            break;
        default:
            cout << "Invalid selection.\n";
        }
    }
}

void memberCustomerProfile(const string& userId, const string& accountType) {
    int choice = 0;
    while (true) {
        cout << "============ MEMBER/CUSTOMER PROFILE ============\n";
        cout << "[ 1 ] View your profile\n";
        cout << "[ 2 ] Edit Profile\n";
        cout << "[ 3 ] Exit (Return to Main Menu)\n";
        cout << "Select option (1-3): ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
        case 1:
            viewProfile(userId, accountType);
            break;
        case 2:
            editProfileCMUI(userId, accountType);
            break;
        case 3:
            cout << "Returning to Main Menu...\n";
            return;
        default:
            cout << "Invalid option. Try again.\n";
        }
    }
}

void viewProfile(const string& userId, const string& accountType) {
    cout << "\n========================================\n";
    cout << "           YOUR PROFILE INFO            \n";
    cout << "========================================\n";
    if (accountType == "Member") {
        int idx = findMemberIndex(userId);
        cout << " ID           : " << userId << "\n";
        cout << " Account Type : " << accountType << "\n";
        cout << " Name         : " << memberDB[idx].nameMember << "\n";
        cout << " Gender       : " << memberDB[idx].genderMember << "\n";
        cout << " Phone        : " << memberDB[idx].phoneMember << "\n";
        cout << " Email        : " << memberDB[idx].emailMember << "\n";
    }
    else {
        int idx = findCustomerIndex(userId);
        cout << " ID           : " << userId << "\n";
        cout << " Account Type : " << accountType << "\n";
        cout << " Name         : " << customerDB[idx].nameCustomer << "\n";
        cout << " Gender       : " << customerDB[idx].genderCustomer << "\n";
        cout << " Phone        : " << customerDB[idx].phoneCustomer << "\n";
        cout << " Email        : " << customerDB[idx].emailCustomer << "\n";
    }
    cout << "========================================\n";
}

void editProfileCMUI(const string& userId, const string& accountType) {
    int updateChoice = 0;
    while (true) {
        cout << "\n--- SELECT FIELD TO EDIT OR CHANGE ---\n";
        cout << "1. Email Address\n";
        cout << "2. Phone Number\n";
        cout << "3. Password\n";
        cout << "4. Cancel & Return\n";
        cout << "Select option (1-4): ";

        if (!(cin >> updateChoice)) {
            clearInput();
            cout << "[Error] Invalid selection. Try again.\n";
            continue;
        }

        if (updateChoice == 4) {
            break;
        }

        switch (updateChoice) {
        case 1: {
            string newEmail;
            while (true) {
                cout << "Enter new Email Address (must end with @gmail.com): ";
                cin >> newEmail;
                if (isValidEmail(newEmail)) break;
                cout << "[Error] Invalid email! Must end with '@gmail.com'. Try again.\n";
            }
            if (accountType == "Member") memberDB[findMemberIndex(userId)].emailMember = newEmail;
            else customerDB[findCustomerIndex(userId)].emailCustomer = newEmail;

            cout << "\n[Success] Email updated successfully!\n";
            break;
        }
        case 2: {
            string newPhone;
            cout << "Enter new Phone Number: ";
            cin >> newPhone;
            if (accountType == "Member") memberDB[findMemberIndex(userId)].phoneMember = newPhone;
            else customerDB[findCustomerIndex(userId)].phoneCustomer = newPhone;

            cout << "\n[Success] Phone number updated successfully!\n";
            break;
        }
        case 3: {
            string newPass;
            while (true) {
                cout << "Enter new Password (min 8 chars, letter & digit): ";
                cin >> newPass;
                if (isValidPassword(newPass)) break;
                cout << "[Error] Password must be at least 8 characters long and contain both letters and digits. Try again.\n";
            }
            if (accountType == "Member") memberDB[findMemberIndex(userId)].passwordMember = newPass;
            else customerDB[findCustomerIndex(userId)].passwordCustomer = newPass;

            cout << "\n[Success] Password updated successfully!\n";
            break;
        }
        default:
            cout << "\n[Error] Invalid option selected. Try again.\n";
        }
    }
}

void staffPortal() {
    int choice = 0;
    while (true) {
        cout << "============ STAFF PORTAL ============\n";
        cout << "[ 1 ] Staff Registration\n";
        cout << "[ 2 ] Staff Login\n";
        cout << "[ 3 ] Exit (Return to Main Menu)\n";
        cout << "Select option (1-3): ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
        case 1:
            registerStaff();
            break;
        case 2:
            staffLogin();
            break;
        case 3:
            cout << "Returning to Main Menu...\n";
            return;
        default:
            cout << "Invalid option. Try again.\n";
        }
    }
}

void registerStaff() {
    if (staffCount >= MAX_STAFF) {
        cout << "[Error] Staff database capacity reached!\n";
        return;
    }

    Staff newStaff;
    cout << "\n--- NEW HAIR SALON STAFF REGISTRATION ---\n";
    string generatedID = "STF" + to_string(staffCounter++);

    clearInput();

    while (true) {
        cout << "Enter Full Name: ";
        getline(cin, newStaff.nameStaff);
        if (isValidName(newStaff.nameStaff)) break;
        cout << "[Error] Invalid name! Alphabet only. Try again.\n";
    }

    string genderInput;
    while (true) {
        cout << "Enter Gender (m/f): ";
        cin >> genderInput;
        clearInput();

        if (genderInput == "m" || genderInput == "M") {
            newStaff.genderStaff = "Male";
            break;
        }
        else if (genderInput == "f" || genderInput == "F") {
            newStaff.genderStaff = "Female";
            break;
        }
        else {
            cout << "[Error] Invalid gender! Enter 'm' or 'f'.\n";
        }
    }

    while (true) {
        cout << "Enter Phone Number (e.g.: xxx-xxxxxxxx): ";
        cin >> newStaff.phoneStaff;
        clearInput();
        if (isValidPhoneNumber(newStaff.phoneStaff)) break;
        cout << "[Error] Invalid phone number format.\n";
    }

    while (true) {
        cout << "Enter Email Address (must end with @gmail.com): ";
        cin >> newStaff.emailStaff;
        clearInput();
        if (isValidEmail(newStaff.emailStaff)) break;
        cout << "[Error] Invalid email address.\n";
    }

    while (true) {
        cout << "Enter Password (Minimun 8 chars, must contain letters & digits): ";
        cin >> newStaff.passwordStaff;
        clearInput();
        if (isValidPassword(newStaff.passwordStaff)) break;
        cout << "[Error] Password must be at least 8 characters long and contain both letters and digits. Try again.\n";
    }

    int posChoice = 0;
    while (true) {
        cout << "\nWhat position do you want to hire for?\n";
        cout << "[ 1 ] Hair Stylist\n[ 2 ] Skincare Specialist\n[ 3 ] Hair Color Stylist\n[ 4 ] Nail Technician\n[ 5 ] Receptionist\n";
        cout << "Select position (1-5): ";

        if (cin >> posChoice && posChoice >= 1 && posChoice <= 5) {
            clearInput();
            switch (posChoice) {
            case 1: newStaff.positionStaff = "Hair Stylist"; break;
            case 2: newStaff.positionStaff = "Skincare Specialist"; break;
            case 3: newStaff.positionStaff = "Hair Color Stylist"; break;
            case 4: newStaff.positionStaff = "Nail Technician"; break;
            case 5: newStaff.positionStaff = "Receptionist"; break;
            }
            break;
        }
        else {
            clearInput();
            cout << "[Error] Invalid position selection. Please enter a number between 1 and 5.\n";
        }
    }
    newStaff.idStaff = generatedID;
    staffDB[staffCount++] = newStaff;

    cout << "\n[Success] Staff registration completed!\n";
    cout << "========================================\n";
    cout << " Assigned Staff ID : " << generatedID << "\n";
    cout << " Name              : " << newStaff.nameStaff << "\n";
    cout << " Position          : " << newStaff.positionStaff << "\n";
    cout << " Phone             : " << newStaff.phoneStaff << "\n";
    cout << " Email             : " << newStaff.emailStaff << "\n";
    cout << "========================================\n";
    cout << "Please keep your Staff ID to log in.\n\n";
}

void staffLogin() {
    string idStaff, passStaff;
    cout << "\n--- STAFF LOGIN ---\n";

    cout << "Staff ID: ";
    cin >> idStaff;

    cout << "Password: ";
    cin >> passStaff;
    clearInput();

    int idx = findStaffIndex(idStaff);
    if (idx != -1 && staffDB[idx].passwordStaff == passStaff) {
        cout << "\nStaff authentication successful!\n";
        cout << "Welcome, " << staffDB[idx].nameStaff << " (" << staffDB[idx].positionStaff << ")!\n";
        showStaffUI(idStaff);
    }
    else {
        cout << "\n[Error] Invalid Staff credentials.\n";
    }
} // FIXED: Removed extra trailing closing brace here

void showStaffUI(const string& username) {
    int choice = 0;
    int idx = findStaffIndex(username);
    while (true) {
        cout << "\n************************************************************\n";
        cout << "                STAFF CONTROL PANEL           \n";
        cout << " Staff ID: " << username << " | " << staffDB[idx].nameStaff
            << " (" << staffDB[idx].positionStaff << ")\n";
        cout << "\n************************************************************\n";
        cout << "[ 1 ] Customer/Member Info Management\n";
        cout << "[ 2 ] Staff Info Management\n";
        cout << "[ 3 ] Service management\n";
        cout << "[ 4 ] Appointment Management\n";
        cout << "[ 5 ] View History\n";
        cout << "[ 6 ] Reporting\n";
        cout << "[ 7 ] Logout\n";
        cout << "Select admin task: ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input.\n";
            continue;
        }

        if (choice == 7) {
            cout << "Logging out of Staff Control Panel...\n";
            break;
        }
        switch (choice) {
        case 1: {
            string confirmID;
            cout << "============= STAFF VERIFICATION REQUIRED =============\n";
            cout << "Enter Staff ID to access Member Management: ";
            cin >> confirmID;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            int confirmIdx = findStaffIndex(confirmID);
            if (confirmIdx != -1 && confirmID == username) {
                cout << "\n[Access Granted] Verified identity: " << staffDB[confirmIdx].nameStaff << "\n";
                memberManagement();
            }
            else {
                cout << "\n[Access Denied] Invalid or mismatched Staff ID!\n";
            }
            break;
        }
        case 2: {
            string confirmID;
            cout << "============= STAFF VERIFICATION REQUIRED =============\n";
            cout << "Enter Staff ID to access Staff Management: ";
            cin >> confirmID;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            int confirmIdx = findStaffIndex(confirmID);
            if (confirmIdx != -1 && confirmID == username) {
                cout << "\n[Access Granted] Verified identity: " << staffDB[confirmIdx].nameStaff << "\n";
                staffManagement();
            }
            else {
                cout << "\n[Access Denied] Invalid or mismatched Staff ID!\n";
            }
            break;
        }
        case 3:
            staffBookingMenu();
            break;
        case 4:
            cout << "\n[System] Appointment management module selected.\n";
            AppointmentManagement();
            break;
        case 5:
            cout << "\n[System] View history module selected.\n";
            break;
        case 6:
            cout << "\n[System] Reporting module selected.\n";
            break;
        default:
            cout << "Invalid selection.\n";
        }
    }
}

void showStaffList() {
    cout << right << setw(70) << "< TABLE STAFF >" << endl;
    string border = "+----------+------------------------+----------+----------------+----------------------------+----------------------+----------------------+";

    cout << "\n" << border << "\n";
    cout << "| " << left << setw(9) << "Staff ID"
        << "| " << setw(22) << "Name"
        << " | " << setw(8) << "Gender"
        << " | " << setw(14) << "Phone number"
        << " | " << setw(26) << "Email"
        << " | " << setw(20) << "Password"
        << " | " << setw(20) << "Position" << " |\n";

    cout << border << "\n";

    for (int i = 0; i < staffCount; ++i) {
        cout << "| " << left << setw(9) << staffDB[i].idStaff
            << "| " << setw(22) << staffDB[i].nameStaff
            << " | " << setw(8) << staffDB[i].genderStaff
            << " | " << setw(14) << staffDB[i].phoneStaff
            << " | " << setw(26) << staffDB[i].emailStaff
            << " | " << setw(20) << staffDB[i].passwordStaff
            << " | " << setw(20) << staffDB[i].positionStaff << " |\n";
        cout << border << "\n";
    }
}

void staffManagement() {
    int choice = 0;
    while (true) {
        cout << "========== STAFF MANAGEMENT MENU ==========\n";
        cout << "[ 1 ] View Staff Table\n";
        cout << "[ 2 ] Search Staff\n";
        cout << "[ 3 ] Delete Staff\n";
        cout << "[ 4 ] Update Staff Information\n";
        cout << "[ 5 ] Return to Staff Control Panel\n";
        cout << "Select option (1-5): ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        if (choice == 5) {
            cout << "Returning to Staff Control Panel...\n";
            break;
        }

        string idStaff;
        switch (choice) {
        case 1: {
            showStaffList();
            break;
        }
        case 2: {
            cout << "\nEnter Staff ID to search: ";
            cin >> idStaff;

            int idx = findStaffIndex(idStaff);
            if (idx != -1) {
                cout << "\n[Found] ID: " << staffDB[idx].idStaff
                    << " | Name: " << staffDB[idx].nameStaff
                    << " | Gender: " << staffDB[idx].genderStaff
                    << " | Phone: " << staffDB[idx].phoneStaff
                    << " | Email: " << staffDB[idx].emailStaff
                    << " | Position: " << staffDB[idx].positionStaff << "\n";
            }
            else {
                cout << "\n[Error] Staff ID '" << idStaff << "' not found.\n";
            }
            break;
        }
        case 3: {
            cout << "\nEnter Staff ID to delete: ";
            cin >> idStaff;

            int idx = findStaffIndex(idStaff);
            if (idx != -1) {
                for (int i = idx; i < staffCount - 1; ++i) {
                    staffDB[i] = staffDB[i + 1];
                }
                staffCount--;
                cout << "\n[Success] Staff '" << idStaff << "' deleted successfully.\n";
            }
            else {
                cout << "\n[Error] Staff ID '" << idStaff << "' not found. Delete canceled.\n";
            }
            break;
        }
        case 4: {
            cout << "\nEnter Staff ID to update: ";
            cin >> idStaff;

            int idx = findStaffIndex(idStaff);
            if (idx == -1) {
                cout << "\n[Error] Staff ID '" << idStaff << "' not found. Update canceled.\n";
                break;
            }

            cout << "\n========== SELECT FIELD TO UPDATE ==========\n";
            cout << "[ 1 ] Email Address\n";
            cout << "[ 2 ] Phone Number\n";
            cout << "[ 3 ] Password\n";
            cout << "[ 4 ] Position\n";
            cout << "Select option (1-4): ";

            int updateChoice = 0;
            if (!(cin >> updateChoice)) {
                clearInput();
                cout << "[Error] Invalid selection. Update canceled.\n";
                break;
            }

            switch (updateChoice) {
            case 1: {
                string newEmail;
                while (true) {
                    cout << "Enter new Email Address (must end with @gmail.com): ";
                    cin >> newEmail;
                    if (isValidEmail(newEmail)) break;
                    cout << "[Error] Invalid email! Must end with '@gmail.com'. Try again.\n";
                }
                staffDB[idx].emailStaff = newEmail;
                cout << "\n[Success] Email updated successfully for Staff ID '" << idStaff << "'!\n";
                break;
            }
            case 2: {
                string newPhone;
                cout << "Enter new Phone Number: ";
                cin >> newPhone;
                staffDB[idx].phoneStaff = newPhone;
                cout << "\n[Success] Phone number updated successfully for Staff ID '" << idStaff << "'!\n";
                break;
            }
            case 3: {
                string newPass;
                while (true) {
                    cout << "Enter new Password (min 8 chars, letter & digit): ";
                    cin >> newPass;
                    if (isValidPassword(newPass)) break;
                    cout << "[Error] Password must be at least 8 characters long and contain both letters and digits. Try again.\n";
                }
                staffDB[idx].passwordStaff = newPass;
                cout << "\n[Success] Password updated successfully for Staff ID '" << idStaff << "'!\n";
                break;
            }
            case 4: {
                string newPos;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter new Hair Salon Position: ";
                getline(cin, newPos);
                staffDB[idx].positionStaff = newPos;
                cout << "\n[Success] Position updated successfully for Staff ID '" << idStaff << "'!\n";
                break;
            }
            default:
                cout << "\n[Error] Invalid option selected. Update canceled.\n";
            }
            break;
        }
        default:
            cout << "Invalid option. Please enter 1 to 5.\n";
        }
    }
}

void showMemberCustomerList() {
    cout << right << setw(75) << "< TABLE MEMBER & CUSTOMER >" << endl;

    string border = "+----------+------------------------+----------+----------------+----------------------------+----------------------+";

    cout << "\n" << border << "\n";
    cout << "| " << left << setw(8) << "ID"
        << " | " << setw(22) << "Name"
        << " | " << setw(8) << "Gender"
        << " | " << setw(14) << "Phone number"
        << " | " << setw(26) << "Email"
        << " | " << setw(20) << "Password" << " |\n";

    cout << border << "\n";

    for (int i = 0; i < memberCount; ++i) {
        cout << "| " << left << setw(8) << memberDB[i].idMember
            << " | " << setw(22) << memberDB[i].nameMember
            << " | " << setw(8) << memberDB[i].genderMember
            << " | " << setw(14) << memberDB[i].phoneMember
            << " | " << setw(26) << memberDB[i].emailMember
            << " | " << setw(20) << memberDB[i].passwordMember << " |\n";
        cout << border << "\n";
    }

    for (int i = 0; i < customerCount; ++i) {
        cout << "| " << left << setw(8) << customerDB[i].idCustomer
            << " | " << setw(22) << customerDB[i].nameCustomer
            << " | " << setw(8) << customerDB[i].genderCustomer
            << " | " << setw(14) << customerDB[i].phoneCustomer
            << " | " << setw(26) << customerDB[i].emailCustomer
            << " | " << setw(20) << customerDB[i].passwordCustomer << " |\n";
        cout << border << "\n";
    }
}

void memberManagement() {
    int choice = 0;
    while (true) {
        cout << "========== CUSTOMER/MEMBER MANAGEMENT MENU ==========\n";
        cout << "[ 1 ] View Customer/Member Table\n";
        cout << "[ 2 ] Search Customer/Member\n";
        cout << "[ 3 ] Delete Customer/Member\n";
        cout << "[ 4 ] Update Customer/Member Information\n";
        cout << "[ 5 ] Return to Staff Control Panel\n";
        cout << "Select option (1-5): ";

        if (!(cin >> choice)) {
            clearInput();
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        if (choice == 5) {
            cout << "Returning to Staff Control Panel...\n";
            break;
        }

        string id;
        switch (choice) {
        case 1: {
            showMemberCustomerList();
            break;
        }
        case 2: {
            cout << "\nEnter Customer/Member ID to search: ";
            cin >> id;

            int memIdx = findMemberIndex(id);
            if (memIdx != -1) {
                cout << "\n[Found] ID: " << memberDB[memIdx].idMember
                    << " | Type: Member | Name: " << memberDB[memIdx].nameMember
                    << " | Phone: " << memberDB[memIdx].phoneMember
                    << " | Email: " << memberDB[memIdx].emailMember << "\n";
            }
            else {
                int custIdx = findCustomerIndex(id);
                if (custIdx != -1) {
                    cout << "\n[Found] ID: " << customerDB[custIdx].idCustomer
                        << " | Type: Standard Customer | Name: " << customerDB[custIdx].nameCustomer
                        << " | Phone: " << customerDB[custIdx].phoneCustomer
                        << " | Email: " << customerDB[custIdx].emailCustomer << "\n";
                }
                else {
                    cout << "\n[Error] Member/Customer ID '" << id << "' not found.\n";
                }
            }
            break;
        }
        case 3: {
            cout << "\nEnter Customer/Member ID to delete: ";
            cin >> id;

            int memIdx = findMemberIndex(id);
            if (memIdx != -1) {
                for (int i = memIdx; i < memberCount - 1; ++i) {
                    memberDB[i] = memberDB[i + 1];
                }
                memberCount--;
                cout << "\n[Success] Member '" << id << "' deleted successfully.\n";
            }
            else {
                int custIdx = findCustomerIndex(id);
                if (custIdx != -1) {
                    for (int i = custIdx; i < customerCount - 1; ++i) {
                        customerDB[i] = customerDB[i + 1];
                    }
                    customerCount--;
                    cout << "\n[Success] Customer '" << id << "' deleted successfully.\n";
                }
                else {
                    cout << "\n[Error] ID '" << id << "' not found. Delete canceled.\n";
                }
            }
            break;
        }
        case 4: {
            cout << "\nEnter Customer/Member ID to update: ";
            cin >> id;

            int memIdx = findMemberIndex(id);
            int custIdx = findCustomerIndex(id);

            if (memIdx == -1 && custIdx == -1) {
                cout << "\n[Error] ID '" << id << "' not found. Update canceled.\n";
                break;
            }

            cout << "\n========== SELECT FIELD TO UPDATE ==========\n";
            cout << "[ 1 ] Email Address\n";
            cout << "[ 2 ] Phone Number\n";
            cout << "[ 3 ] Cancel & Return\n";
            cout << "Select option (1-3): ";

            int updateChoice = 0;
            if (!(cin >> updateChoice)) {
                clearInput();
                cout << "[Error] Invalid selection. Update canceled.\n";
                break;
            }
            if (updateChoice == 3) {
                break;
            }

            switch (updateChoice) {
            case 1: {
                string newEmail;
                while (true) {
                    cout << "Enter new Email Address (must end with @gmail.com): ";
                    cin >> newEmail;
                    if (isValidEmail(newEmail)) break;
                    cout << "[Error] Invalid email! Must end with '@gmail.com'. Try again.\n";
                }
                if (memIdx != -1) memberDB[memIdx].emailMember = newEmail;
                else customerDB[custIdx].emailCustomer = newEmail;
                cout << "\n[Success] Email updated successfully for ID '" << id << "'!\n";
                break;
            }
            case 2: {
                string newPhone;
                cout << "Enter new Phone Number (e.g.: xxx-xxxxxxxx): ";
                cin >> newPhone;
                if (memIdx != -1) memberDB[memIdx].phoneMember = newPhone;
                else customerDB[custIdx].phoneCustomer = newPhone;
                cout << "\n[Success] Phone number updated successfully for ID '" << id << "'!\n";
                break;
            }

            default:
                cout << "\n[Error] Invalid option selected. Update canceled.\n";
            }
            break;
        }
        default:
            cout << "Invalid option. Please enter 1 to 5.\n";
        }
    }
}

void AppointmentManagement() {
    int option = 0;
    // FIXED: Removed initMonthlySchedule() from here to keep existing bookings intact
    do {
        cout << "\nWelcome to the Appointment Scheduler!\n" << endl;
        cout << "Please select an option from the menu below:" << endl;
        cout << "1. View All Appointment" << endl;
        cout << "2. Create a New Appointment" << endl;
        cout << "3. Cancel Appointment" << endl;
        cout << "4. Reschedule Appointment" << endl;
        cout << "5. View Staff Schedule" << endl;
        cout << "6. Appointment Marking" << endl;
        cout << "7. Exit\n" << endl;

        cout << "Select option: ";
        cin >> option;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number from 1 to 7." << endl;
            cout << "\nPress Enter to return to the menu...";
            cin.get();
            continue;
        }

        switch (option) {
        case 1: {
            int day;
            cout << "Enter day (1 to 31): ";
            cin >> day;
            if (cin.fail() || day < 1 || day > 31) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid day! Please enter a day from 1 to 31." << endl;
                break;
            }

            int dayIndex = day - 1;
            cout << "You selected: View All Appointment for Day " << day << endl;
            ViewAllAppointment(schedule[dayIndex], TOTAL_SLOTS);
            break;
        }
        case 2: {
            cout << "You selected: Create a New Appointment" << endl;
            CreateAppointmentStaff();
            break;
        }
        case 3:
            cout << "You selected: Cancel Appointment" << endl;
            break;
        case 4:
            cout << "You selected: Reschedule Appointment" << endl;
            break;
        case 5:
            cout << "You selected: View Staff Schedule" << endl;
            break;
        case 6:
            cout << "You selected: Appointment Marking" << endl;
            break;
        case 7:
            cout << "Returning to Staff Menu..." << endl;
            return;
        default:
            cout << "Invalid option. Please select a valid option from the menu." << endl;
            break;
        }

        if (option != 7) {
            cout << "\nPress Enter to return to the menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

    } while (option != 7);
}

void ViewAllAppointment(const Timeslot schedule[], int size, string filterStaffID) {
    int w_id = string("ID").length();
    int w_time = string("Time Slot").length();
    int w_status = string("Status").length();
    int w_staffID = string("Staff ID").length();
    int w_staffName = string("Staff Name").length();
    int w_custID = string("Customer ID").length();
    int w_custName = string("Customer Name").length();
    int w_service = string("Service").length();

    for (int i = 0; i < size; i++) {
        if (!filterStaffID.empty() && schedule[i].staffID != filterStaffID && schedule[i].isBooked) {
            continue;
        }

        string statusStr = schedule[i].isBooked ? schedule[i].status : "Available";
        string staffIDStr = schedule[i].isBooked ? schedule[i].staffID : "-";
        string staffNameStr = schedule[i].isBooked ? schedule[i].staffName : "-";
        string custIDStr = schedule[i].isBooked ? schedule[i].customerID : "-";
        string custNameStr = schedule[i].isBooked ? schedule[i].customerName : "-";
        string serviceStr = (schedule[i].isBooked && !schedule[i].service.empty()) ? schedule[i].service : "-";

        w_id = max(w_id, (int)to_string(schedule[i].id).length());
        w_time = max(w_time, (int)schedule[i].time.length());
        w_status = max(w_status, (int)statusStr.length());
        w_staffID = max(w_staffID, (int)staffIDStr.length());
        w_staffName = max(w_staffName, (int)staffNameStr.length());
        w_custID = max(w_custID, (int)custIDStr.length());
        w_custName = max(w_custName, (int)custNameStr.length());
        w_service = max(w_service, (int)serviceStr.length());
    }

    string separator
        = "+" + string(w_id + 2, '-')
        + "+" + string(w_time + 2, '-')
        + "+" + string(w_status + 2, '-')
        + "+" + string(w_staffID + 2, '-')
        + "+" + string(w_staffName + 2, '-')
        + "+" + string(w_custID + 2, '-')
        + "+" + string(w_custName + 2, '-')
        + "+" + string(w_service + 2, '-') + "+";

    cout << separator << endl;
    cout << "| " << left << setw(w_id) << "ID" << " "
        << "| " << setw(w_time) << "Time Slot" << " "
        << "| " << setw(w_status) << "Status" << " "
        << "| " << setw(w_staffID) << "Staff ID" << " "
        << "| " << setw(w_staffName) << "Staff Name" << " "
        << "| " << setw(w_custID) << "Customer ID" << " "
        << "| " << setw(w_custName) << "Customer Name" << " "
        << "| " << setw(w_service) << "Service" << " |\n";

    cout << separator << endl;

    for (int i = 0; i < size; i++) {
        if (!filterStaffID.empty() && schedule[i].staffID != filterStaffID && schedule[i].isBooked) {
            continue;
        }

        string statusAppointment = schedule[i].isBooked ? schedule[i].status : "Available";
        string statuscolor = schedule[i].isBooked ? RED : GREEN;
        string staffID = schedule[i].isBooked ? schedule[i].staffID : "-";
        string staffname = schedule[i].isBooked ? schedule[i].staffName : "-";
        string customerID = schedule[i].isBooked ? schedule[i].customerID : "-";
        string customerName = schedule[i].isBooked ? schedule[i].customerName : "-";
        string service = (schedule[i].isBooked && !schedule[i].service.empty()) ? schedule[i].service : "-";

        cout << "| " << left << setw(w_id) << schedule[i].id << " "
            << "| " << setw(w_time) << schedule[i].time << " "
            << "| " << statuscolor << setw(w_status) << statusAppointment << RESET << " "
            << "| " << setw(w_staffID) << staffID << " "
            << "| " << setw(w_staffName) << staffname << " "
            << "| " << setw(w_custID) << customerID << " "
            << "| " << setw(w_custName) << customerName << " "
            << "| " << setw(w_service) << service << " "
            << "|" << endl;
    }
    cout << separator << endl;
}

void initMonthlySchedule() {
    for (int day = 0; day < DAYS_IN_MONTH; day++) {
        for (int slot = 0; slot < TOTAL_SLOTS; slot++) {
            schedule[day][slot] = defaultDaySlots[slot];
        }
    }
}

void getCurrentSystemTime(int& year, int& month, int& day, int& hour) {
    time_t now = time(0);
    tm ltm;
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&ltm, &now);
#else
    localtime_r(&now, &ltm);
#endif

    year = 1900 + ltm.tm_year;
    month = 1 + ltm.tm_mon;
    day = ltm.tm_mday;
    hour = ltm.tm_hour;
}

void CreateAppointmentStaff() {
    string customerID;
    string customerName;

    cout << "Enter the customer ID: ";
    cin >> customerID;

    int memIdx = findMemberIndex(customerID);
    if (memIdx != -1) {
        customerName = memberDB[memIdx].nameMember;
    }
    else {
        int custIdx = findCustomerIndex(customerID);
        if (custIdx != -1) {
            customerName = customerDB[custIdx].nameCustomer;
        }
    }

    if (customerName.empty()) {
        cout << RED << "\n[Error] ID '" << customerID << "' not found in Customer or Member database!" << RESET << endl;
        return;
    }
    else {
        cout << GREEN << "[Found] Name: " << customerName << RESET << endl;
    }

    int curYear, curMonth, curDay, curHour;
    getCurrentSystemTime(curYear, curMonth, curDay, curHour);
    cout << "Today is: " << curYear << "-" << curMonth << "-" << curDay << endl;

    int dayOption;
    cout << "Enter Day of the Month (1 - 31): ";
    cin >> dayOption;

    if (cin.fail() || dayOption < 1 || dayOption > 31) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "\n[Error] Invalid day input!" << RESET << endl;
        return;
    }

    if (dayOption < curDay) {
        cout << RED << "\n[Error] Cannot book appointments for past dates!" << RESET << endl;
        return;
    }

    int dayIndex = dayOption - 1;
    ViewAllAppointment(schedule[dayIndex], TOTAL_SLOTS);

    int Appointment_time;
    cout << "Which timeslot do you prefer? ";
    cin >> Appointment_time;

    if (cin.fail() || Appointment_time < 1 || Appointment_time > TOTAL_SLOTS) {
        cin.clear();
        cout << RED << "\n[Error] Invalid timeslot ID! Please choose between 1 and " << TOTAL_SLOTS << "." << RESET << endl;
        return;
    }

    int slotIndex = Appointment_time - 1;
    int slotStartHours[] = { 9, 11, 13, 15, 17, 19, 21 };

    if (dayOption == curDay && slotStartHours[slotIndex] <= curHour) {
        cout << RED << "\n[Error] This time slot has already passed for today!" << RESET << endl;
        return;
    }

    if (schedule[dayIndex][slotIndex].isBooked) {
        cout << RED << "\n[Sorry] Timeslot is already booked!" << RESET << endl;
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;

    for (int i = 0; i < staffCount; i++) {
        cout << (i + 1) << ". " << staffDB[i].nameStaff
            << " (" << staffDB[i].idStaff << " - " << staffDB[i].positionStaff << ")\n";
    }

    cout << "\nSelect a Staff you preferred: ";
    int staffoption;
    cin >> staffoption;

    if (cin.fail() || staffoption < 1 || staffoption > staffCount) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "\n[Error] Invalid input!" << RESET << endl;
        return;
    }

    int Appointmentoption;
    cout << "\nEnter a Service:\n";
    cout << "1. Wedding Event\n";
    cout << "2. Hair dressing with make up\n";
    cout << "Select service: ";
    cin >> Appointmentoption;

    switch (Appointmentoption) {
    case 1:
        schedule[dayIndex][slotIndex].service = "Wedding Event";
        break;
    case 2:
        schedule[dayIndex][slotIndex].service = "Hair dressing with make up";
        break;
    default:
        // FIXED: Added return to avoid booking slot with an invalid service
        cout << RED << "[Error] Invalid service option. Booking canceled." << RESET << endl;
        return;
    }

    int selectedIndex = staffoption - 1;
    schedule[dayIndex][slotIndex].staffID = staffDB[selectedIndex].idStaff;
    schedule[dayIndex][slotIndex].staffName = staffDB[selectedIndex].nameStaff;
    schedule[dayIndex][slotIndex].customerID = customerID;
    schedule[dayIndex][slotIndex].customerName = customerName;
    schedule[dayIndex][slotIndex].status = "Booked";
    schedule[dayIndex][slotIndex].isBooked = true;

    cout << GREEN << "\n[Success] Appointment successfully created for Timeslot " << schedule[dayIndex][slotIndex].time << "!" << RESET << endl;
}

// --- Member booking ---
void memberBookingMenu(const string& customerID) {
    int choice = 0;
    while (true) {
        cout << "\n----------------------------------------\n";
        cout << "          MEMBER BOOKING SYSTEM \n";
        cout << "----------------------------------------\n";
        cout << "1. View Services\n";
        cout << "2. Search Booking\n";
        cout << "3. Add Single Booking\n";
        cout << "4. Add Multiple Bookings\n";
        cout << "5. Edit Booking\n";
        cout << "6. Cancel Booking\n";
        cout << "7. View My Bookings\n";
        cout << "8. Generate Confirmation Slip\n";
        cout << "9. Exit\n";
        cout << "Select option (1-9): ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number from 1 to 9.\n";
            continue;
        }

        switch (choice) {

        case 1:
            viewServices();
            break;

        case 2:
            searchBooking(customerID);
            break;

        case 3:
            addSingleBooking(customerID);
            break;

        case 4:
            addMultipleBooking(customerID);
            break;

        case 5:
            editBooking(customerID);
            break;

        case 6:
            cancelBooking(customerID);
            break;

        case 7:
            viewBooking(customerID);
            break;

        case 8:
            generateBookingSlip(customerID);
            break;

        case 9:
            return;

        default:
            cout << "[Error] Invalid selection.\n";
        }
    }
}

//VIEW SERVICES
void viewServices() {
    cout << "\n========================================\n";
    cout << right << setw(10) << "SERVICES\n";
    cout << "========================================\n";
    for (int i = 0; i < servicecount; i++) {
        cout << "Service ID : " << servicesDB[i].serviceID << "\n";
        cout << "Service    : " << servicesDB[i].servicename << "\n";
        cout << "Price      : RM " << fixed << setprecision(2) << servicesDB[i].price << "\n";
        cout << "Duration   : " << servicesDB[i].duration << " minutes\n";
        cout << "----------------------------------------\n";
    }
}

//SEARCH BOOKING
void searchBooking(const string& customerID)
{
    string bookingID;

    cout << "\nEnter Booking ID: ";
    cin >> bookingID;

    int dayIndex;
    int slotIndex;

    if (!findBookingID(bookingID, dayIndex, slotIndex))
    {
        cout << "[Error] Booking not found.\n";
        return;
    }

    Timeslot& booking = schedule[dayIndex][slotIndex];

    if (booking.customerID != customerID)
    {
        cout << "[Error] Booking does not belong to this customer.\n";
        return;
    }

    cout << "\n========== BOOKING FOUND ==========\n";
    cout << "Booking ID : " << booking.bookingID << "\n";
    cout << "Customer ID: " << booking.customerID << "\n";
    cout << "Service    : " << booking.service << "\n";
    cout << "Staff ID   : " << booking.staffID << "\n";
    cout << "Date       : Day " << dayIndex + 1 << "\n";
    cout << "Time       : " << booking.time << "\n";
    cout << "Status     : " << booking.status << "\n";
}
// MEMBER - ADD SINGLE BOOKING
void addSingleBooking(const string& customerID) {

    int dayOption;
    int slotOption;

    cout << "\n========== ADD BOOKING ==========\n";
    cout << "Enter Day of Month (1-31): ";
    cin >> dayOption;

    if (cin.fail() || dayOption < 1 || dayOption > 31) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "[Error] Invalid day.\n";
        return;
    }

    int dayIndex = dayOption - 1;
    ViewAllAppointment(schedule[dayIndex], TOTAL_SLOTS);
    cout << "\nSelect Timeslot (1-7): ";
    cin >> slotOption;

    if (cin.fail() || slotOption < 1 || slotOption > TOTAL_SLOTS) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "[Error] Invalid timeslot.\n";
        return;
    }

    int slotIndex = slotOption - 1;

    // CHECK IF SLOT IS ALREADY BOOKED
    if (schedule[dayIndex][slotIndex].isBooked) {
        cout << "\n[Error] This timeslot is already booked.\n";
        return;
    }

    // CHECK CUSTOMER DUPLICATE
    if (isDuplicateBooking(customerID, dayIndex, slotIndex)) {
        cout << "\n[Error] You already have a booking at this date and time.\n";
        return;
    }

    // SELECT SERVICE
    viewServices();

    string serviceID;

    cout << "Enter Service ID: ";
    cin >> serviceID;

    int serviceIndex = findServiceID(serviceID);
    if (serviceIndex == -1) {
        cout << "[Error] Service ID not found.\n";
        return;
    }

    // SELECT STAFF
    string staffID;

    cout << "\nAvailable Staff:\n";

    for (int i = 0; i < staffCount; i++) {
        cout << staffDB[i].idStaff
            << " - "
            << staffDB[i].nameStaff
            << endl;
    }

    cout << "Enter Staff ID: ";
    cin >> staffID;

    int staffIndex = findStaffID(staffID);

    if (staffIndex == -1) {
        cout << "[Error] Staff ID not found.\n";
        return;
    }

    // STORE BOOKING DIRECTLY INTO TIMESLOT
    schedule[dayIndex][slotIndex].bookingID =
        "B" + to_string(bookingCounter++);

    schedule[dayIndex][slotIndex].customerID = customerID;

    schedule[dayIndex][slotIndex].staffID =
        staffDB[staffIndex].idStaff;

    schedule[dayIndex][slotIndex].staffName =
        staffDB[staffIndex].nameStaff;

    schedule[dayIndex][slotIndex].service =
        servicesDB[serviceIndex].servicename;

    schedule[dayIndex][slotIndex].status =
        "Confirmed";

    schedule[dayIndex][slotIndex].isBooked = true;

    cout << "\n[Success] Booking added successfully!\n";

    cout << "Booking ID: "
        << schedule[dayIndex][slotIndex].bookingID
        << endl;
}

// MEMBER - ADD MULTIPLE BOOKINGS
void addMultipleBooking(const string& customerID) {
    char response;
    cout << "\n========== ADD MULTIPLE BOOKINGS ==========\n";

    do {
        addSingleBooking(customerID);
        cout << "\nAdd another booking? (Y/N): ";
        cin >> response;
        response = toupper(response);
    } while (response == 'Y');
    cout << "\nFinished adding multiple bookings.\n";
}

// MEMBER - EDIT BOOKING
void editBooking(const string& customerID) {
    string editid;
    cout << "\nEnter Booking ID to edit: ";
    cin >> editid;

    int dayIndex;
    int slotIndex;

    if (!findBookingID(editid, dayIndex, slotIndex)) {
        cout << "[Error] Booking not found.\n";
        return;
    }
    Timeslot& booking = schedule[dayIndex][slotIndex];

    if (booking.customerID != customerID) {
        cout << "[Error] You cannot edit this booking.\n";
        return;
    }

    if (booking.status == "Cancelled") {
        cout << "[Error] Cancelled booking cannot be edited.\n";
        return;
    }

    viewServices();

    string serviceID;
    cout << "Enter new Service ID: ";
    cin >> serviceID;

    int serviceIndex = findServiceID(serviceID);

    if (serviceIndex == -1)
    {
        cout << "[Error] Service not found.\n";
        return;
    }

    booking.service = servicesDB[serviceIndex].servicename;

    cout << "\n[Success] Booking edited successfully.\n";
}
    
// MEMBER - CANCEL BOOKING
void cancelBooking(const string& customerID) {

    string bookingID;

    cout << "\nEnter Booking ID to cancel: ";
    cin >> bookingID;

    int dayIndex;
    int slotIndex;

    if (!findBookingID(bookingID, dayIndex, slotIndex)) {
        cout << "[Error] Booking not found.\n";
        return;
    }

    if (schedule[dayIndex][slotIndex].customerID != customerID) {
        cout << "[Error] You cannot cancel this booking.\n";
        return;
    }

    if (schedule[dayIndex][slotIndex].status == "Cancelled") {
        cout << "[Error] Booking already cancelled.\n";
        return;
    }

    schedule[dayIndex][slotIndex].status = "Cancelled";
    schedule[dayIndex][slotIndex].isBooked = false;
    cout << "\n[Success] Booking "
        << bookingID
        << " cancelled successfully.\n";
}

// MEMBER - VIEW MY BOOKINGS
void viewBooking(const string& customerID) {

    bool found = false;
    cout << "\n========== MY BOOKINGS ==========\n";

    for (int day = 0; day < DAYS_IN_MONTH; day++) {
        for (int slot = 0; slot < TOTAL_SLOTS; slot++) {
            if (schedule[day][slot].isBooked && schedule[day][slot].customerID == customerID) {
                found = true;
                cout << "\nBooking ID : " << schedule[day][slot].bookingID << "\n";
                cout << "Customer ID: " << schedule[day][slot].customerID << "\n";
                cout << "Service    : " << schedule[day][slot].service << "\n";
                cout << "Staff ID   : " << schedule[day][slot].staffID << "\n";
                cout << "Date       : Day " << day + 1 << "\n";
                cout << "Time       : " << schedule[day][slot].time << "\n"; 
                cout << "Status     : " << schedule[day][slot].status << "\n";
                cout << "--------------------------------\n";
            }
        }
    }
    if (!found) {
        cout << "No bookings found.\n";
    }
}

// MEMBER - GENERATE BOOKING SLIP
void generateBookingSlip(const string& customerID) {

    string bookingID;

    cout << "\nEnter Booking ID: ";
    cin >> bookingID;

    int dayIndex;
    int slotIndex;

    if (!findBookingID(bookingID, dayIndex, slotIndex)) {
        cout << "[Error] Booking not found.\n";
        return;
    }

    if (schedule[dayIndex][slotIndex].customerID != customerID) {
        cout << "[Error] You cannot access this booking.\n";
        return;
    }

    cout << "\n";
    cout << "========================================\n";
    cout << "       BOOKING CONFIRMATION SLIP\n";
    cout << "========================================\n";
    cout << "Booking ID : " << schedule[dayIndex][slotIndex].bookingID << "\n";
    cout << "Customer ID: " << schedule[dayIndex][slotIndex].customerID << "\n";
    cout << "Service    : " << schedule[dayIndex][slotIndex].service << "\n";
    cout << "Staff ID   : " << schedule[dayIndex][slotIndex].staffID << "\n";
    cout << "Date       : Day " << dayIndex + 1 << "\n";
    cout << "Time       : " << schedule[dayIndex][slotIndex].time << "\n";
    cout << "Status     : " << schedule[dayIndex][slotIndex].status << "\n";
    cout << "========================================\n";
    cout << "       Thank you for your booking!\n";
    cout << "========================================\n";
}

// STAFF BOOKING MENU
void staffBookingMenu() {
    int choice;
    while (true) {
        cout << "\n----------------------------------------\n";
        cout << "           STAFF BOOKING SYSTEM\n";
        cout << "----------------------------------------\n";
        cout << "1. Add Services\n";
        cout << "2. View Services\n";
        cout << "3. Delete Services\n";
        cout << "4. Edit Services\n";
        cout << "5. Search Services\n";
        cout << "6. Add Booking\n";
        cout << "7. View Booking\n";
        cout << "8. Reschedule / Cancel Booking\n";
        cout << "9. Edit Booking\n";
        cout << "10. Search Booking\n";
        cout << "11. Exit\n";
        cout << "Select option: ";

        if (!(cin >> choice)) {
            cout << "[Error] Invalid input.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {

        case 1:
            addService();
            break;

        case 2:
            viewServices();
            break;

        case 3:
            deleteService();
            break;

        case 4:
            editService();
            break;

        case 5:
            searchService();
            break;

        case 6:
            staffAddBooking();
            break;

        case 7:
            staffViewBooking();
            break;

        case 8:
            rescheduleCancelBooking();
            break;

        case 9:
            staffEditBooking();
            break;

        case 10:
            staffSearchBooking();
            break;

        case 11:
            return;

        default:
            cout << "[Error] Invalid selection.\n";
        }
    }
}

// STAFF - ADD SERVICES
void addService() {

    if (servicecount >= MAX_SERVICES) {
        cout << "[Error] Service database is full.\n";
        return;
    }

    Services newService;
    newService.serviceID = "SI" + to_string(serviceCounter++);
    cout << "\n========== ADD SERVICE ==========\n";
    cout << "Service ID: " << newService.serviceID << "\n";

    cout << "Enter Service Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, newService.servicename);

    cout << "Enter Price: RM ";
    cin >> newService.price;

    cout << "Enter Duration (minutes): ";
    cin >> newService.duration;

    if (newService.servicename.empty() || newService.price <= 0 || newService.duration <= 0) {
        cout << "[Error] Invalid service information.\n";
        return;
    }

    servicesDB[servicecount] = newService;
    servicecount++;

    cout << "\n[Success] Service added successfully.\n";
}

// STAFF - VIEW SERVICES
void viewAllServices() {
    cout << "\n========== ALL SERVICES ==========\n";
    for (int i = 0; i < servicecount; i++) {
        cout << "\nService ID : "
            << servicesDB[i].serviceID << "\n";

        cout << "Name       : "
            << servicesDB[i].servicename << "\n";

        cout << "Price      : RM "
            << fixed << setprecision(2)
            << servicesDB[i].price << "\n";

        cout << "Duration   : "
            << servicesDB[i].duration
            << " minutes\n";
        cout << "----------------------------------\n";
    }
}

// STAFF - DELETE SERVICE
void deleteService() {
    string id;

    cout << "\nEnter Service ID to delete: ";
    cin >> id;

    int index = findServiceID(id);
    if (index == -1) {
        cout << "[Error] Service not found.\n";
        return;
    }

    for (int i = index; i < servicecount - 1; i++) {
        servicesDB[i] = servicesDB[i + 1];
    }

    servicecount--;
    cout << "\n[Success] Service deleted successfully.\n";
}

// STAFF - EDIT SERVICE
void editService() {
    string id;
    cout << "\nEnter Service ID to edit: ";
    cin >> id;

    int index = findServiceID(id);
    if (index == -1) {
        cout << "[Error] Service not found.\n";
        return;
    }

    // Remove leftover '\n' from cin >> id
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nEnter new service name: ";
    getline(cin, servicesDB[index].servicename);

    cout << "Enter new price: RM ";
    cin >> servicesDB[index].price;

    cout << "Enter new duration: ";
    cin >> servicesDB[index].duration;

    if (servicesDB[index].servicename.empty() ||
        servicesDB[index].price <= 0 ||
        servicesDB[index].duration <= 0) {

        cout << "[Error] Invalid service information.\n";
        return;
    }

    cout << "\n[Success] Service updated successfully.\n";
}

// STAFF - SEARCH SERVICE   
void searchService() {
    string id;
    cout << "\nEnter Service ID to search: ";
    cin >> id;

    int index = findServiceID(id);
    if (index == -1) {
        cout << "[Error] Service not found.\n";
        return;
    }

    cout << "\n========== SERVICE FOUND ==========\n";
    cout << "Service ID : " << servicesDB[index].serviceID << "\n";
    cout << "Service    : " << servicesDB[index].servicename << "\n";
    cout << "Price      : RM " << fixed << setprecision(2) << servicesDB[index].price << "\n";
    cout << "Duration   : " << servicesDB[index].duration << " minutes\n";
}

// STAFF - ADD BOOKING
void staffAddBooking() {
    string customerID;
  
    cout << "\n========== STAFF ADD BOOKING ==========\n";
    cout << "Enter Customer ID: ";
    cin >> customerID;
    int customerIndex = findCustomerIndex(customerID);
    int memberIndex = findMemberIndex(customerID);

    string customerName;

    if (customerIndex != -1)
    {
        customerName = customerDB[customerIndex].nameCustomer;
    }
    else if (memberIndex != -1)
    {
        customerName = memberDB[memberIndex].nameMember;
    }
    else
    {
        cout << "[Error] Customer not found.\n";
        return;
    }
    int dayOption;

    cout << "Enter Day of Month (1-31): ";
    cin >> dayOption;

    if (dayOption < 1 || dayOption > 31)
    {
        cout << "[Error] Invalid day.\n";
        return;
    }

    int dayIndex = dayOption - 1;

    ViewAllAppointment(schedule[dayIndex], TOTAL_SLOTS);

    int slotOption;

    cout << "Select Timeslot (1-7): ";
    cin >> slotOption;

    if (slotOption < 1 || slotOption > TOTAL_SLOTS)
    {
        cout << "[Error] Invalid timeslot.\n";
        return;
    }

    int slotIndex = slotOption - 1;

    if (schedule[dayIndex][slotIndex].isBooked)
    {
        cout << "[Error] This timeslot is already booked.\n";
        return;
    }

    viewServices();

    string serviceID;

    cout << "Enter Service ID: ";
    cin >> serviceID;

    int serviceIndex = findServiceID(serviceID);

    if (serviceIndex == -1)
    {
        cout << "[Error] Service not found.\n";
        return;
    }

    string staffID;

    cout << "\nAvailable Staff:\n";

    for (int i = 0; i < staffCount; i++)
    {
        cout << staffDB[i].idStaff
            << " - "
            << staffDB[i].nameStaff << "\n";
    }

    cout << "Enter Staff ID: ";
    cin >> staffID;

    int staffIndex = findStaffID(staffID);

    if (staffIndex == -1)
    {
        cout << "[Error] Staff not found.\n";
        return;
    }

    // STORE DIRECTLY IN SCHEDULE
    schedule[dayIndex][slotIndex].bookingID =
        "B" + to_string(bookingCounter++);

    schedule[dayIndex][slotIndex].customerID =
        customerID;

    schedule[dayIndex][slotIndex].customerName =
        customerName;

    schedule[dayIndex][slotIndex].service =
        servicesDB[serviceIndex].servicename;

    schedule[dayIndex][slotIndex].staffID =
        staffDB[staffIndex].idStaff;

    schedule[dayIndex][slotIndex].staffName =
        staffDB[staffIndex].nameStaff;

    schedule[dayIndex][slotIndex].status =
        "Confirmed";

    schedule[dayIndex][slotIndex].isBooked =
        true;

    cout << "\n[Success] Booking added successfully.\n";

    cout << "Booking ID: "
        << schedule[dayIndex][slotIndex].bookingID << "\n";
}

// STAFF - VIEW BOOKING
void staffViewBooking() {

    bool found = false;

    cout << "\n========== ALL BOOKINGS ==========\n";
    for (int day = 0; day < DAYS_IN_MONTH; day++) {
        for (int slot = 0; slot < TOTAL_SLOTS; slot++) {
            if (schedule[day][slot].isBooked) {
                found = true;
                cout << "\nBooking ID : " << schedule[day][slot].bookingID << "\n";
                cout << "Customer ID: " << schedule[day][slot].customerID << "\n";
                cout << "Service    : " << schedule[day][slot].service << "\n";
                cout << "Staff ID   : " << schedule[day][slot].staffID << "\n";
                cout << "Date       : Day " << day + 1 << "\n";
                cout << "Time       : " << schedule[day][slot].time << "\n";
                cout << "Status     : " << schedule[day][slot].status << "\n";
                cout << "----------------------------------\n";
            }
        }
    }
    if (!found) {
        cout << "No bookings available.\n";
    }
}

// STAFF - RESCHEDULE / CANCEL BOOKING
void rescheduleCancelBooking() {
    string bookingID;
    int choice;
    cout << "\nEnter Booking ID: ";
    cin >> bookingID;

    int dayIndex;
    int slotIndex;

    if (!findBookingID(bookingID, dayIndex, slotIndex)){
        cout << "[Error] Booking not found.\n";
        return;
    }

    Timeslot& booking = schedule[dayIndex][slotIndex];
    cout << "\n1. Reschedule Booking\n";
    cout << "2. Cancel Booking\n";
    cout << "Select option: ";
    cin >> choice;

    if (choice == 1) {
        int newDay;
        int newSlot;

        cout << "Enter new day (1-31): ";
        cin >> newDay;

        cout << "Enter new timeslot (1-7): ";
        cin >> newSlot;

        if (newDay < 1 || newDay > 31 ||
            newSlot < 1 || newSlot > TOTAL_SLOTS)
        {
            cout << "[Error] Invalid date or timeslot.\n";
            return;
        }

        int newDayIndex = newDay - 1;
        int newSlotIndex = newSlot - 1;

        if (schedule[newDayIndex][newSlotIndex].isBooked)
        {
            cout << "[Error] New timeslot is already booked.\n";
            return;
        }
        // Move booking
        schedule[newDayIndex][newSlotIndex] = booking;

        schedule[newDayIndex][newSlotIndex].time =
            defaultDaySlots[newSlotIndex].time;

        schedule[dayIndex][slotIndex] = defaultDaySlots[slotIndex];

        cout << "\n[Success] Booking rescheduled successfully.\n";
    }

    else if (choice == 2)
    {
        if (booking.status == "Cancelled")
        {
            cout << "[Error] Booking already cancelled.\n";
            return;
        }

        booking.status = "Cancelled";
        booking.isBooked = false;

        cout << "\n[Success] Booking cancelled successfully.\n";
    }
    else
    {
        cout << "[Error] Invalid selection.\n";
    }
}

// STAFF - EDIT BOOKING
void staffEditBooking() {
    string bookingID;
    cout << "\nEnter Booking ID to edit: ";
    cin >> bookingID;

    int dayIndex;
    int slotIndex;
    if (!findBookingID(bookingID, dayIndex, slotIndex))
    {
        cout << "[Error] Booking not found.\n";
        return;
    }

    Timeslot& booking = schedule[dayIndex][slotIndex];

    if (booking.status == "Cancelled")
    {
        cout << "[Error] Cancelled booking cannot be edited.\n";
        return;
    }

    viewAllServices();
    string serviceID;
    cout << "Enter new Service ID: ";
    cin >> serviceID;

    int serviceIndex = findServiceID(serviceID);

    if (serviceIndex == -1)
    {
        cout << "[Error] Service not found.\n";
        return;
    }

    booking.service = servicesDB[serviceIndex].servicename;
    cout << "\nAvailable Staff:\n";

    for (int i = 0; i < staffCount; i++)
    {
        cout << staffDB[i].idStaff << " - " << staffDB[i].nameStaff << "\n";
    }

    cout << "Enter new Staff ID: ";

    string staffID;
    cin >> staffID;

    int staffIndex = findStaffID(staffID);

    if (staffIndex == -1)
    {
        cout << "[Error] Staff not found.\n";
        return;
    }
    booking.staffID = staffDB[staffIndex].idStaff;
    booking.staffName = staffDB[staffIndex].nameStaff;
    cout << "\n[Success] Booking edited successfully.\n";
}

// STAFF - SEARCH BOOKING
void staffSearchBooking() {

    string bookingID;

    cout << "\nEnter Booking ID to search: ";
    cin >> bookingID;

    int dayIndex;
    int slotIndex;
    if (!findBookingID(bookingID, dayIndex, slotIndex))
    {
        cout << "[Error] Booking not found.\n";
        return;
    }
    Timeslot& booking = schedule[dayIndex][slotIndex];

    cout << "\n========== BOOKING FOUND ==========\n";
    cout << "Booking ID : " << booking.bookingID << "\n";
    cout << "Customer ID: " << booking.customerID << "\n";
    cout << "Customer   : " << booking.customerName << "\n";
    cout << "Staff ID   : " << booking.staffID << "\n";
    cout << "Date       : Day " << dayIndex + 1 << "\n";
    cout << "Time       : " << booking.time << "\n";
    cout << "Status     : " << booking.status << "\n";
}