#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 5e5 + 10;
char s[N];
int n, maxd, seq[N], d[N], sa[N], rk[N], t[N], cnt[N], f[N], g[N];
vector<int> G[N];
void init(int s) {
  queue<int> q; q.push(s); d[s] = 0;
  int l = 0;
  while(q.size()) {
    int u = q.front(); q.pop(); maxd = max(maxd, d[u]); seq[++ l] = u;
    for(int v : G[u]) {
      d[v] = d[u] + 1; q.push(v);
    }
  }
  rk[1] = 1;
  rep(i, 2, n) {
    int j = i;
    while(j < n && d[seq[j]] == d[seq[j + 1]]) j ++;
    sort(seq + i, seq + j + 1, [&](int x, int y) {
      return f[x] == f[y] ? x < y : rk[f[x]] < rk[f[y]];
    });
    rep(k, i, j) rk[seq[k]] = k;
    i = j;
  }
}
void build() {
  int m = *max_element(s + 1, s + n + 1);
  rep(i, 1, n) cnt[rk[i] = s[i]] ++;
  rep(i, 1, m) cnt[i] += cnt[i - 1];
  per(i, n, 1) sa[cnt[rk[seq[i]]] --] = seq[i];
  for(int num = 0, k = 0; (1 << k) <= maxd; k ++, m = num, num = 0) {
    fill(cnt, cnt + m + 1, 0);
    rep(i, 1, n) cnt[rk[f[i]]] ++;
    rep(i, 1, m) cnt[i] += cnt[i - 1];
    per(i, n, 1) t[cnt[rk[f[seq[i]]]] --] = seq[i];

    fill(cnt, cnt + m + 1, 0);
    rep(i, 1, n) cnt[rk[i]] ++;
    rep(i, 1, m) cnt[i] += cnt[i - 1];
    per(i, n, 1) sa[cnt[rk[t[i]]] --] = t[i];
    copy(rk + 1, rk + n + 1, t + 1); rk[sa[1]] = num = 1;
    rep(i, 2, n) {
      if(t[f[sa[i - 1]]] == t[f[sa[i]]] && t[sa[i - 1]] == t[sa[i]]) rk[sa[i]] = num;
      else rk[sa[i]] = ++ num;
    }
    if(num == n) break ;
    rep(i, 1, n) g[i] = f[f[i]];
    rep(i, 1, n) f[i] = g[i];
  }
}
int main() {
  scanf("%d", &n);
  rep(i, 2, n) scanf("%d", f + i), G[f[i]].pb(i);
  scanf("%s", s + 1);
  init(1);
  build();
  rep(i, 1, n) printf("%d ", sa[i]);
  return 0;
}