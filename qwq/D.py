T = int (input())
for _ in range(0, T):
    a, b, c, k = map(int, input().split(' '))
    for i in range(0, k):
        if a == b == c:
            break
        a, b, c = (b + c) // 2, (a + c) // 2, (a + b) // 2
    print(a, b, c)