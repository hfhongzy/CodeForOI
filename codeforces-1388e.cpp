#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define eb emplace_back

typedef double db;
typedef long long ll;
typedef long double ldb;
typedef unsigned uint;
typedef unsigned long long ull;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
mt19937 Rand(seed);
uniform_int_distribution<ll> range(0, 1ll << 32);
inline void ucin() {
   ios::sync_with_stdio(0); cin.tie(0);
}
const int N = 4020;
struct Node {
   int l, r, y;
   bool operator < (const Node &b) const {
      return y < b.y || (y == b.y && l < b.l);
   }
} a[N], b[N];
int n;
int inc(int l1, int l2, int r1, int r2) {
   return max(0, min(r1, r2) - max(l1, l2));
}
db solve(Node *a) {
   db ans = 1e8, k = 0;
   sort(a + 1, a + n + 1);
   rep(i, 1, n) {
      rep(j, 1, i - 1) if(a[i].y ^ a[j].y) {
         db dy = a[i].y - a[j].y, c1 = a[j].l - a[i].r, c2 = a[i].l - a[j].r;
         //k <= c1/dy    or
         //k >= c2 / (-dy)
         if(c1 <= 0) {
            k = max(k, c2 / (-dy));
            break ;
         }
      }
   }
   db mx = -1e9, mn = 1e9;
   rep(i, 1, n) {
      mx = max(mx, a[i].r + k * a[i].y);
      mn = min(mn, a[i].l + k * a[i].y);
   }
   return mx - mn;
}
int main() {
   scanf("%d", &n);
   int xl = 1e6 + 10, xr = -1e6 - 10, tag = 1;
   rep(i, 1, n) {
      scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].y);
      xl = min(xl, a[i].l); xr = max(xr, a[i].r);
      b[i] = a[i]; b[i].l *= -1; b[i].r *= -1;
      rep(j, 1, i - 1) {
         if(inc(a[i].l, a[i].r, a[j].l, a[j].r) > 0) {
            tag = 0; break ;
         }
      }
   }
   db ans = min(solve(a), solve(b));
   if(tag) ans = min(ans, (db) xr - xl);
   printf("%.8f\n", ans);
   return 0;
}