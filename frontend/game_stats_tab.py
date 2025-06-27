import streamlit as st
from database.crud import get_ranking_by_time

def game_stats():
    return 0

@st.cache_resource
def get_time_ranking(db, username, level):
    return get_ranking_by_time(db, username, level, 0, 100)
    