/**
 * @file Predateur.cpp
 * @brief Implémentation de la classe Predateur
 */

#include "Predateur.h"
#include "Animal.h"
#include "Proie.h"
#include <cmath>
#include <cstdlib>
#include <vector>

/**
 * @brief Constructeur initialisant position et vitesse aléatoire
 */
Predateur::Predateur(float x, float y, float largeur, float hauteur)
    : Animal(x, y, largeur, hauteur)
{
    mTempsDepuisReproduction = 0.0f;
    mProieDetectee = nullptr;
    mVx = ((rand() % 200) - 100) * 0.5f;
    mVy = ((rand() % 200) - 100) * 0.5f;
}

/**
 * @brief Change aléatoirement de direction (8 directions possibles)
 */
void Predateur::Errer()
{
    int randomValue = rand() % 100;
    
    if (randomValue < 10)
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
 * @brief Renvoie la quantité d'energie necessaire à la reproduction
 */
float Predateur::GetSeuil() const {
    return SEUIL_ENERGIE_REPRODUCTION;
}

/**
 * @brief Vérifie énergie et temps depuis dernière reproduction
 */
bool Predateur::PeutSeReproduire() const
{
    return (mEnergie > SEUIL_ENERGIE_REPRODUCTION 
            && mTempsDepuisReproduction > DELAI_REPRODUCTION);
}

/**
 * @brief Trouve et cible la proie vivante la plus proche
 */
void Predateur::Detecter(const std::vector<Proie*>& proies,
                        const std::vector<Predateur*>& predateurs)
{
    float distMin = 9999.0f;
    mProieDetectee = nullptr;
    
    for (auto* proie : proies)
    {
        if (!proie->EstVivant()) continue;
        
        float dx = proie->GetX() - this->GetX();
        float dy = proie->GetY() - this->GetY();
        float distanceCarre = dx * dx + dy * dy;
        float rayonCarre = RAYON_DETECTION_PROIE * RAYON_DETECTION_PROIE;
        
        if (distanceCarre < rayonCarre && distanceCarre < distMin)
        {
            distMin = distanceCarre;
            mProieDetectee = proie;
        }
    }
}

/**
 * @brief Ajuste vitesse pour se diriger vers la proie cible
 */
void Predateur::Chasser()
{
    float dx = mProieDetectee->GetX() - this->GetX();
    float dy = mProieDetectee->GetY() - this->GetY();
    float distance = sqrt(dx * dx + dy * dy);
    
    if (distance > 0.01f)
    {
        mVx = (dx / distance) * VITESSE_BASE;
        mVy = (dy / distance) * VITESSE_BASE;
    }
}

/**
 * @brief Orchestre détection, chasse et alimentation
 */
void Predateur::Comportement(const std::vector<Proie*>& proies,
                            const std::vector<Predateur*>& predateurs,
                            const std::vector<Plante*>& plantes)
{
    Detecter(proies, predateurs);
    
    if (mProieDetectee)
    {
        Chasser();
        SeNourrir();
    }
    else
    {
        Errer();
    }
}

/**
 * @brief Consomme proie si à portée d'attaque
 */
void Predateur::SeNourrir()
{
    if (!mProieDetectee) return;
    if (!mProieDetectee->EstVivant())
    {
        mProieDetectee = nullptr;
        return;
    }
    
    float dx = mProieDetectee->GetX() - this->GetX();
    float dy = mProieDetectee->GetY() - this->GetY();
    float distance = sqrt(dx * dx + dy * dy);
    
    if (distance <= RAYON_ATTAQUE)
    {
        mProieDetectee->PerdreEnergie(100.0f);
        this->GagnerEnergie(ENERIE_GAGNE_PAR_PROIE);
        mProieDetectee = nullptr;
    }
}

/**
 * @brief Perte d'énergie due au métabolisme et déplacement
 */
void Predateur::Metabolisme(float deltaTime)
{
    /* Métabolisme élevé du prédateur */
    PerdreEnergie(0.35f * deltaTime);
    
    /* Coût du mouvement */
    float vitesse = sqrt(mVx * mVx + mVy * mVy);
    PerdreEnergie(vitesse * 0.05f * deltaTime);
}

/**
 * @brief Déplace l'animal selon sa vitesse et gère les rebonds
 * @param deltaTime Temps écoulé depuis le dernier frame (secondes)
 */
void Predateur::Deplacer(float deltaTime)
{
    /* Mise à jour de la position */
    mX += mVx * deltaTime;
    mY += mVy * deltaTime;

    /* Gestion des rebonds sur bords horizontaux */
    if (mX < 45.0f || mX > mLargeurMonde - 45.0f)
    {
        mVx = -mVx;

        /* Correction pour éviter blocage hors limites */
        if (mX < 45.0f)
            mX = 45.0f;

        if (mX > mLargeurMonde - 45.0f)
            mX = mLargeurMonde - 45.0f;
    }

    /* Gestion des rebonds sur bords verticaux */
    if (mY < 45.0f || mY > mHauteurMonde - 45.0f)
    {
        mVy = -mVy;

        if (mY < 45.0f)
            mY = 45.0f;

        if (mY > mHauteurMonde - 45.0f)
            mY = mHauteurMonde - 45.0f;
    }
}

/**
 * @brief Destructeur
 */
Predateur::~Predateur()
{
}