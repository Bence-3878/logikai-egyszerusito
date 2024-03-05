//
// Created by bence on 2024.03.05..
//
#include "elo.h"

void rW(std::string& s) {
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
}
void sa(const std::string &s){
    int z=0;
    for (int i = 0; i < s.length(); ++i) {
        if( !(('A'<=s[i] && s[i]<='Z') || ('a'<=s[i] && s[i]<='z') ||
              ('0'<=s[i] && s[i]<='9') || s[i]=='!' || s[i]=='*' || s[i]=='+' || s[i]=='_' ||
              s[i]=='(' || s[i]==')' || s[i]=='[' || s[i]==']'))
            throw SyntaxError("ismeretlel karakter: "+ s[i]);
        if(s[i]=='(' || s[i]=='[') z++;
        if(s[i]==')' || s[i]==']') z--;
        if(z<0)
            throw SyntaxError("hiányzik egy '('");
    }
    if(z)
        throw SyntaxError("hiányzik " + std::to_string(z) + " zárójel");
}
void lep(){
    for (int i = n-1 ,c = 1; i >= 0 ; i--){
        int t = ve[i] && c;
        ve[i]^=c;
        c=t;
    }
}

void init(std::ifstream &in){
    std::string s;
    in >> n;

    it = new char[static_cast<int>(pow(2,n))];
    for (int i = 0; i < static_cast<int>(pow(2,n)); ++i) it[i]=0;

    ve = new char[n];
    for (int i = 0; i < n; ++i) ve[i]=0;

    for (int i = 0; i < n; ++i) {
        in >> s;
        vn[s]=i;
    }
}
std::string be(std::ifstream &in){
    std::string uj,s;
    getline(in,s);
    while (getline(in,uj)) s += uj;
    return s;
}
void itt(std::string &s){
    rW(s);
    try {
        sa(s);
    }
    catch (const SyntaxError &e) {
        throw e;
    }
    muvelet elso(s);
    for (int i = 0; i < static_cast<int>(pow(2, n)); ++i) {
        it[i]=elso.ertek();
        lep();
    }
}

