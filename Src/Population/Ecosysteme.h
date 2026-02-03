/**
 * @file Ecosysteme.h
 * @brief Gestionnaire central de l'écosystème
 */

#ifndef ECOSYSTEME_H
#define ECOSYSTEME_H

#include <vector>

class Proie;
class Predateur;
class Plante;

/**
 * @class Ecosysteme
 * @brief Orchestre tous les éléments vivants de la simulation
 */
class Ecosysteme
{
private:
    std::vector<Proie*> mProies;                /**< Liste des proies */
    std::vector<Predateur*> mPredateurs;        /**< Liste des prédateurs */
    std::vector<Plante*> mPlantes;              /**< Liste des plantes */
    std::vector<Plante*> mPlantesConsommees;    /**< Liste des plantes déjà consommées */

    float mTempsDepuisCreationPlante;                          /**< Timer pour créer nouvelles plantes */
    float INTERVALLE_CREATION_PLANTE = 5.0f;  /**< Délai entre créations (secondes) */
    static constexpr int MAX_PLANTES = 60;                     /**< Nombre maximum de plantes */
    
    float mLargeur;                 /**< Largeur du monde */
    float mHauteur;                 /**< Hauteur du monde */
    int mNbreProies;                /**< Nombre actuel de proies */
    int mNbrePredateurs;            /**< Nombre actuel de prédateurs */
    int mNbrePlantes;               /**< Nombre actuel de plantes */
    
    /**
     * @brief Supprime les animaux morts
     */
    void SupprimerMorts();
    
    /**
     * @brief Gère les reproductions
     */
    void Reproduction();
    
public:
    /**
     * @brief Constructeur créant populations initiales
     * @param nbreProies Nombre de proies à créer
     * @param nbrePredateurs Nombre de prédateurs à créer
     * @param nbrePlantes Nombre de plantes à créer
     * @param largeur Largeur du monde
     * @param hauteur Hauteur du monde
     */
    Ecosysteme(int nbreProies, int nbrePredateurs, int nbrePlantes,
               float largeur, float hauteur);
    
    /**
     * @brief Destructeur libérant mémoire
     */
    ~Ecosysteme();
    
    /**
     * @brief Met à jour tout l'écosystème
     * @param deltaTime Temps écoulé (secondes)
     */
    void Update(float deltaTime);
    
    /**
     * @brief Accès lecture seule aux proies
     * @return Vecteur des proies
     */
    const std::vector<Proie*>& GetProies() const;
    
    /**
     * @brief Accès lecture seule aux prédateurs
     * @return Vecteur des prédateurs
     */
    const std::vector<Predateur*>& GetPredateurs() const;
    
    /**
     * @brief Accès lecture seule aux plantes
     * @return Vecteur des plantes
     */
    const std::vector<Plante*>& GetPlantes() const;
    
    /**
     * @brief Compte les proies vivantes
     * @return Nombre de proies
     */
    int GetNombreProies() const;
    
    /**
     * @brief Compte les prédateurs vivants
     * @return Nombre de prédateurs
     */
    int GetNombrePredateurs() const;
    
    /**
     * @brief Compte les plantes disponibles
     * @return Nombre de plantes
     */
    int GetNombrePlantes() const;

    /**
     * @brief Compte les plantes consommées depuis le debut du jeu
     * @return Nombre de plantes consommées
     */
    int GetTotalPlantesConsommees() const;

    /**
     * @brief Compte le temps qui separe l'apparission de 2 plantes
     * @return Intervalle d'apparission des plantes
     */
    int GetDelaiPlantes() const;

    /**
     * @brief Actualise le temps qui sépare l'apparission de 2 plantes
     * @param Delai de réaparission
     */
    void SetDelaiPlantes(float delai);
};

#endif /* ECOSYSTEME_H */