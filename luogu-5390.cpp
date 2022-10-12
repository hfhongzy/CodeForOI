#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 3e6 + 5, mod = 998244353;
int n, cnt[31], pw[N];
inline int MOD(int x) { return x >= mod ? x - mod : x; }
int main() {
   int test; scanf("%d", &test);
   pw[0] = 1;
   rep(i, 1, N - 1) pw[i] = MOD(pw[i - 1] + pw[i - 1]);
   while(test --) {
      fill(cnt, cnt + 31, 0);
      scanf("%d", &n);
      int y = 0;
      rep(i, 1, n) {
         int x; scanf("%d", &x);
         y |= x;
      }
      y = 1ll * y * pw[n - 1] % mod;
      printf("%d\n", y);
   }
   return 0;
}