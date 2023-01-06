#ifndef SRC_user_account_H
#define SRC_user_account_H

#include <iostream>
#include <vector>
#include <string.h>
#include "Token_scanner.h"
#include "error.h"

using std::string,std::vector;

class user_account {
public:
    char ID[32];
    char Passwd[32];
    char name[32];
    int privilege;

    user_account() { privilege = -1; }

    user_account(const char *_ID, const char *_Passwd, const int _privilege, const char *_name) {
        strcpy(ID, _ID);
        strcpy(Passwd, _Passwd);
        privilege = _privilege;
        strcpy(name, _name);
    }

    user_account &operator=(const user_account &obj) {
        strcpy(ID, obj.ID);
        strcpy(Passwd, obj.Passwd);
        privilege = obj.privilege;
        strcpy(name, obj.name);
        return *this;
    }

    friend bool operator<(const user_account &A, const user_account &B) { return strcmp(A.ID, B.ID) < 0; }

    friend bool operator>(const user_account &A, const user_account &B) { return strcmp(A.ID, B.ID) > 0; }

    friend bool operator==(const user_account &A, const user_account &B) { return strcmp(A.ID, B.ID) == 0; }

    friend bool operator>=(const user_account &A, const user_account &B) { return strcmp(A.ID, B.ID) >= 0; }

    friend bool operator<=(const user_account &A, const user_account &B) { return strcmp(A.ID, B.ID) <= 0; }
};
class user
{
public:
    database<user_account> users_block;
    std::vector<user_account> login_stack; //登录栈
    bool exit;
    user(){
        exit=0;
        bool flag=users_block.setfile("user_account");
        if(!flag){
            user_account temp("root","sjtu",7,"");
            char tmp[]="root";
            users_block.insert(tmp,temp);
        }
    }
    void quit(){exit=1;}
    bool check_quit(){return exit;}
    void su(Tokenscanner &scanner);
    void logout();
    void Register(Tokenscanner &scanner);
    void passwd(Tokenscanner &scanner);
    void user_add(Tokenscanner &scanner);
    void user_delete(Tokenscanner &scanner);
};
#endif //SRC_user_account_H
