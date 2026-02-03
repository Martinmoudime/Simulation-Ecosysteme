/**
 * @file Proie.h
 * @brief Classe représentant une proie herbivore de l'écosystème
 */

#ifndef PROIE_H
#define PROIE_H

#include "Animal.h"

class Predateur;
class Plante;

/**
 * @class Proie
 * @brief Herbivore fuyant les prédateurs et se nourrissant de plantes
 */
class Proie : public Animal
{
protected:
    Predateur* mMenaceDetectee;  /**< Prédateur actuellement détecté */
    Plante* mPlanteDetectee;     /**< Plante actuellement ciblée */

private:
    static constexpr float ENERGIE_GAGNE_PAR_PLANTE = 5.0f;        /**< Énergie gagnée par plante */
    static constexpr float DELAI_REPRODUCTION = 40.0f;          /**< Délai entre reproductions (s) */
    static constexpr float SEUIL_ENERGIE_REPRODUCTION = 70.0f;     /**< Énergie min pour reproduction */
    static constexpr float RAYON_ATTAQUE = 20.0f;                  /**< Distance pour consommer plante */
    static constexpr float VITESSE_BASE = 80.0f;                   /**< Vitesse de déplacement (pixels/s) */
    static constexpr float RAYON_DETECTION_PREDATEUR = 150.0f;     /**< Rayon de détection prédateurs */
    static constexpr float RAYON_DETECTION_PLANTE = 100.0f;        /**< Rayon de détection plantes */
    
public:
    /**
     * @brief Constructeur de la proie
     * @param x Position horizontale initiale
     * @param y Position verticale initiale
     * @param largeur Largeur du monde
     * @param hauteur Hauteur du monde
     */
    Proie(float x, float y, float largeur, float hauteur);
    
    /**
     * @brief Destructeur
     */
    ~Proie();
    
    /**
     * @brief Définit le comportement de la proie (fuite, alimentation, errance)
     * @param proies Liste des proies dans le monde (non utilisée)
     * @param predateurs Liste des prédateurs dans le monde
     * @param plantes Liste des plantes disponibles
     */
    void Comportement(const std::vector<Proie*>& proies,
                     const std::vector<Predateur*>& predateurs,
                     const std::vector<Plante*>& plantes) override;

    /**
     * @brief Déplace l'animal selon sa vitesse et gère les rebonds
     * @param deltaTime Temps écoulé depuis le dernier frame (secondes)
     */
    void Deplacer(float deltaTime) override;
    
    /**
     * @brief Vérifie si la proie peut se reproduire
     * @return true si conditions remplies, false sinon
     */
    bool PeutSeReproduire() const override;

    /**
     * @brief Récupère l'énergie minimal pour se reproduire
     * @return La quantité d'energie necessaire par espèce (0-100)
     */
    float GetSeuil() const override;

    /**
     * @brief Gère le métabolisme et perte d'énergie
     * @param deltaTime Temps écoulé (secondes)
     */
    void Metabolisme(float deltaTime) override;
    
    /**
     * @brief Détecte le prédateur le plus proche
     * @param proies Liste des proies (non utilisée)
     * @param predateurs Liste des prédateurs disponibles
     */
    void Detecter(const std::vector<Proie*>& proies,
                 const std::vector<Predateur*>& predateurs) override;
    
private:
    /**
     * @brief Détecte la plante la plus proche
     * @param plantes Liste des plantes disponibles
     */
    void DetecterPlante(const std::vector<Plante*>& plantes);
    
    /**
     * @brief Se dirige vers la plante détectée
     */
    void ChercherPlante();
    
    /**
     * @brief S'éloigne du prédateur détecté
     */
    void Fuir();
    
    /**
     * @brief Mouvement aléatoire en l'absence de menace ou nourriture
     */
    void Errer();
    
    /**
     * @brief Consomme une plante si à portée
     */
    void SeNourrir();
};

#endif /* PROIE_H */