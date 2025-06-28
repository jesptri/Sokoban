from sqlalchemy.orm import Session
from . import models, schemas

def create_result(db: Session, result: schemas.ResultCreate):
    db_result = models.Result(**result.dict())
    db.add(db_result)
    db.commit()
    db.refresh(db_result)
    return db_result

def get_results(db: Session, player_name: str, skip: int = 0, limit: int = 10):
    return (db.query(models.Result)
            .filter(models.Result.player_name == player_name)
            .order_by(models.Result.moves.desc())
            .offset(skip)
            .limit(limit)
            .all())

def get_ranking_by_time(db: Session, level: int, skip: int = 0, limit: int = 10):
    return (
        db.query(models.Result)
        .filter(models.Result.level == level, models.Result.has_won == True)
        .order_by(models.Result.time.asc())
        .offset(skip)
        .limit(limit)
        .all()
    )

def get_ranking_by_moves(db: Session, level: int, skip: int = 0, limit: int = 10):
    return (
        db.query(models.Result)
        .filter(models.Result.level == level, models.Result.has_won == True)
        .order_by(models.Result.moves.asc())
        .offset(skip)
        .limit(limit)
        .all()
    )
