from sqlalchemy import Column, Integer, String, Boolean
from .database import Base

class Result(Base):
    __tablename__ = "results"

    id = Column(Integer, primary_key=True, index=True)
    player_name = Column(String, nullable=False)
    has_won = Column(Boolean, nullable=False, default=False)
    moves = Column(Integer, nullable=False)
    level = Column(Integer, nullable=False)
    time = Column(Integer, nullable=False)
    date = Column(String, nullable=False)
    last_map = Column(String, nullable=True)
    has_saved_game = Column(Boolean, nullable=False, default=False)
