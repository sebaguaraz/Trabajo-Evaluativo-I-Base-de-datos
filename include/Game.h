#ifndef GAMES_H
#define GAMES_H
#include <iostream>
#include <string>
using namespace std;

// Clase que representa un Juego
class Game {
private:
    int id;
    std::string title;
    std::string genre;

public:
    Game(int id, const std::string& title, const std::string& genre);
    
    int getId() const;
    const string& getTitle() const;
    const string& getGenre() const;

};

#endif // GAMES_H