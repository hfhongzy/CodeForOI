#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

const int N = 2e5 + 10;

int n, sg[N];
vector<int> G[N];
void dfs(int u, int fa = 0) {
  sg[u] = 0;
  for(int v : G[u]) if(v ^ fa) {
    dfs(v, u);
    sg[u] ^= sg[v] + 1;
  }
}
int main() {
  scanf("%d", &n);
  int u, v;
  rep(i, 1, n - 1) {
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
  }
  dfs(1);
  puts(sg[1] == 0 ? "Bob" : "Alice");
  return 0;
}