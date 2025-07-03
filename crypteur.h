#ifndef CRYPTEUR_H
#define CRYPTEUR_H

// On utilise des déclarations anticipées pour ne pas inclure les en-têtes Qt ici,
// ce qui est une bonne pratique pour accélérer la compilation.
class QString;
class QByteArray;

enum CrypteurResult { Success = 0, WriteError, ReadError, BadPassword };

class Crypteur {
public:
    // La fonction prend maintenant des objets Qt pour une meilleure compatibilité
    static CrypteurResult traiterFichier(const QString& fichierEntree, const QString& fichierSortie, const QByteArray& cle);
};

#endif // CRYPTEUR_H
