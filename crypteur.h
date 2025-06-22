#ifndef CRYPTEUR_H
#define CRYPTEUR_H

#include <string>

class Crypteur {
public:
    static bool traiterFichier(const std::string& fichierEntree, const std::string& fichierSortie, const std::string& cle);
};

#endif // CRYPTEUR_H
