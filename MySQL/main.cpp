#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

int main() {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;

    // Connect to the database
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("localhost", "root", ""); // Replace with your database credentials
    con->setSchema("houserental"); // Replace with your database name

    // Execute a query to retrieve all data from the 'users' table
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM users");

    // Iterate over the result set and print the data
    while (res->next()) {
        std::cout << "User ID: " << res->getString("User_ID") << std::endl;
        std::cout << "Name: " << res->getString("Name") << std::endl;
        std::cout << "Phone: " << res->getString("Phone") << std::endl;
        std::cout << "Email: " << res->getString("Email") << std::endl;
        // Add more columns as needed
    }

    // Clean up
    delete res;
    delete stmt;
    delete con;

    return 0;
}