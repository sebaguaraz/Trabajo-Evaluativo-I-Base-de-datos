#include <UserMapper.h>

UserMapper::UserMapper(std::shared_ptr<SqliteDatabaseHandler> dbh) : dbh(dbh) {}
    
void UserMapper::createTable() {
        dbh->prepareQuery("CREATE TABLE IF NOT EXISTS Users ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                         "name TEXT, "
                         "email TEXT UNIQUE)");
        dbh->execute();
    }

bool UserMapper::insertUser(std::shared_ptr<User> user) {
    try {
        std::string sql = "INSERT INTO Users (name, email) VALUES (?, ?)";
        
        dbh->prepareQuery(sql);
        dbh->addParameter(1, user->getName());
        dbh->addParameter(2, user->getEmail());
        
        dbh->execute();
        return true;  // Éxito al ejecutar la consulta
    } catch (const std::exception& e) {
        std::cerr << "Error executing insert query: " << e.what() << std::endl;
        return false; // Fallo al ejecutar la consulta
    }
}




std::vector<User> UserMapper::findAllUser() {
    dbh->prepareQuery("SELECT * FROM Users");
    auto table = dbh->fetchAll();
    std::vector<User> users;
    for (const auto& row : table) {
        users.push_back(User(std::stoi(row.at("id")), row.at("name"), row.at("email")));
    }
    return users;
    }
    


bool UserMapper::removeUser(int id) {
    try {
        // Eliminar asociaciones en la tabla intermedia primero
        std::string deleteAssociationsSql = "DELETE FROM Users_Games WHERE user_id = ?";
        dbh->prepareQuery(deleteAssociationsSql);
        dbh->addParameter(1, std::to_string(id));
        dbh->execute();

        // Luego eliminar al usuario de la tabla Users
        std::string deleteUserSql = "DELETE FROM Users WHERE id = ?";
        dbh->prepareQuery(deleteUserSql);
        dbh->addParameter(1, std::to_string(id));
        dbh->execute();

        return true;  // Éxito al ejecutar las consultas
    } catch (const std::exception& e) {
        std::cerr << "Error executing remove user query: " << e.what() << std::endl;
        return false; // Fallo al ejecutar la consulta
    }
}

    
bool UserMapper::updateUser(std::shared_ptr<User> user) {
    try {
        std::string sql = "UPDATE Users SET name = ?, email = ? WHERE id = ?";
        
        dbh->prepareQuery(sql);
        dbh->addParameter(1, user->getName());
        dbh->addParameter(2, user->getEmail());
        dbh->addParameter(3, std::to_string(user->getId()));
        
        dbh->execute();
        return true;  // Éxito al ejecutar la consulta
    } catch (const std::exception& e) {
        std::cerr << "Error executing update query: " << e.what() << std::endl;
        return false; // Fallo al ejecutar la consulta
    }
}


std::vector<User> UserMapper::findByEmail(const std::string& email) {
    try {
        std::vector<User> users;
        std::string sql = "SELECT * FROM Users WHERE email = ?";
        
        dbh->prepareQuery(sql);
        dbh->addParameter(1, email);
        
        auto result = dbh->fetchAll();
        
        for (const auto& row : result) {
            int id = std::stoi(row.at("id"));
            std::string name = row.at("name");
            std::string userEmail = row.at("email");
            
            users.push_back(User(id, name, userEmail));
        }
        
        return users;
    } catch (const std::exception& e) {
        std::cerr << "Error fetching user by email: " << e.what() << std::endl;
        return {};
    }
}


