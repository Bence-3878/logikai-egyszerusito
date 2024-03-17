#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

char *ve;
int n;
std::vector<int> kt,dt;
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

class muvelet {
    char m, *lv;
    muvelet *j, *b;
public:
    muvelet(const std::string &s) : j(nullptr), b(nullptr) {
        int z = 0, v = 0;
        m = 0;
        lv = nullptr;
        for (int i = 0; i < s.length(); ++i) {
            char c = s[i];
            if (!z && (s[i] == '+' || s[i] == '*')) {
                if (v) {
                    j = new muvelet(s.substr(1, i - 2));
                    v = 0;
                } else {
                    j = new muvelet(s.substr(0, i));
                }
                m = s[i];
                b = new muvelet(s.substr(i + 1));
                break;
            } else if (!z && s[i] == '!') {
                m = s[i];
                b = new muvelet(s.substr(i + 1));
                break;
            } else if (s[i] == '(' || s[i] == '[') z++, v++;
            else if (s[i] == ')' || s[i] == ']') z--;
        }
        if (!z && v) {
            m = 1;
            j = new muvelet(s.substr(1, s.length() - 2));
        }
        if (!m) lv = ve + vn[s];

    }

    ~muvelet() {
        delete this->j;
        delete this->b;
    }

    int ertek() {
        switch (this->m) {
            case '+':
                return this->j->ertek() || this->b->ertek();
            case '*':
                return this->j->ertek() && this->b->ertek();
            case '!':
                return !this->b->ertek();
            case 1:
                return this->j->ertek();
            case 0:
                return *lv;
        }
        return 1;
    }
};

inline int bs(int m){
    m=abs(m);
    int s=0;
    while (m){
        s+=m%2;
        m/=2;
    }
    return s;
}
class Prim{
    std::vector<int> l;
    int prim;
public:
    Prim(int p){
        prim=0;
        l.push_back(p);
    }
    Prim(int p1,int p2){
        prim=0;
        if(p1<p2) {
            this->l.push_back(p1);
            this->l.push_back(p2);
        } else{
            this->l.push_back(p2);
            this->l.push_back(p1);
        }
    }
    Prim(const std::vector<int> &p1,const std::vector<int> &p2){
        prim=0;
        for (int i = 0,j = 0; j + i < p1.size() + p2.size();) {
            if(p1[i]<p2[j==p2.size()?j-1:j] && i<p1.size())
                this->l.push_back(p1[i++]);

            else if (p1[i==p1.size()?i-1:i]>p2[j] && j<p2.size())
                this->l.push_back(p2[j++]);

            if(i+j+1==p1.size()+p2.size()) {
                if(i<j)
                    this->l.push_back(p1[i++]);

                else
                    this->l.push_back(p2[j++]);
            }

        }
    }

    inline void ha(){
        prim=1;
    }
    Prim operator+(const Prim &p) const{
        Prim uj(,p);

    }
    int operator==(const Prim &p1) const{
        if(bs(p1.l[0] - this->l[0])!=1)
            return 0;
        int b1=bs(p1.l[0]),b2=bs(this->l[0]);
        if(abs(b1-b2)!=1)
            return 0;
        if (!(b1>b2 && p1.l[0] > this->l[0] || b1<b2 && p1.l[0] < this->l[0]))
            return 0;
        for (int i = 0; i < this->l.size(); ++i) {
            if(p1.l[i] - this->l[i] != p1.l[0] - this->l[0])
                return 0;
        }
        return 1;
    }
};

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
        if(elso.ertek())
            dt.push_back(i);
        else
            kt.push_back(i);
        lep();
    }
}

int joe(int p1,int p2){
    int b1=bs(p1),b2=bs(p2);
    return bs(p1-p2)==1 && abs(b1-b2)==1 && (b1>b2 && p1>p2 || b1<b2 && p1<p2);
}
int joe(const Prim &p1,const Prim &p2){
    return p1==p2;
}
std::vector<Prim> init_pt(const std::vector<int> &v){
    std::vector<Prim> t;
    for (int i = 0; i < v.size(); ++i) {
        t.push_back(v[i]);
    }
    return t;
}

std::string qm(const std::vector<int> &v){
    std::vector<std::vector<Prim>> pt= {init_pt(v)};
    for (int k = 0; k < 20; ++k) {
        std::vector<Prim> t={};
        for (int i = 0; i < pt[k].size(); ++i) {
            for (int j = i; j < pt[k].size(); ++j) {
                if (joe(pt[k][i], pt[k][j]));

            }
        }
    }
    return "";
}

int main(int argv,char *arkc[]) {
    std::ifstream in("teszt",std::ios_base::in);
    if (!in.is_open()) {
        std::cerr << "Nem sikerült megnyitni a fájlt." << std::endl;
        return 1;
    }

    init(in);
    std::string s=be(in);
    in.close();

    try {
        itt(s);
    }
    catch (const SyntaxError &e) {
        std::cerr << e.what();
        exit(1);
    }
    std::string d=qm(dt);
    std::string k=qm(kt);


    return 0;
}
