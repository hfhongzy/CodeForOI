#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e5 + 10;
int n, m, ans[N], vis[N], tim;
vector<int> G[N];
void dfs(int u) {
  vis[u] = ++ tim;
  int arr[4] = {0};
  for(int v : G[u]) {
    if(vis[v]) {
      ++ arr[ans[v]];
    }
  }
  ans[u] = min_element(arr, arr + 4) - arr;
  for(int v : G[u]) {
    if(!vis[v]) {
      dfs(v);
    }
  }
}
int main() {
  int test;
  scanf("%d", &test);
  while(test --) {
    scanf("%d%d", &n, &m);
    rep(i, 1, n) G[i].clear(), vis[i] = 0;
    tim = 0;
    rep(i, 1, m) {
      int u, v;
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
    }
    rep(i, 1, n) if(!vis[i]) dfs(i);
    rep(i, 1, n) putchar('a' + ans[i]);
    puts("");
  }  
  return 0;
}