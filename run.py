import subprocess
import sys
from pathlib import Path

# Chemin vers l'exécutable
exe_path = Path("build/simulation.exe")

# Vérifier si l'exécutable existe
if not exe_path.exists():
    print("❌ Exécutable introuvable !")
    print(f"   Cherché: {exe_path}")
    print("\n💡 Compilez d'abord avec: python build.py")
    sys.exit(1)

# Lancer l'exécutable
print(f"🚀 Lancement de {exe_path}...")
print("-" * 50)

try:
    subprocess.run([str(exe_path)])
except KeyboardInterrupt:
    print("\n⏹️  Arrêté par l'utilisateur")
except Exception as e:
    print(f"❌ Erreur: {e}")