#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;

ll calc(ll n, int p) {
  ll x = 1;
  for(ll i = 0; n - i * i >= 1; i ++)
    x = x * (n - i * i) % p;
  return (x + p) % p;
}
ll solve(ll l, ll r, int p) {
  ll ans = 0;
  while(r >= l) {
    ans += calc(r --, p) == 0;
  }
  return ans;
}
int main() {
  // freopen("c.in", "r", stdin);
  // freopen("c.out", "w", stdout);
  ll l, r; int p;
  scanf("%lld%lld%d", &l, &r, &p);
  printf("%lld\n", solve(l, r, p));
  return 0;
}
