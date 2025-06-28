import subprocess
import tempfile
import os

from modules.const import *

def write_c_map_file(map_rows, filename):
    print("map_rows: " + str(map_rows))
    height = len(map_rows)
    width = len(map_rows[0]) if height > 0 else 0
    with open(filename, "w") as f:
        f.write(f"{width} {height}\n")
        for row in map_rows:
            print("row: " + str(row))
            f.write(row + "\n")

def run_solver(map_rows):
    # Create a temporary file for the map
    with tempfile.NamedTemporaryFile(mode="w+", delete=False, suffix=".in") as tmp_file:
        write_c_map_file(map_rows, "./tmp_level.in")

    try:
        result = subprocess.run(
            [SOLVER_EXECUTABLE, "./tmp_level.in"],
            capture_output=True,
            text=True
        )
        return result.stdout
    finally:
        os.remove("./tmp_level.in")

def parse_solver_output(output):
    solution = None
    maps_explored = None
    for line in output.splitlines():
        if line.startswith("Solution found:"):
            solution = line.split(":", 1)[1].strip()
        elif line.startswith("Maps explored:"):
            maps_explored = int(line.split(":", 1)[1].strip())
    return solution, maps_explored