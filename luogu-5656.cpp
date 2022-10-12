#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
int a, b, c;
void exgcd(ll a, ll b, ll &x, ll &y, ll &g) {
  if(!b) { x = 1, y = 0, g = a; return ; }
  exgcd(b, a % b, y, x, g); y -= a / b * x;
}
int main() {
  int test;
  scanf("%d", &test);
  while(test --) {
    scanf("%d%d%d", &a, &b, &c);
    ll x, y, g;
    exgcd(a, b, x, y, g);
    if(c % g) { puts("-1"); continue ; }
    ll u = b / g, v = a / g;
    ll x0 = (x * (c / g) % u + u) % u;
    if(!x0) x0 = u;
    ll y0 = (c - x0 * a) / b;
    if(y0 > 0) {
      ll s = (y0 - 1) / v;
      ll x1 = x0 + s * u, y1 = y0 - s * v; 
      printf("%lld %lld %lld %lld %lld\n", s + 1, x0, y1, x1, y0);
    } else {
      ll y0 = (y * (c / g) % v + v) % v;
      if(!y0) y0 = v;
      printf("%lld %lld\n", x0, y0);
    }
  }
  return 0;
}