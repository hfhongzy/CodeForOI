#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#include <set>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
 
#define ucin ios::sync_with_stdio(0), cin.tie(0)
#define fs first
#define sc second
#define pb push_back
#define mp make_pair
 
typedef double db;
typedef long long ll;
const int mod = 998244353;
inline void upd(int &x, const int &y) {
   (x += y) >= mod ? x -= mod : 0;
}
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
int n, m, s;
struct Lbase {
   ll a[64];
   int size() {
      int s = 0;
      rep(i, 0, m - 1) s += a[i] > 0;
      return s;
   }
   void insert(ll x) {
      per(i, m - 1, 0) if(x >> i & 1) {
         if(!a[i]) {
            a[i] = x;
            per(j, i - 1, 0) if(a[i] >> j & 1) a[i] ^= a[j];
            rep(j, i + 1, m - 1) if(a[j] >> i & 1) a[j] ^= a[i];
            break ;
         }
         x ^= a[i];
      }
   }
} L;
namespace task1 {

vector<int> pos;
int ans[64];
void main() {
   rep(i, 0, m - 1) if(L.a[i]) pos.pb(i);
   for(int i = 0; i < (1 << s); i ++) {
      ll x = 0;
      rep(j, 0, s - 1) if(i >> j & 1) x ^= L.a[pos[j]];
      ans[__builtin_popcountll(x)] ++;
   }
   int tot = qpow(2, n - s);
   rep(i, 0, m) {
      ans[i] = 1ll * ans[i] * tot % mod;
      printf("%d ", ans[i]);
   }
   putchar('\n');
}

}
namespace task2 {

vector<int> pos, bit;
int ans[64], z, dp[64][1 << 16], t[64][1 << 16], b[64];
void main() {
   rep(i, 0, m - 1) if(L.a[i]) pos.pb(i); else bit.pb(i);
   z = bit.size();
   rep(i, 0, (int) pos.size() - 1) {
      rep(j, 0, z - 1) {
         if(L.a[pos[i]] >> bit[j] & 1) {
            b[i] ^= 1 << j;
         }
      }
   }
   dp[0][0] = 1;
   rep(i, 1, s) {
      rep(j, 0, i) rep(k, 0, (1 << z) - 1) t[j][k] = 0;
      rep(j, 0, i - 1) rep(k, 0, (1 << z) - 1) if(dp[j][k]) {
         upd(t[j][k], dp[j][k]); upd(t[j + 1][k ^ b[i - 1]], dp[j][k]);
      }
      rep(j, 0, i) rep(k, 0, (1 << z) - 1) dp[j][k] = t[j][k];
   }
   rep(i, 0, s) rep(k, 0, (1 << z) - 1) upd(ans[__builtin_popcountll(k) + i], dp[i][k]);
   int tot = qpow(2, n - s);
   rep(i, 0, m) {
      ans[i] = 1ll * ans[i] * tot % mod;
      printf("%d ", ans[i]);
   }
   putchar('\n');
}

}
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, n) { ll x; scanf("%lld", &x); L.insert(x); }
   s = L.size();
   ll Ag1 = 1ll << s, Ag2 = (1ll << (m - s)) * m * m;
   if(Ag1 < Ag2) task1::main(); else task2::main();
   return 0;
}