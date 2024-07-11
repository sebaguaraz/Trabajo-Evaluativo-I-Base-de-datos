#include <iostream>
#include <memory>
#include <SqliteDatabaseHandler.h>
#include <MenuHandler.h>

int main() {
    auto dbh = std::make_shared<SqliteDatabaseHandler>();
    dbh->setConfFile("configuration.ini");

    MenuHandler menuHandler(dbh);
    menuHandler.displayMenu();

    return 0;
}

