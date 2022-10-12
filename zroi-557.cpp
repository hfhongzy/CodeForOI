#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef unsigned long long ull;
const int N = 1005;
const int mod = 998244353;
struct Bitset {
  vector<ull> a;
  void resize(int n) { a.resize((n >> 6) + 2); }
  void set(int x) { a[x >> 6] |= 1ull << (x & 63); }
  bool operator [](int x) const { return a[x >> 6] >> (x & 63) & 1; }
  void operator ^= (const Bitset &b) {
    for(int i = 0; i < (int)a.size(); i ++) a[i] ^= b.a[i];
  }
} a[N], b[N];
int n, m, row[N], ano[N], rk, ans[N][N];
char s[N];
int main() {
  scanf("%d%d", &n, &m);
  rep(i, 1, n) {
    a[i].resize(m);
    b[i].resize(m);
    b[i].set(i);
    scanf("%s", s + 1);
    rep(j, 1, m) {
      if(s[j] == '1') a[i].set(j);
    }
  }
  rep(i, 1, m) {
    int k = 0;
    rep(j, rk + 1, n) if(a[j][i]) {
      k = j; break ;
    }
    if(!k) continue ;
    row[i] = ++ rk;
    swap(a[rk], a[k]);
    swap(b[rk], b[k]);
    for(k = 1; k <= n; k ++) if(k != rk && a[k][i]) {
      a[k] ^= a[rk]; b[k] ^= b[rk];
    }
  }
  rep(i, 1, m) if(row[i]) {
    rep(j, i + 1, m) if(a[row[i]][j]) {
      ano[i] = 1; break ;
    }
  }
  rep(i, 1, n) {
    int la = 0;
    per(j, n, 1) if(b[j][i]) { la = j; break ; }
    rep(j, 1, m) {
      if(!row[j]) {
        ans[i][j] = la > rk ? 1 : 0;
      } else {
        if(b[row[j]][i]) {
          ans[i][j] = -1;
          if(la > rk) ans[i][j] ++;
          if(ano[j]) ans[i][j] ++;
        } else {
          ans[i][j] = la > rk && ano[j] ? 1 : 0;
        }
      }
    }
  }
  ull res = 0;
  rep(i, 1, n) rep(j, 1, m) res += (ull)(rk + ans[i][j]) * i * j;
  printf("%llu\n", res % mod);
  return 0;
}