n = int(input())
m = n * (n + 1) // 2
ans = pow(2, m)
ans += 3 * pow(2, (m - ((n+1) // 2)) // 2 + ((n+1) // 2))
if n % 3 == 1:
    ans += 2 * pow(2, m // 3 + 1)
else:
    ans += 2 * pow(2, m // 3)
ans = ans // 6
print (ans)