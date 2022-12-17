from dataclasses import dataclass
import re

@dataclass(frozen=True)
class Valve:
    name: str
    flow: int
    next: tuple

    def __repr__(self) -> str:
        return self.name

def dfs(cur: Valve, nextvalves: dict, distance=0, visited=set(), curflow=0, cumulativeflow=0, depth=-1):
    # visit
    for _ in range(distance):
        if depth >= 30:
            return cumulativeflow
        depth += 1
        cumulativeflow += curflow

    # open valve
    if depth >= 30:
        return cumulativeflow
    depth += 1
    cumulativeflow += curflow

    # opened valve
    curflow += cur.flow

    maxflow = 0
    for next, nextdistance in nextvalves[cur]:
        if next in visited:
            continue
        visited.add(next)
        maxflow = max(maxflow, dfs(next, nextvalves, nextdistance, visited, curflow, cumulativeflow, depth))
        visited.remove(next)

    if maxflow == 0:
        for _ in range(30 - depth):
            if depth >= 30:
                return cumulativeflow
            depth += 1
            cumulativeflow += curflow
        return cumulativeflow
    return maxflow

def bfs(cur: Valve, valves: dict, nextvalves: list):
    queue = [(cur, 0)]
    visited = {cur}

    while queue:
        cur, depth = queue.pop(0)
        depth += 1
        for next in (valves[n] for n in cur.next):
            if next in visited:
                continue
            visited.add(next)
            if next.flow:
                nextvalves.append((next, depth))
            queue.append((next, depth))

def main():
    valves: dict[str, Valve] = {}
    try:
        while s := input():
            name_, flow_ = re.match(r"Valve ([A-Z]{2}) has flow rate=(\d+);", s).groups()
            flow_ = int(flow_)
            next_ = re.split(r",? ", s)[9:]
            valves[name_] = Valve(name_, flow_, tuple(next_))
    except EOFError:
        pass

    nextvalves = {}
    a = []
    bfs(valves["AA"], valves, a)
    nextvalves[valves["AA"]] = a
    for valve, _ in a:
        b = []
        bfs(valve, valves, b)
        nextvalves[valve] = b
    print(dfs(valves["AA"], nextvalves))

main()
