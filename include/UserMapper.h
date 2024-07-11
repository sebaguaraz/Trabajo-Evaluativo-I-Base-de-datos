#ifndef UserMapper_H
#define UserMapper_H
#include <memory>
#include <vector>
#include <SqliteDatabaseHandler.h>
#include <User.h>
#include <iostream>
#include <string>
using namespace std;

class UserMapper {
public:
    UserMapper(std::shared_ptr<SqliteDatabaseHandler> dbh);
    
    void createTable();

    bool insertUser(std::shared_ptr<User> user);

    std::vector<User> findAllUser();

    bool updateUser(std::shared_ptr<User> user);

    bool removeUser(int id);

    vector<User> findByEmail(const string& email);
    

    // Implement other CRUD operations as needed
private:
    std::shared_ptr<SqliteDatabaseHandler> dbh;
};

#endif // UserMapper_H