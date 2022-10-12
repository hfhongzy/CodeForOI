#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 505, INF = 1e9 + 10;

int n, m;
int ml[N], mr[N], pre[N], q[N], lx[N], ly[N], slack[N], G[N][N];
bool vx[N], vy[N];

void get(int x) {
   while(x) {
      mr[x] = pre[x];
      swap(x, ml[ pre[x] ]);
   }
}
void bfs(int s) {
   int ql = 0, qr = 0;
   q[qr ++] = s; vx[s] = 1;
   while(1) {
      while(ql < qr) {
         int u = q[ql ++];
         for(int v = 1; v <= n; v++)
            if(!vy[v]) {
               int t = lx[u] + ly[v] - G[u][v];
               if(t > slack[v]) continue;
               pre[v] = u;
               if(!t) {
                  if(!mr[v]) { get(v); return; }
                  vx[ mr[v] ] = vy[v] = 1;
                  q[qr ++] = mr[v];
               } else slack[v] = t;
            }
      }
      int v, mn = INF;
      for(int i = 1; i <= n; i++)
         if(!vy[i] && slack[i] < mn) mn = slack[i], v = i;
      for(int i = 1; i <= n; i++) {
         if(vx[i]) lx[i] -= mn;
         if(vy[i]) ly[i] += mn;
         else slack[i] -= mn;
      }
      if(!mr[v]) { get(v); return; }
      ql = qr = 0;
      vx[ mr[v] ] = vy[v] = 1;
      q[qr ++] = mr[v];
   }
}

int main() {
   scanf("%d%d", &n, &m);
   memset(lx, ~ 0x3f, sizeof lx);
   memset(G, ~ 0x3f, sizeof G);

   for(int i = 1; i <= m; i ++) {
      int x, y, w;
      scanf("%d%d%d", &x, &y, &w);
      lx[x] = max(lx[x], G[x][y] = w);
   }
   for(int i = 1; i <= n; i ++) {
      fill(vx, vx + n + 1, 0);
      fill(vy, vy + n + 1, 0);
      fill(slack, slack + n + 1, INF);
      bfs(i);
   }
   ll ans = 0;
   for(int i = 1; i <= n; i++) ans += lx[i] + ly[i];
   printf("%lld\n", ans);
   for(int i = 1; i <= n; i ++) printf("%d ", mr[i]);
   puts("");
   return 0;
}