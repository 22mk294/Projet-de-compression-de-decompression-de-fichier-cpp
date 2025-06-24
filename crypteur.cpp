#include "crypteur.h"
#include <QFile>
#include <QByteArray>
#include <vector>
#include <numeric> // Requis pour std::iota

// --- Implémentation du chiffrement par flux (inspiré de RC4) ---
// Cet algorithme utilise la clé pour générer un flux d'octets pseudo-aléatoires.
// Chaque octet du fichier est ensuite combiné (XOR) avec un octet de ce flux.
// C'est beaucoup plus sécurisé que de simplement répéter la clé.

// Cette classe interne gère l'état de l'algorithme.
class StreamCipherState {
public:
    // 1. Le "Key-Scheduling Algorithm" (KSA) initialise l'état avec la clé.
    StreamCipherState(const QByteArray& key) {
        S.resize(256);
        std::iota(S.begin(), S.end(), 0); // Initialise le tableau S avec 0, 1, 2, ...

        int j = 0;
        for (int i = 0; i < 256; ++i) {
            unsigned char key_byte = static_cast<unsigned char>(key.at(i % key.length()));
            j = (j + S[i] + key_byte) % 256;
            std::swap(S[i], S[j]); // Mélange le tableau S en utilisant la clé
        }
    }

    // 2. Le "Pseudo-random generation algorithm" (PRGA) génère le prochain octet du flux.
    char getNextKeystreamByte() {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        std::swap(S[i], S[j]);
        return S[(S[i] + S[j]) % 256];
    }

private:
    std::vector<unsigned char> S;
    int i = 0;
    int j = 0;
};


bool Crypteur::traiterFichier(const QString& fichierEntree, const QString& fichierSortie, const QByteArray& cle) {
    if (cle.isEmpty()) {
        return false; // Pas de chiffrement sans clé
    }

    QFile inputFile(fichierEntree);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        return false; // Impossible d'ouvrir le fichier d'entrée
    }

    QFile outputFile(fichierSortie);
    if (!outputFile.open(QIODevice::WriteOnly)) {
        inputFile.close();
        return false; // Impossible de créer le fichier de sortie
    }


    // L'algorithme est symétrique : la même opération est utilisée pour chiffrer et déchiffrer.
    StreamCipherState cipher(cle);

    const qint64 bufferSize = 4096;

    while (!inputFile.atEnd()) {
        // On utilise QByteArray pour lire un bloc du fichier.
        QByteArray buffer = inputFile.read(bufferSize);
        
        // On applique l'opération XOR sur chaque octet du bloc.
        for (int i = 0; i < buffer.size(); ++i) {
            char keystreamByte = cipher.getNextKeystreamByte();
            buffer[i] = buffer[i] ^ keystreamByte;
        }
        
        // On écrit le bloc traité dans le fichier de sortie.
        if (outputFile.write(buffer) != buffer.size()) {
            inputFile.close();
            outputFile.close();
            return false; // Erreur d'écriture
        }
    }

    inputFile.close();
    outputFile.close();

    return true; // Succès
}
