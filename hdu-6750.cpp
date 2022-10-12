#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;

const int N = 1e6 + 4;
const int mod = 1e9 + 7;

int p[78498 + 5], c, mu[N];
bitset<1000005> tag;
void sieve(int n) {
  mu[1] = 1;
  for(int i = 2; i <= n; i ++) {
    if(!tag[i]) { p[++ c] = i; mu[i] = -1; }
    for(int j = 1; j <= c && i * p[j] <= n; j ++) {
      tag[i * p[j]] = 1;
      if(i % p[j] == 0) break ;
      mu[i * p[j]] = - mu[i];
    }
    if(mu[i]) mu[i] = mu[i] == -1 ? mod - i : i;
    (mu[i] += mu[i - 1]) %= mod;
  }
}
ll S(ll n) {
  if(n >= mod) n %= mod;
  return n * (n + 1) / 2 % mod;
}
ll G(ll n) {
  int ans = 0;
  for(ll i = 1, j; i <= n; i = j + 1) {
    j = n / (n / i);
    ans = (ans + (S(j) - S(i - 1) + mod) * (n / i % mod)) % mod;
  }
  return ans;
}
int main() {
  int test; scanf("%d", &test); sieve(1e6); //cout << c << endl;
  while(test --) {
    ll n, ans = 0; scanf("%lld", &n);
    int m = (ll) sqrt(n);
    for(ll i = 1, r; i <= m; i = r + 1) {
      r = min(m, (int) sqrt(n / (n / (i * i))));
      ans = (ans + (mu[r] - mu[i - 1] + mod) * G(n / (i * i))) % mod;
    }
    printf("%lld\n", ans);
  }
  return 0;
}