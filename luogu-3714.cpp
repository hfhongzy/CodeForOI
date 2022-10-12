#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 2e5 + 10, INF = 2e9 + 1e5;
struct Edge { int v, w; };
int n, m, L, R, ans = -INF, rt, size, c[N], sz[N], f[N];
vector<Edge> G[N];
bool cal[N];
void findrt(int u, int fa = 0) {
   sz[u] = 1; f[u] = 0;
   for(int i = 0; i < (int) G[u].size(); i ++) {
      Edge &e = G[u][i];
      if(e.v != fa && !cal[e.v]) {
         findrt(e.v, u); sz[u] += sz[e.v];
         f[u] = max(f[u], sz[e.v]);
      }
   }
   f[u] = max(f[u], size - sz[u]);
   if(!rt || f[u] < f[rt]) rt = u;
}
int vD[N], cD[N], col[N];
int dfsD(int u, int fa = 0) {
   int dp = 0;
   for(int i = 0; i < (int) G[u].size(); i ++) {
      Edge &e = G[u][i];
      if(!cal[e.v] && e.v != fa) {
         col[e.v] = e.w;
         dp = max(dp, 1 + dfsD(e.v, u));
      }
   }
   return dp;
}
int La[N], Max[N], cur[N];
void dfs(int u, int de, int cost, int fa = 0) {
   cur[de] = max(cur[de], cost);
   for(int i = 0; i < (int) G[u].size(); i ++) {
      Edge &e = G[u][i];
      if(!cal[e.v] && e.v != fa) {
         dfs(e.v, de + 1, cost + (e.w != col[u] ? c[e.w] : 0), u);
      }
   }
}
vector<int> vec;
bool cmp(int a, int b) {
   return cD[col[a]] < cD[col[b]] || (cD[col[a]] == cD[col[b]] && vD[a] < vD[b]);
}
void solve(int u) {
   cal[u] = 1; vec.clear();
   for(int i = 0; i < (int) G[u].size(); i ++) {
      Edge &e = G[u][i];
      if(!cal[e.v]) cD[e.w] = 0;
   }
   for(int i = 0; i < (int) G[u].size(); i ++) {
      Edge &e = G[u][i];
      if(!cal[e.v]) {
         vec.push_back(e.v);
         col[e.v] = e.w;
         vD[e.v] = dfsD(e.v) + 1;
         cD[e.w] = max(cD[e.w], vD[e.v]);
      }
   }
   sort(vec.begin(), vec.end(), cmp);
   static int q[N]; int mxx = 0; La[0] = 0;
   for(int i = 0, j, cur_c; i < (int) vec.size(); i = j + 1) {
      j = i; cur_c = col[vec[i]];
      for(; j + 1 < vec.size() && col[vec[j + 1]] == cur_c; j ++) ;
      int mx = 0;
      for(int k = i; k <= j; k ++) {
         int v = vec[k]; fill(cur + 1, cur + vD[v] + 1, -INF);
         dfs(v, 1, c[cur_c]);
         int ql = 1, qr = 0, p = min(R, mx);
         for(int x = 1; x <= vD[v]; x ++) { //[L - x, R - x]
            for(; p >= L - x && p >= 1; p --) {
               while(ql < qr && Max[q[qr - 1]] <= Max[p]) {
                  qr --;
               }
               q[qr ++] = p;
            }
            while(ql < qr && q[ql] > R - x) ql ++;
            if(ql < qr && cur[x] > -INF) {
               ans = max(ans, cur[x] + Max[q[ql]] - c[cur_c]);
            }
         }
         for(int x = 1; x <= vD[v]; x ++)
            Max[x] = x <= mx ? max(Max[x], cur[x]) : cur[x];
         mx = max(mx, vD[v]);
      }

      int ql = 1, qr = 0, p = min(R, mxx);
      for(int x = 1; x <= mx; x ++) { //[L - x, R - x]
         for(; p >= L - x && p >= 0; p --) {
            while(ql < qr && La[q[qr - 1]] <= La[p]) {
               qr --;
            }
            q[qr ++] = p;
         }
         while(ql < qr && q[ql] > R - x) ql ++;
         if(ql < qr && Max[x] > -INF) {
            ans = max(ans, Max[x] + La[q[ql]]);
         }
      }
      for(int x = 1; x <= mx; x ++)
         La[x] = x <= mxx ? max(La[x], Max[x]) : Max[x];
      mxx = max(mxx, mx);
   }
   for(int i = 0; i < (int) G[u].size(); i ++) {
      Edge &e = G[u][i];
      if(!cal[e.v]) { rt = 0; size = sz[e.v]; findrt(e.v); solve(rt); }
   }
}
int main() {
   scanf("%d%d%d%d", &n, &m, &L, &R);
   for(int i = 1; i <= m; i ++) scanf("%d", c + i);
   for(int i = 1; i < n; i ++) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      G[u].push_back((Edge) {v, w});
      G[v].push_back((Edge) {u, w});
   }
   rt = 0; size = n; findrt(1); solve(rt);
   // for(int i = 1; i <= n; i ++) assert(cal[i]);
   printf("%d\n", ans);
   return 0;
}