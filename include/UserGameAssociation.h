#ifndef UserGameAssociation_H
#define UserGameAssociation_H
#include <memory>
#include <vector>
#include <SqliteDatabaseHandler.h>
#include <UserMapper.h>
#include <GameMapper.h>
#include <User.h>
#include <Game.h>
#include <iostream>
#include <string>
using namespace std;

class UserGameAssociation {
public:
    UserGameAssociation(std::shared_ptr<SqliteDatabaseHandler> dbh);
    
    void createTable();

    bool associate(int userId, int gameId);

    std::vector<std::pair<User, Game>> findAllAssociations(std::shared_ptr<UserMapper> userMapper, std::shared_ptr<GameMapper> gameMapper);



    // Implement other CRUD operations as needed
private:
    std::shared_ptr<SqliteDatabaseHandler> dbh;
};

#endif // UserGameAssociation_H