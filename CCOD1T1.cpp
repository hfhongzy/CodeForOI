#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
char gc() {
  const int SZ = 1 << 20;
  // return getchar();
  static char buf[SZ], *S, *T;
  if(S == T) T = (S = buf) + fread(buf, 1, SZ, stdin);
  return S == T ? EOF : *S ++;
}
template<class T> void read(T &x) {
  x = 0; char c = gc(); bool na = 0;
  for(; c < '0' || c > '9'; c = gc()) na |= c == '-';
  for(; c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
  if(na) x = -x;
}
const int N = 1e5 + 10;
const int M = 1e6 + 10;
const int B = 100;
struct node {
  int v, id;
};
vector<node> vec[N];
int n, k, q, a[N], cnt[N], op[M], ord[N];
ll s1[M], s2[M];
template<class T>
struct BIT {
  vector<T> c;
  int n;
  BIT(int sz) { c.resize(1 + (n = sz)); }
  void add(int x, T y) {
    for(; x <= n; x += x & (-x))
      c[x] += y;
  }
  T qry(int x) {
    T ans = 0;
    for(; x >= 1; x &= x - 1)
      ans += c[x];
    return ans;
  }
};
int main() {
  read(n); read(k); read(q);
  ll ans = 0;
  BIT<int> bit(k);
  rep(i, 1, n) read(a[i]), ++ cnt[a[i]];
  per(i, n, 1) ans += bit.qry(a[i] - 1), bit.add(a[i], 1);
  rep(i, 1, n) ord[i] = i;
  rep(i, 1, q) {
    read(op[i]);
    swap(ord[op[i]], ord[op[i] + 1]);
    int u = ord[op[i]], v = ord[op[i] + 1];
    if(u > v) swap(u, v);
    vec[u].pb({v, i});
  }
  rep(i, 1, k) if(cnt[i] > B) {
    static ll r1[N], r2[N];
    rep(j, 1, k) r1[j] = r2[j] = 0;
    int t = 0;
    per(j, n, 1) {
      if(a[j] == i) ++ t;
      else r2[a[j]] += t;
    }
    t = 0;
    rep(j, 1, n) {
      if(a[j] == i) ++ t;
      else r1[a[j]] += t;
    }
    for(auto e : vec[i]) {
      s1[e.id] = r1[e.v];
      s2[e.id] = r2[e.v];
    }
  }
  static int w[N];
  rep(i, 1, n) {
    if(cnt[a[i]] <= B)
      for(auto e : vec[a[i]])
        s2[e.id] += w[e.v];
    ++ w[a[i]];
  }
  rep(i, 1, k) w[i] = 0;
  per(i, n, 1) {
    if(cnt[a[i]] <= B)
      for(auto e : vec[a[i]])
        s1[e.id] += w[e.v];
    ++ w[a[i]];
  }
  rep(i, 1, n) ord[i] = i;
  rep(i, 1, q) {
    int x = op[i];
    if(ord[x] < ord[x + 1]) {
      ans = ans - s2[i] + s1[i];
    } else {
      ans = ans - s1[i] + s2[i];
    }
    swap(ord[x], ord[x + 1]);
    printf("%lld\n", ans);
  }
  return 0;
}