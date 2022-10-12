#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
char gc() {
  // return getchar();
  static char buf[1 << 17], *S, *T;
  if(S == T) T = (S = buf) + fread(buf, 1, 1 << 17, stdin);
  return S == T ? EOF : *S ++;
}
template<class T>
void read(T &x) {
  x = 0; char c = gc(); bool na = 0;
  for(; !isdigit(c); c = gc()) na |= c == '-';
  for(; isdigit(c); c = gc()) x = x * 10 + (c & 15);
  if(na) x = -x;
}
const int N = 2e5 + 10;
int n, m, sz[N], f[N], tot, rt;
vector<int> G[N];
int top[N], son[N], d[N], p[N];
bool vis[N];
ll a[N];
void pdfs(int u, int fa = 0) {
  sz[u] = 1; d[u] = d[fa] + 1; p[u] = fa;
  for(int v : G[u]) if(v != fa) {
    pdfs(v, u);
    if(sz[v] > sz[son[u]]) son[u] = v;
    sz[u] += sz[v];
  }
}
void pdfs2(int u, int t) {
  top[u] = t;
  if(son[u]) {
    pdfs2(son[u], t);
    for(int v : G[u]) if(!top[v]) pdfs2(v, v);
  }
}
int LCA(int u, int v) {
  for(; top[u] != top[v]; u = p[top[u]])
    if(d[top[u]] < d[top[v]]) swap(u, v);
  return d[u] < d[v] ? u : v;
}
int dis(int u, int v) { return d[u] + d[v] - 2 * d[LCA(u, v)]; }
void findrt(int u, int fa = 0) {
  f[u] = sz[u] = 1;
  for(int v : G[u]) if(v != fa && !vis[v]) {
    findrt(v, u);
    f[u] = max(f[u], sz[v]);
    sz[u] += sz[v];
  }
  f[u] = max(f[u], tot - sz[u]);
  if(!rt || f[rt] > f[u]) rt = u;
}
int pre[N];
ll sum[N], sf[N], cnt[N], W, S, tmp[N];
void solve(int u, int fa = 0) {
  tmp[u] = a[u];
  for(int v : G[u]) if(v != fa) {
    solve(v, u); tmp[u] += tmp[v];
  }
  W += tmp[u] * (S - tmp[u]);
}
void build(int u) {
  vis[u] = 1;
  for(int v : G[u]) if(!vis[v]) {
    tot = sz[v]; rt = 0; findrt(v);
    pre[rt] = u; build(rt);
  }
}
void modify(int u, ll val) {
  for(int v = u, la = 0; v; la = v, v = pre[v]) {
    ll d = dis(v, u);
    cnt[v] += val; sum[v] += val * d;
    if(la) sf[la] += val * d;
  }
}
ll calc(int u) {
  ll ans = 0;
  for(int v = u, la = 0; v; la = v, v = pre[v]) {
    ll d = dis(v, u);
    ans += d * (cnt[v] - cnt[la]) + sum[v] - sf[la];
  }
  return ans;
}
int main() {
  read(n); read(m);
  int op, u, v;
  rep(i, 1, n - 1) {
    read(u); read(v); G[u].pb(v); G[v].pb(u);
  }
  pdfs(1); pdfs2(1, 1);
  tot = n; rt = 0; findrt(1); build(rt);
  rep(i, 1, n) read(a[i]), modify(i, a[i]), S += a[i];
  solve(1);
  rep(i, 1, m) {
    read(op); read(u);
    if(op == 1) {
      ll z; read(z); z -= a[u];
      W += z * calc(u);
      modify(u, z); a[u] += z; S += z;
    } else {
      printf("%lld\n", S * (calc(u) + S) - W);
    }
  }
  return 0;
}