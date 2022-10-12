#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
const int mod = 998244353;

int n, m, op;
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll) a * a % mod)
    if(b & 1) ans = (ll) ans * a % mod;
  return ans;
}

namespace task0 {

vector<int> G[N];
void main() {
  rep(i, 1, n - 1) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  rep(i, 1, n) sort(G[i].begin(), G[i].end());
  int c = n;
  rep(i, 1, n - 1) {
    int u, v;
    scanf("%d%d", &u, &v);
    if(binary_search(G[u].begin(), G[u].end(), v))
      c --;
  }
  int ans = 1;
  rep(i, 1, c) ans = (ll)ans * m % mod;
  printf("%d\n", ans);
}

}
namespace task1 {

vector<int> G[N];
int dp[N][2], t;
void dfs(int u, int fa = 0) {
  dp[u][1] = t; dp[u][0] = 1;
  for(int v : G[u]) if(v != fa) {
    dfs(v, u);
    int z0 = (ll)dp[u][0] * (dp[v][0] + dp[v][1]) % mod;
    int z1 = ( (ll)dp[u][1] * (dp[v][0] + dp[v][1]) + (ll)dp[u][0] * dp[v][1] ) % mod;
    dp[u][0] = z0;
    dp[u][1] = z1;
  }
}
void main() {
  t = (ll)m * qpow(n, mod - 2) % mod;
  rep(i, 1, n - 1) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  dfs(1);
  int res = (ll)dp[1][1] * qpow((ll)n * n % mod, mod - 2) % mod;
  printf("%d\n", res);
}

}
namespace task2 {

void main() {

}

}
int main() {
  scanf("%d%d%d", &n, &m, &op);
  if(op == 0) task0::main();
  if(op == 1) task1::main();
  if(op == 2) task2::main();
  return 0;
}