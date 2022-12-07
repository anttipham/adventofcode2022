from __future__ import annotations

class Node:
    parent: Node = None
    children: dict[str, Node]
    size: int = 0
    name: str = ""

    def __init__(self) -> None:
        self.children = {}


q = []
def dfs(cur: Node, d=0):
    size = cur.size

    for next_ in cur.children:
        size += dfs(cur.children[next_], d+1)
    q.append(size)
    return size


def main():
    root = Node()
    root.name = "/"
    cur = root
    s = input()
    s = input()
    try:
        while s:
            if s == "$ cd ..":
                cur = cur.parent
                s = input()
            elif s.startswith("$ cd "):
                path = s.removeprefix("$ cd ")
                cur = cur.children[path]
                s = input()
            elif s == "$ ls":
                while (s := input()) and not s.startswith("$"):
                    a, b = s.split()
                    if a == "dir":
                        cur.children[b] = Node()
                        cur.children[b].parent = cur
                        cur.children[b].name = b
                    else:
                        cur.size += int(a)
    except EOFError:
        pass
    dfs(root)


    q.sort()
    used = 70000000 - max(q)
    need = 30000000 - used
    for filesize in q:
        if filesize >= need:
            print(filesize)
            return

main()
