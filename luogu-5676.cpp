#include <algorithm>
#include <cstdio>
#include <stack>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
using namespace std;
const int N = 2e5 + 10;
struct Edge {
   int v, nxt;
} e[N];
int T, ec, ans, n, m, a[N], b[N], dfn[N], low[N], hd[N], idx;
bool ins[N];
void clr() {
   fill(hd + 1, hd + n + m + 1, -1); ec = 0;
}
void link(int u, int v) {
   e[ec] = (Edge) {v, hd[u]}; hd[u] = ec ++;
}
stack<int> s;
void dfs(int u) {
   dfn[u] = low[u] = ++ idx; ins[u] = 1; s.push(u);
   for(int i = hd[u]; ~ i; i = e[i].nxt) {
      int v = e[i].v;
      if(!dfn[v]) {
         dfs(v);
         low[u] = min(low[u], low[v]);
      } else if(ins[v]) {
         low[u] = min(low[u], dfn[v]);
      }
   }
   for(int v = u * 2; v <= m; v += u) {
      if(!dfn[v]) {
         dfs(v);
         low[u] = min(low[u], low[v]);
      } else if(ins[v]) {
         low[u] = min(low[u], dfn[v]);
      }
   }
   if(low[u] == dfn[u]) {
      int v, sz = 0, cnt = 0;
      do {
         v = s.top(); s.pop(); ins[v] = 0; sz ++;
         cnt += v > m;
      } while(v != u);
      if(sz > 1) ans += cnt;
   }
}
int main() {
   scanf("%d", &T);
   while(T --) {
      scanf("%d", &n);
      rep(i, 1, n) scanf("%d", a + i);
      rep(i, 1, n) scanf("%d", b + i);
      m = max(*max_element(a + 1, a + n + 1), *max_element(b + 1, b + n + 1));
      clr();
      rep(i, 1, n) {
         link(a[i], m + i); link(m + i, b[i]);
      }
      idx = ans = 0;
      rep(i, 1, n + m) dfn[i] = low[i] = 0;
      rep(i, 1, n + m) if(!dfn[i]) dfs(i);
      printf("%d\n", ans);
   }
   return 0;
}