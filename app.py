import streamlit as st
import subprocess
import os
from PIL import Image
from io import BytesIO
import base64

# Chemins
# LEVEL_PATH = "levels/soko_dumb.in"
EXECUTABLE = "./play_step"
IMAGE_DIR = "images"

# Taille standard des tiles (32x32)
TILE_SIZE = (32, 32)

# Mapping file name → level name

file_map = {
    "Level 1": "levels/level1.in",
    "Level 2": "levels/level2.in",
    "Level 3": "levels/level3.in",
    "Level 4": "levels/level4.in",
    "Level 5": "levels/level5.in",
    "Level 6": "levels/level6.in",
    "Level 7": "levels/level7.in",
    "Level 8": "levels/level8.in",
}

level_names_list = list(file_map.keys())

selected_level = st.selectbox("Choose the level: ", level_names_list, key = "level_select")

level_path = file_map[selected_level]

# Mapping caractères → fichiers image
tile_map = {
    "#": "yoshi-32-bordered-wall.bmp",
    "@": "yoshi-32-worker.bmp",
    "$": "yoshi-32-box.bmp",
    ".": "yoshi-32-dock.bmp",
    " ": "yoshi-32-floor.bmp",
    "+": "yoshi-32-worker-docked.bmp",
    "*": "yoshi-32-box-docked.bmp",  # au cas où
}

# S'assurer que l'exécutable est présent
if not os.path.exists(EXECUTABLE):
    st.error(f"Executable not found at: {EXECUTABLE}")
    st.stop()

# Initialiser les commandes utilisateur
if "commands" not in st.session_state:
    st.session_state.commands = ""

# Mise en cache des images converties en HTML <img>
@st.cache_resource
def load_tile_images():
    img_tags = {}
    for char, filename in tile_map.items():
        path = os.path.join(IMAGE_DIR, filename)
        if os.path.exists(path):
            img = Image.open(path).resize(TILE_SIZE)
            buffered = BytesIO()
            img.save(buffered, format="PNG")
            img_str = base64.b64encode(buffered.getvalue()).decode("utf-8")
            tag = f'<img src="data:image/png;base64,{img_str}" width="{TILE_SIZE[0]}" height="{TILE_SIZE[1]}">'
            img_tags[char] = tag
        else:
            img_tags[char] = f"<span>{char}</span>"  # fallback
    return img_tags

def run_game(commands):
    try:
        result = subprocess.run(
            [EXECUTABLE, level_path, commands],
            capture_output=True,
            text=True,
            check=True
        )
        return result.stdout.split('\n')  # << CORRIGÉ ICI
    except subprocess.CalledProcessError as e:
        return [f"Erreur : {e.stderr}"]

# Fonction d'affichage graphique de la carte
def display_map(map_str, img_tags):
    rows = map_str.strip().split("\n")
    html = ""
    for row in rows:
        for char in row:
            html += img_tags.get(char, img_tags.get(" ", "<span>?</span>"))
        html += "<br>"
    st.markdown(html, unsafe_allow_html=True)

# Chargement des images converties
img_tags = load_tile_images()

# Titre et interface
st.title("Sokoban Game")
st.markdown("Use the buttons to move the player!")

# Exécution du jeu
output_lines = run_game(st.session_state.commands)
display_map("\n".join(output_lines[:-1]), img_tags)

print("output_lines:" + str(output_lines))

for line in output_lines:
    if "Won!" in line:
        st.success("🎉 Bravo, tu as gagné !")
        break

# Contrôles de mouvement
col1, col2, col3 = st.columns(3)
with col2:
    if st.button("↑"):
        st.session_state.commands += "n"
        st.rerun()
with col1:
    if st.button("←"):
        st.session_state.commands += "w"
        st.rerun()
with col3:
    if st.button("→"):
        st.session_state.commands += "e"
        st.rerun()
if st.button("↓"):
    st.session_state.commands += "s"
    st.rerun()

# Bouton de reset
if st.button("🔄 Restart"):
    st.session_state.commands = ""
    st.rerun()
