#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2510;
int n, m, s, d[N];
ll sum;
struct ufs {
  int f[N];
  void init() { rep(i, 1, n) f[i] = i; }
  int find(int u) { return u == f[u] ? u : f[u] = find(f[u]); }
  bool unite(int u, int v) { u = find(u); v = find(v); f[u] = v; return u != v; }
} a, b;
struct node {
  int u, v, w;
  node() { u = v = w = 0; }
  node(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
};
int main() {
  scanf("%d%d%d", &n, &m, &s);
  a.init();
  rep(i, 1, m) {
    int u, v;
    scanf("%d%d", &u, &v);
    d[u] ++; d[v] ++;
    sum += abs(u - v);
    a.unite(u, v);
  }
  rep(i, 1, n) {
    d[i] ++; d[s] ++;
    b = a; b.unite(i, s);
    vector<int> v;
    rep(j, 1, n) if(d[j] & 1) v.pb(j);
    ll ans = 0;
    for(int j = 0; j < int(v.size()); j += 2) {
      b.unite(v[j], v[j + 1]);
      ans += v[j + 1] - v[j];
      for(int k = v[j]; k < v[j + 1]; k ++)
        b.unite(k, k + 1);
    }
    vector<node> e, es(n + 1);
    vector<int> cnt(n);
    int p = 0;
    rep(j, 1, n) if(d[j]) {
      if(p) {
        e.pb(node{b.find(p), b.find(j), j - p});
        cnt[j - p] ++;
      }
      p = j;
    }
    rep(j, 1, n - 1) cnt[j] += cnt[j - 1];
    for(node x : e) es[cnt[x.w] --] = x;
    rep(j, 1, cnt[n - 1]) {
      if(b.unite(es[j].u, es[j].v)) {
        ans += 2 * es[j].w;
      }
    }
    ans += sum;
    printf("%lld%c", ans, " \n"[i == n]);
    d[i] --; d[s] --;
  }
  return 0;
}