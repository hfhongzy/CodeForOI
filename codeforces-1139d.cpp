#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
const int mod = 1e9 + 7;
int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
int dec(int x, int y) { return (x -= y) < 0 ? x + mod : x; }
bool tag[N];
int p[N], pc;
vector<int> vec[N];
void sieve(int n) {
  rep(i, 2, n) {
    if(!tag[i]) p[++ pc] = i;
    for(int v, j = 1; j <= pc && (v = i * p[j]) <= n; j ++) {
      tag[v] = 1;
      if(i % p[j] == 0) break ;
    }
  }
  rep(i, 1, pc)
    for(int j = p[i]; j <= n; j += p[i])
      vec[j].pb(p[i]);
}
int m, inv[N], ans;
int solve(int v) { //E(delete any)
  return (ll)m * inv[m - m / v] % mod;
}
int main() {
  scanf("%d", &m);
  sieve(m);
  inv[1] = 1;
  rep(i, 2, m) inv[i] = (mod - mod / i) * (ll)inv[mod % i] % mod;
  rep(i, 1, m) {
    int res = 0;
    int k = int(vec[i].size());
    for(int s = 1; s < (1 << k); s ++) {
      int c = 0, v = 1;
      rep(u, 0, k - 1) if(s >> u & 1) {
        c ^= 1; v *= vec[i][u];
      }
      int cur = solve(v);
      res = c ? add(res, cur) : dec(res, cur);
    }
    ans = add(ans, res);
  }
  ans = (ll)ans * inv[m] % mod;
  printf("%d\n", add(1, ans));
  return 0;
}