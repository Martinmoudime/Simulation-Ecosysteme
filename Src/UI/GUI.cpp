/**
 * @file GUI.cpp
 * @brief Implémentation des méthodes de la classe GUI pour gérer l'interface graphique
 */

#include "GUI.h"

/**
 * @brief Constructeur par défaut de la classe GUI
 */
GUI::GUI() : mWindow(nullptr), mRenderer(nullptr)
{
}

/**
 * @brief Destructeur de la classe GUI
 */
GUI::~GUI()
{
}

/**
 * @brief Initialise le contexte ImGui avec SDL
 * @param window Pointeur vers la fenêtre SDL
 * @param renderer Pointeur vers le renderer SDL
 */
void GUI::Initialize(SDL_Window *window, SDL_Renderer *renderer)
{
    mWindow = window;
    mRenderer = renderer;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
    
    AppliquerStyleConfiguration();
}

/**
 * @brief Détruit le contexte ImGui et libère les ressources
 */
void GUI::Destroy()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

/**
 * @brief Applique un style professionnel pour la configuration
 */
void GUI::AppliquerStyleConfiguration()
{
    ImGuiStyle &style = ImGui::GetStyle();
    
    style.WindowRounding = 10.0f;
    style.FrameRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 4.0f;
    style.WindowPadding = ImVec2(15, 15);
    style.FramePadding = ImVec2(10, 6);
    style.ItemSpacing = ImVec2(12, 8);
    
    ImVec4 *colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.95f, 0.95f, 0.96f, 1.0f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.20f, 0.50f, 0.35f, 1.0f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 0.60f, 0.42f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.45f, 1.0f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.30f, 0.70f, 0.52f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.22f, 0.50f, 0.38f, 1.0f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.88f, 0.88f, 0.90f, 1.0f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.82f, 0.82f, 0.85f, 1.0f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.45f, 1.0f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.22f, 0.50f, 0.38f, 1.0f);
    colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.45f, 0.55f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.30f, 0.70f, 0.52f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.45f, 1.0f);
    colors[ImGuiCol_Text] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
}

/**
 * @brief Applique un style professionnel sombre pour la simulation
 */
void GUI::AppliquerStyleSimulation()
{
    ImGuiStyle &style = ImGui::GetStyle();
    
    style.WindowRounding = 8.0f;
    style.FrameRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding = 3.0f;
    style.WindowPadding = ImVec2(12, 12);
    style.FramePadding = ImVec2(8, 5);
    style.ItemSpacing = ImVec2(10, 6);
    style.Alpha = 0.94f;
    
    ImVec4 *colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.11f, 0.13f, 0.95f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.16f, 0.18f, 1.0f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.20f, 0.22f, 0.24f, 1.0f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.50f, 0.40f, 0.85f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.60f, 0.48f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.18f, 0.45f, 0.36f, 1.0f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.18f, 0.20f, 0.22f, 0.85f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.24f, 0.26f, 0.90f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.25f, 0.60f, 0.48f, 1.0f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.30f, 0.70f, 0.56f, 1.0f);
    colors[ImGuiCol_Header] = ImVec4(0.20f, 0.50f, 0.40f, 0.55f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.60f, 0.48f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.50f, 0.40f, 1.0f);
    colors[ImGuiCol_Text] = ImVec4(0.92f, 0.93f, 0.94f, 1.0f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.25f, 0.70f, 0.55f, 1.0f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.30f, 0.80f, 0.65f, 1.0f);
}

/**
 * @brief Affiche le menu de configuration initial
 * @param windowWidth Largeur de la fenêtre
 * @param windowHeight Hauteur de la fenêtre
 * @return Configuration choisie par l'utilisateur
 */
ConfigEcosysteme GUI::AfficherMenuConfiguration(int windowWidth, int windowHeight)
{
    ConfigEcosysteme config;
    config.nbProies = 20;
    config.nbPredateurs = 5;
    config.nbPlantes = 30;
    config.nbPlantesConso = 50;
    config.delaiPlantes = 5.0f;
    config.typeEcosysteme = 0;
    config.pret = false;
    
    const char *typesEcosysteme[] = {"🌲 Forêt", "🌊 Océan"};
    
    bool enCours = true;
    SDL_Event event;
    
    while (enCours)
    {
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
            {
                config.pret = false;
                return config;
            }
        }
        
        ImGui_ImplSDL3_NewFrame();
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui::NewFrame();
        
        /* Fenêtre de configuration centrée */
        float windowW = 650.0f;
        float windowH = 580.0f;
        ImGui::SetNextWindowPos(ImVec2((windowWidth - windowW) / 2, (windowHeight - windowH) / 2));
        ImGui::SetNextWindowSize(ImVec2(windowW, windowH));
        
        ImGui::Begin("🌍 Configuration de l'Écosystème", nullptr,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
        
        ImGui::Dummy(ImVec2(0, 10));
        ImGui::TextWrapped("Configurez les paramètres initiaux de votre simulation écologique.");
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 10));
        
        /* Type d'écosystème */
        ImGui::Text("📍 Type d'Écosystème");
        ImGui::Combo("##type", &config.typeEcosysteme, typesEcosysteme, 2);
        
        ImGui::Dummy(ImVec2(0, 15));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 10));
        
        /* Population initiale */
        ImGui::Text("🐾 Population Initiale");
        ImGui::Dummy(ImVec2(0, 5));
        ImGui::SliderInt("Proies (Herbivores)", &config.nbProies, 5, 50);
        ImGui::SliderInt("Prédateurs (Carnivores)", &config.nbPredateurs, 1, 20);
        
        ImGui::Dummy(ImVec2(0, 15));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 10));
        
        /* Végétation */
        ImGui::Text("🌱 Végétation");
        ImGui::Dummy(ImVec2(0, 5));
        ImGui::SliderInt("Nombre de Plantes", &config.nbPlantes, 10, 100);
        ImGui::SliderInt("Plantes pour Satiété", &config.nbPlantesConso, 10, 100);
        ImGui::SliderFloat("Vitesse de Repousse (s)", &config.delaiPlantes, 1.0f, 10.0f, "%.1f");
        
        ImGui::Dummy(ImVec2(0, 20));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 10));
        
        /* Résumé */
        ImGui::Text("📊 Résumé de la Configuration");
        ImGui::Dummy(ImVec2(0, 5));
        ImGui::BulletText("Écosystème : %s", typesEcosysteme[config.typeEcosysteme]);
        ImGui::BulletText("Population : %d proies, %d prédateurs", config.nbProies, config.nbPredateurs);
        ImGui::BulletText("Végétation : %d plantes (repousse en %.1fs)", config.nbPlantes, config.delaiPlantes);
        
        ImGui::Dummy(ImVec2(0, 20));
        
        /* Bouton de lancement */
        float buttonWidth = 250.0f;
        ImGui::SetCursorPosX((windowW - buttonWidth) / 2);
        if (ImGui::Button("🚀 Lancer la Simulation", ImVec2(buttonWidth, 50)))
        {
            config.pret = true;
            enCours = false;
        }
        
        ImGui::End();
        
        /* Rendu */
        SDL_SetRenderDrawColor(mRenderer, 35, 40, 45, 255);
        SDL_RenderClear(mRenderer);
        
        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), mRenderer);
        SDL_RenderPresent(mRenderer);
        
        SDL_Delay(16);
    }
    
    /* Changer le style pour la simulation */
    AppliquerStyleSimulation();
    
    return config;
}

/**
 * @brief Prépare une nouvelle frame ImGui
 */
void GUI::DebutFrame()
{
    ImGui_ImplSDL3_NewFrame();
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui::NewFrame();
}

/**
 * @brief Finalise et rend la frame ImGui
 * @param renderer Pointeur vers le renderer SDL
 */
void GUI::FinFrame(SDL_Renderer *renderer)
{
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

/**
 * @brief Affiche le panneau de contrôle avec sliders et boutons
 */
void GUI::AfficherPanneauControle(int &nbProies, int &nbPreds, int &nbPlantes,
                                   int &nbPlantesConso, float &delaiPlantes,
                                   bool &enPause, bool &enCours, bool &relancer,
                                   int windowWidth)
{
    ImGui::SetNextWindowPos(ImVec2(windowWidth - 330, 10));
    ImGui::SetNextWindowSize(ImVec2(320, 420));
    
    ImGui::Begin("⚙️ Contrôles");
    
    /* Boutons de contrôle */
    if (ImGui::Button(enPause ? "▶️ Reprendre" : "⏸️ Pause", ImVec2(-1, 40)))
    {
        enPause = !enPause;
    }
    
    if (ImGui::Button("🔄 Relancer", ImVec2(-1, 40)))
    {
        relancer = true;
    }
    
    if (ImGui::Button("❌ Quitter", ImVec2(-1, 40)))
    {
        enCours = false;
    }
    
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 5));
    
    /* Paramètres */
    ImGui::Text("Paramètres de Relance");
    ImGui::Dummy(ImVec2(0, 5));
    ImGui::SliderInt("Proies", &nbProies, 5, 50);
    ImGui::SliderInt("Prédateurs", &nbPreds, 1, 20);
    ImGui::SliderInt("Plantes", &nbPlantes, 10, 100);
    ImGui::SliderInt("Satiété", &nbPlantesConso, 10, 100);
    ImGui::SliderFloat("Repousse", &delaiPlantes, 1.0f, 10.0f, "%.1fs");
    
    ImGui::End();
}

/**
 * @brief Affiche les statistiques et graphiques de population avec courbes
 */
void GUI::AfficherStatistiques(int nbProies, int nbPreds, int nbPlantes,
                                int nbConsommees)
{
    mHistoriqueProies.push_back(static_cast<float>(nbProies));
    mHistoriquePredateurs.push_back(static_cast<float>(nbPreds));
    mHistoriquePlantes.push_back(static_cast<float>(nbPlantes));

    if (mHistoriqueProies.size() > 150)
    {
        mHistoriqueProies.erase(mHistoriqueProies.begin());
        mHistoriquePredateurs.erase(mHistoriquePredateurs.begin());
        mHistoriquePlantes.erase(mHistoriquePlantes.begin());
    }

    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::SetNextWindowSize(ImVec2(360, 550));
    
    ImGui::Begin("📊 Statistiques en Temps Réel");
    
    ImGui::Text("Évolution des Populations");
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 5));
    
    /* Proies */
    ImGui::Text("🐰 Proies : %d", nbProies);
    ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.40f, 0.80f, 0.45f, 1.0f));
    ImGui::PlotLines("##Proies", mHistoriqueProies.data(), mHistoriqueProies.size(),
                     0, nullptr, 0.0f, 60.0f, ImVec2(0, 100));
    ImGui::PopStyleColor();
    
    ImGui::Dummy(ImVec2(0, 5));
    
    /* Prédateurs */
    ImGui::Text("🐺 Prédateurs : %d", nbPreds);
    ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.90f, 0.35f, 0.35f, 1.0f));
    ImGui::PlotLines("##Predateurs", mHistoriquePredateurs.data(), mHistoriquePredateurs.size(),
                     0, nullptr, 0.0f, 25.0f, ImVec2(0, 100));
    ImGui::PopStyleColor();
    
    ImGui::Dummy(ImVec2(0, 5));
    
    /* Plantes */
    ImGui::Text("🌱 Plantes : %d", nbPlantes);
    ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.35f, 0.65f, 0.90f, 1.0f));
    ImGui::PlotLines("##Plantes", mHistoriquePlantes.data(), mHistoriquePlantes.size(),
                     0, nullptr, 0.0f, 120.0f, ImVec2(0, 100));
    ImGui::PopStyleColor();
    
    ImGui::Dummy(ImVec2(0, 10));
    ImGui::Separator();
    ImGui::Text("🍃 Plantes Consommées : %d", nbConsommees);

    ImGui::End();
}