#include <bits/stdc++.h>
#define fs first
#define sc second
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

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
void add(int u, int v, flow_t c, cost_t w, bool rev = 0) {
  if(rev) swap(u, v);
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
const int INF = 1e9;
const int N = 2020;
net<8005, 100005, int, int> flow;
int n, m, id[N][N], c, cnt[32];
int main() {
  flow.config(INF, INF);
  rep(i, 1, 15) cnt[i] = cnt[i & (i - 1)] + 1;
  scanf("%d%d", &n, &m);
  rep(i, 1, n) rep(j, 1, m) id[i][j] = c + 1, c += 4;
  flow.clear(c + 2);
  int t = 0, z = 0;
  const int dx[] = {-1, 0, 1, 0};
  const int dy[] = {0, 1, 0, -1};
  rep(i, 1, n) rep(j, 1, m) {
    scanf("%d", &z);
    t += cnt[z];
    if(!cnt[z]) continue ;
    bool out = (i + j) & 1;
    rep(k, 0, 3) if(z >> k & 1)
      out ? flow.add(id[i][j] + k, c + 2, 1, 0) : flow.add(c + 1, id[i][j] + k, 1, 0);
    if(!out) {
      rep(k, 0, 3) {
        int x = i + dx[k], y = j + dy[k];
        if(id[x][y]) {
          flow.add(id[i][j] + k, id[x][y] + (k ^ 2), 1, 0);
        }
      }
    }
    if(cnt[z] == 3) {
      rep(k, 0, 3) if(!(z >> k & 1))
        rep(v, 0, 3) if(k != v)
          flow.add(id[i][j] + v, id[i][j] + k, 1, 1 + ((k ^ v) == 2), out);
    }
    if(cnt[z] == 2 && z != 5 && z != 10) {
      rep(k, 0, 3) if(z >> k & 1)
        flow.add(id[i][j] + k, id[i][j] + (k ^ 2), 1, 1, out);
    }
    if(cnt[z] == 1) {
      rep(k, 0, 3) if(z >> k & 1)
        rep(v, 0, 3) if(k != v)
          flow.add(id[i][j] + k, id[i][j] + v, 1, 1 + ((k ^ v) == 2), out);
    }
  }
  auto res = flow.mcmf(c + 1, c + 2);
  printf("%d\n", res.fs * 2 == t ? res.sc : -1);
  return 0;
}