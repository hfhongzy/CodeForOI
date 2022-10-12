#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int n, r, b, top, st[N], sum[N], ans[N];
char s[N];
int main() {
   scanf("%d%d%d%s", &n, &r, &b, s + 1);
   if(r == 0) {
      bool mark = b && (n % b == 0);
      rep(i, 1, n) if(s[i] == 'R') mark = 0;
      puts(mark ? "YES" : "NO");
      if(mark) {
         printf("%d\n", n / b);
         rep(i, 1, n) {
            printf("%d ", i);
            if(i % b == 0) putchar('\n');
         }
      }
      return 0;
   }
   
   rep(i, 1, n) {
      st[++ top] = i; sum[top] = sum[top - 1] + (s[i] == 'R' ? 1 : -1);
      if(top >= r + b && sum[top] - sum[top - r - b] == r - b) {
         rep(j, top - r - b + 1, top) ans[++ ans[0]] = st[j];
         top -= r + b;
      }
   }
   if(top) {
      puts("NO");
      return 0;
   }
   puts("YES");
   printf("%d\n", n / (r + b));
   per(i, n, 1) {
      printf("%d ", ans[i]);
      if(i % (r + b) == 1) putchar('\n');
   }
   return 0;
}