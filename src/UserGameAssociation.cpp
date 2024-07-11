#include <UserGameAssociation.h>

UserGameAssociation::UserGameAssociation(std::shared_ptr<SqliteDatabaseHandler> dbh): dbh(dbh) {}
    
void UserGameAssociation::createTable(){

    
    dbh->prepareQuery("CREATE TABLE IF NOT EXISTS Users_Games ("
                        "user_id INTEGER NOT NULL, "
                        "game_id INTEGER NOT NULL, "
                        "FOREIGN KEY(user_id) REFERENCES Users(id),"
                        "FOREIGN KEY(game_id) REFERENCES Game(id),"
                        "PRIMARY KEY (user_id, game_id))");
    dbh->execute();
    }


bool UserGameAssociation::associate(int userId, int gameId){
    try {
        std::string sql = "INSERT INTO Users_Games (user_id, game_id) VALUES (?, ?)";
        dbh->prepareQuery(sql);
        dbh->addParameter(1, std::to_string(userId));
        dbh->addParameter(2, std::to_string(gameId));
        dbh->execute();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error executing association query: " << e.what() << std::endl;
        return false;
    }
}


//----------------------------------------------

std::vector<std::pair<User, Game>> UserGameAssociation::findAllAssociations(std::shared_ptr<UserMapper> userMapper, std::shared_ptr<GameMapper> gameMapper) {
    try {
        std::vector<std::pair<User, Game>> associations;
        
        std::string sql = "SELECT Users.id AS userId, Users.name AS userName, Users.email AS userEmail, "
                          " Game.id AS gameId, Game.title AS gameTitle, Game.genre AS gameGenre FROM Users "
                          "INNER JOIN Users_Games ON Users.id = Users_Games.user_id "
                          "INNER JOIN Game ON Game.id = Users_Games.game_id";
        
        dbh->prepareQuery(sql);
        auto result = dbh->fetchAll();
        
        for (const auto& row : result) {
            int userId = std::stoi(row.at("userId"));
            std::string userName = row.at("userName");
            std::string userEmail = row.at("userEmail");
            int gameId = std::stoi(row.at("gameId"));
            std::string gameTitle = row.at("gameTitle");
            std::string gameGenre = row.at("gameGenre");
            
            User user(userId, userName, userEmail);
            Game game(gameId, gameTitle, gameGenre);
            
            associations.push_back(std::make_pair(user, game));
        }
        
        return associations;
    } catch (const std::exception& e) {
        std::cerr << "Error fetching associations: " << e.what() << std::endl;
        return {};
    }
}


