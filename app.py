import streamlit as st
import os
import time
from datetime import datetime
import ast

from modules.utils import *
from modules.game_data import *
from database.schemas import *
from database.main import add_result, get_saved_maps
from database.database import SessionLocal, engine
import database.models as models

st.session_state

# Chargement des images converties
img_tags = load_tile_images()
# print("img_tags: " + str(img_tags))

models.Base.metadata.create_all(bind=engine)

db = SessionLocal()
level_names_list = list(FILE_MAP.keys())

col_1, col_2, col_3 = st.columns(3)


with col_1:
    player_name = st.text_input("Enter your name: ", key="player_name", placeholder="Player Name")
    if "player_name" not in st.session_state:
        st.session_state.player_name = player_name


with col_2:
    selected_level = st.selectbox(
        "Choose the level: ",
        level_names_list,
        key="level_select",
        on_change=lambda: st.session_state.update({"commands": ""})
    )


saved_maps = get_saved_maps(level=selected_level.split(' ')[1], player_name=player_name, db=db)
reload_options_first_list_element = ["Reload a level ?"]
reload_options = [str(get_date_format(i.date)) + " (" + str(i.moves) + " " + move_or_moves(i.moves) + ")" for i in saved_maps] if saved_maps else ["No saves"]

with col_3:
    reloaded_level = st.selectbox(
        "Reload level: ",
        reload_options_first_list_element + reload_options,
        key="reload_level"
    )

level_path = FILE_MAP[selected_level]

if not os.path.exists(EXECUTABLE):
    st.error(f"Executable not found at: {EXECUTABLE}")
    st.stop()


if "commands" not in st.session_state:
    st.session_state.commands = ""
    
if "is_map_reloaded" not in st.session_state:
    st.session_state.is_map_reloaded = False


if "start_time" not in st.session_state:
    st.session_state.start_time = time.time()


# === APP === #


st.title("Sokoban Game")
st.markdown("Use the buttons to move the player!")

map_loaded_from_save = False
saved_map_obj = None

if "reload_level" in st.session_state:
    reload_value = st.session_state["reload_level"]
    if reload_value not in reload_options_first_list_element and reload_value != "No saves":
        index = reload_options.index(reload_value)
        saved_map_obj = saved_maps[index]
        map_loaded_from_save = True

        if not st.session_state["is_map_reloaded"]:
            output_lines = ast.literal_eval(saved_map_obj.last_map)
            display_map("\n".join(output_lines[:-1]), img_tags)
            map_loaded_from_save = False
            st.session_state["is_map_reloaded"] = True
            # st.rerun()
# else:
output_lines = run_game(st.session_state.commands, level_path)
display_map("\n".join(output_lines[:-1]), img_tags)

# Vérification victoire
for line in output_lines:
    if "Won!" in line:
        elapsed_time = int(time.time() - st.session_state.start_time)
        try:
            level_number = int(selected_level.split(' ')[1])
        except (IndexError, ValueError):
            level_number = 0
        result = ResultCreate(
            player_name=str(player_name) if player_name else "player_name",
            has_won=True,
            moves=len(st.session_state.commands),
            level=level_number,
            time=elapsed_time,
            date=datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
            has_saved_game=False
        )
        add_result(result, db)
        st.success("🎉 Congratulations, you won !")
        break

# Contrôles de déplacement
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

# Boutons restart / save
col_restart, col_save_game = st.columns(2)

with col_restart:
    if st.button("🔄 Restart"):
        st.session_state.commands = ""
        st.rerun()

with col_save_game:
    if st.button("💾 Save Game"):
        print("Saving game...")
        try:
            level_number = int(selected_level.split(' ')[1])
        except (IndexError, ValueError):
            level_number = 0
        result = ResultCreate(
            player_name=str(player_name) if player_name else "player_name",
            has_won=True,
            moves=len(st.session_state.commands),
            level=level_number,
            time=0,
            date=datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
            last_map="\n".join(output_lines[:-1]),  # ✅ correction ici
            has_saved_game=True
        )
        add_result(result, db)
        st.success("🎉 Game saved!")
        st.rerun()
