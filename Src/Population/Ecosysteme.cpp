/**
 * @file Ecosysteme.cpp
 * @brief Implémentation de la classe Ecosysteme
 */

#include "Ecosysteme.h"
#include "Proie.h"
#include "Predateur.h"
#include "Plante.h"
#include <cstdlib>

/**
 * @brief Constructeur créant populations aléatoirement
 */
Ecosysteme::Ecosysteme(int nbreProies, int nbrePredateurs, int nbrePlantes,
                       float largeur, float hauteur)
    : mLargeur(largeur)
    , mHauteur(hauteur)
    , mNbreProies(nbreProies)
    , mNbrePredateurs(nbrePredateurs)
    , mNbrePlantes(nbrePlantes)
    , mTempsDepuisCreationPlante(0.0f)
{

    const float MARGE = 35.0f;  /* Marge indisponible  representant les bords */

    /* Créer proies */
    for (int i = 0; i < nbreProies; i++)
    {
        float x = static_cast<float>(rand() % static_cast<int>(largeur));
        float y = static_cast<float>(rand() % static_cast<int>(hauteur));
        mProies.push_back(new Proie(x, y, largeur, hauteur));
    }
    
    /* Créer prédateurs */
    for (int i = 0; i < nbrePredateurs; i++)
    {
        float x = static_cast<float>(rand() % static_cast<int>(largeur));
        float y = static_cast<float>(rand() % static_cast<int>(hauteur));
        mPredateurs.push_back(new Predateur(x, y, largeur, hauteur));
    }
    
    /* Créer plantes */
    for (int i = 0; i < nbrePlantes; i++)
    {
        float x = MARGE + (rand() % static_cast<int>(largeur - 2 * MARGE));
        float y = MARGE + (rand() % static_cast<int>(hauteur - 2 * MARGE));
        mPlantes.push_back(new Plante(x, y));
    }
}

/**
 * @brief Destructeur libérant toute la mémoire
 */
Ecosysteme::~Ecosysteme()
{
    for (auto* proie : mProies)
        delete proie;
    
    for (auto* pred : mPredateurs)
        delete pred;
    
    for (auto* plante : mPlantes)
        delete plante;
}

/**
 * @brief Retourne vecteur des proies
 */
const std::vector<Proie*>& Ecosysteme::GetProies() const
{
    return mProies;
}

/**
 * @brief Retourne vecteur des prédateurs
 */
const std::vector<Predateur*>& Ecosysteme::GetPredateurs() const
{
    return mPredateurs;
}

/**
 * @brief Retourne vecteur des plantes
 */
const std::vector<Plante*>& Ecosysteme::GetPlantes() const
{
    return mPlantes;
}

/**
 * @brief Compte proies vivantes
 */
int Ecosysteme::GetNombreProies() const
{
    return mProies.size();
}

/**
 * @brief Compte prédateurs vivants
 */
int Ecosysteme::GetNombrePredateurs() const
{
    return mPredateurs.size();
}

/**
 * @brief Compte le temps qui separe l'apparission de 2 plantes
 */
int Ecosysteme::GetDelaiPlantes() const
{
    return INTERVALLE_CREATION_PLANTE;
}

/**
 * @brief Compte plantes disponibles
 */
int Ecosysteme::GetNombrePlantes() const
{
    int count = 0;
    for (auto* plante : mPlantes)
    {
        if (plante->EstDisponible())
            count++;
    }
    return count;
}

void Ecosysteme::SupprimerMorts() {
    for (int i = mPredateurs.size() - 1; i >= 0; i--) {
        if (!mPredateurs[i]->EstVivant())
        {
            delete mPredateurs[i];
            mPredateurs.erase(mPredateurs.begin() + i);
        }
        
    }

    for (int i = mProies.size() - 1; i >= 0; i--) {
        if (!mProies[i]->EstVivant())
        {
            delete mProies[i];
            mProies.erase(mProies.begin() + i);
        }
        
    }
}

void Ecosysteme::Reproduction() {    
    std::vector<Predateur*> nouveauxPredateurs;  // Liste temporaire
    
    for (auto* pred : mPredateurs)
    {
        if (pred->PeutSeReproduire() && (rand() % 100) > 75)
        {
            pred->PerdreEnergie(pred->GetSeuil());
            pred->ReinitialiserReproduction();
            nouveauxPredateurs.push_back(
                new Predateur(pred->GetX(), pred->GetY(), mLargeur, mHauteur)
            );
        }
    }
    
    // Ajouter tous les bébés APRÈS la boucle
    for (auto* bebe : nouveauxPredateurs)
    {
        mPredateurs.push_back(bebe);
    }

        std::vector<Proie*> nouvellesProies;  // Liste temporaire
    
    for (auto* proi : mProies)
    {
        if (proi->PeutSeReproduire() && (rand() % 100) > 75)
        {
            proi->PerdreEnergie(proi->GetSeuil());
            proi->ReinitialiserReproduction();
            nouvellesProies.push_back(
                new Proie(proi->GetX(), proi->GetY(), mLargeur, mHauteur)
            );
        }
    }
    
    // Ajouter tous les bébés APRÈS la boucle
    for (auto* bebe : nouvellesProies)
    {
        mProies.push_back(bebe);
    }
}

/**
 * @brief Met à jour tout l'écosystème pour un frame
 * @param deltaTime Temps écoulé depuis le dernier frame (secondes)
 */
void Ecosysteme::Update(float deltaTime)
{
    /* Comportement et déplacement des proies */
    for (auto* proie : mProies)
    {
        proie->Comportement(mProies, mPredateurs, mPlantes);
        proie->Deplacer(deltaTime);
        proie->Metabolisme(deltaTime);
        proie->IncrementerTempsReproduction(deltaTime);
    }

    /* Comportement et déplacement des prédateurs */
    for (auto* pred : mPredateurs)
    {
        pred->Comportement(mProies, mPredateurs, mPlantes);
        pred->Deplacer(deltaTime);
        pred->Metabolisme(deltaTime);
        pred->IncrementerTempsReproduction(deltaTime);
    }

    /* Régénération des plantes toutes les 5 secondes */
    mTempsDepuisCreationPlante += deltaTime;
    
    if (mTempsDepuisCreationPlante >= INTERVALLE_CREATION_PLANTE)
    {
        mTempsDepuisCreationPlante = 0.0f;  /* Reset timer */

        const float MARGE = 30.0f;          /* Marge indisponible  representant les bords */
        
        /* Ajouter une plante si sous le maximum */
        if (static_cast<int>(mPlantes.size()) < MAX_PLANTES)
        {
            float x = MARGE + (rand() % static_cast<int>(mLargeur - 2 * MARGE));
            float y = MARGE + (rand() % static_cast<int>(mHauteur - 2 * MARGE));
            mPlantes.push_back(new Plante(x, y));
        }
    }

    /* Détecter et compter nouvelles plantes consommées */
    for (auto* plante : mPlantes)
    {
        if (!plante->EstDisponible())
        {
            /* Vérifier si déjà comptée */
            bool dejaComptee = false;
            for (auto* consommee : mPlantesConsommees)
            {
                if (consommee == plante)
                {
                    dejaComptee = true;
                    break;
                }
            }
            
            /* Ajouter si nouvelle */
            if (!dejaComptee)
            {
                mPlantesConsommees.push_back(plante);
            }
        }
    }

    /* Supprimer les animaux morts */
    SupprimerMorts();

    /* Gérer les reproductions */
    Reproduction();
}

/**
 * @brief Compte le nombre total de plantes consommées
 * @return Nombre de plantes consommées depuis le début
 */
int Ecosysteme::GetTotalPlantesConsommees() const {
    return mPlantesConsommees.size();
}

/**
 * @brief Actualise le temps qui sépare l'apparission de 2 plantes
 * @param Delai de réaparission
 */
void Ecosysteme::SetDelaiPlantes(float delai) {
    INTERVALLE_CREATION_PLANTE = delai;
}
