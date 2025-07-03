#include "crypteur.h"
#include <QFile>
#include <QByteArray>
#include <vector>
#include <numeric> 
#include <QFileInfo>

// --- Implémentation du chiffrement par flux (inspiré de RC4) ---
// Cet algorithme utilise la clé pour générer un flux d'octets pseudo-aléatoires.
// Chaque octet du fichier est ensuite combiné (XOR) avec un octet de ce flux.
// C'est beaucoup plus sécurisé que de simplement répéter la clé.

// Cette classe interne gère l'état de l'algorithme.
class StreamCipherState {
public:
    StreamCipherState(const QByteArray& key) {
        S.resize(256);
        std::iota(S.begin(), S.end(), 0); 

        int j = 0;
        for (int i = 0; i < 256; ++i) {
            unsigned char key_byte = static_cast<unsigned char>(key.at(i % key.length()));
            j = (j + S[i] + key_byte) % 256;
            std::swap(S[i], S[j]); 
        }
    }

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


CrypteurResult Crypteur::traiterFichier(const QString& fichierEntree, const QString& fichierSortie, const QByteArray& cle) {
    if (cle.isEmpty()) {
        return BadPassword;
    }

    QFile inputFile(fichierEntree);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        return ReadError;
    }

    QFile outputFile(fichierSortie);
    if (!outputFile.open(QIODevice::WriteOnly)) {
        inputFile.close();
        return WriteError;
    }

    // Mode : chiffrement si le nom d'entrée != nom de sortie OU si le contenu n'est pas déjà chiffré
    // Ici, on ne stocke plus l'extension d'origine, on ne touche qu'au contenu
    const QByteArray signature = "CRYPTOK";
    StreamCipherState cipher(cle);
    const qint64 bufferSize = 4096;

    // On regarde si le fichier d'entrée commence déjà par la signature chiffrée
    bool modeChiffrement = true;
    if (QFileInfo(fichierEntree) == QFileInfo(fichierSortie)) {
        // Si on chiffre sur place, on détecte le mode par le contenu
        QByteArray sigTest = inputFile.peek(signature.size());
        StreamCipherState cipherTest(cle);
        QByteArray sig = sigTest;
        for (int i = 0; i < sig.size(); ++i)
            sig[i] = sig[i] ^ cipherTest.getNextKeystreamByte();
        if (sig == signature) modeChiffrement = false;
    } else if (QFileInfo(fichierSortie).suffix().toLower() == "enc") {
        modeChiffrement = true;
    } else if (QFileInfo(fichierEntree).suffix().toLower() == "enc") {
        modeChiffrement = false;
    }

    if (modeChiffrement) {
        // Chiffrement : écrire la signature chiffrée en premier
        QByteArray sig = signature;
        for (int i = 0; i < sig.size(); ++i)
            sig[i] = sig[i] ^ cipher.getNextKeystreamByte();
        if (outputFile.write(sig) != sig.size()) {
            inputFile.close(); outputFile.close(); return WriteError;
        }
    } else {
        // Déchiffrement : lire et vérifier la signature
        QByteArray sig = inputFile.read(signature.size());
        for (int i = 0; i < sig.size(); ++i)
            sig[i] = sig[i] ^ cipher.getNextKeystreamByte();
        if (sig != signature) {
            inputFile.close(); outputFile.close(); return BadPassword;
        }
    }

    while (!inputFile.atEnd()) {
        QByteArray buffer = inputFile.read(bufferSize);
        for (int i = 0; i < buffer.size(); ++i) {
            char keystreamByte = cipher.getNextKeystreamByte();
            buffer[i] = buffer[i] ^ keystreamByte;
        }
        if (outputFile.write(buffer) != buffer.size()) {
            inputFile.close(); outputFile.close(); return WriteError;
        }
    }

    inputFile.close();
    outputFile.close();
    return Success;
}
