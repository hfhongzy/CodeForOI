#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, q, a[N], fa[N];
vector<int> G[N];
multiset<ll> S[N], A;
ll w[N];
void dfs(int u) {
   for(int v : G[u]) {
      dfs(v);
      S[u].insert(w[v]);
   }
   w[u] = a[u] + (S[u].size() ? * -- S[u].end() : 0);
   A.insert(w[u]);
}
void modify(int u, int v) {
   if(a[u] == v) return ;
   ll from = w[u];
   A.erase(A.lower_bound(from));
   w[u] -= a[u]; a[u] = v; w[u] += v;
   ll to = w[u];
   A.insert(to);
   for(int x = fa[u]; x; x = fa[x]) {
      if(from ^ to) {
         S[x].erase(S[x].lower_bound(from));
         S[x].insert(to);
         A.erase(A.lower_bound(from = w[x]));
         A.insert(to = w[x] = a[x] + * -- S[x].end());
      } else break ;
   }
}
int main() {
   // freopen("zroi-785.in", "r", stdin);
   scanf("%d%d", &n, &q);
   rep(i, 1, n) scanf("%d", a + i);
   rep(i, 2, n) {
      scanf("%d", fa + i); G[fa[i]].push_back(i);
   }
   dfs(1);
   int u, v;
   rep(i, 1, q) {
      scanf("%d%d", &u, &v);
      modify(u, v);
      printf("%lld\n", *A.begin());
   }
   // cerr << "time = " << clock() / (double) CLOCKS_PER_SEC << '\n';
   return 0;
}