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
// mt19937_64 
uniform_int_distribution<ll> range(0, 1ll << 32);
inline void ucin() {
   ios::sync_with_stdio(0); cin.tie(0);
}
// uniform_real_distribution<double> dbran;
template<class T> inline void chkmax(T &x, const T &y) { if(x < y) x = y; }
template<class T> inline void chkmin(T &x, const T &y) { if(x > y) x = y; }

const int N = 2e5 + 10;
const int mod = 998244353;

int n, a[N], st[N], top, r[N], l[N], ans; //r:>a[i]; l:<a[i]
int id, dp[N], rt[N], sz[N << 5], ls[N << 5], rs[N << 5];
void update(int p, int &u, int l, int r, int x, int y) {
   u = ++ id; sz[u] = (sz[p] + y) % mod;
   if(l == r) return ;
   int mid = (l + r) >> 1;
   if(x <= mid) {
      rs[u] = rs[p]; update(ls[p], ls[u], l, mid, x, y);
   } else {
      ls[u] = ls[p]; update(rs[p], rs[u], mid + 1, r, x, y);
   }
}
int query(int u, int v, int l, int r, int qr) {
   if(l > qr) return 0;
   if(r <= qr) return (sz[u] - sz[v] + mod) % mod;
   int mid = (l + r) >> 1;
   return (query(ls[u], ls[v], l, mid, qr) + query(rs[u], rs[v], mid + 1, r, qr)) % mod;
}
vector<int> cc[N];
int bit[N];
int qry(int u) {
   int ans = 0;
   for(; u >= 1; u &= u - 1) {
      (ans += bit[u]) %= mod;
   }
   return ans;
}
void upd(int u, int v) {
   for(; u <= n; u += u & (-u)) {
      (bit[u] += v) %= mod;
   }
}
namespace ns {

int dp[N];
void main() {
   rep(i, 1, n) {
      if(!l[i]) {
         dp[i] = 1;
      } else {

      }
   }
}

}
int main() {
   scanf("%d", &n);
   rep(i, 1, n) scanf("%d", a + i);
   per(i, n, 1) {
      while(top && a[st[top]] < a[i]) {
         top --;
      }
      r[i] = top ? st[top] : n + 1;
      st[++ top] = i;
   }
   top = 0;
   rep(i, 1, n) {
      while(top && a[st[top]] > a[i]) {
         top --;
      }
      l[i] = top ? st[top] : 0;
      st[++ top] = i;
   }
   if(n <= 5000) return ns::main(), 0;
   rep(i, 1, n) {
      for(int u : cc[i]) {
         upd(a[u], mod - dp[u]);
      }
      if(!l[i]) dp[i] = 1;
      else {
         dp[i] = (qry(a[i]) + query(rt[i - 1], rt[l[i] - 1], 1, n, a[i])) % mod;
         (dp[i] += mod - dp[i - 1]) %= mod;
      }
      update(rt[i - 1], rt[i], 1, n, a[i], dp[i]);
      upd(a[i], dp[i]);
      cc[r[i] + 1].pb(i);
      if(r[i] == n + 1) {
         (ans += dp[i]) %= mod;
      }
      // printf("dp %d = %d\n", i, dp[i]);
   }
   printf("%d\n", ans);
   return 0;
}