import streamlit as st
import subprocess
import os
from PIL import Image
from io import BytesIO
import base64

from modules.const import *

@st.cache_resource
def load_tile_images():
    IMG_TAGS = {}
    for char, filename in TILE_MAP.items():
        path = os.path.join(IMAGE_DIR, filename)
        if os.path.exists(path):
            img = Image.open(path).resize(TILE_SIZE)
            buffered = BytesIO()
            img.save(buffered, format="PNG")
            img_str = base64.b64encode(buffered.getvalue()).decode("utf-8")
            tag = f'<img src="data:image/png;base64,{img_str}" width="{TILE_SIZE[0]}" height="{TILE_SIZE[1]}">'
            IMG_TAGS[char] = tag
        else:
            IMG_TAGS[char] = f"<span>{char}</span>"
    return IMG_TAGS

IMG_TAGS = load_tile_images()

def run_game(commands, level_path):
    try:
        result = subprocess.run(
            [EXECUTABLE, level_path, commands],
            capture_output=True,
            text=True,
            check=True
        )
        return result.stdout.split('\n')
    except subprocess.CalledProcessError as e:
        return [f"Erreur : {e.stderr}"]

def display_map(map_str, IMG_TAGS):
    rows = map_str.strip().split("\n")
    html = ""
    for row in rows:
        for char in row:
            html += IMG_TAGS.get(char, IMG_TAGS.get(" ", "<span>?</span>"))
        html += "<br>"
    st.markdown(html, unsafe_allow_html=True)    