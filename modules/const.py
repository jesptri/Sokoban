PLAY_EXECUTABLE = "./play_step"
SOLVER_EXECUTABLE = "./solve"

IMAGE_DIR = "modules/images"
TILE_SIZE = (40,40) #(32, 32)

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

LEVEL_NAMES_LIST = list(FILE_MAP.keys())

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

GAME_EXPLANATIONS = """
🎮 **About your player ID:**

You can play the game **without entering a username**. In that case, you’ll be automatically assigned to a **shared guest account**, which is used by everyone who plays anonymously. This means your scores will be mixed with other anonymous players.

If you choose to enter a **custom username**, make sure to **remember and reuse it** in future sessions so your scores stay linked to your name.

🧠 Please be **fair**: don’t use someone else’s username on purpose. Respecting others keeps the game fun for everyone!

---

ℹ️ **P.S.**: I intentionally chose **not to implement a password system**, as I believe it’s unnecessary for a casual game like this. The goal is to keep things light, fun, and accessible without the burden of account creation.
"""

TABS_NAMES = ["Play the game !", "Overall game stats"]
