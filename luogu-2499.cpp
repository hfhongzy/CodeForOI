#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 510, INF = 1e9 + 10;

namespace KM {

int n, G[N][N], ml[N], mr[N], slack[N], q[N], ql, qr, lx[N], ly[N], pre[N];
bool vl[N], vr[N];
void get(int u) {
   while(u) {
      mr[u] = pre[u];
      swap(u, ml[pre[u]]);
   }
}
void bfs(int s) {
   ql = qr = 0; q[qr ++] = s; vl[s] = 1;
   while(1) {
      while(ql < qr) {
         int u = q[ql ++];
         rep(v, 1, n) if(!vr[v]) {
            int t = lx[u] + ly[v] - G[u][v];
            if(t > slack[v]) continue ;
            pre[v] = u;
            if(!t) {
               if(!mr[v]) { get(v); return ; }
               vr[v] = vl[mr[v]] = 1;
               q[qr ++] = mr[v];
            } else slack[v] = t;
         }
      }
      int mn = INF, v = 0;
      rep(i, 1, n) if(!vr[i] && mn > slack[i]) mn = slack[v = i];
      rep(i, 1, n) {
         if(vl[i]) lx[i] -= mn;
         if(vr[i]) ly[i] += mn;
         else slack[i] -= mn;
      }
      if(!mr[v]) { get(v); return ; }
      ql = qr = 0; vr[v] = vl[mr[v]] = 1;
      q[qr ++] = mr[v];
   }
}
int KM() {
   fill(ml + 1, ml + n + 1, 0);
   fill(mr + 1, mr + n + 1, 0);
   fill(lx + 1, lx + n + 1, -INF);
   fill(ly + 1, ly + n + 1, 0);
   rep(i, 1, n) rep(j, 1, n) lx[i] = max(lx[i], G[i][j]);
   rep(i, 1, n) {
      fill(slack + 1, slack + n + 1, INF);
      fill(vl + 1, vl + n + 1, 0);
      fill(vr + 1, vr + n + 1, 0);
      bfs(i);
   }
   int ans = 0;
   rep(i, 1, n) ans += lx[i] + ly[i];
   return ans;
}

}
int main() {
   static char str[N][N];
   static int n, m, k, a, b, s[N][2], t[N][2];
   scanf("%d%d%d%d%d", &n, &m, &k, &a, &b);
   rep(i, 1, n) scanf("%s", str[i] + 1);
   rep(i, 1, k) scanf("%d%d", s[i], s[i] + 1);
   rep(i, 1, k) scanf("%d%d", t[i], t[i] + 1);
   int dx[8] = {a, b, -a, -b, -a, -b, a, b};
   int dy[8] = {b, a, b, a, -b, -a, -b, -a};
   static int q[N * N][2], ql, qr;
   static int d[N][N];
   KM::n = k;
   rep(i, 1, k) {
      rep(j, 1, n) fill(d[j] + 1, d[j] + m + 1, -1);
      int x = s[i][0], y = s[i][1];
      ql = qr = 0; q[qr][0] = x; q[qr][1] = y; qr ++;
      d[x][y] = 0;
      while(ql < qr) {
         x = q[ql][0]; y = q[ql][1]; ql ++;
         rep(j, 0, 7) {
            int nx = x + dx[j], ny = y + dy[j];
            if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && -1 == d[nx][ny] && str[nx][ny] != '*') {
               d[nx][ny] = d[x][y] + 1; q[qr][0] = nx; q[qr][1] = ny; qr ++;
            }
         }
      }
      rep(j, 1, k) {
         x = t[j][0]; y = t[j][1];
         KM::G[i][j] = d[x][y] == -1 ? -INF : - d[x][y]; 
      }
   }
   printf("%d\n", - KM::KM());
   return 0;
}