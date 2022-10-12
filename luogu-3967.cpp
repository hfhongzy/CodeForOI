#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 80 + 10, INF = 1e9 + 10;
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
   fill(lx + 1, lx + n + 1, 0);
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
int main() {
   scanf("%d", &n);
   rep(i, 1, n) rep(j, 1, n) scanf("%d", &G[i][j]);
   int res = KM(); printf("%d\n", res);
   static int pa[N];
   copy(ml + 1, ml + n + 1, pa + 1);
   int tmp = 0;
   rep(i, 1, n) {
      int z = pa[i];
      swap(G[i][z], tmp);
      if(KM() == res) {
         pa[i] = -1;
      }
      swap(G[i][z], tmp);
   }
   rep(i, 1, n) if(~ pa[i]) printf("%d %d\n", i, pa[i]);
   return 0;
}