def read():
    try:
        rocks = set()
        while s := input():
            through = [tuple(int(x) for x in point.split(",")) for point in s.split(" -> ")]
            for i in range(len(through)-1):
                x1, y1 = through[i]
                x2, y2 = through[i+1]
                if x1 > x2:
                    x1, x2 = x2, x1
                if y1 > y2:
                    y1, y2 = y2, y1
                if x1 == x2:
                    rocks.update((x1, y) for y in range(y1, y2+1))
                if y1 == y2:
                    rocks.update((x, y1) for x in range(x1, x2+1))
    except EOFError:
        pass
    return rocks


def dfs(cur, rocks, sand, maxY):
    x, y = cur
    if cur in rocks or cur in sand:
        return True

    for next in ((x, y+1), (x-1, y+1), (x+1, y+1)):
        if next in rocks or next in sand or next[1] >= maxY+2:
            continue
        if not dfs(next, rocks, sand, maxY):
            return False
    sand.add(cur)
    return True


def main():
    rocks = read()
    sand = set()
    maxY = max(y for _, y in rocks)
    dfs((500, 0), rocks, sand, maxY)
    # rocksX = [x for x, y in rocks]
    # for i in range(max(rocksY)+1):
    #     for j in range(min(rocksX), max(rocksX)+1):
    #         if (j, i) in sand:
    #             print("o", end="")
    #         elif (j, i) in rocks:
    #             print("#", end="")
    #         else:
    #             print(".", end="")
    #     print()
    print(len(sand))


main()
