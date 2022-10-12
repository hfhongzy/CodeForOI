#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 175;
const int mod = 998244353;
struct mat {
  int n, m, a[N][N];
  mat() {}
  mat(int x, int y) : n(x), m(y) {}
  mat operator * (const mat &b) const {
    mat ans(n, b.m);
    rep(i, 1, ans.n) rep(j, 1, ans.m) {
      __int128 z = 0;
      rep(k, 1, m) z += (ll)a[i][k] * b.a[k][j];
      ans.a[i][j] = z % mod;
    }
    return ans;
  }
} pw[62];
int m, k, inv[10], ID[10][10][10];
int main() {
  inv[1] = 1;
  rep(i, 2, 9) inv[i] = (mod - mod / i) * (ll)inv[mod % i] % mod;
  int test;
  scanf("%d%d%d", &test, &m, &k);
  int id = 0;
  rep(a, 0, k)
    rep(b, 0, (m >= 2 ? k - a : 0))
      rep(c, 0, (m == 3 ? k - a - b : 0))
        ID[a][b][c] = ++ id;
  ++ id;
  rep(a, 0, k)
    rep(b, 0, (m >= 2 ? k - a : 0))
      rep(c, 0, (m == 3 ? k - a - b : 0)) {
        int u = ID[a][b][c], iv = inv[a + b + c + 1];
        int z = a + b + c < k;
        if(m == 1) {
          if(a) pw->a[u][ID[a - 1][0][0]] = (ll)a * iv % mod;
        }
        if(m == 2) {
          if(a) pw->a[u][ID[a - 1][b][0]] = (ll)a * iv % mod;
          if(b) pw->a[u][ID[a + 1][b + z - 1][0]] = (ll)b * iv % mod;
        }
        if(m == 3) {
          if(a) pw->a[u][ID[a - 1][b][c]] = (ll)a * iv % mod;
          if(b) pw->a[u][ID[a + 1][b - 1][c + z]] = (ll)b * iv % mod;
          if(c) pw->a[u][ID[a][b + 1][c + z - 1]] = (ll)c * iv % mod;
        }
        pw->a[u][u] = pw->a[u][id] = iv;
      }
  pw->a[id][id] = 1;
  pw->n = pw->m = id;
  rep(i, 1, 59) pw[i] = pw[i - 1] * pw[i - 1];
  while(test --) {
    ll n;
    scanf("%lld", &n);
    mat c(1, id);
    rep(i, 1, id) c.a[1][i] = 0;
    c.a[1][ID[m == 1][m == 2][m == 3]] = 1;
    rep(i, 0, 59) if(n >> i & 1) c = c * pw[i];
    printf("%d\n", c.a[1][id]);
  }
  return 0;
}