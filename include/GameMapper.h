#ifndef GameMapper_H
#define GameMapper_H
#include <memory>
#include <vector>
#include <SqliteDatabaseHandler.h>
#include <Game.h>
#include <iostream>
#include <string>
using namespace std;

class GameMapper {
public:
    GameMapper(std::shared_ptr<SqliteDatabaseHandler> dbh);
    
    void createTable();

    bool insertGame(std::shared_ptr<Game> game);

    std::vector<Game> findAllGame();

    bool updateGame(std::shared_ptr<Game> game);

    bool removeGame(int id);

    vector<Game> findByTitle(const string& title);
    

    // Implement other CRUD operations as needed
private:
    std::shared_ptr<SqliteDatabaseHandler> dbh;
};

#endif // GameMapper_H