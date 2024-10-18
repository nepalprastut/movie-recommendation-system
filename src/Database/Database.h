// #ifndef DATABASE_H
// #define DATABASE_H

// #include <mysql/mysql.h>
// #include <string>
// #include <vector>

// using namespace std;


// class Database{
// public:
//     Database(string host, string user, string password, string dbName);
//     ~Database();

//     bool connect();
//     void disconnect();
//     bool execQuery(string query);
//     vector<vector<string>> fetchResults(string query);

// private:
//     MYSQL* conn;
//     string host;
//     string user;
//     string password;
//     string dbName;
// };

// #endif