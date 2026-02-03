/**
 * @file Predateur.h
 * @brief Classe représentant un prédateur de l'écosystème
 */

#ifndef PREDATEUR_H
#define PREDATEUR_H

#include "Animal.h"

class Proie;

/**
 * @class Predateur
 * @brief Carnivore chassant les proies pour se nourrir
 */
class Predateur : public Animal
{
protected:
    Proie* mProieDetectee;  /**< Proie actuellement ciblée */
    
private:
    static constexpr float VITESSE_BASE = 120.0f;               /**< Vitesse de déplacement (pixels/s) */
    static constexpr float SEUIL_ENERGIE_REPRODUCTION = 30.0f; /**< Énergie min pour reproduction */
    static constexpr float DELAI_REPRODUCTION = 15.0f;          /**< Délai entre reproductions (s) */
    static constexpr float RAYON_ATTAQUE = 40.0f;               /**< Distance d'attaque (pixels) */
    static constexpr float RAYON_DETECTION_PROIE = 150.0f;      /**< Rayon de détection proies */
    static constexpr float ENERIE_GAGNE_PAR_PROIE = 30.0f;      /**< Énergie gagnée en mangeant */
    
public:
    /**
     * @brief Constructeur du prédateur
     * @param x Position horizontale initiale
     * @param y Position verticale initiale
     * @param largeur Largeur du monde
     * @param hauteur Hauteur du monde
     */
    Predateur(float x, float y, float largeur, float hauteur);
    
    /**
     * @brief Destructeur
     */
    ~Predateur();
    
    /**
     * @brief Définit le comportement du prédateur (chasse ou errance)
     * @param proies Liste des proies dans le monde
     * @param predateurs Liste des prédateurs dans le monde
     * @param plantes Liste des plantes (non utilisée par prédateur)
     */
    void Comportement(const std::vector<Proie*>& proies,
                     const std::vector<Predateur*>& predateurs,
                     const std::vector<Plante*>& plantes) override;
    
    /**
     * @brief Gère le métabolisme et perte d'énergie
     * @param deltaTime Temps écoulé (secondes)
     */
    void Metabolisme(float deltaTime) override;

    /**
     * @brief Déplace l'animal selon sa vitesse et gère les rebonds
     * @param deltaTime Temps écoulé depuis le dernier frame (secondes)
     */
    void Deplacer(float deltaTime) override;
    
    /**
     * @brief Vérifie si prédateur peut se reproduire
     * @return true si conditions remplies, false sinon
     */
    bool PeutSeReproduire() const override;

     /**
     * @brief Récupère l'énergie minimal pour se reproduire
     * @return La quantité d'energie necessaire par espèce (0-100)
     */
    float GetSeuil() const override;
    
    /**
     * @brief Détecte la proie la plus proche
     * @param proies Liste des proies disponibles
     * @param predateurs Liste des prédateurs (non utilisée)
     */
    void Detecter(const std::vector<Proie*>& proies,
                 const std::vector<Predateur*>& predateurs) override;

private:
    /**
     * @brief Poursuit la proie détectée
     */
    void Chasser();
    
    /**
     * @brief Mouvement aléatoire en l'absence de cible
     */
    void Errer();
    
    /**
     * @brief Consomme une proie si à portée
     */
    void SeNourrir();
};

#endif /* PREDATEUR_H */