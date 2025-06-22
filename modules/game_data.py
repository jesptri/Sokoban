import streamlit as st
import subprocess
import os
from PIL import Image
from io import BytesIO
import base64

from modules.const import *

# Mise en cache des images converties en HTML <img>
@st.cache_resource
def load_tile_images():
    img_tags = {}
    for char, filename in TILE_MAP.items():
        # print(IMAGE_DIR, filename)
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

def run_game(commands, level_path):
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
            # print("char: " + str(char))
            html += img_tags.get(char, img_tags.get(" ", "<span>?</span>"))
        html += "<br>"
    st.markdown(html, unsafe_allow_html=True)    