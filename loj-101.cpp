#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;

template <const int N, const int M, class flow_t>
struct net {

struct Edge {
  int v, nxt;
  flow_t c, f;
} e[M * 2];
int hd[N], cur[N], n, ec, s, t;
int d[N];
flow_t FINF;
void clear(int n) { this->n = n; fill(hd, hd + n + 1, -1); ec = 0; }
void config(flow_t f) { FINF = f; }
void add(int u, int v, flow_t c) {
  e[ec] = {v, hd[u], c, 0}; hd[u] = ec ++;
  e[ec] = {u, hd[v], 0, 0}; hd[v] = ec ++;
}
bool bfs() {
  fill(d, d + n + 1, -1);
  queue<int> q; q.push(t); d[t] = 998244353;
  while(q.size()) {
    int u = q.front(); q.pop();
    for(int i = hd[u]; ~i; i = e[i].nxt) {
      int v = e[i].v;
      if(e[i ^ 1].f < e[i ^ 1].c && !~d[v]) {
        d[v] = d[u] - 1;
        q.push(v);
        if(v == s) return ~d[s];
      }
    }
  }
  return ~d[s];
}
flow_t dfs(int u, flow_t a) {
  if(u == t || !a) return a;
  flow_t ans = 0, f;
  for(int &i = cur[u]; ~i; i = e[i].nxt) {
    Edge &e = net::e[i];
    if(d[e.v] == d[u] + 1 && (f = dfs(e.v, min(a, e.c - e.f))) > 0) {
      net::e[i].f += f; net::e[i ^ 1].f -= f; ans += f;
      if(!(a -= f)) break ;
    }
  }
  return ans;
}
flow_t dinic(int s, int t) {
  this->s = s; this->t = t;
  flow_t ans = 0;
  while(bfs()) {
    copy(hd, hd + n + 1, cur);
    ans += dfs(s, FINF);
  }
  return ans;
}

};
net<105, 5005, ll> flow;
int main() {
  int n, m, s, t;
  scanf("%d%d%d%d", &n, &m, &s, &t);
  flow.clear(n);
  flow.config(INT_MAX);
  rep(i, 1, m) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    flow.add(u, v, c);
  }
  printf("%lld\n", flow.dinic(s, t));
  return 0;
}