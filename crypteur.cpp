#include "crypteur.h"
#include <fstream>
#include <vector>

bool Crypteur::traiterFichier(const std::string& fichierEntree, const std::string& fichierSortie, const std::string& cle) {
    std::ifstream in(fichierEntree, std::ios::binary);
    if (!in) {
        return false;
    }

    std::ofstream out(fichierSortie, std::ios::binary);
    if (!out) {
        return false;
    }

    std::vector<char> buffer(std::istreambuf_iterator<char>(in), {});
    
    for (size_t i = 0; i < buffer.size(); ++i) {
        buffer[i] ^= cle[i % cle.length()];
    }

    out.write(buffer.data(), buffer.size());
    return true;
}
