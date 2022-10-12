#include <bits/stdc++.h>
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;

constexpr int N = 1e6 + 10;
constexpr double c = (1+sqrt(5))/2;

bool tag[N];
int p[N], pc, phi[N];
void sieve(int n) {
  mu[1] = phi[1] = 1;
  for(int i = 2; i <= n; i ++) {
    if(!tag[i]) {
      p[++ pc] = i;
      mu[i] = -1;
      phi[i] = i-1;
    }
    for(int j = 1; j <= pc && i * p[j] <= n; j ++) {
      int v = i * p[j];
      tag[v] = 1;
      if(i % p[j] == 0) {
        phi[v] = phi[i] * p[j];
        break ;
      }
      mu[v] = -mu[i];
      phi[v] = phi[i] * (p[j]-1);
    }
  }
}

ll n, m, a[N], t[N];
int main() {
  scanf("%lld", &n);
  for(m = 1; m * m <= n; m ++) ;
  sieve(m);
  ll ans = 0;
  for(int p = 1; p <= m; p ++)
    a[p] = floor(p / c) - 1;
  for(int p = 1; p <= m; p ++) {
    if(mu[p])
      for(int q = p; q <= m; q += p)
        t[q] += mu[p] * (a[q] / p);
    ans += n / (p*p) * (phi[p] - t[p]);
  }
  printf("%lld\n", ans);
  return 0;
}