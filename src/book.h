#ifndef SRC_BOOK_H
#define SRC_BOOK_H
#include <iostream>
#include <vector>
#include <string>
#include "Token_scanner.h"
#include "user.h"
#include "error.h"
#include "database.h"
class book_inf{
public:
    char ISBN[21];
    char bookname[61];
    char author[61];
    char keyword[61];
    int store;
    double price;
    book_inf() = default;

    book_inf(const char* ISBN_,const char* bookname_,const char* author_,const char* keyword_){
        strcpy(ISBN,ISBN_);
        strcpy(bookname,bookname_);
        strcpy(author,author_);
        strcpy(keyword,keyword_);
        store=0;
        price=0;
    }

    book_inf &operator= (const book_inf &obj){
        strcpy(ISBN,obj.ISBN);
        strcpy(bookname,obj.bookname);
        strcpy(author,obj.author);
        strcpy(keyword,obj.keyword);
        store=obj.store;
        price=obj.price;
        return *this;
    }

    friend bool operator<(const book_inf &A,const book_inf &B){return strcmp(A.ISBN,B.ISBN)<0;}
    friend bool operator>(const book_inf &A,const book_inf &B){return strcmp(A.ISBN,B.ISBN)>0;}
    friend bool operator<=(const book_inf &A,const book_inf &B){return strcmp(A.ISBN,B.ISBN)<=0;}
    friend bool operator>=(const book_inf &A,const book_inf &B){return strcmp(A.ISBN,B.ISBN)>=0;}
    friend bool operator==(const book_inf &A,const book_inf &B){return strcmp(A.ISBN,B.ISBN)==0;}

};
class book
{
public:
    database<book_inf> books;
    book() {books.setfile("book_data");}
    std::vector<string> book_stack;
    void login();
    void logout();
    void show(Tokenscanner &scanner,user &users);
    void buy(Tokenscanner &scanner,user &users);
    void select(Tokenscanner &scanner,user &users);
    void modify(Tokenscanner &scanner,user &users);
    void import(Tokenscanner &scanner,user &users);
};

#endif //SRC_BOOK_H
