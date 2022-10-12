#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
namespace net {

const int N = 2e4 + 10;
const int M = 2e6 + 10;
const int INF = 2147483640;

int n;
struct Edge { int v, c, f, nxt; } e[M];
int hd[N], p;
void clr(int sz) {
  fill(hd + 1, hd + sz + 1, -1); p = n = 0;
}
void add(int u, int v, int c) {
  e[p] = (Edge) {v, c, 0, hd[u]}; hd[u] = p ++;
  e[p] = (Edge) {u, 0, 0, hd[v]}; hd[v] = p ++;
}
queue<int> q;
int d[N], cur[N];
bool bfs() {
  fill(d + 1, d + n + 1, -1); q.push(1); d[1] = 0;
  while(!q.empty()) {
    int u = q.front(); q.pop();
    for(int i = hd[u]; ~ i; i = e[i].nxt) {
      int v = e[i].v; 
      if(d[v] == -1 && e[i].c > e[i].f) {
        d[v] = d[u] + 1; q.push(v);
      }
    }
  }
  return ~ d[n];
}
int dfs(int u, int a) {
  if(u == n || a == 0) return a;
  int ans = 0, f;
  for(int &i = cur[u]; ~ i; i = e[i].nxt) {
    int v = e[i].v;
    if(d[u] + 1 == d[v] && e[i].c > e[i].f && (f = dfs(v, min(a, e[i].c - e[i].f))) > 0) {
      ans += f; e[i].f += f; e[i ^ 1].f -= f;
      if((a -= f) == 0) break ;
    }
  }
  return ans;
}
int dinic() {
  int ans = 0;
  while(bfs()) {
    copy(hd + 1, hd + n + 1, cur + 1);
    ans += dfs(1, INF);
  }
  return ans;
}

}
const int N = 3010;
int n, m, a[N];
int main() {
  freopen("collection.in", "r", stdin);
  freopen("collection.out", "w", stdout);
  int test; scanf("%d", &test);
  while(test --) {
    scanf("%d%d", &n, &m);
    rep(i, 1, n) scanf("%d", a + i);
    static int tim[N];
    net::clr(2 + n + 2 * m); net::n = 1;
    rep(i, 1, n) {
      tim[i] = ++ net::n;
      net::add(1, tim[i], 1);
    }
    rep(i, 1, m) {
      int u, v;
      scanf("%d%d", &u, &v);
      net::n += 2;
      net::add(tim[u], net::n - 1, a[u]);
      net::add(tim[v], net::n, a[v]);
      net::add(net::n - 1, net::n, 1);
      net::add(net::n, net::n - 1, 1);
      tim[u] = net::n - 1;
      tim[v] = net::n;
    }
    net::add(tim[1], ++ net::n, a[1]);
    printf("%d\n", net::dinic());
  }
  return 0;
}