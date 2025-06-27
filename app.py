import streamlit as st
import os
import time
from datetime import datetime
import ast

from frontend.game_stats_tab import *
from frontend.play_game_tab import *

from modules.utils import *
from modules.game_data import *

from database.schemas import *
from database.database import SessionLocal, engine
import database.models as models

# === APP === #

st.sidebar.title("Sokoban Game")

with st.sidebar:
    player_name = st.text_input("Enter your username: ", key="player_name", placeholder="Player Name")
    if "player_name" not in st.session_state:
        st.session_state.player_name = player_name
        
    st.info(GAME_EXPLANATIONS)

if not player_name:
    st.info("You are currently playing anonymously.")    
else:
    st.info("You are currently playing under '" + str(player_name) + "' username.")

tabs = st.tabs(TABS_NAMES)

models.Base.metadata.create_all(bind=engine)

db = SessionLocal()

with tabs[0]:
    play_game(player_name, db)
    
with tabs[1]:
    game_stats()
