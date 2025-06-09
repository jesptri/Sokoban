import streamlit as st
import os
import time
from datetime import datetime

from game_data import *
from sokoban_api.schemas import *
from sokoban_api.main import add_result
from sokoban_api.database import SessionLocal, engine
import sokoban_api.models as models

models.Base.metadata.create_all(bind=engine)

# st.session_state

db = SessionLocal()
level_names_list = list(FILE_MAP.keys())

col_1, col_2 = st.columns(2)
with col_1:
    player_name = st.text_input("Enter your name: ", key="player_name", placeholder="Player Name")
    if "player_name" not in st.session_state:
        st.session_state.player_name = player_name

with col_2:
    selected_level = st.selectbox("Choose the level: ", level_names_list, key = "level_select", on_change=lambda: st.session_state.update({"commands": ""}))




level_path = FILE_MAP[selected_level]

if not os.path.exists(EXECUTABLE):
    st.error(f"Executable not found at: {EXECUTABLE}")
    st.stop()

# Initialiser les commandes utilisateur
if "commands" not in st.session_state:
    st.session_state.commands = ""

# Store start time if not already set
if "start_time" not in st.session_state:
    st.session_state.start_time = time.time()    

# Chargement des images converties
img_tags = load_tile_images()

#### APP ####

# Title and instructions

st.title("Sokoban Game")
st.markdown("Use the buttons to move the player!")

# Execution of the game
output_lines = run_game(st.session_state.commands, level_path)
display_map("\n".join(output_lines[:-1]), img_tags)

for line in output_lines:
    if "Won!" in line:
        elapsed_time = int(time.time() - st.session_state.start_time)
        result = ResultCreate(
            player_name = str(player_name) if player_name else "player_name",
            has_won = True,  
            moves = len(st.session_state.commands),   
            level = int(selected_level.split(' ')[1]),
            time = elapsed_time,
            date = str(datetime.now().strftime("%Y-%m-%d %H:%M:%S")),
            has_saved_game = False
        )
        
        add_result(result, db)
        st.success("🎉 Congratulations, you won !")
        break



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

print("Number of commands:", len(st.session_state.commands))

# Restart button

col_restart, col_save_game = st.columns(2)
with col_restart:
    if st.button("🔄 Restart"):
        st.session_state.commands = ""
        st.rerun()
with col_save_game:
    if st.button("💾 Save Game"):
        print("Saving game...")
        result = ResultCreate(
            player_name = str(player_name) if player_name else "player_name",
            has_won = True,  
            moves = len(st.session_state.commands),   
            level = int(selected_level.split(' ')[1]),
            time = 0,
            date = str(datetime.now().strftime("%Y-%m-%d %H:%M:%S")),
            last_map = str(output_lines),
            has_saved_game = True
        )
        add_result(result, db)
        st.success("🎉 Congratulations, you won !")
        st.rerun()