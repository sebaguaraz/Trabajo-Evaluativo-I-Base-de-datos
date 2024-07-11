#include <User.h>

User::User(int id, const string& name, const string& email): id(id), name(name), email(email) {}

int User::getId() const { return id; }

const string& User::getName() const { return name; }

const string& User::getEmail() const { return email; }
