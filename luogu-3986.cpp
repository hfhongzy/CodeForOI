#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
int k, ans, f[64];
void exgcd(ll a, ll b, ll &x, ll &y) {
  if(!b) { x = 1; y = 0; return ; }
  exgcd(b, a % b, y, x); y -= x * (a / b);
}
int main() {
  scanf("%d", &k);
  f[0] = 0; f[1] = 1;
  int p;
  for(p = 1; f[p] + f[p - 1] <= k; p ++) f[p + 1] = f[p] + f[p - 1];
  // cerr << "p = " << p << endl;
  //x*f[n]+y*f[n+1]=1 n>=1
  ll x, y;
  for(int i = 1; i < p; i ++) {
    exgcd(f[i], f[i + 1], x, y);
    ll x0 = ((x * k) % f[i + 1] + f[i + 1]) % f[i + 1];
    if(!x0) x0 = f[i + 1];
    // if((k - x0 * f[i]) % f[i + 1]) assert(0);
    ll y0 = (k - x0 * f[i]) / f[i + 1];
    if(y0 <= 0) continue ;
    ans = (ans + 1 + (y0 - 1) / f[i]) % mod;
    // printf("%d:%lld\n", i, 1 + (y0 - 1) / f[i]);
  }
  printf("%d\n", ans);
  return 0;
}