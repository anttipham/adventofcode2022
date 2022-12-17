from dataclasses import dataclass
import re
from itertools import product

@dataclass(frozen=True)
class Valve:
    name: str
    flow: int
    next: tuple

    def __repr__(self) -> str:
        return self.name

def dfs(cur1: Valve, cur2: Valve, nextvalves: dict, distance1=0, distance2=0, visited=set(), curflow=0, cumulativeflow=0, depth=-1):
    visited = visited.copy()
    # visit
    travel = min(distance1, distance2)
    for _ in range(travel):
        if depth >= 26:
            return cumulativeflow
        depth += 1
        cumulativeflow += curflow
    distance1 -= travel
    distance2 -= travel

    # opening valve
    if depth >= 26:
        return cumulativeflow
    depth += 1
    cumulativeflow += curflow
    distance1 -= 1
    distance2 -= 1

    # opened valve
    if distance1 == -1:
        curflow += cur1.flow
        visited.add(cur1)
    if cur1 != cur2 and distance2 == -1:
        curflow += cur2.flow
        visited.add(cur2)

    maxflow = 0
    nextvalves1 = (valve for valve in nextvalves[cur1] if valve not in visited) if distance1 == -1 else [(cur1, distance1)]
    nextvalves2 = (valve for valve in nextvalves[cur2] if valve not in visited) if distance2 == -1 else [(cur2, distance2)]
    nextvalvepairs = product(nextvalves1, nextvalves2)

    for nextvalves1_, nextvalves2_ in nextvalvepairs:
        next1, nextdistance1 = nextvalves1_
        next2, nextdistance2 = nextvalves2_
        if next1 in visited or next2 in visited:
            continue
        maxflow = max(maxflow, dfs(next1, next2, nextvalves, nextdistance1, nextdistance2, visited, curflow, cumulativeflow, depth))

    if maxflow == 0:
        for _ in range(26 - depth):
            if depth >= 26:
                return cumulativeflow
            depth += 1
            cumulativeflow += curflow
        return cumulativeflow
    return maxflow

def bfs(cur: Valve, valves: dict, nextvalves: list):
    queue: list[tuple[Valve, int]] = [(cur, 0)]
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
    print(dfs(valves["AA"], valves["AA"], nextvalves))

main()
