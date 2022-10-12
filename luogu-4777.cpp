#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;
const int N = 1e5 + 10;
int n;
ll c[N], d[N]; //x \equiv d \pmod {c}
ll mul(ll a, ll b, ll p) {
  ll r = a * b - (ll)((long double)a * b / p + 0.5) * p;
  return r < 0 ? r + p : r;
}
void exgcd(ll a, ll b, ll &x, ll &y, ll &g) {
  if(!b) x = 1, y = 0, g = a;
  else exgcd(b, a % b, y, x, g), y -= a / b * x;
}
int main() {
  scanf("%d", &n);
  rep(i, 1, n) scanf("%lld%lld", c + i, d + i);
  ll a = c[1], b = d[1];
  rep(i, 2, n) {
    ll k, t, g;
    exgcd(a, c[i], k, t, g);
    assert((d[i] - b) % g == 0);
    t = c[i] / g;
    k = mul(k, (d[i] - b) / g, t);
    ll na = a * t;
    b = (mul(a, k, na) + b) % na;
    a = na;
  }
  printf("%lld\n", b);
  return 0;
}