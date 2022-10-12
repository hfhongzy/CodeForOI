#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
const int M = 3e6 + 10;
const ll mod = 23333333333333333;
int n, m, cnt[N];
int rk[N], sa[N], t[N], st[20][N], lg[N];
char s[N];
void build() {
  int m = *max_element(s + 1, s + n + 1);
  rep(i, 1, n) cnt[rk[i] = s[i]] ++;
  rep(i, 1, m) cnt[i] += cnt[i - 1];
  rep(i, 1, n) sa[cnt[rk[i]] --] = i;
  for(int k = 1, z = 0; k < n; k <<= 1, m = z, z = 0) {
    rep(i, n - k + 1, n) t[++ z] = i;
    rep(i, 1, n) if(sa[i] > k) t[++ z] = sa[i] - k;
    rep(i, 1, m) cnt[i] = 0;
    rep(i, 1, n) cnt[rk[i]] ++;
    rep(i, 1, m) cnt[i] += cnt[i - 1];
    per(i, n, 1) sa[cnt[rk[t[i]]] --] = t[i];
    copy(rk + 1, rk + n + 1, t + 1); rk[sa[1]] = z = 1;
    rep(i, 2, n) {
      if(t[sa[i]] == t[sa[i - 1]] && t[sa[i] + k] == t[sa[i - 1] + k]) {
        rk[sa[i]] = z;
      } else {
        rk[sa[i]] = ++ z;
      }
    }
    if(z == n) break ;
  }
  int z = 0;
  rep(i, 1, n) {
    if(rk[i] == 1) {
      st[0][1] = z = 0; continue ;
    }
    if(z) z --;
    int u = sa[rk[i] - 1];
    while(s[u + z] == s[i + z]) z ++;
    st[0][rk[i]] = z;
  }
  rep(i, 2, n) lg[i] = lg[i >> 1] + 1;
  rep(i, 1, lg[n]) rep(j, 1, n - (1 << i) + 1)
    st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}
int query(int l, int r) {
  int k = lg[r - l + 1];
  return min(st[k][l], st[k][r - (1 << k) + 1]);
}
ll solve() {
  static int n, c[N], st[N], top, l[N], r[N];
  scanf("%d", &n);
  rep(i, 1, n) scanf("%d", c + i), c[i] = rk[c[i]];
  if(n == 1) return 0;
  sort(c + 1, c + n + 1);
  n = unique(c + 1, c + n + 1) - c - 1;
  per(i, n, 2) c[i] = query(c[i - 1] + 1, c[i]);
  top = 0;
  rep(i, 2, n) {
    while(top && c[st[top]] > c[i]) {
      r[st[top --]] = i;
    }
    l[i] = top ? st[top] : 1;
    st[++ top] = i;
  }
  while(top) r[st[top --]] = n + 1;
  ll res = 0;
  rep(i, 2, n) res += (ll)c[i] * (i - l[i]) * (r[i] - i);
  return res % mod;
}
int main() {
  scanf("%d%d%s", &n, &m, s + 1);
  build();
  rep(i, 1, m) printf("%lld\n", solve());
  return 0;
}