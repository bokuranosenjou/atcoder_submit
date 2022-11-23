N,x = map(int,input().split())
if x == 1 or x == 2 * N - 1:
    print("No")
elif N == 2:
    print("Yes")
    print(1)
    print(2)
    print(3)
else:
    print("Yes")
    ans = [-1] * (2 * N)
    use = [False] * (2*N)
    if x > 2:
        ans[N-1] = x - 1
        ans[N] = x
        ans[N+1] = x + 1
        ans[N+2] = x - 2
        use[x-1] = True
        use[x] = True
        use[x+1] = True
        use[x-2] = True
    else:
        ans[N-1] = x + 1
        ans[N] = x
        ans[N+1] = x - 1
        ans[N+2] = x + 2
        use[x+1] = True
        use[x] = True
        use[x-1] = True
        use[x+2] = True
    num = 1
    for i in range(1,2*N):
        if ans[i] != -1:continue
        while True:
            if use[num] :
                num += 1
            else:
                ans[i] = num
                num += 1
                break
    print(*ans[1:],sep="\n")