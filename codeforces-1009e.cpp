#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
const int mod = 998244353;
int n, ans, a[N], pw[N] = {1};
int main() {
  scanf("%d", &n);
  rep(i, 1, n) scanf("%d", a + i), (a[i] += a[i - 1]) %= mod;
  rep(i, 1, n) pw[i] = pw[i - 1] * 2 % mod;
  ans = a[n];
  rep(i, 1, n - 1) {
    int tot = ( 2ll * pw[n - 1 - i] + (i < n - 1 ? (n - i - 1ll) * pw[n - i - 2] : 0) ) % mod;
    ans = (ans + (ll)a[i] * tot) % mod;
  }
  printf("%d\n", ans);
  return 0;
}