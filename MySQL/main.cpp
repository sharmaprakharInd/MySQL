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

string S_no, Name, Phone, Email, User_ID, Passkey;
void login() {
    int logCounter = 0;
    cout << "Enter your User_ID:\t";
    cin >> User_ID;
    cout << "Enter your passkey:\t";
    cin >> Passkey;
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
        //std::cout << "User ID: " << res->getString("User_ID") << std::endl;
        //std::cout << "Name: " << res->getString("Name") << std::endl;
        //std::cout << "Phone: " << res->getString("Phone") << std::endl;
        //std::cout << "Email: " << res->getString("Email") << std::endl;
        //std::cout << "Passkey: " << res->getString("Passkey") << std::endl;
        //cout << "h\n";
        //cout << Passkey << res->getString("Passkey") << endl;

        if (res->getString("Passkey").compare(Passkey))
        {
            
            logCounter++;
        }
    }
    if (logCounter > 0) {
        std::cout << "Login successful!" << std::endl;
    }
    else {
        std::cout << "Login failed. Invalid credentials." << std::endl;
    }


    delete res;
    delete stmt;
    delete con;

}
void intotable() {
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
        cout << "Inserted Successfuly!" << endl;
    }
}
void signup() {
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
    intotable();
}

int main() {
    //signup();
    login();

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

    // Clean up
    delete res;
    delete stmt;
    delete con;

    return 0;
}