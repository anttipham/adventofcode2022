def main():
    ss = ""
    x = 1
    i = 0
    try:
        while s := input():
            if x-1 <= i and i <= x+1:
                ss += "#"
            else:
                ss += "."
            if i % 40 == 0:
                ss += "\n"

            i += 1
            i = i % 40
            if s == 'noop':
                continue

            # print(s)
            _, value = s.split()
            value = int(value)
            if x-1 <= i and i <= x+1:
                ss += "#"
            else:
                ss += "."
            if i % 40 == 0:
                ss += "\n"

            i += 1
            i = i % 40
            x += value
    except EOFError:
        pass

    print(ss)


main()
