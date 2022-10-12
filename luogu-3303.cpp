#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
typedef double db;
const int N = 2e4 + 10;
const int mod = 1e9 + 7;
const int P[] = {2, 3, 5, 7};
ll n;
int k, m, a[16], z;
ll num[N], arr[N], f[16][N][2];
int lw(ll x) {
  return lower_bound(num + 1, num + z + 1, x) - num;
}
void dfs(int u, ll x) {
  if(u == 4) { num[++ z] = x; return ; }
  for(; x <= n; x *= P[u]) dfs(u + 1, x);
}
int main() {
  scanf("%lld%d", &n, &k);
  dfs(0, 1);
  sort(num + 1, num + z + 1);
  for(; n; n /= 10) a[++ m] = n % 10;
  f[m + 1][1][1] = 1;
  rep(i, 2, m) f[i][1][0] = 1;
  per(i, m, 1) {
    rep(j, 1, z) rep(lim, 0, 1) if(f[i + 1][j][lim]) {
      rep(x, 1, (lim ? a[i] : 9)) {
        f[i][lw(num[j] * x)][lim && (x == a[i])] += f[i + 1][j][lim];
      }
    }
  }
  rep(i, 1, z) arr[i] = f[1][i][0] + f[1][i][1];
  sort(arr + 1, arr + z + 1, greater<ll>());
  struct node {
    int i, j;
    db val;
    bool operator < (const node &b) const {
      return val < b.val;
    }
  };
  priority_queue<node> q;
  rep(i, 1, z) q.push({i, 1, arr[i] * (db)arr[1]});
  int ans = 0;
  rep(i, 1, k) {
    node cur = q.top(); q.pop();
    ans = (ans + (arr[cur.i] % mod) * (arr[cur.j] % mod)) % mod;
    if(cur.j < z) q.push({cur.i, cur.j + 1, (db)arr[cur.i] * arr[cur.j + 1]});
  }
  printf("%d\n", ans);
  return 0;
}