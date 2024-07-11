#include <GameMapper.h>

GameMapper::GameMapper(std::shared_ptr<SqliteDatabaseHandler> dbh): dbh(dbh) {}
    
void GameMapper::createTable(){
        dbh->prepareQuery("CREATE TABLE IF NOT EXISTS Game ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                         "title TEXT UNIQUE, "
                         "genre TEXT)");
        dbh->execute();
    }

bool GameMapper::insertGame(std::shared_ptr<Game> game) {
    try {
        std::string sql = "INSERT INTO Game (title, genre) VALUES (?, ?)";
        
        dbh->prepareQuery(sql);
        dbh->addParameter(1, game->getTitle());
        dbh->addParameter(2, game->getGenre());
        
        dbh->execute();
        return true;  // Éxito al ejecutar la consulta
    } catch (const std::exception& e) {
        std::cerr << "Error executing insert query: " << e.what() << std::endl;
        return false; // Fallo al ejecutar la consulta
    }
}

std::vector<Game> GameMapper::findAllGame(){
    dbh->prepareQuery("SELECT * FROM Game");
    auto table = dbh->fetchAll();
    std::vector<Game> games;
    for (const auto& row : table) {
        games.push_back(Game(std::stoi(row.at("id")), row.at("title"), row.at("genre")));
    }
    return games;
    }

bool GameMapper::updateGame(std::shared_ptr<Game> game){
    try {
        std::string sql = "UPDATE Game SET title = ?, genre = ? WHERE id = ?";
        
        dbh->prepareQuery(sql);
        dbh->addParameter(1, game->getTitle());
        dbh->addParameter(2, game->getGenre());
        dbh->addParameter(3, std::to_string(game->getId()));
        
        dbh->execute();
        return true;  // Éxito al ejecutar la consulta
    } catch (const std::exception& e) {
        std::cerr << "Error executing update query: " << e.what() << std::endl;
        return false; // Fallo al ejecutar la consulta
    }
}



bool GameMapper::removeGame(int id){
    try {

        // Eliminar asociaciones en la tabla intermedia primero
        std::string deleteAssociationsSql = "DELETE FROM Users_Games WHERE game_id = ?";
        dbh->prepareQuery(deleteAssociationsSql);
        dbh->addParameter(1, std::to_string(id));
        dbh->execute();

        std::string sql = "DELETE FROM Game WHERE id = ?";
        dbh->prepareQuery(sql);
        dbh->addParameter(1, std::to_string(id));
        dbh->execute();

        return true;  // Éxito al ejecutar la consulta
    } catch (const std::exception& e) {
        std::cerr << "Error executing remove query: " << e.what() << std::endl;
        return false; // Fallo al ejecutar la consulta
    }
}


vector<Game> GameMapper::findByTitle(const string& title){

    try {
        std::vector<Game> games;
        std::string sql = "SELECT * FROM Game WHERE title = ?";
        
        dbh->prepareQuery(sql);
        dbh->addParameter(1, title);
        
        auto result = dbh->fetchAll();
        
        for (const auto& row : result) {
            int id = std::stoi(row.at("id"));
            std::string title = row.at("title");
            std::string genre = row.at("genre");
            
            games.push_back(Game(id, title, genre));
        }
        
        return games;
    } catch (const std::exception& e) {
        std::cerr << "Error fetching user by email: " << e.what() << std::endl;
        return {};
    }
}