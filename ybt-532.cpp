#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef unsigned long long ull;
const int N = 2e5 + 10;
const int base = 2333;

int n, maxd, s[N], d[N], sa[N], rk[N], t[N], cnt[N], f[21][N], st[21][N], lg[N];
vector<int> G[N];
ull ha[21][N];
int LCP(int u, int v) {
  int ans = 0;
  per(i, lg[n], 0) {
    if(f[i][u] && f[i][v] && ha[i][u] == ha[i][v]) {
      u = f[i][u]; v = f[i][v]; ans ^= 1 << i;
    }
  }
  return ans;
}
void build() {
  int m = *max_element(s + 1, s + n + 1);
  rep(i, 1, n) cnt[rk[i] = s[i]] ++;
  rep(i, 1, m) cnt[i] += cnt[i - 1];
  per(i, n, 1) sa[cnt[rk[i]] --] = i;
  for(int num = 0, k = 0; (1 << k) <= maxd; k ++, m = num, num = 0) {
    int *pa = ::f[k];
    fill(cnt, cnt + m + 1, 0);
    rep(i, 1, n) cnt[rk[pa[i]]] ++;
    rep(i, 1, m) cnt[i] += cnt[i - 1];
    per(i, n, 1) t[cnt[rk[pa[i]]] --] = i;

    fill(cnt, cnt + m + 1, 0);
    rep(i, 1, n) cnt[rk[i]] ++;
    rep(i, 1, m) cnt[i] += cnt[i - 1];
    per(i, n, 1) sa[cnt[rk[t[i]]] --] = t[i];
    copy(rk + 1, rk + n + 1, t + 1); rk[sa[1]] = num = 1;
    rep(i, 2, n) {
      if(t[pa[sa[i - 1]]] == t[pa[sa[i]]] && t[sa[i - 1]] == t[sa[i]]) rk[sa[i]] = num;
      else rk[sa[i]] = ++ num;
    }
    if(num == n) break ;
  }
  rep(i, 1, n) rk[sa[i]] = i;
  rep(i, 2, n) lg[i] = lg[i >> 1] + 1;
  rep(i, 2, n) st[0][i] = LCP(sa[i - 1], sa[i]);// printf("LCP %d %d = %d\n", sa[i - 1], sa[i], st[0][i]);
  rep(i, 1, lg[n]) {
    rep(j, 2, n - (1 << i) + 1) {
      st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    }
  }
}
int query(int x, int y) {
  int k = lg[y - x];
  // printf("qr node %d %d [%d %d]= %d\n", sa[x], sa[y], x + 1, y, min(st[k][x + 1], st[k][y - (1 << k) + 1]));
  return min(st[k][x + 1], st[k][y - (1 << k) + 1]);
}
int mx[N * 32], mn[N * 32], ls[N * 32], rs[N * 32], id;
void insert(int &u, int l, int r, int p) {
  u = ++ id; mn[u] = mx[u] = p;
  if(l == r) return ;
  int mid = (l + r) >> 1;
  if(p <= mid) insert(ls[u], l, mid, p);
  else insert(rs[u], mid + 1, r, p);
}
int cur, rt[N], ans;
int smerge(int u, int v) {
  if(!u || !v) return u | v;
  if(ls[u] && rs[v]) cur = max(cur, query(mx[ls[u]], mn[rs[v]]));
  if(rs[u] && ls[v]) cur = max(cur, query(mx[ls[v]], mn[rs[u]]));
  mx[u] = max(mx[u], mx[v]); mn[u] = min(mn[u], mn[v]);
  ls[u] = smerge(ls[u], ls[v]); rs[u] = smerge(rs[u], rs[v]);
  return u;
}
void dfs(int u) {
  // printf("rk%d = %d\n", u, rk[u]);
  insert(rt[u], 1, n, rk[u]);
  for(int v : G[u]) {
    dfs(v);
    cur = -1;
    rt[u] = smerge(rt[u], rt[v]);
    if(~cur) ans = max(ans, d[u] + cur);
    // printf("(%d, %d) = %d cur = %d\n", u, v, d[u] + cur, cur);
  }
}
int main() {
  freopen("recollection.in", "r", stdin); freopen("recollection.out", "w", stdout);
  scanf("%d", &n); s[1] = 0;
  rep(i, 2, n) scanf("%d%d", f[0] + i, s + i), s[i] ++, G[f[0][i]].pb(i), d[i] = d[f[0][i]] + 1;
  maxd = *max_element(d + 1, d + n + 1);
  rep(i, 1, n) ha[0][i] = s[i];
  ull pw = base;
  rep(i, 1, 20) {
    if((1 << i) > n) break ;
    rep(j, 1, n) {
      f[i][j] = f[i - 1][f[i - 1][j]];
      ha[i][j] = ha[i - 1][f[i - 1][j]] + ha[i - 1][j] * pw;
      // printf("f[%d] 2^%d = %d %llu\n", j, i, f[i][j], ha[i][]);
    }
    pw *= pw;
  }
  build();
  dfs(1);
  printf("%d\n", ans);
  return 0;
}