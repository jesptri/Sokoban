from sqlalchemy.orm import Session
from . import models, schemas

def create_result(db: Session, result: schemas.ResultCreate):
    db_result = models.Result(**result.dict())
    db.add(db_result)
    db.commit()
    db.refresh(db_result)
    return db_result

def get_results(db: Session, username: str, skip: int = 0, limit: int = 10):
    return (db.query(models.Result)
            .filter(models.Result.username == username)
            .order_by(models.Result.moves.desc())
            .offset(skip)
            .limit(limit)
            .all())

def get_ranking_by_time(db: Session, username: str, level: str, skip: int = 0, limit: int = 10):
    return (
        db.query(models.Result)
        .filter(models.Result.username == username and models.Result.username == level)
        .order_by(models.Result.time.desc())
        .offset(skip)
        .limit(limit)
        .all()
    )
