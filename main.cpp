#include "muvelet.h"
#include "elo.h"




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


    return 0;
}
