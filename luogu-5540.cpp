#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int N = 210, M = 1e4 + 10, INF = 1 << 30;
struct edge {
   int u, v, a, b, w;
} e[M];
int n, m, f[N];
pii ans(INF, INF);
int find(int u) {
   return u == f[u] ? u : f[u] = find(f[u]);
}
bool unite(int u, int v) {
   u = find(u); v = find(v);
   return u == v ? 0 : (f[u] = v, 1);
}
pii kruskal(int wa, int wb) { //min(wa\suma + wb\sumb)
   rep(i, 1, m) e[i].w = wa * e[i].a + wb * e[i].b;
   sort(e + 1, e + m + 1, [&](edge x, edge y) { return x.w < y.w; });
   rep(i, 1, n) f[i] = i;
   int sa = 0, sb = 0;
   rep(i, 1, m) {
      int u = e[i].u, v = e[i].v;
      if(unite(u, v)) {
         sa += e[i].a; sb += e[i].b;
      }
   }
   if((ll)sa * sb < (ll)ans.fs * ans.sc) ans = pii(sa, sb);
   else if((ll)sa * sb == (ll)ans.fs * ans.sc) ans = min(ans, pii(sa, sb));
   return pii(sa, sb);
}
bool cross(pii a, pii b, pii c) { //ab \times ac
   b.fs -= a.fs; b.sc -= a.sc; c.fs -= a.fs; c.sc -= a.sc;
   return (ll)b.fs * c.sc < (ll)b.sc * c.fs;
}
void solve(pii l, pii r) {
   pii mid = kruskal(l.sc - r.sc, r.fs - l.fs);
   if(cross(l, r, mid)) { solve(l, mid); solve(mid, r); }
}
int main() {
   scanf("%d%d", &n, &m);
   int u, v, a, b;
   rep(i, 1, m) {
      scanf("%d%d%d%d", &u, &v, &a, &b);
      e[i] = {u + 1, v + 1, a, b};
   }
   pii l = kruskal(1, 0), r = kruskal(0, 1);
   solve(l, r);
   printf("%d %d\n", ans.fs, ans.sc);
   return 0;
}