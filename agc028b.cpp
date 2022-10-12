#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
int n, a[N], inv[N];
int main() {
  scanf("%d", &n);
  rep(i, 1, n) scanf("%d", a + i);
  inv[1] = 1;
  rep(i, 2, n) inv[i] = (mod - mod / i) * (ll)inv[mod % i] % mod;
  rep(i, 1, n) (inv[i] += inv[i - 1]) %= mod;
  int ans = 0;
  rep(i, 1, n) {
    ans = (ans + (ll)a[i] * (inv[i] + inv[n - i + 1] - 1)) % mod;
  }
  rep(i, 1, n) ans = (ll)ans * i % mod;
  printf("%d\n", ans);
  return 0;
}