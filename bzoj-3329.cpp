#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
int a[64], m;
ll dp[64][2][2];
ll solve1(ll n) {
  m = 0;
  for(; n; n >>= 1) {
    a[++ m] = n & 1;
  }
  memset(dp, 0, sizeof dp);
  dp[m + 1][0][1] = 1;
  per(i, m, 1) {  
    rep(x, 0, 1) rep(s, 0, 1) if(dp[i + 1][x][s]) {
      rep(y, 0, (s ? a[i] : 1)) if(!(x && y)) {
        dp[i][y][s && y == a[i]] += dp[i + 1][x][s];
      }
    }
  }
  ll ans = 0;
  rep(x, 0, 1) rep(s, 0, 1) ans += dp[1][x][s];
  return ans - 1;
}
struct mat {
  int a[4];
  mat operator * (const mat &b) {
    mat ans;
    ans.a[0] = ((ll)a[0] * b.a[0] + (ll)a[1] * b.a[2]) % mod;
    ans.a[1] = ((ll)a[0] * b.a[1] + (ll)a[1] * b.a[3]) % mod;
    ans.a[2] = ((ll)a[2] * b.a[0] + (ll)a[3] * b.a[2]) % mod;
    ans.a[3] = ((ll)a[2] * b.a[1] + (ll)a[3] * b.a[3]) % mod;
    return ans;
  }
};
mat Pow(mat a, ll b) {
  mat ans = a; b --;
  for(; b; b >>= 1, a = a * a)
    if(b & 1) ans = ans * a;
  return ans;
}
int solve2(ll n) {
  mat ans = {1, 0, 0, 0};
  ans = ans * Pow(mat{1, 1, 1, 0}, n);
  return (ans.a[0] + ans.a[1]) % mod;
}
int main() {
  int test; scanf("%d", &test);
  while(test --) {
    ll n; scanf("%lld", &n);
    printf("%lld\n%d\n", solve1(n), solve2(n));
  }
  return 0;
}