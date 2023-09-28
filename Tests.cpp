#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "ClassThatUseDb.h"
#include "MockDBConnection.h"

using namespace testing;

// Test case for opening a database connection.
TEST(ClassThatUseDbTest, OpenConnection) {
    MockDBConnection mockConnection;
    ClassThatUseDb classUnderTest(&mockConnection);

    EXPECT_CALL(mockConnection, open("test_db")).WillOnce(Return(true));
    EXPECT_TRUE(classUnderTest.openConnection("test_db"));
}

// Test case for using a database connection.
TEST(ClassThatUseDbTest, UseConnection) {
    MockDBConnection mockConnection;
    ClassThatUseDb classUnderTest(&mockConnection);

    EXPECT_CALL(mockConnection, execQuery("SELECT * FROM table")).WillOnce(Return(true));
    EXPECT_TRUE(classUnderTest.useConnection("SELECT * FROM table"));
}

// Test case for closing a database connection.
TEST(ClassThatUseDbTest, CloseConnection) {
    MockDBConnection mockConnection;
    ClassThatUseDb classUnderTest(&mockConnection);

    EXPECT_CALL(mockConnection, close()).WillOnce(Return(true));
    EXPECT_TRUE(classUnderTest.closeConnection());
}
