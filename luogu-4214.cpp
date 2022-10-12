#include <bits/stdc++.h>
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef unsigned uint;
typedef long long ll;
const int N = 3010;
mt19937 mt(time(0));
struct edge { int u, v; } e[N * 2];
int n, m, bcc, cur, low[N], dfn[N], bel[N], sz[N], z, cnt, ans, banu, banv;
uint val[N], w[N];
vector<int> G[N], T[N];
stack<int> st;
bool ins[N];
bool ban(int u, int v) {
  return (banu == u && banv == v) || (banu == v && banv == u);
}
void tarjan(int u, int p = 0) {
  if(!p) z = 0;
  cur ++; dfn[u] = low[u] = ++ z; st.push(u); ins[u] = 1;
  // cerr << "u = " << u << endl;
  for(int v : G[u]) if(v != p && !ban(u, v)) {
    if(!dfn[v]) {
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
    } else if(ins[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if(low[u] == dfn[u]) {
    sz[++ bcc] = 0;
    for(int v = 0; v != u; ) {
      v = st.top(); st.pop(); bel[v] = bcc; sz[bcc] ++; ins[v] = 0;
    }
  }
}
int main() {
  scanf("%d%d", &n, &m); cnt = n * (n - 1) / 2;
  int u, v;
  rep(i, 1, m) {
    scanf("%d%d", &u, &v);
    G[u].pb(v); G[v].pb(u);
    e[i] = {u, v};
  }
  int las = 0;
  rep(i, 1, n) if(!dfn[i]) {
    tarjan(i);
    int now = cur - las;
    cnt -= las * now; //f = 0
    cnt -= now * (now - 1) / 2;
    ans += now * (now - 1) / 2;
    las = cur;
  }
  // rep(i, 1, n) debug("bel%d = %d\n", i, bel[i]);
  rep(i, 1, bcc) {
    cnt += sz[i] * (sz[i] - 1) / 2;
    ans -= sz[i] * (sz[i] - 1) / 2;
  }
  rep(i, 1, m) {
    fill(dfn + 1, dfn + n + 1, 0);
    banu = e[i].u; banv = e[i].v; bcc = 0;
    rep(j, 1, n) if(!dfn[j]) tarjan(j);
    rep(j, 1, bcc) w[j] = mt();
    rep(j, 1, n) val[j] ^= w[bel[j]];
  }
  sort(val + 1, val + n + 1);
  int s = 0;
  rep(i, 1, n) {
    if(i == 1 || val[i - 1] != val[i]) {
      s = 0;
    }
    cnt -= s;
    ans += 3 * s ++;
  }
  // cerr << "cnt = " << cnt << endl;
  ans += cnt * 2;
  printf("%d\n", ans);
  return 0;
}