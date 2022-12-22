import re

def main():
    board = []
    max_width = 0
    while s := input():
        board.append(s)
        max_width = max(max_width, len(s))
    max_height = len(board)

    path = (int(x) if x.isdigit() else x for x in re.findall(r"L|R|\d+", input()))

    x = 0
    y = 0
    while board[y][x] == " ":
        x += 1

    dx = 1
    dy = 0
    for p in path:
        if p == "L":
            dx, dy = dy, -dx
            continue
        if p == "R":
            dx, dy = -dy, dx
            continue

        nextx = x
        nexty = y
        for _ in range(p):
            while True:
                nextx += dx
                nexty += dy
                nextx %= max_width
                nexty %= max_height
                try:
                    if board[nexty][nextx] != " ":
                        break
                except IndexError:
                    pass
            if board[nexty][nextx] == "#":
                break
            x = nextx
            y = nexty
    if dx:
        f = abs(dx - 1)
    else:
        f = abs(dy - 2)
    print(1000 * (y+1) + 4 * (x+1) + f)


main()
