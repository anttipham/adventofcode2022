from collections import Counter

def main():
    s = input()
    c = Counter()

    c.update(s[:4])
    for i in range(4, len(s)):
        if len(c) == 4:
            print(c)
            print(i)
            return

        c[s[i]] += 1
        c[s[i-4]] -= 1
        if c[s[i-4]] == 0:
            del c[s[i-4]]
        print(c)


main()
