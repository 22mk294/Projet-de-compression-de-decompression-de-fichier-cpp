#include "crypteur.h"
#include <fstream>
#include <vector>

// La fonction de chiffrement/déchiffrement a été améliorée pour être plus robuste et efficace.
// Elle traite maintenant les fichiers par blocs pour éviter de charger des fichiers volumineux en mémoire,
// et elle gère correctement le cas où la clé est vide.

bool Crypteur::traiterFichier(const std::string& fichierEntree, const std::string& fichierSortie, const std::string& cle) {
    // 1. Vérifier si la clé est vide. Le chiffrement est impossible sans clé.
    if (cle.empty()) {
        return false;
    }

    // 2. Ouvrir les fichiers en mode binaire.
    std::ifstream in(fichierEntree, std::ios::binary);
    if (!in) {
        // Impossible d'ouvrir le fichier d'entrée
        return false;
    }

    std::ofstream out(fichierSortie, std::ios::binary);
    if (!out) {
        // Impossible de créer le fichier de sortie
        return false;
    }

    // 3. Traiter le fichier par blocs pour être efficace avec la mémoire.
    const size_t bufferSize = 4096; // Traiter par blocs de 4KB
    char buffer[bufferSize];
    size_t keyIndex = 0;

    while (in.read(buffer, sizeof(buffer))) {
        size_t bytesRead = in.gcount();
        for (size_t i = 0; i < bytesRead; ++i) {
            buffer[i] ^= cle[keyIndex];
            keyIndex = (keyIndex + 1) % cle.length();
        }
        out.write(buffer, bytesRead);
    }

    // Gérer le dernier bloc qui peut être plus petit que bufferSize
    size_t bytesRead = in.gcount();
    if (bytesRead > 0) {
        for (size_t i = 0; i < bytesRead; ++i) {
            buffer[i] ^= cle[keyIndex];
            keyIndex = (keyIndex + 1) % cle.length();
        }
        out.write(buffer, bytesRead);
    }

    // 4. S'assurer que tout s'est bien passé
    return in.eof() && out.good();
}
