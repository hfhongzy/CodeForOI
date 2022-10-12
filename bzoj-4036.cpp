#include <algorithm>
#include <cstdio>
using namespace std;
typedef double db;
const int N = 1 << 20 | 5;
int n, all, cnt[N];
db p[N], sub[N];
void fwtor(db *a, int n) {
   for(int i = 1; i < n; i <<= 1)
      for(int j = 0; j < n; j += i << 1)
         for(int k = 0; k < i; k ++)
            a[j + k + i] += a[j + k];
}
int main() {
   scanf("%d", &n); n = 1 << n;
   for(int i = 0; i < n; i ++) {
      scanf("%lf", p + i);
      if(i) cnt[i] = cnt[i & (i - 1)] + 1;
      if(p[i] > 0) all |= i;
   }
   if(all < n - 1) { puts("INF"); return 0; }
   copy(p, p + n, sub); fwtor(sub, n); 
   db ans = 0;
   for(int i = 1; i < n; i ++) {
      if(cnt[i] & 1) ans += 1.0 / (1 - sub[all ^ i]);
      else ans -= 1.0 / (1 - sub[all ^ i]);
   }
   printf("%f\n", ans);
   return 0;
}
/*
max(S) = \sum_{T \subset S}^{2^n - 1} (-1)^{|T|-1} min(T)
min(T) = \sigma(p) - subset(C(T))
dp[(1 << n) - 1] = 0;
dp[S] = \sum_{i = 0}^{2^n - 1} p[i] * dp[S | i]
*/