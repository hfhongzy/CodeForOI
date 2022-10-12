#include <algorithm>
#include <cstdio>
#include <queue>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
const int T = 810;
int n, m, p[T], a[T], sump, ti[T][T];
#define ID(x, y) n + sump * (x - 1) + y

const int N = 1e5 + 10, M = 1e7 + 5;
const int INF = 1e9;
struct Edge { int v, c, f, w, nxt; } eg[M * 2];
int nd, ans, s, t, hd[N], ec;
void init() { fill(hd + 1, hd + nd + 1, -1); ec = 0; }
void add(int u, int v, int c, int w) {
  eg[ec] = (Edge) {v, c, 0, w, hd[u]}; hd[u] = ec ++;
  eg[ec] = (Edge) {u, 0, 0, -w, hd[v]}; hd[v] = ec ++;
}
int f[N], la[N], d[N];
bool inq[N], use[N];
bool mcmf() {
  queue<int> q;
  fill(f + 1, f + nd + 1, 0); f[s] = INF;
  fill(d + 1, d + nd + 1, INF); d[s] = 0;
  q.push(s); inq[s] = 1;
  while(q.size()) {
    int u = q.front(); q.pop(); inq[u] = 0;
    for(int i = hd[u]; ~ i; i = eg[i].nxt) {
      Edge &e = eg[i];
      if(d[e.v] > d[u] + e.w && e.c > e.f) {
        d[e.v] = d[u] + e.w; la[e.v] = i;
        f[e.v] = min(f[u], e.c - e.f);
        if(!inq[e.v]) { q.push(e.v); inq[e.v] = 1; }
      }
    }
  }
  if(d[t] == INF) return 0;
  ans += f[t] * d[t];
  return 1;
}
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, n) scanf("%d", p + i), sump += p[i];
  rep(i, 1, n) rep(j, 1, m) scanf("%d", &ti[i][j]);
  nd = t = n + sump * m + 2; s = nd - 1; init();
  rep(i, 1, n) add(s, i, p[i], 0);
  rep(i, 1, m) {
    add(ID(i, sump), t, 1, 0); use[ID(i, sump)] = 1;
    rep(j, 1, n) add(j, ID(i, sump), 1, ti[j][i]);
  }
  while(mcmf()) {
    for(int u = t; u != s; u = eg[la[u] ^ 1].v) {
      if(u > n && u <= nd - 2) {
        int x = (u - n - 1) / sump + 1;
        int y = (u - n - 1) % sump + 1;
        if(y > 1 && !use[ID(x, y - 1)]) {
          add(ID(x, y - 1), t, 1, 0); use[ID(x, y - 1)] = 1;
          rep(i, 1, n) {
            add(i, ID(x, y - 1), 1, ti[i][x] * (sump - y + 2));
          }
        }
      }
      eg[la[u]].f += f[t]; eg[la[u] ^ 1].f -= f[t];
    }
  }
  printf("%d\n", ans);
  return 0;
}