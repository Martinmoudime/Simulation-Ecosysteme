/**
 * @file Animal.h
 * @brief Classe abstraite représentant un animal de l'écosystème
 */

#ifndef ANIMAL_H
#define ANIMAL_H

#include <vector>

class Proie;
class Predateur;
class Plante;

/**
 * @class Animal
 * @brief Classe de base pour tous les animaux (proies et prédateurs)
 */
class Animal
{
protected:
    float mX;                        /**< Position horizontale dans le monde */
    float mY;                        /**< Position verticale dans le monde */
    float mVx;                       /**< Vitesse horizontale (pixels/seconde) */
    float mVy;                       /**< Vitesse verticale (pixels/seconde) */
    float mEnergie;                  /**< Niveau d'énergie actuel (0-100) */
    bool mVivant;                    /**< État vital de l'animal */
    float mLargeurMonde;             /**< Largeur de la zone de simulation */
    float mHauteurMonde;             /**< Hauteur de la zone de simulation */
    float mTempsDepuisReproduction;  /**< Temps écoulé depuis dernière reproduction */
    
public:
    /**
     * @brief Constructeur de la classe Animal
     * @param posX Position initiale en X
     * @param posY Position initiale en Y
     * @param largeur Largeur du monde de simulation
     * @param hauteur Hauteur du monde de simulation
     */
    Animal(float posX, float posY, float largeur, float hauteur);
    
    /**
     * @brief Destructeur virtuel
     */
    virtual ~Animal();
    
    /**
     * @brief Déplace l'animal selon sa vitesse et gère les rebonds
     * @param deltaTime Temps écoulé depuis le dernier frame (secondes)
     */
    virtual void Deplacer(float deltaTime) = 0;
    

    /**
     * @brief Recupère la direction du déplqcement
     * @return Vitesse de déplacement
     */
    float GetDirection();


    /**
     * @brief Réduit l'énergie de l'animal
     * @param quantite Quantité d'énergie à soustraire
     */
    void PerdreEnergie(float quantite);

    /**
     * @brief Incrémente le temps écoulé depuis dernière reproduction
     * @param deltaTime Temps écoulé depuis le dernier frame (secondes)
     */
    void IncrementerTempsReproduction(float deltaTime);
    
    /**
     * @brief Augmente l'énergie de l'animal
     * @param quantite Quantité d'énergie à ajouter
     */
    void GagnerEnergie(float quantite);
    
    /**
     * @brief Récupère la position horizontale
     * @return Position X actuelle
     */
    float GetX() const;
    
    /**
     * @brief Récupère la position verticale
     * @return Position Y actuelle
     */
    float GetY() const;
    
    /**
     * @brief Vérifie si l'animal est vivant
     * @return true si vivant, false sinon
     */
    bool EstVivant() const;
    
    /**
     * @brief Récupère le niveau d'énergie
     * @return Énergie actuelle (0-100)
     */
    float GetEnergie() const;

    /**
     * @brief Récupère l'énergie minimal pour se reproduire
     * @return La quantité d'energie necessaire par espèce (0-100)
     */
    virtual float GetSeuil() const = 0;
    
    /**
     * @brief Réinitialise le compteur de reproduction
     */
    void ReinitialiserReproduction();
    
    /**
     * @brief Définit le comportement spécifique de l'espèce
     * @param proies Liste des proies dans le monde
     * @param predateurs Liste des prédateurs dans le monde
     * @param plantes Liste des plantes disponibles
     * 
     * Méthode abstraite à implémenter dans les classes dérivées
     */
    virtual void Comportement(const std::vector<Proie*>& proies,
                             const std::vector<Predateur*>& predateurs,
                             const std::vector<Plante*>& plantes) = 0;

protected:
    /**
     * @brief Vérifie conditions de reproduction
     * @return true si peut se reproduire, false sinon
     */
    virtual bool PeutSeReproduire() const = 0;
    
    /**
     * @brief Détecte entités proches
     * @param proies Liste des proies
     * @param predateurs Liste des prédateurs
     */
    virtual void Detecter(const std::vector<Proie*>& proies,
                         const std::vector<Predateur*>& predateurs) = 0;
    
    /**
     * @brief Gère perte d'énergie métabolique
     * @param deltaTime Temps écoulé (secondes)
     */
    virtual void Metabolisme(float deltaTime) = 0;
};

#endif /* ANIMAL_H */