#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;

int n, m, a, b, c, _a, _b, _c, rt;
int ans[N], dfn[N], dr[N], sz[N];
vector<int> G[N], son[N];
bool mark[N];

void quit() {
   static int cnt[3], map[3], use[3];
   rep(i, 1, n) cnt[ans[i]] ++;
   rep(i, 0, 2) if(!use[i] && cnt[i] == _a) { use[i] = 1; map[i] = 1; break ; }
   rep(i, 0, 2) if(!use[i] && cnt[i] == _b) { use[i] = 1; map[i] = 2; break ; }
   rep(i, 0, 2) if(!use[i] && cnt[i] == _c) { use[i] = 1; map[i] = 3; break ; }
   rep(i, 1, n) cout << map[ans[i]] << (i == n ? '\n' : ' ');
   exit(0);
}
auto intree = [](int u, int fa) {
   return dfn[fa] <= dfn[u] && dfn[u] <= dr[fa];
};
void dfs(int u) {
   dfn[u] = ++ *dfn; sz[u] = 1;
   for(int v : G[u]) if(!dfn[v]) {
      dfs(v); sz[u] += sz[v]; son[u].pb(v);
   }
   dr[u] = *dfn;
}
bool dfs2(int u) {
   for(int v : G[u]) if(!intree(v, rt)) return true;
   for(int v : son[u]) if(dfs2(v)) return true;
   return false;
}
void dfs3(int u, int &lim, int col) {
   if(!lim || mark[u]) return ;
   lim --; ans[u] = col;
   for(int v : son[u]) {
      if(!lim) break ;
      dfs3(v, lim, col);
   }
}
void dfs4(int u, int &lim, int col) {
   if(!lim || ans[u]) return ;
   lim --; ans[u] = col;
   for(int v : G[u]) {
      if(!lim) break ;
      dfs4(v, lim, col);
   }
}
void solve(int L, int R) { //2L <= R & 2R > n
   if(L > R) return ;
   rep(i, 1, n) if(L <= sz[i] && sz[i] <= R) {
      int sz1 = L, sz2 = n - R;
      dfs3(i, sz1, 1);
      rep(j, 1, n) if(!ans[j]) {
         dfs4(j, sz2, 2);
         break ;
      }
      quit();
   }
   rep(i, 1, n) if(sz[i] > R) {
      bool tag = true;
      for(int v : son[i]) if(sz[v] > R) { tag = false; break ; }
      if(tag) { rt = i; break ; }
   }
   int p = sz[rt];
   for(int v : son[rt]) {
      bool mv = dfs2(v);
      if(mv) {
         mark[v] = 1;
         p -= sz[v];
         if(p <= R) {
            int sz1 = L, sz2 = n - R;
            dfs3(rt, sz1, 1);
            rep(i, 1, n) if(!ans[i]) {
               dfs4(i, sz2, 2);
               break ;
            }
            quit();
         }
      }
   }
   for(int v : son[rt]) mark[v] = 0;
}

int main() {
   ios::sync_with_stdio(false); cin.tie(NULL);

   cin >> n >> m >> a >> b >> c;
   _a = a; _b = b; _c = c;
   if(a > b) swap(a, b);
   if(b > c) swap(b, c);
   if(a > b) swap(a, b);
   int u, v;
   rep(i, 1, m) {
      cin >> u >> v;
      G[u + 1].pb(v + 1); G[v + 1].pb(u + 1);
   }
   dfs(1);
   solve(a, n - b); solve(b, n - a);
   rep(i, 1, n) cout << 0 << (" \n"[i == n]);
   return 0;
}