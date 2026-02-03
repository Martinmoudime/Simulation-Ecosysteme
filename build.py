import os
import subprocess
from pathlib import Path

# Configuration
SDL3_DIR = "Externals/SDL3"
SRC_FILES = [
    "Src/UI/GUI.cpp",
    "Src/Graphics/Renderer.cpp",
    "Src/Core/Main.cpp",
    "Src/Population/Animal.cpp",
    "Src/Population/Proie.cpp", 
    "Src/Population/Plante.cpp",
    "Src/Population/Predateur.cpp",
    "Src/Population/Ecosysteme.cpp",
    "Externals/imgui/imgui.cpp",
    "Externals/imgui/imgui_draw.cpp",
    "Externals/imgui/imgui_tables.cpp",
    "Externals/imgui/imgui_widgets.cpp",
    "Externals/imgui/backends/imgui_impl_sdl3.cpp",
    "Externals/imgui/backends/imgui_impl_sdlrenderer3.cpp",
]

OUTPUT = "Build/simulation.exe"

# Créer le dossier build
Path("Build").mkdir(exist_ok=True)

# Compiler
cmd = [
    "clang++",
    "-std=c++17",
    "-IExternals/SDL3/include",
    "-ISrc",
    "-IExternals/imgui",
    "-IExternals/imgui/backends",
    "-L" + SDL3_DIR + "/lib",
    "-o", OUTPUT
] + SRC_FILES + ["-lSDL3", "-lSDL3_image"]

print("Compilation...")
result = subprocess.run(cmd)

if result.returncode == 0:
    print("✅ Succès !")
else:
    print("❌ Erreur")