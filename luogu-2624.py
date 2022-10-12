n = int(input())
d = raw_input().split(" ")
if n == 1 and int(d[0]) == 0:
   print(1)
   exit()
fac = [1]
for i in range (1, n):
   fac.append(fac[i - 1] * i)
ans = fac[n - 2];
x = 0
y = n - 2
for i in range (0, n):
   if int(d[i]) == 0:
      ans = 0
   else:
      ans = ans // fac[int(d[i]) - 1]
      y -= int(d[i]) - 1
if y != 0:
   ans = 0
print(ans)