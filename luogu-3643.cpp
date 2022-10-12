#include <algorithm>
#include <cstdio>
using namespace std;

const int mod = 1e9 + 7, N = 610;

int n, a[N], b[N], c[N * 2], f[N], bin[N], inv[N];

int main() {
   scanf("%d", &n);
   for(int i = 1; i <= n; i ++) {
      scanf("%d%d", a + i, b + i);
      c[i * 2 - 1] = a[i];
      c[i * 2] = ++ b[i];
   }
   c[2 * n + 1] = 0;
   sort(c + 1, c + 2 * n + 2);
   int m = unique(c + 1, c + 2 * n + 2) - c - 1;
   for(int i = 1; i <= n; i ++) {
      a[i] = lower_bound(c + 1, c + m + 1, a[i]) - c;
      b[i] = lower_bound(c + 1, c + m + 1, b[i]) - c;
   }
   inv[1] = 1;
   for(int i = 2; i <= n; i ++) {
      inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
   }
   f[0] = 1;
   for(int j = 2; j <= m; j ++) { //[c[j-1], c[j])
      int L = c[j] - c[j - 1];
      bin[0] = 1;
      for(int i = 1; i <= n; i ++) bin[i] = bin[i - 1] * (i + L - 1ll) % mod * inv[i] % mod;
      for(int i = n; i >= 1; i --) if(a[i] <= j - 1 && b[i] >= j) {
         int cur = 0, cnt = 1;
         for(int k = i - 1; k >= 0; k --) {
            cur = (cur + 1ll * f[k] * bin[cnt]) % mod;
            cnt += (a[k] <= j - 1 && b[k] >= j);
         }
         (f[i] += cur) %= mod;
      }
   }
   int ans = 0;
   for(int i = 1; i <= n; i ++) (ans += f[i]) %= mod;
   printf("%d\n", ans);
   return 0;
}
/*
f[i][j] = \sum_{k = 0}^{i - 1} f[k][1..j-1] * C(c + L - 1, c);
*/