/*
 * @file Main.cpp
 * @brief Point d'entrée du programme de simulation écosystème
 */

#include "../UI/GUI.h"
#include "../Graphics/Renderer.h"
#include "../Population/Ecosysteme.h"
#include "../Population/Proie.h"
#include "../Population/Predateur.h"
#include "../Population/Plante.h"
#include "../Population/Animal.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[])
{
    srand(static_cast<unsigned int>(time(nullptr)));
    
    std::cout << "=== Démarrage Simulation Écosystème ===" << std::endl;
    
    /* Initialiser le renderer */
    Renderer renderer;
    
    if (!renderer.Initialiser())
    {
        std::cerr << "❌ Échec initialisation SDL" << std::endl;
        return -1;
    }
    
    std::cout << "✅ SDL initialisé" << std::endl;

    /* Initialiser GUI */
    GUI gui;
    gui.Initialize(renderer.ObtenirFenetre(), renderer.ObtenirRenderer());

    std::cout << "✅ GUI initialisée" << std::endl;

    /* Menu de configuration initial */
    ConfigEcosysteme config = gui.AfficherMenuConfiguration(WINDOW_WIDTH, WINDOW_HEIGHT);

    if (!config.pret)
    {
        gui.Destroy();
        renderer.Nettoyer();
        return 0;
    }

    /* Créer l'écosystème avec la config */
    Ecosysteme* eco = new Ecosysteme(config.nbProies, config.nbPredateurs, 
                                      config.nbPlantes, WINDOW_WIDTH, WINDOW_HEIGHT);
    eco->SetDelaiPlantes(config.delaiPlantes);

    /* DÉCLARER TOUTES LES TEXTURES AVANT LE SWITCH */
    SDL_Texture* textureFond = nullptr;
    SDL_Texture* textureFondJour = nullptr;
    SDL_Texture* textureFondNuit = nullptr;
    SDL_Texture* texturePlante = nullptr;
    
    /* Textures Loup */
    SDL_Texture* textureLoup1 = nullptr;
    SDL_Texture* textureLoup1_left = nullptr;
    SDL_Texture* textureLoup2 = nullptr;
    SDL_Texture* textureLoup2_left = nullptr;
    SDL_Texture* textureLoup3 = nullptr;
    SDL_Texture* textureLoup3_left = nullptr;
    
    /* Textures Lapin */
    SDL_Texture* textureLapin1 = nullptr;
    SDL_Texture* textureLapin1_left = nullptr;
    SDL_Texture* textureLapin2 = nullptr;
    SDL_Texture* textureLapin2_left = nullptr;
    SDL_Texture* textureLapin3 = nullptr;
    SDL_Texture* textureLapin3_left = nullptr;

    /* Textures Requin */
    SDL_Texture* textureRequin = nullptr;
    SDL_Texture* textureRequin_left = nullptr;

    /* Textures Poisson */
    SDL_Texture* texturePoisson = nullptr;
    SDL_Texture* texturePoisson_left = nullptr;
    
    /* Variables pour l'animation */
    int frameAnimLoup = 0;      // 0, 1, 2 pour Frame1, Frame2, Frame3
    int frameAnimLapin = 0;     // 0, 1, 2 pour Frame1, Frame2, Frame3
    int compteurFrames = 0;     // Pour ralentir l'animation
    
    /* Variables pour le cycle jour/nuit */
    float tempsEcouleJourNuit = 0.0f;
    const float DUREE_DEMI_CYCLE = 30.0f;  // 30 secondes par phase
    bool estJour = true;
    
    /* Charger les textures selon le type d'écosystème */
    switch (config.typeEcosysteme)
    {
    case 0:  // 🌲 Forêt
        std::cout << "🌲 Chargement textures Forêt..." << std::endl;
        
        /* Fond jour et nuit */
        textureFondJour = renderer.ChargerTexture("Assets/Img/Background/Foret_Jour.jpeg");
        textureFondNuit = renderer.ChargerTexture("Assets/Img/Background/Foret_Nuit.jpeg");
        textureFond = textureFondJour;  // Commencer par le jour
        
        texturePlante = renderer.ChargerTexture("Assets/Img/Plantes/REMOVE/Herbe.png");
        
        /* Loup Frame 1 */
        textureLoup1 = renderer.ChargerTexture("Assets/Img/Loup_moves/REMOVE/Frame1.png");
        textureLoup1_left = renderer.ChargerTexture("Assets/Img/Loup_moves/REMOVE/Frame1_Left.png");
        
        /* Loup Frame 2 */
        textureLoup2 = renderer.ChargerTexture("Assets/Img/Loup_moves/REMOVE/Frame2.png");
        textureLoup2_left = renderer.ChargerTexture("Assets/Img/Loup_moves/REMOVE/Frame2_Left.png");
        
        /* Loup Frame 3 */
        textureLoup3 = renderer.ChargerTexture("Assets/Img/Loup_moves/REMOVE/Frame3.png");
        textureLoup3_left = renderer.ChargerTexture("Assets/Img/Loup_moves/REMOVE/Frame3_Left.png");
                
        /* Lapin Frame 1 */
        textureLapin1 = renderer.ChargerTexture("Assets/Img/Lapin_moves/REMOVE/Frame1.png");
        textureLapin1_left = renderer.ChargerTexture("Assets/Img/Lapin_moves/REMOVE/Frame1_Left.png");
        
        /* Lapin Frame 2 */
        textureLapin2 = renderer.ChargerTexture("Assets/Img/Lapin_moves/REMOVE/Frame2.png");
        textureLapin2_left = renderer.ChargerTexture("Assets/Img/Lapin_moves/REMOVE/Frame2_Left.png");

        /* Lapin Frame 3 */
        textureLapin3 = renderer.ChargerTexture("Assets/Img/Lapin_moves/REMOVE/Frame3.png");
        textureLapin3_left = renderer.ChargerTexture("Assets/Img/Lapin_moves/REMOVE/Frame3_Left.png");
        
        /* Vérification */
        if (!textureFondJour || !textureFondNuit || !texturePlante || 
            !textureLoup1 || !textureLoup1_left || 
            !textureLoup2 || !textureLoup2_left ||
            !textureLoup3 || !textureLoup3_left ||
            !textureLapin1 || !textureLapin1_left ||
            !textureLapin2 || !textureLapin2_left ||
            !textureLapin3 || !textureLapin3_left)
        {
            std::cerr << "❌ Erreur chargement textures Forêt" << std::endl;
            gui.Destroy();
            renderer.Nettoyer();
            return -1;
        }
        
        std::cout << "✅ Textures Forêt chargées (Loup: 3 frames, Lapin: 3 frames, Jour+Nuit)" << std::endl;
        break;
        
    case 1:  // 🌊 Océan
        std::cout << "🌊 Chargement textures Maritime..." << std::endl;
        
        /* Fond jour et nuit */
        textureFondJour = renderer.ChargerTexture("Assets/Img/Background/Maritime_Jour.jpeg");
        textureFondNuit = renderer.ChargerTexture("Assets/Img/Background/Maritime_Nuit.jpeg");
        textureFond = textureFondJour;  // Commencer par le jour
        
        texturePlante = renderer.ChargerTexture("Assets/Img/Plantes/REMOVE/Algue.png");
        
        /* Requin */
        textureRequin = renderer.ChargerTexture("Assets/Img/Animaux/REMOVE/Requin.png");
        textureRequin_left = renderer.ChargerTexture("Assets/Img/Animaux/REMOVE/Requin_left.png");

        /* Poisson */
        texturePoisson = renderer.ChargerTexture("Assets/Img/Animaux/REMOVE/Poisson.png");
        texturePoisson_left = renderer.ChargerTexture("Assets/Img/Animaux/REMOVE/Poisson_left.png");
        
        /* Vérification */
        if (!textureFondJour || !textureFondNuit || !texturePlante ||
            !textureRequin || !textureRequin_left ||
            !texturePoisson || !texturePoisson_left)
        {
            std::cerr << "❌ Erreur chargement textures Maritime" << std::endl;
            gui.Destroy();
            renderer.Nettoyer();
            return -1;
        }
        
        std::cout << "✅ Textures Maritime chargées (Jour+Nuit)" << std::endl;
        break;
        
    case 2:  // ✈️ Air
        std::cout << "✈️ Chargement textures Aérienne..." << std::endl;
        // À compléter plus tard
        break;
        
    default:
        std::cerr << "❌ Type d'écosystème invalide" << std::endl;
        gui.Destroy();
        renderer.Nettoyer();
        return -1;
    }

    std::cout << "✅ Écosystème créé : Type=" << config.typeEcosysteme 
              << ", Proies=" << config.nbProies 
              << ", Prédateurs=" << config.nbPredateurs << std::endl;

    /* Paramètres du panneau de controle */
    int nb_proies = config.nbProies;
    int nb_preds = config.nbPredateurs;
    int nb_plantes = config.nbPlantes;
    int nb_plantes_conso = config.nbPlantesConso;
    float DelaiPlantes = config.delaiPlantes;
    bool enPause = false;
    bool relancer = false;
    
    /* Variables de la boucle de jeu */
    bool enCours = true;
    SDL_Event event;
    Uint64 dernierTemps = SDL_GetTicks();
    int frameCount = 0;
    
    std::cout << "\n🎮 Simulation lancée ! Fermez la fenêtre pour quitter.\n" << std::endl;
    
    /* Boucle principale */
    while (enCours)
    {
        /* Gérer les événements */
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
            {
                enCours = false;
            }
        }
        
        /* Calculer deltaTime */
        Uint64 tempsActuel = SDL_GetTicks();
        float deltaTime = enPause ? 0.0 : (tempsActuel - dernierTemps) / 1000.0f;
        dernierTemps = tempsActuel;
        
        /* Nouveau Frame GUI */
        gui.DebutFrame();
        
        /* Mettre à jour la simulation */
        eco->Update(deltaTime);
        
        /* CYCLE JOUR/NUIT */
        if (!enPause)
        {
            tempsEcouleJourNuit += deltaTime;
            
            // Vérifier si on doit basculer
            if (tempsEcouleJourNuit >= DUREE_DEMI_CYCLE)
            {
                tempsEcouleJourNuit = 0.0f;
                estJour = !estJour;
                
                // Basculer le fond
                if (estJour)
                {
                    textureFond = textureFondJour;
                    std::cout << "🌞 Lever du jour !" << std::endl;
                }
                else
                {
                    textureFond = textureFondNuit;
                    std::cout << "🌙 Tombée de la nuit !" << std::endl;
                }
            }
        }
        
        /* ANIMATION - Changer de frame toutes les 10 frames SDL */
        compteurFrames++;
        if (compteurFrames >= 10)
        {
            compteurFrames = 0;
            
            /* Loup : cycle 0 → 1 → 2 → 0 */
            frameAnimLoup = (frameAnimLoup + 1) % 3;
            
            /* Lapin : cycle 0 → 1 → 2 → 0 */
            frameAnimLapin = (frameAnimLapin + 1) % 3;
        }
        
        /* Interface GUI */
        gui.AfficherPanneauControle(nb_proies, nb_preds, nb_plantes, nb_plantes_conso,
                             DelaiPlantes, enPause, enCours, relancer, WINDOW_WIDTH);

        gui.AfficherStatistiques(eco->GetNombreProies(), eco->GetNombrePredateurs(),
                                  eco->GetNombrePlantes(), eco->GetTotalPlantesConsommees());

        if (relancer)
        {
            delete eco;
            eco = new Ecosysteme(nb_proies, nb_preds, nb_plantes, WINDOW_WIDTH, WINDOW_HEIGHT);
            eco->SetDelaiPlantes(DelaiPlantes);
            std::cout << "Ecosysteme relancé !" << std::endl;
            relancer = false;
            
            // Réinitialiser le cycle jour/nuit
            tempsEcouleJourNuit = 0.0f;
            estJour = true;
            textureFond = textureFondJour;
        }
        
        /* Dessiner */
        renderer.EffacerEcran();
        
        /* 1. Fond (celui qui est actif) */
        renderer.DessinerTexture(textureFond, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        
        /* 2. Plantes */
        for (auto* plante : eco->GetPlantes())
        {
            if (plante->EstDisponible())
            {
                renderer.DessinerTexture(texturePlante, 
                                        static_cast<int>(plante->GetX()), 
                                        static_cast<int>(plante->GetY()), 
                                        35, 35);
            }
        }
        
        /* 3. Proies avec animation */
        for (auto* proie : eco->GetProies())
        {
            SDL_Texture* textureActuelle = nullptr;
            
            /* Déterminer la direction selon la vitesse */
            bool versGauche = (proie->GetDirection() < 0);
            
            switch (config.typeEcosysteme)
            {
                case 0:  // Forêt
                    /* Choisir la frame selon l'animation ET la direction */
                    if (frameAnimLapin == 0)
                        textureActuelle = versGauche ? textureLapin1_left : textureLapin1;
                    else if (frameAnimLapin == 1)
                        textureActuelle = versGauche ? textureLapin2_left : textureLapin2;
                    else
                        textureActuelle = versGauche ? textureLapin3_left : textureLapin3;
                    break;
                    
                case 1:  // Maritime
                    textureActuelle = versGauche ? texturePoisson_left : texturePoisson;
                    break;
                    
                case 2:  // Aérien
                    // Prochainement
                    break;
            }
            
            renderer.DessinerTexture(textureActuelle,
                                    static_cast<int>(proie->GetX()),
                                    static_cast<int>(proie->GetY()),
                                    35, 35);
        }
        
        /* 4. Prédateurs avec animation */
        for (auto* pred : eco->GetPredateurs())
        {
            SDL_Texture* textureActuelle = nullptr;
            
            /* Déterminer la direction selon la vitesse */
            bool versGauche = (pred->GetDirection() < 0);

            switch (config.typeEcosysteme)
            {
                case 0:  // Forêt
                    /* Choisir la frame selon l'animation ET la direction */
                    if (frameAnimLoup == 0)
                        textureActuelle = versGauche ? textureLoup1_left : textureLoup1;
                    else if (frameAnimLoup == 1)
                        textureActuelle = versGauche ? textureLoup2_left : textureLoup2;
                    else
                        textureActuelle = versGauche ? textureLoup3_left : textureLoup3;
                    break;
                    
                case 1:  // Maritime
                    textureActuelle = versGauche ? textureRequin_left : textureRequin;
                    break;
                    
                case 2:  // Aérien
                    // Prochainement
                    break;
            }
            
            renderer.DessinerTexture(textureActuelle,
                                    static_cast<int>(pred->GetX()),
                                    static_cast<int>(pred->GetY()),
                                    60, 60);
        }

        /* Rendre GUI */
        gui.FinFrame(renderer.ObtenirRenderer());
        
        /* Afficher à l'écran */
        renderer.Afficher();

        /* Statistiques console */
        frameCount++;
        
        /* Limiter à ~60 FPS */
        SDL_Delay(16);
    }
    
    /* Nettoyage */
    delete eco;
    
    SDL_DestroyTexture(textureFondJour);
    SDL_DestroyTexture(textureFondNuit);
    SDL_DestroyTexture(texturePlante);
    SDL_DestroyTexture(textureLoup1);
    SDL_DestroyTexture(textureLoup1_left);
    SDL_DestroyTexture(textureLoup2);
    SDL_DestroyTexture(textureLoup2_left);
    SDL_DestroyTexture(textureLoup3);
    SDL_DestroyTexture(textureLoup3_left);
    SDL_DestroyTexture(textureLapin1);
    SDL_DestroyTexture(textureLapin1_left);
    SDL_DestroyTexture(textureLapin2);
    SDL_DestroyTexture(textureLapin2_left);
    SDL_DestroyTexture(textureLapin3);
    SDL_DestroyTexture(textureLapin3_left);
    SDL_DestroyTexture(texturePoisson);
    SDL_DestroyTexture(texturePoisson_left);
    SDL_DestroyTexture(textureRequin);
    SDL_DestroyTexture(textureRequin_left);

    Uint64 tempsFinal = SDL_GetTicks();
    std::cout << "La simulation a duré : " << (tempsFinal - dernierTemps) / 1000.0f << " secondes" << std::endl;
    std::cout << "Nombre de Frames : " << frameCount << std::endl;

    gui.Destroy();
    renderer.Nettoyer();
    
    std::cout << "\n✅ Programme terminé proprement" << std::endl;
    
    return 0;
}
