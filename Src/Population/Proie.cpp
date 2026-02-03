/**
 * @file Proie.cpp
 * @brief Implémentation de la classe Proie
 */

#include "Proie.h"
#include "Animal.h"
#include "Predateur.h"
#include "Plante.h"
#include <cmath>
#include <cstdlib>
#include <vector>

/**
 * @brief Constructeur initialisant position et vitesse aléatoire
 */
Proie::Proie(float x, float y, float largeur, float hauteur)
    : Animal(x, y, largeur, hauteur)
{
    mTempsDepuisReproduction = 0.0f;
    mMenaceDetectee = nullptr;
    mPlanteDetectee = nullptr;
    mVx = ((rand() % 200) - 100) * 0.5f;
    mVy = ((rand() % 200) - 100) * 0.5f;
}

/**
 * @brief Change aléatoirement de direction (8 directions possibles)
 */
void Proie::Errer()
{
    int randomValue = rand() % 100;
    
    if (randomValue < 5)
    {
        int direction = rand() % 8;

        switch (direction)
        {
            case 0:  /* Bas */
                mVx = 0;
                mVy = VITESSE_BASE;
                break;
            case 1:  /* Haut */
                mVx = 0;
                mVy = -VITESSE_BASE;
                break;
            case 2:  /* Droite */
                mVx = VITESSE_BASE;
                mVy = 0;
                break;
            case 3:  /* Gauche */
                mVx = -VITESSE_BASE;
                mVy = 0;
                break;
            case 4:  /* Bas-droite */
                mVx = VITESSE_BASE;
                mVy = VITESSE_BASE;
                break;
            case 5:  /* Haut-gauche */
                mVx = -VITESSE_BASE;
                mVy = -VITESSE_BASE;
                break;
            case 6:  /* Bas-gauche */
                mVx = -VITESSE_BASE;
                mVy = VITESSE_BASE;
                break;
            case 7:  /* Haut-droite */
                mVx = VITESSE_BASE;
                mVy = -VITESSE_BASE;
                break;
        }
    }
}

/**
 * @brief Vérifie énergie et temps depuis dernière reproduction
 */
bool Proie::PeutSeReproduire() const
{
    return (mEnergie > SEUIL_ENERGIE_REPRODUCTION 
            && mTempsDepuisReproduction > DELAI_REPRODUCTION);
}

/**
 * @brief Renvoie la quantité d'energie necessaire à la reproduction
 */
float Proie::GetSeuil() const {
    return SEUIL_ENERGIE_REPRODUCTION;
}

/**
 * @brief Gère la perte d'énergie métabolique
 * @param deltaTime Temps écoulé (secondes)
 */
void Proie::Metabolisme(float deltaTime)
{
    float vitesse;

    /* Métabolisme de base */
    PerdreEnergie(0.1f * deltaTime);

    /* Coût du déplacement */
    vitesse = sqrt(mVx * mVx + mVy * mVy);
    PerdreEnergie(vitesse * 0.01f * deltaTime);
}

/**
 * @brief Trouve et cible le prédateur vivant le plus proche
 */
void Proie::Detecter(const std::vector<Proie*>& proies,
                    const std::vector<Predateur*>& predateurs)
{
    float distMin = 9999.0f;
    mMenaceDetectee = nullptr;
    
    for (auto* pred : predateurs)
    {
        if (!pred->EstVivant()) continue;
        
        float dx = pred->GetX() - this->GetX();
        float dy = pred->GetY() - this->GetY();
        float distanceCarre = dx * dx + dy * dy;
        float rayonCarre = RAYON_DETECTION_PREDATEUR * RAYON_DETECTION_PREDATEUR;
        
        if (distanceCarre < rayonCarre && distanceCarre < distMin)
        {
            distMin = distanceCarre;
            mMenaceDetectee = pred;
        }
    }
}

/**
 * @brief Ajuste vitesse pour s'éloigner du prédateur
 */
void Proie::Fuir()
{
    float dx = mMenaceDetectee->GetX() - this->GetX();
    float dy = mMenaceDetectee->GetY() - this->GetY();
    float distance = sqrt(dx * dx + dy * dy);
    
    if (distance > 0.01f)
    {
        /* Direction opposée au prédateur */
        mVx = -(dx / distance) * VITESSE_BASE;
        mVy = -(dy / distance) * VITESSE_BASE;
    }
}

/**
 * @brief Orchestre fuite, alimentation ou errance selon situation
 */
void Proie::Comportement(const std::vector<Proie*>& proies,
                        const std::vector<Predateur*>& predateurs,
                        const std::vector<Plante*>& plantes)
{
    Detecter(proies, predateurs);
    
    if (mMenaceDetectee)
    {
        Fuir();
    }
    else if (mPlanteDetectee)
    {
        ChercherPlante();
        SeNourrir();
    }
    else
    {
        Errer();
        DetecterPlante(plantes);
    }
}

/**
 * @brief Ajuste vitesse pour se diriger vers la plante cible
 */
void Proie::ChercherPlante()
{
    float dx = mPlanteDetectee->GetX() - this->GetX();
    float dy = mPlanteDetectee->GetY() - this->GetY();
    float distance = sqrt(dx * dx + dy * dy);
    
    if (distance > 0.01f)
    {
        mVx = (dx / distance) * VITESSE_BASE;
        mVy = (dy / distance) * VITESSE_BASE;
    }
}

/**
 * @brief Trouve et cible la plante disponible la plus proche
 */
void Proie::DetecterPlante(const std::vector<Plante*>& plantes)
{
    float distMin = 9999.0f;
    mPlanteDetectee = nullptr;
    
    for (auto* plant : plantes)
    {
        if (!plant->EstDisponible()) continue;
        
        float dx = plant->GetX() - this->GetX();
        float dy = plant->GetY() - this->GetY();
        float distanceCarre = dx * dx + dy * dy;
        float rayonCarre = RAYON_DETECTION_PLANTE * RAYON_DETECTION_PLANTE;
        
        if (distanceCarre < rayonCarre && distanceCarre < distMin)
        {
            distMin = distanceCarre;
            mPlanteDetectee = plant;
        }
    }
}

/**
 * @brief Consomme plante si à portée
 */
void Proie::SeNourrir()
{
    if (!mPlanteDetectee) return;
    if (!mPlanteDetectee->EstDisponible())
    {
        mPlanteDetectee = nullptr;
        return;
    }
    
    float dx = mPlanteDetectee->GetX() - this->GetX();
    float dy = mPlanteDetectee->GetY() - this->GetY();
    float distance = sqrt(dx * dx + dy * dy);
    
    if (distance <= RAYON_ATTAQUE)
    {
        mPlanteDetectee->Consommer();
        this->GagnerEnergie(ENERGIE_GAGNE_PAR_PLANTE);
        mPlanteDetectee = nullptr;
    }
}

/**
 * @brief Déplace l'animal selon sa vitesse et gère les rebonds
 * @param deltaTime Temps écoulé depuis le dernier frame (secondes)
 */
void Proie::Deplacer(float deltaTime)
{
    /* Mise à jour de la position */
    mX += mVx * deltaTime;
    mY += mVy * deltaTime;

    /* Gestion des rebonds sur bords horizontaux */
    if (mX < 30.0f || mX > mLargeurMonde - 30.0f)
    {
        mVx = -mVx;

        /* Correction pour éviter blocage hors limites */
        if (mX < 30.0f)
            mX = 30.0f;

        if (mX > mLargeurMonde - 30.0f)
            mX = mLargeurMonde - 30.0f;
    }

    /* Gestion des rebonds sur bords verticaux */
    if (mY < 30.0f || mY > mHauteurMonde - 30.0f)
    {
        mVy = -mVy;

        if (mY < 30.0f)
            mY = 30.0f;

        if (mY > mHauteurMonde - 30.0f)
            mY = mHauteurMonde - 30.0f;
    }
}

/**
 * @brief Destructeur
 */
Proie::~Proie()
{
}