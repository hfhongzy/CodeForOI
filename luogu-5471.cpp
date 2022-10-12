#include <algorithm>
#include <cstdio>
#include <queue>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
template<typename T> inline void chkmin(T &a, const T &b) { if(a > b) a = b; }
template<typename T> inline void chkmax(T &a, const T &b) { if(a < b) a = b; }
using namespace std;

const int N = 7e4 + 10;
const int M = 1.5e5 + 10;
const int INF = 2e9 + 10;

struct trans {
   int u, w, lx, rx, ly, ry;
   bool operator < (const trans &b) const {
      return u < b.u;
   }
} a[M];
int tu[M];
int rt, n, m, w, h, x[N], y[N], dis[N * 2], fir[N];

int per[N], ch[N][2], ranx[N][2], rany[N][2], cmpd;
bool cmp(int u, int v) { return cmpd ? y[u] < y[v] : x[u] < x[v]; }
void pushup(int u) {
   ranx[u][0] = ranx[u][1] = x[u];
   rany[u][0] = rany[u][1] = y[u];
   rep(i, 0, 1) {
      int &v = ch[u][i];
      if(!v) continue ;
      chkmin(ranx[u][0], ranx[v][0]);
      chkmax(ranx[u][1], ranx[v][1]);
      chkmin(rany[u][0], rany[v][0]);
      chkmax(rany[u][1], rany[v][1]);
   }
}
int build(int l, int r, int d = 0) {
   if(l > r) return 0;
   if(l == r) {
      pushup(per[l]);
      return per[l];
   }
   int mid = (l + r) >> 1; cmpd = d;
   nth_element(per + l, per + mid, per + r + 1, cmp);
   int u = per[mid];
   ch[u][0] = build(l, mid - 1, d ^ 1);
   ch[u][1] = build(mid + 1, r, d ^ 1);
   pushup(u); return u;
}
struct Node {
   int u, d;
   bool operator < (const Node &b) const {
      return d > b.d;
   }
};
priority_queue<Node> q;
int qid, cur;
bool qpush(int u, int w) {
   if(dis[u] > dis[cur] + w) {
      dis[u] = dis[cur] + w;
      q.push((Node) {u, dis[u]});
      return 1;
   }
   return 0;
}
void check(int u) {
   if(u == 0) return ;
   if(a[qid].rx < ranx[u][0] || ranx[u][1] < a[qid].lx ||
      a[qid].ry < rany[u][0] || rany[u][1] < a[qid].ly) {
      return ;
   }
   if(a[qid].lx <= ranx[u][0] && ranx[u][1] <= a[qid].rx &&
      a[qid].ly <= rany[u][0] && rany[u][1] <= a[qid].ry) {
      if(qpush(n + u, a[qid].w)) {
      }
      return ;
   }
   if(a[qid].lx <= x[u] && x[u] <= a[qid].rx &&
      a[qid].ly <= y[u] && y[u] <= a[qid].ry) {
      qpush(u, a[qid].w);
   }
   check(ch[u][0]); check(ch[u][1]);
}
void extend(int u) {
   cur = u;
   if(u <= n) {
      for(int i = fir[u]; i <= m && tu[i] == u; i ++) {
         qid = i; check(rt);
      }
   } else {
      qpush(u - n, 0);
      if(ch[u - n][0]) qpush(ch[u - n][0] + n, 0);
      if(ch[u - n][1]) qpush(ch[u - n][1] + n, 0);
   }
}
void dijkstra(int s) {
   rep(i, 1, 2 * n) dis[i] = INF;
   q.push((Node) {s, dis[s] = 0});
   while(q.size()) {
      int u = q.top().u, du = q.top().d; q.pop();
      if(dis[u] >= du) extend(u);
   }
}
int main() {
   //freopen("jump.in", "r", stdin); freopen("jump.out", "w", stdout);
   scanf("%d%d%d%d", &n, &m, &w, &h);
   rep(i, 1, n) scanf("%d%d", x + i, y + i), per[i] = i;
   rep(i, 1, m) scanf("%d%d%d%d%d%d", &a[i].u, &a[i].w, &a[i].lx, &a[i].rx, &a[i].ly, &a[i].ry);
   sort(a + 1, a + m + 1);
   rep(i, 1, m) if(!fir[a[i].u]) fir[a[i].u] = i;
   rep(i, 1, n) if(!fir[a[i].u]) fir[a[i].u] = m + 1;
   rep(i, 1, m) tu[i] = a[i].u;

   rt = build(1, n);
   dijkstra(1);
   rep(i, 2, n) printf("%d\n", dis[i]);
   return 0;
}
//KD-Tree 父连子，树上结点连对应结点