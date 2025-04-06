#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>

using namespace std;

// Enumération des états possibles d'une case
enum CouleurCase
{
    VIDE,
    ROND,
    CROIX
};

// Définition de la grille de jeu
typedef array<array<CouleurCase, 3>, 3> Grille;

// Classe Morpion
class JeuMorpion
{
private:
    Grille grille; // Grille de jeu

    // Méthode pour placer un coup
    bool placer_coup(size_t ligne, size_t colonne, CouleurCase coup)
    {
        if (ligne >= grille.size() || colonne >= grille[ligne].size())
        {
            cout << "Erreur : case invalide" << endl;
            return false;
        }
        if (grille[ligne][colonne] == VIDE)
        {
            grille[ligne][colonne] = coup;
            return true;
        }
        else
        {
            cout << "Case déjà occupée !" << endl;
            return false;
        }
    }

public:
    // Méthode pour initialiser la grille
    void initialise()
    {
        for (auto &ligne : grille)
        {
            for (auto &Kase : ligne)
            {
                Kase = VIDE;
            }
        }
    }

    // Méthode pour afficher la grille
    void afficherGrille()
    {
        cout << "  0   1   2  \n";
        cout << "-------------\n";
        for (size_t i = 0; i < grille.size(); i++)
        {
            cout << i << "| ";
            for (const auto &Kase : grille[i])
            {
                switch (Kase)
                {
                case VIDE:
                    cout << "  | ";
                    break;
                case ROND:
                    cout << "O | ";
                    break;
                case CROIX:
                    cout << "X | ";
                    break;
                }
            }
            cout << "\n-------------\n";
        }
        cout << endl;
    }

    // Méthode pour placer un ronf
    bool placer_rond(size_t ligne, size_t colonne)
    {
        return placer_coup(ligne, colonne, ROND);
    }

    // Méthode pour placer une croix
    bool placer_croix(size_t ligne, size_t colonne)
    {
        return placer_coup(ligne, colonne, CROIX);
    }

    // Méthode pour vérifier si la grille est pleine
    bool grillePleine()
    {
        for (const auto &ligne : grille)
        {
            for (const auto &Kase : ligne)
            {
                if (Kase == VIDE)
                {
                    return false;
                }
            }
        }
        return true;
    }

    // Méthode pour vérifier s'il y a un gagnant
    CouleurCase verifierGagnant()
    {
        for (int i = 0; i < 3; i++)
        {
            if (grille[i][0] != VIDE && grille[i][0] == grille[i][1] && grille[i][1] == grille[i][2])
            {
                return grille[i][0];
            }
            if (grille[0][i] != VIDE && grille[0][i] == grille[1][i] && grille[1][i] == grille[2][i])
            {
                return grille[0][i];
            }
        }

        if (grille[0][0] != VIDE && grille[0][0] == grille[1][1] && grille[1][1] == grille[2][2])
        {
            return grille[0][0];
        }
        if (grille[0][2] != VIDE && grille[0][2] == grille[1][1] && grille[1][1] == grille[2][0])
        {
            return grille[0][2];
        }
        // Si aucun gagnant, retourner VIDE pour indiquer que le jeu continue
        // ou que la grille est pleine sans gagnant
        return VIDE;
    }

    // Méthode pour vérifier si une case est vide
    bool caseLibre(int x, int y)
    {
        return grille[x][y] == VIDE;
    }
};

// ----------- BOT INTELLIGENT ------------
// Essaie de gagner ou de bloquer le joueur
// Prend le centre ou un coin si possible
// Sinon, joue un coup aléatoire
bool trouve_coup_gagnant(JeuMorpion &jeu, CouleurCase symbole, int &x, int &y)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (jeu.caseLibre(i, j))
            {
                JeuMorpion copie = jeu;
                if (symbole == CROIX)
                    copie.placer_croix(i, j);
                else
                    copie.placer_rond(i, j);
                if (copie.verifierGagnant() == symbole)
                {
                    x = i;
                    y = j;
                    return true;
                }
            }
        }
    }
    return false;
}

void jouer_bot_intelligent(JeuMorpion &jeu)
{
    int x, y;

    // Peut-il gagner ?
    if (trouve_coup_gagnant(jeu, CROIX, x, y))
    {
        jeu.placer_croix(x, y);
        cout << "Le bot joue (victoire) en (" << x << ", " << y << ")\n";
        return;
    }

    // Peut-il bloquer le joueur ?
    if (trouve_coup_gagnant(jeu, ROND, x, y))
    {
        jeu.placer_croix(x, y);
        cout << "Le bot joue (blocage) en (" << x << ", " << y << ")\n";
        return;
    }

    // Prendre le centre si libre
    if (jeu.caseLibre(1, 1))
    {
        jeu.placer_croix(1, 1);
        cout << "Le bot joue (centre) en (1, 1)\n";
        return;
    }

    // Prendre un coin libre
    int coins[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    for (auto &coin : coins)
    {
        if (jeu.caseLibre(coin[0], coin[1]))
        {
            jeu.placer_croix(coin[0], coin[1]);
            cout << "Le bot joue (coin) en (" << coin[0] << ", " << coin[1] << ")\n";
            return;
        }
    }

    // Sinon, coup aléatoire
    do
    {
        x = rand() % 3;
        y = rand() % 3;
    } while (!jeu.placer_croix(x, y));
    cout << "Le bot joue (random) en (" << x << ", " << y << ")\n";
}

// ----------- FIN BOT INTELLIGENT ------------

void jouer_partie(bool vsBot)
{
    int ligne, colonne;
    JeuMorpion jeu;
    CouleurCase gagnant;
    jeu.initialise();
    jeu.afficherGrille();

    while (!jeu.grillePleine())
    {
        bool coupValide;

        // Joueur O
        do
        {
            cout << "Joueur O - Entrez ligne et colonne (0-2) : ";
            cin >> ligne >> colonne;
            coupValide = jeu.placer_rond(ligne, colonne);
        } while (!coupValide);

        jeu.afficherGrille();
        gagnant = jeu.verifierGagnant();
        if (gagnant != VIDE)
            break;
        if (jeu.grillePleine())
            break;

        // Joueur X ou bot
        if (vsBot)
        {
            jouer_bot_intelligent(jeu);
        }
        else
        {
            do
            {
                cout << "Joueur X - Entrez ligne et colonne (0-2) : ";
                cin >> ligne >> colonne;
                coupValide = jeu.placer_croix(ligne, colonne);
            } while (!coupValide);
        }

        // Afficher la grille
        jeu.afficherGrille();
        gagnant = jeu.verifierGagnant();
        if (gagnant != VIDE)
            break;
        if (jeu.grillePleine())
            break;
    }

    // Afficher le résultat
    if (gagnant == ROND)
    {
        cout << "Le joueur O a gagné !" << endl;
    }
    else if (gagnant == CROIX)
    {
        cout << (vsBot ? "Le bot a gagné !" : "Le joueur X a gagné !") << endl;
    }
    else
    {
        cout << "Match nul !" << endl;
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(0))); // Initialiser le générateur de nombres aléatoires
    while (true)
    {
        cout << "Jeu du Morpion" << endl;
        cout << "\n=== MENU ===" << endl;
        cout << "1. Jouer contre un autre joueur" << endl;
        cout << "2. Jouer contre le bot" << endl;
        cout << "3. Quitter" << endl;
        cout << "Choisissez une option : ";

        int choix;
        cin >> choix;

        if (choix == 1)
        {
            jouer_partie(false);
        }
        else if (choix == 2)
        {
            jouer_partie(true);
        }
        else if (choix == 3)
        {
            cout << "Merci d'avoir joué ! À bientôt !" << endl;
            break;
        }
        else
        {
            cout << "Choix invalide, veuillez réessayer." << endl;
        }
        cout << endl; // Ligne vide pour séparer les parties
    }

    return 0;
}