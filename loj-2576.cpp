#include <algorithm>
#include <cstring>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
#define fs first
#define sc second
using namespace std;
typedef pair<int, int> P;
const int N = 1e4 + 10;
const int base = 1926, mod = 1e9 + 7, mod2 = 998244853;
struct hasher {
   P h[N], pw[N];
   void build(char *s) {
      pw[0] = P(1, 1); h[0] = P(0, 0);
      for(int i = 1; s[i]; i ++) {
         pw[i].fs = 1ll * pw[i - 1].fs * base % mod;
         pw[i].sc = 1ll * pw[i - 1].sc * base % mod2;
         h[i].fs = (1ll * h[i - 1].fs * base + s[i]) % mod;
         h[i].sc = (1ll * h[i - 1].sc * base + s[i]) % mod2;
      }
   }
   P calc(char *s) {
      P ans(0, 0);
      for(int i = 1; s[i]; i ++) {
         ans.fs = (1ll * ans.fs * base + s[i]) % mod;
         ans.sc = (1ll * ans.sc * base + s[i]) % mod2;
      }
      return ans;
   }
   P query(int l, int r) {
      return P(
         (h[r].fs - 1ll * pw[r - l + 1].fs * h[l - 1].fs % mod + mod) % mod,
         (h[r].sc - 1ll * pw[r - l + 1].sc * h[l - 1].sc % mod2 + mod2) % mod2
      );
   }
} H;
int k, n, f[N], g[N];
char str[N], tmp[N];
int main() {
   scanf("%d%s", &k, str + 1);
   H.build(str); n = strlen(str + 1);
   rep(i, 0, n) f[i] = 1;
   rep(i, 1, k) {
      copy(f, f + n + 1, g);
      fill(f, f + n + 1, 0);
      int x; scanf("%d", &x);
      rep(j, 1, x) {
         scanf("%s", tmp + 1);
         int m = strlen(tmp + 1);
         P cur = H.calc(tmp);
         rep(p, 0, n - m) if(cur == H.query(p + 1, p + m)) {
            (f[p + m] += g[p]) %= mod;
         }
      }
   }
   int ans = 0;
   rep(i, 0, n) (ans += f[i]) %= mod;
   printf("%d\n", ans);
   return 0;
}