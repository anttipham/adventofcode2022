from collections import namedtuple, Counter
import math

Monkey = namedtuple('Monkey', ['items', 'op', 'op_with', 'mod', 'true_monkey', 'false_monkey'])


def main():
    monkeys = []
    try:
        while True:
            input()  # Monkey 0:
            _, _, *items = input().split()  # Starting items: 79, 98
            _, _, _, _, op, op_with = input().split()  # Operation: new = old * 19
            _, _, _, mod = input().split()  # Test: divisible by 23
            _, _, _, _, _, true_monkey = input().split()  # If true: throw to monkey 2
            _, _, _, _, _, false_monkey = input().split()  # If false: throw to monkey 3

            items = [int(x.strip(",")) for x in items]
            mod = int(mod)
            try:
                op_with = int(op_with)
            except ValueError:
                op_with = 0
            true_monkey = int(true_monkey)
            false_monkey = int(false_monkey)

            monkeys.append(Monkey(items, op, op_with, mod, true_monkey, false_monkey))
            input()  # \n
    except EOFError:
        pass

    biz = Counter()
    mod = math.prod([x.mod for x in monkeys])
    for i in range(10000):
        for mi, m in enumerate(monkeys):
            while m.items:
                item = m.items[0]
                biz[mi] += 1
                del m.items[0]

                op_with = m.op_with if m.op_with else item
                if m.op == "+":
                    item += op_with
                if m.op == "*":
                    item *= op_with
                item = item % mod
                if item % m.mod == 0:
                    monkeys[m.true_monkey].items.append(item)
                else:
                    monkeys[m.false_monkey].items.append(item)
        if i % 1000 == 0:
            print(i+1, biz.most_common())

    print(biz.most_common(2)[0][1] * biz.most_common(2)[1][1])

main()
