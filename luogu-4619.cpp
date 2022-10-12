#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
int p[N], c[N], d[N], mu[N], pc;
bool tag[N];
void sieve(int n) {
  mu[1] = d[1] = 1; c[1] = 0;
  for(int v, i = 2; i <= n; i ++) {
    if(!tag[i]) { p[++ pc] = i; d[i] = 2; c[i] = 1; mu[i] = -1; }
    for(int j = 1; j <= pc && (v = i * p[j]) <= n; j ++) {
      tag[v] = 1;
      if(i % p[j] == 0) {
        c[v] = c[i] + 1;
        d[v] = d[i] / c[v] * (c[v] + 1);
        break ;
      }
      mu[v] = -mu[i]; d[v] = d[i] * 2; c[v] = 1;
    }
  }
  rep(i, 2, n) (d[i] += d[i - 1]) %= mod;
}
int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }
ll lcm(ll x, ll y) { return x / gcd(x, y) * y; }
struct edge { int u, v, w; }; //w:lcm
vector<edge> e;
vector<int> G[N];
int vis[N], w[N], deg[N], tim;
int solve(int a, int b, int c) {
  vector<edge>().swap(e);
  rep(i, 1, c) {
    deg[i] = 0; vector<int>().swap(G[i]);
  }
  rep(i, 1, c) {
    for(int j = i; j <= c; j += i) if(mu[j]) {
      for(int k = j, r = (ll)c * i / j; k <= r; k += i) if(mu[k]) {
        if(gcd(j, k) == i) {
          e.pb({j, k, j / i * k}); deg[k] ++; deg[j] ++;
        }
      }
    }
  }
  for(int i = 0; i < int(e.size()); i ++) {
    edge &x = e[i];
    if(deg[x.u] < deg[x.v] || (deg[x.u] == deg[x.v] && x.u < x.v))
      swap(x.u, x.v);
    G[x.u].pb(i);
  }
  int ans = 0;
  rep(i, 1, c) if(mu[i]) {
    ++ tim;
    for(int id1 : G[i]) vis[e[id1].v] = tim, w[e[id1].v] = e[id1].w;
    for(int id1 : G[i]) {
      int j = e[id1].v;
      for(int id2 : G[j]) {
        int k = e[id2].v;
        if(vis[k] == tim) {
          int w1 = e[id1].w, w2 = e[id2].w, w3 = w[k];
          #define F(x, y, z) (1ll * d[a / x] * d[b / y] % mod * d[c / z])
          ll cur = 0;
          if(i == j && j == k) {
            cur = F(w1, w2, w3);
          } else if(i == j || j == k || i == k) {
            cur = F(w1, w2, w3) + F(w2, w3, w1) + F(w3, w1, w2);
          } else {
            cur = F(w1, w2, w3) + F(w1, w3, w2) + F(w2, w1, w3) + F(w2, w3, w1) + F(w3, w1, w2) + F(w3, w2, w1);
          }
          ans = (ans + mu[i] * mu[j] * mu[k] * cur) % mod;
        }
      }
    }
  }
  if(ans < 0) ans += mod;
  return ans;
}
int main() {
  sieve(100000);
  int test, a, b, c;
  scanf("%d", &test);
  while(test --) {
    scanf("%d%d%d", &a, &b, &c);
    if(a > b) swap(a, b);
    if(b > c) swap(b, c);
    if(a > b) swap(a, b);
    printf("%d\n", solve(a, b, c));
  }
  return 0;
}