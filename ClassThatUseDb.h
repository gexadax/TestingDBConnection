#pragma once
#include "DBConnection.h"

// Class that uses a DBConnection to interact with a database.
class ClassThatUseDb {
public:
    ClassThatUseDb(DBConnection* connection);

    bool openConnection(const std::string& dbName);

    bool useConnection(const std::string& query);

    bool closeConnection();

private:
    DBConnection* dbConnection;
};
