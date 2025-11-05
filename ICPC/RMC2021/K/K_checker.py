#!/usr/bin/env python3
import sys
from pathlib import Path

def read_only_line(path: Path) -> str:
    try:
        with path.open('r', encoding='utf-8') as f:
            line = f.readline()
            # ensure it's the only line
            extra = f.readline()
    except FileNotFoundError:
        sys.exit(f"Error: file not found: {path}")
    if line == "":
        sys.exit(f"Error: file is empty: {path}")
    if extra != "":
        sys.exit(f"Error: expected exactly one line in {path}, but found more.")
    return line.rstrip("\n")

def read_third_line(path: Path) -> str:
    try:
        with path.open('r', encoding='utf-8') as f:
            lines = f.readlines()
    except FileNotFoundError:
        sys.exit(f"Error: file not found: {path}")
    if len(lines) < 3:
        sys.exit(f"Error: expected at least 3 lines in {path}, found {len(lines)}.")
    return lines[2].rstrip("\n")

def check_team(final_team, preference):
    if final_team != 'X' and preference != '?' and final_team != preference:
        return False
    
    else:
        return True

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {Path(sys.argv[0]).name} <base>")
        print("Reads <base>.in (3rd line), <base>.ans (only line), and delete.txt (only line).")
        sys.exit(1)

    base_arg = Path(sys.argv[1])
    directory = base_arg.parent if base_arg.parent != Path("") else Path(".")
    stem = base_arg.name  # treat argument as base name (no extension)

    in_path = directory / f"{stem}.in"
    ans_path = directory / f"{stem}.ans"
    del_path = directory / "delete.txt"

    ans_str = read_only_line(ans_path)
    del_str = read_only_line(del_path)
    in_str  = read_third_line(in_path)

    # Count 'X'
    ans_X = ans_str.count('X')
    del_X = del_str.count('X')
    print(f"X count in {ans_path.name}: {ans_X}")
    print(f"X count in {del_path.name}: {del_X}")

    # Verify lengths match
    n1, n2, n3 = len(ans_str), len(del_str), len(in_str)
    if not (n1 == n2 == n3):
        sys.exit(
            f"Error: string lengths differ: "
            f"{ans_path.name}={n1}, {del_path.name}={n2}, {in_path.name} (line 3)={n3}"
        )

    # Check per-index equality
    N = n1
    for i in range(N):
        if not check_team(ans_str[i], in_str[i]):
            sys.exit(
                f"Mismatch at index {i} between {ans_path.name} and {in_path.name}: "
                f"{ans_str[i]!r} != {in_str[i]!r}"
            )
        if not check_team(del_str[i], in_str[i]):
            sys.exit(
                f"Mismatch at index {i} between {del_path.name} and {in_path.name}: "
                f"{del_str[i]!r} != {in_str[i]!r}"
            )

    print(f"OK: All {N} positions match {in_path.name} for both {ans_path.name} and {del_path.name}.")

if __name__ == "__main__":
    main()
