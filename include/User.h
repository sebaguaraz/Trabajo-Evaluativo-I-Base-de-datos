#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
using namespace std;

// Clase que representa un Usuario
class User {
private:
    int id;
    string name;
    string email;
public:
    User(int id, const string& name, const string& email);

    int getId() const;
    const string& getName() const;
    const string& getEmail() const;
};

#endif // USER_H