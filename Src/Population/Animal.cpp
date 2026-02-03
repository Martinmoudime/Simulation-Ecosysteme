/**
 * @file Animal.cpp
 * @brief Implémentation des méthodes de la classe Animal
 */

#include "Animal.h"
#include <cmath>

/**
 * @brief Constructeur de la classe Animal
 * @param posX Position initiale en X
 * @param posY Position initiale en Y
 * @param largeur Largeur du monde de simulation
 * @param hauteur Hauteur du monde de simulation
 */
Animal::Animal(float posX, float posY, float largeur, float hauteur)
    : mX(posX)
    , mY(posY)
    , mVx(0.0f)
    , mVy(0.0f)
    , mEnergie(100.0f)
    , mVivant(true)
    , mLargeurMonde(largeur)
    , mHauteurMonde(hauteur)
    , mTempsDepuisReproduction(0.0f)
{
    /* Initialisation via liste d'initialisation */
}

/**
 * @brief Réduit l'énergie de l'animal
 * @param quantite Quantité d'énergie à soustraire
 */
void Animal::PerdreEnergie(float quantite)
{
    mEnergie -= quantite;

    /* Mort si énergie épuisée */
    if (mEnergie <= 0.0f)
    {
        mEnergie = 0.0f;
        mVivant = false;
    }
}

/**
 * @brief Augmente l'énergie de l'animal
 * @param quantite Quantité d'énergie à ajouter
 */
void Animal::GagnerEnergie(float quantite)
{
    mEnergie += quantite;

    /* Plafonner à 100 */
    if (mEnergie > 100.0f)
        mEnergie = 100.0f;
}

/**
 * @brief Incrémente le temps écoulé depuis dernière reproduction
 * @param deltaTime Temps écoulé depuis le dernier frame (secondes)
 */
void Animal::IncrementerTempsReproduction(float deltaTime)
{
    mTempsDepuisReproduction += deltaTime;
}

/**
 * @brief Réinitialise le compteur de reproduction
 */
void Animal::ReinitialiserReproduction()
{
    mTempsDepuisReproduction = 0.0f;
}

/**
 * @brief Récupère la position horizontale
 * @return Position X actuelle
 */
float Animal::GetX() const
{
    return mX;
}

/**
 * @brief Récupère la position verticale
 * @return Position Y actuelle
 */
float Animal::GetY() const
{
    return mY;
}

/**
 * @brief Vérifie si l'animal est vivant
 * @return true si vivant, false sinon
 */
bool Animal::EstVivant() const
{
    return mVivant;
}

/**
 * @brief Récupère le niveau d'énergie
 * @return Énergie actuelle (0-100)
 */
float Animal::GetEnergie() const
{
    return mEnergie;
}

/**
 * @brief Recupère la direction du déplqcement
 * @return Vitesse de déplacement
 */
float Animal::GetDirection()
{
    return mVx;
}

/**
 * @brief Destructeur de la classe Animal
 */
Animal::~Animal()
{
}

