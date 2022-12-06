from collections import Counter

def main():
    s = input()
    c = Counter()

    c.update(s[:14])
    for i in range(14, len(s)):
        if len(c) == 14:
            print(c)
            print(i)
            return

        c[s[i]] += 1
        c[s[i-14]] -= 1
        if c[s[i-14]] == 0:
            del c[s[i-14]]
        # print(c)


main()
