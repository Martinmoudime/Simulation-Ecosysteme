/**
 * @file GUI.h
 * @brief Déclaration de la classe GUI pour gérer l'interface graphique
 */

#pragma once

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <SDL3/SDL.h>
#include <vector>

/**
 * @struct ConfigEcosysteme
 * @brief Structure contenant la configuration initiale de l'écosystème
 */
struct ConfigEcosysteme
{
    int nbProies;           /**< Nombre initial de proies */
    int nbPredateurs;       /**< Nombre initial de prédateurs */
    int nbPlantes;          /**< Nombre initial de plantes */
    int nbPlantesConso;     /**< Nombre de plantes pour satiété */
    float delaiPlantes;     /**< Délai d'apparition des plantes */
    int typeEcosysteme;     /**< Type d'écosystème (0=Forêt, 1=Savane, 2=Désert) */
    bool pret;              /**< True si prêt à lancer */
};

/**
 * @class GUI
 * @brief Gère l'interface graphique ImGui de la simulation
 */
class GUI
{
public:
    /**
     * @brief Constructeur par défaut
     */
    GUI();
    
    /**
     * @brief Destructeur
     */
    ~GUI();

    /**
     * @brief Initialise ImGui avec SDL
     * @param window Pointeur vers la fenêtre SDL
     * @param renderer Pointeur vers le renderer SDL
     */
    void Initialize(SDL_Window *window, SDL_Renderer *renderer);
    
    /**
     * @brief Détruit le contexte ImGui
     */
    void Destroy();
    
    /**
     * @brief Affiche le menu de configuration initial et bloque jusqu'au lancement
     * @param windowWidth Largeur de la fenêtre
     * @param windowHeight Hauteur de la fenêtre
     * @return Configuration choisie par l'utilisateur
     */
    ConfigEcosysteme AfficherMenuConfiguration(int windowWidth, int windowHeight);
    
    /**
     * @brief Démarre une nouvelle frame ImGui
     */
    void DebutFrame();
    
    /**
     * @brief Finalise et affiche la frame ImGui
     * @param renderer Pointeur vers le renderer SDL
     */
    void FinFrame(SDL_Renderer *renderer);
    
    /**
     * @brief Affiche le panneau de contrôle de la simulation
     * @param nbProies Nombre de proies (modifiable)
     * @param nbPreds Nombre de prédateurs (modifiable)
     * @param nbPlantes Nombre de plantes (modifiable)
     * @param nbPlantesConso Nombre de plantes pour satiété (modifiable)
     * @param delaiPlantes Délai d'apparition des plantes (modifiable)
     * @param enPause État pause de la simulation (modifiable)
     * @param enCours État de la boucle principale (modifiable)
     * @param relancer Flag pour relancer la simulation (modifiable)
     * @param windowWidth Largeur de la fenêtre
     */
    void AfficherPanneauControle(int &nbProies, int &nbPreds, int &nbPlantes,
                                  int &nbPlantesConso, float &delaiPlantes,
                                  bool &enPause, bool &enCours, bool &relancer,
                                  int windowWidth);
    
    /**
     * @brief Affiche les statistiques et graphiques de la simulation
     * @param nbProies Nombre actuel de proies
     * @param nbPreds Nombre actuel de prédateurs
     * @param nbPlantes Nombre actuel de plantes
     * @param nbConsommees Nombre total de plantes consommées
     */
    void AfficherStatistiques(int nbProies, int nbPreds, int nbPlantes,
                              int nbConsommees);

private:
    SDL_Window *mWindow;                       /**< Pointeur vers la fenêtre SDL */
    SDL_Renderer *mRenderer;                   /**< Pointeur vers le renderer SDL */
    std::vector<float> mHistoriqueProies;      /**< Historique population proies */
    std::vector<float> mHistoriquePredateurs;  /**< Historique population prédateurs */
    std::vector<float> mHistoriquePlantes;     /**< Historique population plantes */
    
    /**
     * @brief Applique un style professionnel sombre pour la simulation
     */
    void AppliquerStyleSimulation();
    
    /**
     * @brief Applique un style clair et accueillant pour la configuration
     */
    void AppliquerStyleConfiguration();
};