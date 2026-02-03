/**
 * @file Plante.h
 * @brief Classe représentant une ressource végétale
 */

#ifndef PLANTE_H
#define PLANTE_H

/**
 * @class Plante
 * @brief Ressource immobile consommable par les proies
 */
class Plante
{
private:
    float mX;            /**< Position horizontale */
    float mY;            /**< Position verticale */
    bool mDisponible;    /**< État de disponibilité */
    
public:
    /**
     * @brief Constructeur
     * @param x Position horizontale initiale
     * @param y Position verticale initiale
     */
    Plante(float x, float y);
    
    /**
     * @brief Destructeur
     */
    ~Plante();
    
    /**
     * @brief Récupère position X
     * @return Position horizontale
     */
    float GetX() const;
    
    /**
     * @brief Récupère position Y
     * @return Position verticale
     */
    float GetY() const;
    
    /**
     * @brief Vérifie si plante peut être consommée
     * @return true si disponible, false sinon
     */
    bool EstDisponible() const;
    
    /**
     * @brief Marque la plante comme consommée
     */
    void Consommer();
};

#endif /* PLANTE_H */