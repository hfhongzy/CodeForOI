#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT)
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n;
ll A, B;
vector< pair<ll, ll> > rg;
ll gcd(ll a, ll b) {
  return !b ? a : gcd(b, a % b);
}
int main() {
  scanf("%d%lld%lld", &n, &A, &B);
  ll l, r;
  if((long double) A / gcd(A, B + 1) * B > 4e18) {
    ll s = 0;
    while(n --) {
      scanf("%lld%lld", &l, &r);
      s += r - l + 1;
    }
    printf("%lld\n", s);
    return 0;
  }
  ll T = A / gcd(A, B + 1) * B;
  rep(i, 1, n) {
    scanf("%lld%lld", &l, &r);
    if(r - l + 1 >= T) {
      printf("%lld\n", T);
      return 0;
    }
    l %= T; r %= T;
    if(l <= r) rg.pb(make_pair(l, r));
    else {
      rg.pb(make_pair(l, T - 1));
      rg.pb(make_pair(0, r));
    }
  }
  sort(rg.begin(), rg.end());
  ll s = 0, la = -1;
  for(auto x : rg) {
    if(x.second <= la) continue ;
    if(x.first > la) {
      s += x.second - x.first + 1;
      la = x.second;
    } else {
      s += x.second - la;
      la = x.second;
    }
  }
  printf("%lld\n", s);
  return 0;
}