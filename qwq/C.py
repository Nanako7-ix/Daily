n = int (input())
a = map(int, input().split(' '))

ans = 0
for _ in a:
    ans += _ != 1

print(ans)