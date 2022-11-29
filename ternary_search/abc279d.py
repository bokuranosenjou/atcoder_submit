from math import sqrt
A,B = map(int,input().split())

def f(n):
    return B * n + A / sqrt(1 + n)

l = -1
r = 1 << 60
while abs(l-r) > 3:
    t1 = (2 * l + r) // 3
    t2 = (l + r * 2) // 3
    if (f(t1) < f(t2)): r = t2
    else: l = t1

ans = 1<<60
for i in range(l-5,r+5):
    if (i < 0):continue
    ans = min(ans, f(i))
print(ans)
