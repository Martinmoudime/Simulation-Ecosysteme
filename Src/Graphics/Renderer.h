/**
 * @file Renderer.h
 * @brief Gestionnaire du rendu graphique avec SDL3
 * @author Martin
 * @date 2025/12/22
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL3/SDL.h>
#include <string>

/* Constantes de fenêtre */
inline const int WINDOW_WIDTH = 1280;
inline const int WINDOW_HEIGHT = 640;
inline const char* WINDOW_TITLE = "Simulation Écosystème - Prédateurs/Proies";

/**
 * @class Renderer
 * @brief Gère l'initialisation et le rendu SDL3
 */
class Renderer
{
public:
    /**
     * @brief Constructeur
     */
    Renderer();
    
    /**
     * @brief Destructeur
     */
    ~Renderer();
    
    /**
     * @brief Initialise SDL3 et crée la fenêtre
     * @return true si succès, false sinon
     */
    bool Initialiser();
    
    /**
     * @brief Nettoie et ferme SDL3
     */
    void Nettoyer();
    
    /**
     * @brief Efface l'écran (prépare le prochain frame)
     */
    void EffacerEcran();
    
    /**
     * @brief Affiche tout ce qui a été dessiné
     */
    void Afficher();
    
    /**
     * @brief Charge une texture depuis un fichier
     * @param cheminFichier Chemin vers l'image
     * @return Pointeur vers la texture SDL (NULL si erreur)
     */
    SDL_Texture* ChargerTexture(const std::string& cheminFichier);
    
    /**
     * @brief Dessine une texture à l'écran
     * @param texture Texture à dessiner
     * @param x Position X
     * @param y Position Y
     * @param largeur Largeur d'affichage
     * @param hauteur Hauteur d'affichage
     */
    void DessinerTexture(SDL_Texture* texture, int x, int y, 
                         int largeur, int hauteur);
    
    /**
     * @brief Récupère le renderer SDL3
     * @return Pointeur vers le renderer
     */
    SDL_Renderer* ObtenirRenderer() const;

    /**
     * @brief Récupère la fenêtre SDL3
     * @return Pointeur vers la fenêtre
    */
    SDL_Window* ObtenirFenetre() const;

private:
    SDL_Window* mFenetre;         /**< Fenêtre SDL */
    SDL_Renderer* mRenderer;      /**< Renderer SDL */
    bool mEstInitialise;          /**< État d'initialisation */
};

#endif /* RENDERER_H */