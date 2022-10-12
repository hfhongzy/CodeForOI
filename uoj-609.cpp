#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2048;
const int mod = 998244353;
int n, m, a[N];
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
    if(b & 1) ans = (ll)ans * a % mod;
  return ans;
}
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, n) scanf("%d", a + i);
  sort(a + 1, a + n + 1);
  bool mark0 = 1, mark1 = 1;
  rep(i, 1, n - 1) mark0 &= a[i] + m <= a[i + 1], mark1 &= a[i] == a[i + 1];
  if(mark0) {
    rep(i, 1, n) {
      ll inv2 = (mod + 1) / 2;
      printf("%lld\n", (a[i] + m * inv2) % mod);
    }
    return 0;
  }
  if(mark1) {
    int inv = qpow(n + 1, mod - 2);
    rep(i, 1, n) {
      printf("%lld\n", (a[1] + (ll)m * i % mod * inv) % mod);
    }
    return 0;
  }
  return 0;
}