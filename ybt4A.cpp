#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;
const int N = 1e6 + 10;
const int MOD[5] = {1000000009, 999999937, 999999929, 999999893, 999999883};
const int base = 2333;

int mod, pw[N], a[N], b[N], n, m;
ll solve(int n, int *a) {
  static int p[N * 2], f[N * 2], pre[N * 2];
  p[0] = -1;
  rep(i, 1, n) { p[i * 2 - 1] = '#'; p[i * 2] = a[i]; }
  p[n = 2 * n + 1] = '#'; p[n + 1] = -2;
  int maxr = 0, mid = 0;
  rep(i, 1, n) {
    f[i] = i < maxr ? min(maxr - i, f[2 * mid - i]) : 1;
    while(p[i + f[i]] == p[i - f[i]]) f[i] ++;
    if(i + f[i] > maxr) { maxr = i + f[i]; mid = i; }
  }
  pre[1] = 1;
  int la = 1, c = 1;
  for(int i = 3; i <= n; i += 2) {
    if(la >= i - f[i] + 1) {
      la = i; c ++;
    }
    pre[i] = c;
  }
  la = n;
  ll ans = pre[n - 2];
  for(int i = n - 2; i >= 3; i -= 2) {
    if(la <= i + f[i] - 1) {
      ans += pre[i - 2];
      la = i;
    }
  }
  return ans;
}
int main() {
  freopen("paper.in", "r", stdin);
  freopen("paper.out", "w", stdout);
  srand(time(0));
  mod = MOD[rand() % 5];
  scanf("%d%d", &n, &m);
  static char s[N];
  pw[0] = 1;
  rep(i, 1, max(n, m)) pw[i] = (ll)pw[i - 1] * base % mod;
  rep(i, 1, n) {
    scanf("%s", s + 1);
    rep(j, 1, m) {
      a[i] = (a[i] + (ll)pw[j - 1] * s[j]) % mod;
      b[j] = (b[j] + (ll)pw[i - 1] * s[j]) % mod;
    }
  }
  printf("%lld\n", solve(n, a) * solve(m, b));
  return 0;
}