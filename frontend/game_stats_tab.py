import streamlit as st
from database.database import SessionLocal
from database.crud import get_ranking_by_time, get_ranking_by_moves

def game_stats():
    db = SessionLocal()
    level = st.number_input("Select level", min_value=0, step=1)
    ranking_type = st.selectbox("Rank by", ["Time", "Moves"])

    if ranking_type == "Time":
        ranking = get_ranking_by_time(db, level)
    else:
        ranking = get_ranking_by_moves(db, level)

    if ranking:
        st.write(f"### Best players for level {level} (by {ranking_type.lower()})")
        st.table([
            {
                "Player": r.player_name,
                "Moves": r.moves,
                "Time": r.time,
                "Date": r.date
            }
            for r in ranking
        ])
        best = ranking[0]
        st.success(f"🏆 Best player: {best.player_name} ({best.moves} moves, {best.time} seconds)")
    else:
        st.info("No player has managed to win this level yet!")