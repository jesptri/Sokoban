EXECUTABLE = "./play_step"
IMAGE_DIR = "modules/images"
TILE_SIZE = (32, 32)

# Mapping file name → level name
FILE_MAP = {
    "Level 0": "levels/level0.in",
    "Level 1": "levels/level1.in",
    "Level 2": "levels/level2.in",
    "Level 3": "levels/level3.in",
    "Level 4": "levels/level4.in",
    "Level 5": "levels/level5.in",
    "Level 6": "levels/level6.in",
    "Level 7": "levels/level7.in",
    "Level 8": "levels/level8.in",
}

# Mapping caractères → fichiers image
TILE_MAP = {
    "#": "yoshi-32-bordered-wall.bmp",
    "@": "yoshi-32-worker.bmp",
    "$": "yoshi-32-box.bmp",
    ".": "yoshi-32-dock.bmp",
    " ": "yoshi-32-floor.bmp",
    "+": "yoshi-32-worker-docked.bmp",
    "*": "yoshi-32-box-docked.bmp",
}