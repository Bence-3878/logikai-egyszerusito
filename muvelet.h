//
// Created by bence on 2024.03.05..
//

#ifndef SZAMJEGYES_MUVELET_H
#define SZAMJEGYES_MUVELET_H


#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>

char *it,*ve;
int n;
std::map<std::string ,int> vn;

class SyntaxError : public std::exception{
private:
    std::string message;

public:
    explicit SyntaxError(const std::string& message) : message(message) {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};

class muvelet{
    char m,*lv;
    muvelet *j,*b;
public:
    muvelet(const std::string &s);
    ~muvelet();
    int ertek();
};



#endif //SZAMJEGYES_MUVELET_H
