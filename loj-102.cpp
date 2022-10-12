#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;

template <const int N, const int M, class flow_t, class cost_t>
struct net {

using pa = pair<flow_t, cost_t>;
struct Edge {
  int v, nxt;
  flow_t c, f;
  cost_t w;
} e[M * 2];
int hd[N], cur[N], n, ec, s, t;
cost_t d[N];
cost_t CINF;
flow_t FINF;
void clear(int n) { this->n = n; fill(hd, hd + n + 1, -1); ec = 0; }
void config(flow_t f, cost_t c) { FINF = f; CINF = c; }
void add(int u, int v, flow_t c, cost_t w) {
  e[ec] = {v, hd[u], c, 0, w}; hd[u] = ec ++;
  e[ec] = {u, hd[v], 0, 0, -w}; hd[v] = ec ++;
}
bool inq[N];
bool spfa() {
  fill(d + 1, d + n + 1, CINF);
  queue<int> q; q.push(s); d[s] = 0; inq[s] = 1;
  while(q.size()) {
    int u = q.front(); q.pop(); inq[u] = 0;
    for(int i = hd[u]; ~i; i = e[i].nxt) {
      int v = e[i].v;
      if(e[i].f < e[i].c && d[u] + e[i].w < d[v]) {
        d[v] = d[u] + e[i].w;
        if(!inq[v]) { inq[v] = 1; q.push(v); }
      }
    }
  }
  return d[t] < CINF;
}
pa dfs(int u, flow_t a) {
  if(u == t || !a) return pa(a, 0);
  pa ans(0, 0), t;
  inq[u] = 1;
  for(int &i = cur[u]; ~i; i = e[i].nxt) {
    Edge &e = net::e[i];
    if(!inq[e.v] && d[e.v] == d[u] + e.w && (t = dfs(e.v, min(a, e.c - e.f))).fs > 0) {
      ans.fs += t.fs;
      ans.sc += t.sc + t.fs * e.w;
      e.f += t.fs;
      net::e[i ^ 1].f -= t.fs;
      if(!(a -= t.fs)) break ;
    }
  }
  inq[u] = 0;
  return ans;
}
pa mcmf(int s, int t) {
  this->s = s; this->t = t;
  pa ans(0, 0);
  while(spfa()) {
    copy(hd, hd + n + 1, cur);
    pa c = dfs(s, FINF);
    ans.fs += c.fs; ans.sc += c.sc;
  }
  return ans;
}

};
net<405, 30005, int, int> flow;
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  flow.clear(n);
  flow.config(INT_MAX, INT_MAX);
  rep(i, 1, m) {
    int u, v, c, w;
    scanf("%d%d%d%d", &u, &v, &c, &w);
    flow.add(u, v, c, w);
  }
  auto ans = flow.mcmf(1, n);
  printf("%d %d\n", ans.fs, ans.sc);
  return 0;
}