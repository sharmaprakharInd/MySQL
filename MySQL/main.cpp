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
    Users(){
       // cout << "Null\n";
    }
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
    
    int size=0;
    int b=0;
    int br=0;
    double price=0.0;
    string lastrev;
    char laundry='\0', parking='\0'; //laundary -> Y,n; Parking -> S(street),G(Garage),N(none)
    string city, area, Zipcode;
    int rented=0;
public:
    Property(){}
    void setData(string OID,int s, int brr, int brrr, double p, char l, char pr, string c, string a , string z  ) {
        Owner_ID = OID;
        size = s;
        b = brr;
        br = brrr;
        price = p;
        laundry = l;
        parking = pr;
        city = c;
        area = a;
        Zipcode = z;
    }
    string getData(char ch) {
        switch (ch) {
        case 'O':return Owner_ID;
        case 's':return to_string(size);
        case 'b':return to_string(b);
        case 'B':return to_string(br);
        case 'P':return to_string(price);
        case 'l':return to_string(laundry);
        case 'p':return to_string(parking);
        case 'c':return city;
        case 'a':return area;
        case 'Z':return Zipcode;
        case 'R':return lastrev;
        default:return "0";
        }
    }

};
void intotable(string table, Property& p) {
    MYSQL* conn; conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "houserental", 3306, NULL, 0)) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "logged in Database" << endl;
    }
    string ins = "INSERT INTO properties (Owner_ID , Zipcode , b , br , size ,price ,laundary,parking ,city ,area ) VALUES (";
    ins += "'" + p.getData('O') + "',";
    ins += "'" + p.getData('Z') + "',";
    ins += (p.getData('b')) + ",";
    ins += (p.getData('B')) + ",";
    ins += (p.getData('s')) + ",";
    ins += (p.getData('P')) + ",";
    ins += "'" + p.getData('l') + "',";
    ins += "'" + p.getData('p') + "',";
    ins += "'" + p.getData('c') + "',";
    ins += "'" + p.getData('a') + "');";
    if (mysql_query(conn, ins.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Data Saved Successfully!" << endl;
    }
}
void listProperty(Users& u) {
    string Owner_ID;
    int si;
    int bed;
    int bath;
    double pr;
    char laun, park; //laundry -> Y,n; Parking -> S(street),G(Garage),N(none)
    string ci, ar, Zipc;
    Owner_ID = u.getData('U');
    cout << "welcome User \t " << Owner_ID << endl;
    cout << "Enter the size of the property:\t";
    cin >> si;
    cout << "Enter the number of bedrooms:\t";
    cin >> bed;
    cout << "Enter the number of bathrooms;\t";
    cin >> bath;
    cout << "Enter the price:\t";
    cin >> pr;
    cin.ignore();
    cout << "Is laundry service available(Y/N)";
    cin >> laun;
    cin.ignore();
    cout << "Is Parking facility available S(street),G(Garage),N(none)";
    cin >> park;
    cin.ignore();
    cout << "Enter The city:\t";
    getline(cin, ci);
    cin.ignore();
    cout << "Enter The locality:\t";
    cin >> ar;
    cin.ignore();
    //std::getline(std::cin, ar);
    cout << "Enter The Zipcode:\t";
    getline(cin, Zipc);
    Property P;
    P.setData(Owner_ID, si, bed, bath, pr, laun, park, ci, ar, Zipc);
    intotable("property", P);

}
void searchProperty(Users& u) {
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::ResultSet* res;
    // Connect to the database
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("localhost", "root", "");
    con->setSchema("houserental");
    cout << "Welcome to property search\n";
    cout << "Welcome user:\t" << u.getData('U');
    cout << "Enter the area:\t";
    string ar1; int c;
    cin >> ar1;
    // Execute a query to retrieve all data from the 'users' table
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM properties WHERE area='" + ar1 + "'");
    cout << "Prop_ID\t Size \t price \t b \t br \t laundary \t parking \t lastrev\n" << endl;

    while (res->next()) {
        if (res->getString("rented") == "") {
            cout << res->getInt("Prop_ID") << "\t" << res->getInt("size") << "\t" << res->getDouble("price") << "\t" << res->getInt("b") << "\t" << res->getInt("br") << "\t\t" << res->getString("laundary") << "\t" << res->getString("parking") << "\t" << res->getString("lastrev") << "\t" << endl;
        }
    }
    cout << "Enter the ID of the property which you have to rent:\t";
    cin >> c;

    MYSQL* conn; conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "houserental", 3306, NULL, 0)) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "logged in Databsse" << endl;
    }
    string insert = "UPDATE properties SET rented = 1 WHERE Prop_ID =" + to_string(c);
    if (mysql_query(conn, insert.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    insert = "UPDATE properties SET renter ='"+ u.getData('U') +"' WHERE Prop_ID =" + to_string(c);
    if (mysql_query(conn, insert.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Data Saved Successfuly!" << endl;
    }
    cout << "You have rented this property congatutiolation";
    cout << "Prop_ID\t Size \t price \t b \t br \t laundary \t parking \t lastrev\n" << endl;
    while (res->next()) {
        if (res->getInt("Prop_ID") == c) {
            cout << res->getInt("Prop_ID") << "\t" << res->getInt("size") << "\t" << res->getDouble("price") << "\t" << res->getInt("b") << "\t" << res->getInt("br") << "\t\t" << res->getString("laundary") << "\t" << res->getString("parking") << "\t" << res->getString("lastrev") << "\t" << endl;
        }
    }
}
void unrent(int propn) {
    string rev;
    cout << "Enter a review:\t";
    cin >> rev;
    MYSQL* conn; conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "houserental", 3306, NULL, 0)) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "logged in Databsse" << endl;
    }
    string insert = "UPDATE properties SET lastrev ='"+rev+"' WHERE Prop_ID =" + to_string(propn);
    if (mysql_query(conn, insert.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    insert = "UPDATE properties SET rented = NULL WHERE Prop_ID =" + to_string(propn);
    if (mysql_query(conn, insert.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    insert = "UPDATE properties SET renter = NULL WHERE Prop_ID =" + to_string(propn);
    if (mysql_query(conn, insert.c_str())) {
        cout << "Error: " << mysql_error(conn) << endl;
    }
    else {
        cout << "Data Saved Successfuly!" << endl;
    }
}
void login() {
    string S_no, Name, Phone, Email, User_ID, Passkey;
    Users usr; char ur; int propn;
    int logCounter = 0;
    cout << "Enter your User_ID:\t";
    cin >> User_ID;
    cout << "Enter your passkey:\t";
    cin >> Passkey;
    //getline(cin, Passkey);
    for (int i = 0; i < Passkey.length(); ++i) { // Encrypt
        char currentChar = Passkey[i];
        int newAsciiValue = currentChar + 4;
        // Handle wrapping around the ASCII table
        if (newAsciiValue > 126) {
            newAsciiValue = newAsciiValue % 127 + 32; // Wrap around to printable characters
        }

        Passkey[i] = static_cast<char>(newAsciiValue);
    }
    //cout << Passkey<<"Hi\n";
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
        //cout << res->getString("Passkey") <<"hi" << Passkey << res->getString("Passkey").compare(Passkey) << endl;
        if (res->getString("Passkey").compare(Passkey)==0)
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
    if (logCounter ==0) {
        std::cout << "Login failed. Invalid credentials." << std::endl;
        exit(0);
    }
   
    char choice;
    int c = 0;
    res = stmt->executeQuery("SELECT * FROM properties WHERE renter='" + User_ID + "'");
     
        cout << "You're currently renting the following:\n";
        cout << "Prop_ID\t Size \t price \t b \t br \t laundary \t parking \t lastrev\n" << endl;

        while (res->next()) {
            c++;
            cout << res->getInt("Prop_ID") << "\t" << res->getInt("size") << "\t" << res->getDouble("price") << "\t" << res->getInt("b") << "\t" << res->getInt("br") << "\t\t" << res->getString("laundary") << "\t" << res->getString("parking") << "\t" << res->getString("lastrev") << "\t" << endl;
        }
        if (c > 0) {
            cout << "Would you like to unrent any property:(Y/N)\t";
            cin >> ur;
            if (ur == 'Y') {
                cout << "Enter the property you want to rent:\t";
                cin >> propn;
                unrent(propn);
            }
        }
        else {
            cout << "no propperty found\n";
        }
    delete res;
    delete stmt;
    delete con;
    cout << "Would you like to list property(Y/N):\t";
    cin >> choice;
    if (choice == 'Y' || choice == 'y') {
        listProperty(usr);
    }
    else
        searchProperty(usr);
}
void signup() {
    string S_no, Name, Phone, Email, User_ID, Passkey;
    Users u;
    cout << "Welcome To Signup Page\n";
    cout << "Enter your name:\t";
    cin >> Name;
hel:  cout << "Enter your Phone:\t";
    cin >> Phone;
    if (Phone.length() != 10) {
        cout << "Not a Valid Phone\n";
        goto hel;
    }
    cout << "Enter your Email:\t";
    cin >> Email;
    int name_length = Name.length();
    User_ID = Name.substr(0, min(name_length, 4));
    int phone_length = Phone.length();
    User_ID += Phone.substr(phone_length - min(phone_length, 4), min(phone_length, 4));
    cout << "Your User ID is: \t" << User_ID << endl;
    cout << "Enter a password: \t";
    cin >> Passkey;
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
        listProperty(u);
    }
    else
        searchProperty(u);
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
       home: cout << "Are you an existing user(Y/N)\t";
        char ch;
        cin >> ch;
        if (ch == '0') {
            cout << "Welcome Admin\n";
            showTables();
        }
        else if (ch == 'y' || ch == 'Y')
            login();
        else if(ch == 'n' || ch == 'N')
            signup();
    return 0;
}