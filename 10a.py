def main():
    strength = 0
    x = 1
    i = 0
    try:
        while s := input():
            i += 1
            if (i-20) % 40 == 0:
                print(i, x)
                strength += i * x

            if s == 'noop':
                continue

            i += 1
            _, value = s.split()
            value = int(value)
            if (i-20) % 40 == 0:
                print(i, x)
                strength += i * x

            x += value
    except EOFError:
        pass

    print(strength)


main()
