#include <Game.h>

Game::Game(int id, const std::string& title, const std::string& genre): id(id), title(title), genre(genre) {}

int Game::getId() const { return id; }

const string& Game::getTitle() const { return title; }

const string& Game::getGenre() const { return genre; }