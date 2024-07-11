#include <MenuHandler.h>

MenuHandler::MenuHandler(const std::shared_ptr<SqliteDatabaseHandler>& dbh)
    : dbh(dbh) {
    userMapper = std::make_shared<UserMapper>(dbh);
    userMapper->createTable(); // crear la tabla users si aún no existe

    gameMapper = std::make_shared<GameMapper>(dbh);
    gameMapper->createTable(); // crear la tabla game si aún no existe

    associationMapper = std::make_shared<UserGameAssociation>(dbh);
    associationMapper->createTable(); // crear la tabla intermedia si aún no existe
}

void MenuHandler::displayMenu() {
    int option;
    do {
        std::cout << "----- MENU -----" << std::endl;
        std::cout << "1. Add User" << std::endl;
        std::cout << "2. Remove User" << std::endl;
        std::cout << "3. Update User" << std::endl;
        std::cout << "4. List Users" << std::endl;
        std::cout << "5. Add Game" << std::endl;
        std::cout << "6. Remove Game" << std::endl;
        std::cout << "7. Update Game" << std::endl;
        std::cout << "8. List Games" << std::endl;
        std::cout << "9. Associate User with Game" << std::endl;
        std::cout << "10. List All Associations" << std::endl;
        std::cout << "11. Find Associations by User" << std::endl;
        std::cout << "12. Find Associations by Games" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter an option: ";
        std::cin >> option;
        std::cin.ignore(); // Limpiar el buffer después de leer la opción

        switch (option) {
            case 1:
                addUser();
                break;
            case 2:
                removeUser();
                break;
            case 3:
                updateUser();
                break;
            case 4:
                listUsers();
                break;
            case 5:
                addGame();
                break;
            case 6:
                removeGame();
                break;
            case 7:
                updateGame();
                break;
            case 8:
                listGames();
                break;
            case 9:
                associateUserWithGame();
                break;
            case 10:
                listAllAssociations();
                break;
            case 11:
                findAssociationsByUser();
                break;
            case 12:
                findAssociationsByGames();
                break;
            case 0:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
                break;
        }
    } while (option != 0);
}

void MenuHandler::addUser() {
    std::string name, email;
    std::cout << "Enter name: ";
    std::getline(std::cin, name);
    std::cout << "Enter email: ";
    std::getline(std::cin, email);

    auto user = std::make_shared<User>(0, name, email); // Crear el usuario aquí
    if (userMapper->insertUser(user)) {
        std::cout << "User added successfully." << std::endl;
    } else {
        std::cout << "Failed to add user." << std::endl;
    }
}

void MenuHandler::removeUser() {
    int id;
    std::cout << "Enter id: ";
    std::cin >> id;
    std::cin.ignore();
    if (userMapper->removeUser(id)) {
        std::cout << "User removed successfully." << std::endl;
    } else {
        std::cout << "Failed to remove user." << std::endl;
    }
}

void MenuHandler::updateUser() {
    int id;
    std::string name, email;
    std::cout << "Enter id for update: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Enter new name: ";
    std::getline(std::cin, name);
    std::cout << "Enter new email: ";
    std::getline(std::cin, email);

    auto user = std::make_shared<User>(id, name, email);
    if (userMapper->updateUser(user)) {
        std::cout << "User updated successfully." << std::endl;
    } else {
        std::cout << "Failed to update user." << std::endl;
    }
}

void MenuHandler::listUsers() {
    auto users = userMapper->findAllUser();
    for (const auto& user : users) {
        std::cout << "ID: " << user.getId() << ", Name: " << user.getName() << ", Email: " << user.getEmail() << std::endl;
    }
}

void MenuHandler::addGame() {
    std::string title, genre;
    std::cout << "Enter title: ";
    std::getline(std::cin, title);
    std::cout << "Enter genre: ";
    std::getline(std::cin, genre);

    auto game = std::make_shared<Game>(0, title, genre); // Crear un nuevo juego con ID 0, que será asignado automáticamente en la base de datos
    if (gameMapper->insertGame(game)) {
        std::cout << "Game added successfully." << std::endl;
    } else {
        std::cout << "Failed to add game." << std::endl;
    }
}

void MenuHandler::removeGame() {
    int id;
    std::cout << "Enter id of Game: ";
    std::cin >> id;
    std::cin.ignore();
    if (gameMapper->removeGame(id)) {
        std::cout << "Game removed successfully." << std::endl;
    } else {
        std::cout << "Failed to remove game." << std::endl;
    }
}

void MenuHandler::updateGame() {
    int id;
    std::string title, genre;
    std::cout << "Enter id for update: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "Enter new title: ";
    std::getline(std::cin, title);
    std::cout << "Enter new genre: ";
    std::getline(std::cin, genre);

    auto game = std::make_shared<Game>(id, title, genre);
    if (gameMapper->updateGame(game)) {
        std::cout << "Game updated successfully." << std::endl;
    } else {
        std::cout << "Failed to update game." << std::endl;
    }
}

void MenuHandler::listGames() {
    auto games = gameMapper->findAllGame();
    for (const auto& game : games) {
        std::cout << "ID: " << game.getId() << ", Title: " << game.getTitle() << ", Genre: " << game.getGenre() << std::endl;
    }
}

void MenuHandler::associateUserWithGame() {
    int userId, gameId;
        std::cout << "Enter user ID: ";
        std::cin >> userId;
        std::cin.ignore(); // Limpiar el buffer después de leer el ID

        std::cout << "Enter game ID: ";
        std::cin >> gameId;
        std::cin.ignore(); // Limpiar el buffer después de leer el ID

        if (associationMapper->associate(userId, gameId)) {
            std::cout << "Association created successfully." << std::endl;
        }
        else {
        std::cout << "Failed to associate user with the game." << std::endl;
    }
}

void MenuHandler::listAllAssociations(){

        auto associations = associationMapper->findAllAssociations(userMapper, gameMapper);

        for (const auto& [user, game] : associations) {
            std::cout << "User: " << user.getName() << " (Email: " << user.getEmail() << "), Game: " << game.getTitle() << " (Genre: " << game.getGenre() << ")" << std::endl;
        }



}

void MenuHandler::findAssociationsByUser() {
    std::string email;
    std::cout << "Enter user email to search: ";
    std::getline(std::cin, email);

    auto users = userMapper->findByEmail(email);
    for (const auto& user : users) {
        std::cout << "User: " << user.getName() << ", Email: " << user.getEmail() << std::endl;
        
        auto associations = associationMapper->findAllAssociations(userMapper, gameMapper);
        for (const auto& [associatedUser, game] : associations) {
            if (associatedUser.getId() == user.getId()) {
                std::cout << "\tGame: " << game.getTitle() << ", Genre: " << game.getGenre() << std::endl;
            }
        }
    }
}

void MenuHandler::findAssociationsByGames(){

        std::string title;
        std::cout << "Enter game title to search: ";
        std::getline(std::cin, title);

        auto games = gameMapper->findByTitle(title);
        for (const auto& game : games) {
            std::cout << "Game: " << game.getTitle() << " (Genre: " << game.getGenre() << ")" << std::endl;
            auto associations = associationMapper->findAllAssociations(userMapper, gameMapper);
            for (const auto& [user, associatedGame] : associations) {
                if (associatedGame.getId()== game.getId()) {
                    std::cout << "\tUser: " << user.getName() << ", Email: " << user.getEmail() << std::endl;
                }
            }
        }
}


