#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int inv6 = 166374059;
const int inv2 = (mod + 1) >> 1;
int n, a, b, c;

namespace ELA { //Euclid-Like Algorithm

struct node { ll f, g, h; };
node solve(ll a, ll b, ll c, ll n) {
  node ans, tmp;
  ll n0 = n % mod;
  if(a == 0) {
    ans.f = (n0 + 1) * (b / c) % mod;
    ans.g = (b / c) * n0 % mod * (n0 + 1) % mod * inv2 % mod;
    ans.h = (n0 + 1) * (b / c) % mod * (b / c) % mod;
    return ans;
  }
  if(a >= c || b >= c) {
    tmp = solve(a % c, b % c, c, n);
    ans.f = (tmp.f + (a / c) * n0 % mod * (n0 + 1) % mod * inv2 + (b / c) * (n0 + 1)) % mod;
    ans.g = (tmp.g + (a / c) * n0 % mod * (n0 + 1) % mod * (2 * n + 1) % mod * inv6 + (b / c) * n0 % mod * (n0 + 1) % mod * inv2) % mod;
    ans.h = ((a / c) * (a / c) % mod * n0 % mod * (n0 + 1) % mod * (2 * n0 + 1) % mod * inv6 + 
        (b / c) * (b / c) % mod * (n0 + 1) + (a / c) * (b / c) % mod * n0 % mod * (n0 + 1) + 
        tmp.h + 2 * (a / c) % mod * tmp.g + 2 * (b / c) % mod * tmp.f) % mod;
    return ans;
  }
  ll m = (a * n + b) / c;,
  tmp = solve(c, c - b - 1, a, m - 1);
  ans.f = (n0 * (m % mod) - tmp.f) % mod;
  ans.g = (n0 * (n0 + 1) % mod * (m % mod) - tmp.f - tmp.h) % mod * inv2 % mod;
  ans.h = (n0 * (m % mod) % mod * ((m + 1) % mod) - 2 * tmp.g - 2 * tmp.f - ans.f) % mod;
  return ans;
}

}
int OUT(int x) {
  return x < 0 ? x + mod : x;
}
int main() {
  int test;
  scanf("%d", &test);
  while(test --) {
    scanf("%d%d%d%d", &n, &a, &b, &c);
    ELA::node x = ELA::solve(a, b, c, n);
    printf("%d %d %d\n", OUT(x.f), OUT(x.h), OUT(x.g));
  }
  return 0;
}