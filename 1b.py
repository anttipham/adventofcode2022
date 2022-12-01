a = []
cum = 0
try:
    while True:
        while x := input():
            cum += int(x)
        a.append(cum)
        cum = 0
except EOFError:
    a.sort()
    print(a[-1]+a[-2]+a[-3])