#include "user.h"
#include <cstring>
void user::su(Tokenscanner &scanner) {

    string userid = scanner.nextToken();
    if (!scanner.check_ID(userid)) throw (error("Invalid"));
    string passwd = scanner.nextToken();
    if (scanner.haveMoreTokens()) throw (error("Invalid"));
    char *index_;
    strcpy(index_, userid.c_str());
    if (!users_block.find(index_))throw (error("Invalid"));

    user_account Value = users_block.find_value(index_);
    if (!passwd.empty()) {
        if (!scanner.check_ID(passwd))throw (error("Invalid"));
        if (strcmp(passwd.c_str(), Value.Passwd) == 0) {
            login_stack.push_back(Value);
        } else throw (error("Invalid"));
    } else {
        if (login_stack.empty())throw (error("Invalid"));
        user_account &cur_account = login_stack.back();
        if (cur_account.privilege > Value.privilege) {
            login_stack.push_back(Value);
        } else throw (error("Invalid"));
    }
}

void user::logout() {
    if (login_stack.empty())throw (error("Invalid"));
    login_stack.pop_back();
}

void user::Register(Tokenscanner &scanner) {
    user_account temp;
    string userid = scanner.nextToken();
    if (!scanner.check_ID(userid))throw (error("Invalid"));
    string passwd = scanner.nextToken();
    if (!scanner.check_Passwd(passwd))throw (error("Invalid"));
    string username = scanner.nextToken();
    if (!scanner.check_Username(username))throw (error("Invalid"));
    if (scanner.haveMoreTokens())throw (error("Invalid"));
    char *index_;
    strcpy(index_, userid.c_str());
    if (users_block.find(index_))throw (error("Invalid"));
    strcpy(temp.ID, userid.c_str());
    strcpy(temp.Passwd, passwd.c_str());
    temp.privilege = 1;
    strcpy(temp.name, username.c_str());
    users_block.insert(index_, temp);
}

void user::passwd(Tokenscanner &scanner) {
    if (login_stack.empty())throw (error("Invalid"));
    else if (login_stack.back().privilege == 0)throw (error("Invalid"));
    string userid = scanner.nextToken();
    if (!scanner.check_ID(userid))throw (error("Invalid"));
    string CurrentPassword = scanner.nextToken();
    if (!scanner.check_Passwd(CurrentPassword))throw (error("Invalid"));
    if (!scanner.haveMoreTokens()) {
        user_account &cur_account = login_stack.back();
        if (cur_account.privilege == 7) {
            char index_[32];
            strcpy(index_, userid.c_str());
            if (users_block.find(index_)) {
                user_account Value = users_block.find_value(index_);
                strcpy(Value.Passwd, CurrentPassword.c_str());
                users_block.modify(index_, Value);
                return;
            } else throw (error("Invalid"));
        } else throw (error("Invalid"));
    }
    std::string NewPassword = scanner.nextToken();
    if (!scanner.check_Passwd(NewPassword))throw (error("Invalid"));
    char *index_;
    strcpy(index_, userid.c_str());
    if (users_block.find(index_)) {
        user_account Value = users_block.find_value(index_);
        if (strcmp(Value.Passwd, CurrentPassword.c_str()) == 0) {
            strcpy(Value.Passwd, NewPassword.c_str());
            users_block.modify(index_, Value);
        } else throw (error("Invalid"));
    } else throw (error("Invalid"));
}

void user::user_add(Tokenscanner &scanner) {
    if (login_stack.empty())throw (error("Invalid"));
    else if (login_stack.back().privilege < 3)throw (error("Invalid"));
    string userid = scanner.nextToken();
    if (!scanner.check_ID(userid))throw (error("Invalid"));
    string password = scanner.nextToken();
    if (!scanner.check_Passwd(password))throw (error("Invalid"));
    string privilege_ = scanner.nextToken();
    if (!scanner.check_Privilege(privilege_))throw (error("Invalid"));
    int privilege = privilege_[0] - '0';
    if (privilege >= login_stack.back().privilege)throw (error("Invalid"));
    string username = scanner.nextToken();
    if (!scanner.check_Username(username))throw (error("Invalid"));
    if (scanner.haveMoreTokens())throw (error("Invalid"));
    char index_[31];
    strcpy(index_, userid.c_str());
    if (users_block.find(index_))throw (error("Invalid"));
    user_account temp(userid.c_str(), password.c_str(), privilege, username.c_str());
    users_block.insert(index_, temp);
}

void user::user_delete(Tokenscanner &scanner) {
    if (login_stack.empty())throw (error("Invalid"));
    else if (login_stack.back().privilege != 7)throw (error("Invalid"));
    string userid = scanner.nextToken();
    char *index_;
    strcpy(index_, userid.c_str());
    if (!users_block.find(index_))throw (error("Invalid"));
    user_account Value = users_block.find_value(index_);
    users_block.Delete(index_, Value);
}