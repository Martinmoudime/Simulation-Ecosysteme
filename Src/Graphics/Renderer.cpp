/**
 * @file Renderer.cpp
 * @brief Implémentation du gestionnaire de rendu
 */

#include "Renderer.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

/**
 * @brief Constructeur - initialise les pointeurs à NULL
 */
Renderer::Renderer()
    : mFenetre(nullptr), mRenderer(nullptr), mEstInitialise(false)
{
}

/**
 * @brief Destructeur - nettoie les ressources
 */
Renderer::~Renderer()
{
    Nettoyer();
}

/**
 * @brief Initialise SDL3 et crée la fenêtre
 */
bool Renderer::Initialiser()
{
    /* Initialiser SDL3 */
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "Erreur SDL_Init: " << SDL_GetError() << std::endl;
        return false;
    }
    
    /* Créer la fenêtre */
    mFenetre = SDL_CreateWindow(
        WINDOW_TITLE,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );
    
    if (!mFenetre)
    {
        std::cerr << "Erreur SDL_CreateWindow: " << SDL_GetError() << std::endl;
        return false;
    }
    
    /* Créer le renderer */
    mRenderer = SDL_CreateRenderer(mFenetre, nullptr);
    
    if (!mRenderer)
    {
        std::cerr << "Erreur SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        return false;
    }

    // SDL_SetRenderDrawBlendMode(mRenderer, SDL_BLENDMODE_BLEND);
    
    /* Initialiser SDL_image pour charger PNG/JPG */
    // int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    // if (!(IMG_Init(imgFlags) & imgFlags))
    // {
    //     std::cerr << "Erreur IMG_Init: " << IMG_GetError() << std::endl;
    //     return false;
    // }
    
    mEstInitialise = true;
    return true;
}

/**
 * @brief Nettoie SDL3
 */
void Renderer::Nettoyer()
{
    if (mRenderer)
    {
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }
    
    if (mFenetre)
    {
        SDL_DestroyWindow(mFenetre);
        mFenetre = nullptr;
    }
    
    // IMG_Quit();
    SDL_Quit();
    
    mEstInitialise = false;
}

/**
 * @brief Efface l'écran en noir
 */
void Renderer::EffacerEcran()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
    SDL_RenderClear(mRenderer);
}

/**
 * @brief Affiche le rendu à l'écran
 */
void Renderer::Afficher()
{
    SDL_RenderPresent(mRenderer);
}

/**
 * @brief Charge une image en texture SDL
 */
SDL_Texture* Renderer::ChargerTexture(const std::string& cheminFichier)
{
    SDL_Surface* surface = IMG_Load(cheminFichier.c_str());
    if (!surface)
    {
        std::cerr << "Erreur IMG_Load (" << cheminFichier << "): " 
                  << SDL_GetError() << std::endl;
        return nullptr;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    SDL_DestroySurface(surface);
    
    if (!texture)
    {
        std::cerr << "Erreur SDL_CreateTextureFromSurface: " 
                  << SDL_GetError() << std::endl;
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    return texture;
}

/**
 * @brief Dessine une texture à une position donnée
 */
void Renderer::DessinerTexture(SDL_Texture* texture, int x, int y,
                                int largeur, int hauteur)
{
    SDL_FRect destRect = {
        static_cast<float>(x),
        static_cast<float>(y),
        static_cast<float>(largeur),
        static_cast<float>(hauteur)
    };
    
    SDL_RenderTexture(mRenderer, texture, nullptr, &destRect);
}

/**
 * @brief Retourne le renderer SDL
 */
SDL_Renderer* Renderer::ObtenirRenderer() const
{
    return mRenderer;
}

/**
 * @brief Récupère la fenêtre SDL3
 * @return Pointeur vers la fenêtre
 */
SDL_Window* Renderer::ObtenirFenetre() const
{
    return mFenetre;
}