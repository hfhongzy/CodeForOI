#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; i ++)
using namespace std;
const int N = 1e4 + 10;
int n, m, col[N], d[N];
vector<int> G[N], cur;
bool vis[N], del[N];
void dfs(int u, int fa, int len, int endp) {
   if(u == endp) { cur.pb(len); return ; }
   rep(i, 0, (int) G[u].size() - 1) {
      int v = G[u][i];
      if(v == fa) continue ;
      dfs(v, u, len + 1, endp);
   }
}
bool solve(int u) {
   queue<int> q; q.push(u); col[u] = 0;
   bool tag = 0;
   int _n = 0, _m = 0, rt = 0, rt2 = 0;
   while(q.size()) {
      int u = q.front(); q.pop(); vis[u] = 1; _n ++;
      if(d[u] == 3) {
         if(rt) rt2 = u; else rt = u;
      }
      rep(i, 0, (int) G[u].size() - 1) {
         int v = G[u][i];
         if(del[v]) continue ;
         _m ++;
         if(~ col[v]) {
            if(col[v] == col[u]) {
               return 0;
            }
         } else {
            col[v] = col[u] ^ 1; q.push(v);
         }
      }
   }
   _m /= 2;
   if(_m >= _n + 2) return 0;
   if(_m <= _n) return 1;
   cur.clear(); dfs(rt, 0, 0, rt2);
   sort(cur.begin(), cur.end());
   return cur[0] == 2 && cur[1] == 2 && cur[2] % 2 == 0;
}
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      scanf("%d%d", &n, &m);
      rep(i, 1, n) G[i].clear(), vis[i] = del[i] = d[i] = 0;
      rep(i, 1, m) {
         int u, v;
         scanf("%d%d", &u, &v);
         G[u].pb(v); G[v].pb(u); d[u] ++; d[v] ++;
      }
      queue<int> q;
      rep(i, 1, n) if(d[i] <= 1) q.push(i);
      while(q.size()) {
         int u = q.front(); q.pop(); del[u] = 1;
         rep(i, 0, (int) G[u].size() - 1) {
            int v = G[u][i];
            if(-- d[v] == 1) {
               q.push(v);
            }
         }
      }
      fill(col + 1, col + n + 1, -1);
      bool ans = 1;
      rep(i, 1, n) if(!vis[i] && !del[i]) {
         if(!solve(i)) {
            ans = 0; break ;
         }
      }
      puts(ans ? "YES" : "NO");
   }
   return 0;
}
/*
不是二分图 -> NO
n >= m + 2 -> NO
2 - 2 - 偶 -> YES
*/