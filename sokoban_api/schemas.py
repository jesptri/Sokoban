from typing import Optional
from pydantic import BaseModel

class ResultCreate(BaseModel):
    player_name: str
    has_won: bool
    moves: int
    level: int
    time: int
    date: str
    last_map: Optional[str] = None
    has_saved_game: bool = False

class ResultOut(ResultCreate):
    id: int

    class Config:
        orm_mode = True
