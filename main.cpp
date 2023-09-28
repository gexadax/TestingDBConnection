#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// connecting to the database
class DBConnection {
public:
    virtual bool open(const std::string& dbName) = 0;
    virtual bool close() = 0;
    virtual bool execQuery(const std::string& query) = 0;
};

// The class that will use the database connection
class ClassThatUseDb {
public:
    ClassThatUseDb(DBConnection* connection) : dbConnection(connection) {}

    bool openConnection(const std::string& dbName) {
        return dbConnection->open(dbName);
    }

    bool useConnection(const std::string& query) {
        return dbConnection->execQuery(query);
    }

    bool closeConnection() {
        return dbConnection->close();
    }

private:
    DBConnection* dbConnection;
};

// Mock class for DBConnection
class MockDBConnection : public DBConnection {
public:
    MOCK_METHOD(bool, open, (const std::string& dbName), (override));
    MOCK_METHOD(bool, close, (), (override));
    MOCK_METHOD(bool, execQuery, (const std::string& query), (override));
};

// Tests using GTest and GMock
TEST(ClassThatUseDbTest, OpenConnection) {
    MockDBConnection mockConnection;
    ClassThatUseDb classUnderTest(&mockConnection);

    EXPECT_CALL(mockConnection, open("test_db")).WillOnce(testing::Return(true));
    EXPECT_TRUE(classUnderTest.openConnection("test_db"));
}

TEST(ClassThatUseDbTest, UseConnection) {
    MockDBConnection mockConnection;
    ClassThatUseDb classUnderTest(&mockConnection);

    EXPECT_CALL(mockConnection, execQuery("SELECT * FROM table")).WillOnce(testing::Return(true));
    EXPECT_TRUE(classUnderTest.useConnection("SELECT * FROM table"));
}

TEST(ClassThatUseDbTest, CloseConnection) {
    MockDBConnection mockConnection;
    ClassThatUseDb classUnderTest(&mockConnection);

    EXPECT_CALL(mockConnection, close()).WillOnce(testing::Return(true));
    EXPECT_TRUE(classUnderTest.closeConnection());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
