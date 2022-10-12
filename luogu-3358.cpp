#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, INF = 1e9 + 10;
struct MCMF {
   struct Edge {
      int v, c, f, w, nxt;
   } e[N];
   int dis[N], hd[N], a[N], la[N], ec, n;
   bool inq[N];
   void init(int _n) {
      n = _n; fill(hd + 1, hd + n + 1, -1); ec = 0;
   }
   void add(int u, int v, int c, int w) {
      e[ec] = (Edge) {v, c, 0, w, hd[u]}; hd[u] = ec ++;
      e[ec] = (Edge) {u, 0, 0, -w, hd[v]}; hd[v] = ec ++;
   }
   ll spfa(int s, int t) {
      fill(inq + 1, inq + n + 1, 0);
      queue<int> q; ll ans = 0;
      while(1) {
         fill(dis + 1, dis + n + 1, -INF);
         q.push(s); dis[s] = 0; inq[s] = 1; a[s] = INF;
         while(q.size()) {
            int u = q.front(); q.pop(); inq[u] = 0;
            for(int i = hd[u]; ~ i; i = e[i].nxt) {
               Edge &p = e[i];
               if(p.f < p.c && dis[p.v] < dis[u] + p.w) {
                  a[p.v] = min(a[u], p.c - p.f);
                  dis[p.v] = dis[u] + p.w; la[p.v] = i;
                  if(!inq[p.v]) { inq[p.v] = 1; q.push(p.v); }
               }
            }
         }
         if(dis[t] == -INF) break ;
         ans += (ll) dis[t] * a[t];
         for(int u = t; u != s; u = e[la[u] ^ 1].v) {
            e[la[u]].f += a[t]; e[la[u] ^ 1].f -= a[t];
         }
      }
      return ans;
   }
} mcmf;
int n, k, num[N], L[N], R[N];
int main() {
   scanf("%d%d", &n, &k);
   rep(i, 1, n) scanf("%d%d", L + i, R + i), num[++ *num] = L[i], num[++ *num] = R[i];
   sort(num + 1, num + *num + 1);
   *num = unique(num + 1, num + *num + 1) - num - 1;
   int s = *num + 1, t = s + 1; mcmf.init(t);
   mcmf.add(s, 1, k, 0); mcmf.add(*num, t, k, 0);
   rep(i, 1, *num - 1) mcmf.add(i, i + 1, INF, 0);
   rep(i, 1, n) {
      int x = R[i] - L[i];
      L[i] = lower_bound(num + 1, num + *num + 1, L[i]) - num;
      R[i] = lower_bound(num + 1, num + *num + 1, R[i]) - num;
      mcmf.add(L[i], R[i], 1, x);
   }
   printf("%lld\n", mcmf.spfa(s, t));
   return 0;
}