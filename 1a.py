a = []
cum = 0
try:
    while True:
        while x := input():
            cum += int(x)
        a.append(cum)
        cum = 0
except EOFError:
    print(max(a))