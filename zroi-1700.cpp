#include <bits/stdc++.h>
using namespace stdp;

typedef unsigned long long ll;
const int N = 1000054, mod = 998244353;

int n, m, ans[N], fac[N], fav[N];

ll qpow(ll a, int n) {
  ll ans = 1;
  for(; n; n >>= 1, a = a * a % mod)
    if(n & 1) ans = ans * a % mod;
  return ans;
}

void init(int n) {
  for(int i = 1; i <= n; ++ i) fac[i] = (ll)fac[i - 1] * i % mod;
  fav[n] = qpow(fac[n], mod - 2);
  for(int i = n; i >= 1; -- i) fav[i - 1] = (ll)fav[i] * i % mod;
}

int main() {
  int i, j, ty, R = 0;
  cin >> ty >> n, m = n / 2, init(n + 1);
  for(i = 0, j = n + 1; i <= m; ++i, j -= 2)
    ans[i] = (ll)j * j % mod * fac[n] % mod * fav[i] % mod * fav[n - i + 1] % mod;
  if (ty == 1) cin >> i, cout << ans[i] << '\n';
  else {
    for(i = m; i >= 0; --i) R = (R * 233ll + ans[i]) % mod;
    cout << R << '\n';
  }
  return 0;
}