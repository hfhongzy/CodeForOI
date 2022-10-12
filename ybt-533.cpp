#include <bits/stdc++.h>
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10; 
struct node {
  int l, r, id;
} q[N];
int m, ans[N], B[N], sz;
int n, cnt[N], rk[N], sa[N], t[N], st[20][N], lg[N];
char s[N];
void build() {
  int m = '1';
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
  if(!l || r == n + 1) return 0;
  l ++;
  int k = lg[r - l + 1];
  return min(st[k][l], st[k][r - (1 << k) + 1]);
}
namespace lk { //link list

int l[N], r[N], st[N], top;
void build() {
  r[0] = 1; l[n + 1] = n; top = 0;
  rep(i, 1, n) l[i] = i - 1, r[i] = i + 1;
}
void del(int i) {
  l[r[i]] = l[i]; r[l[i]] = r[i]; st[++ top] = i;
}
int add() { //cancel deletion, return the contribution
  int i = st[top --];
  l[r[i]] = r[l[i]] = i;
  return max(query(l[i], i), query(i, r[i]));
}

}
int main() {
  freopen("history.in", "r", stdin);
  freopen("history.out", "w", stdout);
  scanf("%d%d%s", &n, &m, s + 1);
  reverse(s + 1, s + n + 1);
  int sz = max(1, n / (int)sqrt(m));
  rep(i, 1, n) B[i] = (i - 1) / sz + 1;
  build();
  rep(i, 1, m) {
    scanf("%d%d", &q[i].l, &q[i].r);
    q[i].l = n - q[i].l + 1;
    q[i].r = n - q[i].r + 1;
    swap(q[i].l, q[i].r);
    q[i].id = i;
  }
  sort(q + 1, q + m + 1, [&](node a, node b) {
    return B[a.l] == B[b.l] ? a.r > b.r : a.l < b.l;
  });
  rep(i, 1, m) {
    int j = i;
    int id = B[q[i].l], br = min(id * sz, n), bl = (id - 1) * sz + 1;
    while(j < m && q[j + 1].l <= br) j ++;
    lk::build();
    rep(k, 1, br) lk::del(rk[k]);
    per(k, n, br + 1) lk::del(rk[k]);
    static int par[N]; //ans of [br + 1, i]
    par[br] = 0;
    rep(k, br + 1, n)
      par[k] = max(par[k - 1], lk::add());
    per(k, br, bl) lk::add();
    int r = n;
    rep(u, i, j) {
      per(k, r, q[u].r + 1) lk::del(rk[k]);
      r = q[u].r;
      int c = br < q[u].r ? par[q[u].r] : 0;
      rep(k, bl, min(q[u].r, br)) lk::del(rk[k]);
      per(k, min(q[u].r, br), q[u].l) c = max(c, lk::add());
      ans[q[u].id] = c;
      per(k, q[u].l - 1, bl) lk::add();
    }
    i = j;
  }
  rep(i, 1, m) printf("%d\n", ans[i]);
  return 0;
}