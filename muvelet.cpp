//
// Created by bence on 2024.03.05..
//

#include "muvelet.h"

muvelet::muvelet(const std::string &s)  : j(nullptr), b(nullptr){
    int z=0,v=0;
    m=0;
    lv= nullptr;
    for (int i = 0; i < s.length(); ++i) {
        char c=s[i];
        if (!z && (s[i] == '+' || s[i] == '*')){
            if(v){
                j = new muvelet(s.substr(1, i - 2));
                v=0;
            } else {
                j = new muvelet(s.substr(0, i));
            }
            m = s[i];
            b = new muvelet(s.substr(i + 1));
            break;
        }
        else if(!z && s[i]=='!'){
            m=s[i];
            b=new muvelet(s.substr(i + 1));
            break;
        }
        else if (s[i]=='(' || s[i]=='[') z++,v++;
        else if (s[i]==')' || s[i]==']') z--;
    }
    if (!z&&v) {
        m=1;
        j = new muvelet(s.substr(1, s.length() - 2));
    }
    if(!m) lv = ve + vn[s];

}

muvelet::~muvelet() {
    delete this->j;
    delete this->b;
}

int muvelet::ertek() {
    switch (this->m) {
        case '+':
            return this->j->ertek()||this->b->ertek();
        case '*':
            return this->j->ertek()&&this->b->ertek();
        case '!':
            return !this->b->ertek();
        case 1:
            return this->j->ertek();
        case 0:
            return *lv;
    }
}

