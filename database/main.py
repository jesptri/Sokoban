from fastapi import FastAPI, Depends
from sqlalchemy.orm import Session
from . import models, schemas, crud
from .database import SessionLocal, engine
from typing import List

response_model=List[schemas.ResultOut]

models.Base.metadata.create_all(bind=engine)

app = FastAPI()

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()

@app.post("/results/", response_model=schemas.ResultOut)
def add_result(result: schemas.ResultCreate, db: Session = Depends(get_db)):
    return crud.create_result(db, result)

@app.get("/results/", response_model=List[schemas.ResultOut])
def get_results(username, skip: int = 0, limit: int = 10, db: Session = Depends(get_db)):
    return crud.get_results(db, username, skip=skip, limit=limit)

def get_saved_maps(level, player_name, skip: int = 0, limit: int = 100, db=None):
    if db is None:
        db = SessionLocal()
    return (
        db.query(models.Result)
        .filter(models.Result.has_saved_game == True and models.Result.level == level and player_name == player_name)
        .offset(skip)
        .limit(limit)
        .all()
    )