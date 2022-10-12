#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

const int N = 2e5 + 10;

int n, m, s, dis[N];
set<int> S;
vector<int> G[N];
bool vis[N];

void solve() {
   scanf("%d%d", &n, &m);
   rep(i, 1, n) G[i].clear(), vis[i] = 0;
   S.clear();
   int u, v;
   rep(i, 1, m) {
      scanf("%d%d", &u, &v);
      G[u].pb(v); G[v].pb(u);
   }
   rep(i, 1, n) sort(G[i].begin(), G[i].end());
   scanf("%d", &s);
   queue<int> q; q.push(s); vis[s] = 1; dis[s] = 0;
   rep(i, 1, n) if(i != s) S.insert(i);
   while(q.size()) {
      int u = q.front(); q.pop();
      for(set<int>::iterator it = S.begin(); it != S.end(); ) {
         int v = *it;
         if(!binary_search(G[u].begin(), G[u].end(), v)) {
            vis[v] = 1; dis[v] = dis[u] + 1; q.push(v); S.erase(v);
         }
         it = S.lower_bound(v + 1);
      }
   }
   int tag = 0;
   rep(i, 1, n) if(i != s) tag ++ ? putchar(' ') : 0, printf("%d", vis[i] ? dis[i] : -1);
   putchar('\n');
}
int main() {
   int test; scanf("%d", &test);
   while(test --) solve();   
   return 0;
}