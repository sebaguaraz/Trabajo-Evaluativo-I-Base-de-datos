#ifndef MenuHandler_H
#define MenuHandler_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <SqliteDatabaseHandler.h>
#include <User.h>
#include <Game.h>
#include <UserMapper.h>
#include <GameMapper.h>
#include <UserGameAssociation.h>

class MenuHandler {
public:
    MenuHandler(const std::shared_ptr<SqliteDatabaseHandler>& dbh);
    void displayMenu();

private:
    std::shared_ptr<SqliteDatabaseHandler> dbh;
    std::shared_ptr<UserMapper> userMapper;
    std::shared_ptr<GameMapper> gameMapper;
    std::shared_ptr<UserGameAssociation> associationMapper;

    void addUser();
    void removeUser();
    void updateUser();
    void listUsers();
    void addGame();
    void removeGame();
    void updateGame();
    void listGames();
    void associateUserWithGame();
    void listAllAssociations();
    void findAssociationsByUser();
    void findAssociationsByGames();
 
};

#endif // MenuHandler_H

