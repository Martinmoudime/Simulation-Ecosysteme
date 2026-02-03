/**
 * @file Plante.cpp
 * @brief Implémentation de la classe Plante
 */

#include "Plante.h"

/**
 * @brief Constructeur initialisant position et disponibilité
 * @param x Position horizontale
 * @param y Position verticale
 */
Plante::Plante(float x, float y)
    : mX(x)
    , mY(y)
    , mDisponible(true)
{
    /* Initialisation via liste d'initialisation */
}

/**
 * @brief Marque la plante comme consommée (indisponible)
 */
void Plante::Consommer()
{
    mDisponible = false;
}

/**
 * @brief Vérifie si la plante est disponible
 * @return true si disponible, false sinon
 */
bool Plante::EstDisponible() const
{
    return mDisponible;
}

/**
 * @brief Récupère la position horizontale
 * @return Position X
 */
float Plante::GetX() const
{
    return mX;
}

/**
 * @brief Récupère la position verticale
 * @return Position Y
 */
float Plante::GetY() const
{
    return mY;
}

/**
 * @brief Destructeur
 */
Plante::~Plante()
{
}