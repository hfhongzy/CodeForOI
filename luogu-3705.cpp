#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef double db;

const int N = 505;
const db INF = 1e9 + 10;

int n, m, ml[N], mr[N], pre[N], q[N], a[N][N], b[N][N];
bool vx[N], vy[N];
db lx[N], ly[N], slack[N], G[N][N];
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
         for(int v = 1; v <= n; v ++)
            if(!vy[v]) {
               db t = lx[u] + ly[v] - G[u][v];
               if(t > slack[v]) continue;
               pre[v] = u;
               if(!t) {
                  if(!mr[v]) { get(v); return; }
                  vx[ mr[v] ] = vy[v] = 1;
                  q[qr ++] = mr[v];
               } else slack[v] = t;
            }
      }
      int v; db mn = INF;
      for(int i = 1; i <= n; i ++)
         if(!vy[i] && slack[i] < mn) mn = slack[i], v = i;
      for(int i = 1; i <= n; i ++) {
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
   scanf("%d", &n);
   rep(i, 1, n) rep(j, 1, n) scanf("%d", a[i] + j);
   rep(i, 1, n) rep(j, 1, n) scanf("%d", b[i] + j);
   db l = 0, r = 1e6, mid;
   while(r - l > 1e-7) {
      mid = (l + r) / 2;
      fill(ml + 1, ml + n + 1, 0);
      fill(mr + 1, mr + n + 1, 0);
      fill(ly + 1, ly + n + 1, 0);
      for(int i = 1; i <= n; i ++) {
         lx[i] = -INF;
         for(int j = 1; j <= n; j ++) {
            lx[i] = max(lx[i], G[i][j] = a[i][j] - mid * b[i][j]);
         }
      }
      for(int i = 1; i <= n; i ++) {
         fill(vx, vx + n + 1, 0);
         fill(vy, vy + n + 1, 0);
         fill(slack, slack + n + 1, INF);
         bfs(i);
      }
      db ans = 0;
      for(int i = 1; i <= n; i++) ans += lx[i] + ly[i];
      if(ans >= 0) l = mid; else r = mid;
   }
   printf("%.6f\n", r);
   return 0;
}