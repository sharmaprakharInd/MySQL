#include <iostream>
#include<mysql.h>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <mysqld_error.h>
#include <sstream>
#include <C:\Program Files\MySQL\Connector C++ 1.1\include\cppconn\driver.h>
using namespace std;

class Users {
    //DataMembers
    string Name, Phone, Email, User_ID, Passkey;
public:
    Users(){}
     void setData(string Na, string Ph, string Em, string UID, string PKey){
         Name = Na;
         Phone = Ph;
         Email = Em;
         User_ID = UID;
         Passkey = PKey;
     }
     string getData(char ch) {
         switch (ch) {
         case 'N':return Name; break;
         case 'P':return Phone; break;
         case 'E':return Email; break;
         case 'U':return User_ID; break;
         case 'K':return Passkey; break;
         default:return "0";
         }
     }
};
class Property {
    string Owner_ID;
    
    int size;
    int b;
    int br;
    double price;
    string lastrev;
    char laundary, parking; //laundary -> Y,n; Parking -> S(street),G(Garage),N(none)
    string city, area, Zipcode;
    int rented;
public:
    Property(){}
    void setData(string OID,int s, int brr, int brrr, double p, char l, char pr, string c, string a , string z  ) {
        Owner_ID = OID;
        size = s;
        b = brr;
        br = brrr;
        price = p;
        laundary = l;
        parking = pr;
        city = c;
        area = a;
        Zipcode = z;
    }
    string getData(char ch) {
        switch (ch) {
       
        default:return "0";
        }
    }

};
void listProperty(){}
void searchProperty(){}
void login() {
    string S_no, Name, Phone, Email, User_ID, Passkey;
    Users usr;
    int logCounter = 0;
    cout << "Enter your User_ID:\t";
    cin >> User_ID;
    cout << "Enter your passkey:\t";
    cin >> Passkey;
    getline(cin, Passkey);
    for (int i = 0; i < Passkey.length(); ++i) { // Encrypt
        char currentChar = Passkey[i];
        int newAsciiValue = currentChar + 4;
        // Handle wrapping around the ASCII table
        if (newAsciiValue > 126) {
            newAsciiValue = newAsciiValue % 127 + 32; // Wrap around to printable characters
        }

        Passkey[i] = static_cast<char>(newAsciiValue);
    }
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;
    // Connect to the database
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("localhost", "root", "");
    con->setSchema("houserental");
    // Execute a query to retrieve all data from the 'users' table
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM users WHERE User_ID='"+User_ID+"'");
    // Iterate over the result set and print the data
    while (res->next()) {
        if (res->getString("Passkey").compare(Passkey))
        {
            Name = res->getString("Name");
            Email= res->getString("Email");
            Phone = res->getString("Phone");
            std::cout << "Login successful!" << std::endl;
            logCounter++;
            usr.setData(Name, Phone, Email, User_ID, Passkey);
            break;
        }
    }
    if (logCounter < 0) {
        std::cout << "Login failed. Invalid credentials." << std::endl;
    }

    delete res;
    delete stmt;
    delete con;
    char choice;
    cout << "Would you like to list property(Y/N):\t";
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        listProperty();
    }
    else
        searchProperty();
}
void signup() {
    string S_no, Name, Phone, Email, User_ID, Passkey;
    Users u;
    cout << "Welcome To Signup Page\n";
    cout << "Enter your name:\t";
    getline(cin, Name);
hel:  cout << "Enter your Phone:\t";
    getline(cin, Phone);
    if (Phone.length() != 10) {
        cout << "Not a Valid Phone\n";
        goto hel;
    }
    cout << "Enter your Email:\t";
    getline(cin, Email);
    int name_length = Name.length();
    User_ID = Name.substr(0, min(name_length, 4));
    int phone_length = Phone.length();
    User_ID += Phone.substr(phone_length - min(phone_length, 4), min(phone_length, 4));
    cout << "Your User ID is: \t" << User_ID << endl;
    cout << "Enter a password: \t";
    getline(cin, Passkey);
    for (int i = 0; i < Passkey.length(); ++i) {
        char currentChar = Passkey[i];
        int newAsciiValue = currentChar + 4;

        // Handle wrapping around the ASCII table
        if (newAsciiValue > 126) {
            newAsciiValue = newAsciiValue % 127 + 32; // Wrap around to printable characters
        }

        Passkey[i] = static_cast<char>(newAsciiValue);
    }
    
    MYSQL* conn; conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "houserental", 3306, NULL, 0)) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "logged in Databsse" << endl;
    }
    string insert = "INSERT INTO users (Name, Phone, Email, User_ID, Passkey) VALUES ('" + Name + "','" + Phone + "','" + Email + "','" + User_ID + "','" + Passkey + "')";
    if (mysql_query(conn, insert.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Data Saved Successfuly!" << endl;
    }
    u.setData(Name, Phone, Email, User_ID, Passkey);
    char choice;
    cout << "Would you like to list property(Y/N):\t";
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        listProperty();
    }
    else
        searchProperty();
}
void showTables() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;
    // Connect to the database
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("localhost", "root", "");
    con->setSchema("houserental");
    // Execute a query to retrieve all data from the 'users' table
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM users");
    // Iterate over the result set and print the data
    while (res->next()) {
        std::cout << "User ID: " << res->getString("User_ID") << std::endl;
        std::cout << "Name: " << res->getString("Name") << std::endl;
        std::cout << "Phone: " << res->getString("Phone") << std::endl;
        std::cout << "Email: " << res->getString("Email") << std::endl;
        std::cout << "Passkey: " << res->getString("Passkey") << std::endl;
        // Add more columns as needed
    }
    res = stmt->executeQuery("SELECT * FROM Properties");
    while (res->next()) {

    }
    // Clean up
    delete res;
    delete stmt;
    delete con;

}

int main() {
    cout << "Welcome to Property rental\n";
        cout << "Are you an existing user(Y/N)\t";
        char ch;
        cin >> ch;
        if (ch == '0') {
            cout << "Welcome Admin\n";
            showTables();
        }
        else if (ch == 'y' || ch == 'Y')
            login();
        else

            signup();
    return 0;
}