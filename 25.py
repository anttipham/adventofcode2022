from itertools import pairwise

def todec(snafu):
    if not snafu:
        return 0
    zeros = len(snafu) - 1
    digit = snafu[0]
    if digit == "-": digit = "-1"
    if digit == "=": digit = "-2"
    return int(f"{digit + zeros*'0'}", 5) + todec(snafu[1:])

def tosnafu(dec):
    startingSnafu = "2"
    while todec(f"{startingSnafu}") < dec:
        startingSnafu += "2"
    snafu = len(startingSnafu) * ["="]
    def test(char, i):
        copy = snafu.copy()
        copy[i] = char
        return todec("".join(copy))
    for i in range(len(snafu)):
        snafu[i] = "2"
        for lower, higher in pairwise("=-012"):
            if test(lower, i) <= dec < test(higher, i):
                snafu[i] = lower
    return "".join(snafu)

def main():
    r = 0
    try:
        while s := input():
            r += todec(s)
    except EOFError:
        pass
    print(tosnafu(r))

main()
