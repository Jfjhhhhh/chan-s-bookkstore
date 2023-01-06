#include <iostream>
#include "Token_scanner.h"
#include "book.h"
#include "user.h"
#include "error.h"

void processLine(std::string &line, user &users, book &books) {
    Tokenscanner scanner;
    scanner.read(line);
    string s = scanner.nextToken();

    if (s == "su") users.su(scanner),books.login();
    else if (s == "logout") books.logout(),users.logout();
    else if (s == "register")users.Register(scanner);
    else if (s == "passwd")users.passwd(scanner);
    else if (s == "useradd")users.user_add(scanner);
    else if (s == "delete")users.user_delete(scanner);
    else if (s == "exit" || s == "quit")users.quit();
    else if (s == "show") books.show(scanner, users);
    else if (s == "buy")books.buy(scanner, users);
    else if (s == "select")books.select(scanner, users);
    else if (s == "modify")books.modify(scanner, users);
    else if (s == "import")books.import(scanner, users);
    else {


    }
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    user users;
    book books;
    while (1) {
        try {
            std::string input;
            if (!getline(std::cin, input))return 0;
            processLine(input, users, books);
            if (users.check_quit())return 0;
        } catch (error &msg) {
            std::cout << msg.toString() << std::endl;
        }
    }
}
