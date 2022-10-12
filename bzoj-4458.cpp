#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
struct Uni {
  int b[N], m;
  void init(int *a, int n) {
    copy(a, a + n + 1, b + 1);
    sort(b + 1, b + n + 2);
    m = unique(b + 1, b + n + 2) - b - 1;
    for(int i = 0; i <= n; i ++)
      a[i] = lower_bound(b + 1, b + m + 1, a[i]) - b; 
  }
  int &operator [] (int x) { return b[x]; }
} uni;
int n, k, l, r, lgn, lg[N], fa[N], f[N][21], d[N];
int id, a[N], rt[N], sz[N * 22], ch[N * 22][2];
ll ans;
vector<int> G[N];
struct Node {
  int st, x, val;
  bool operator < (const Node &b) const {
    return val < b.val;
  }
};
void build(int &u, int l, int r) {
  u = ++ id; sz[u] = l <= a[0] && a[0] <= r;
  if(l == r) return ;
  int mid = (l + r) >> 1;
  build(ch[u][0], l, mid);
  build(ch[u][1], mid + 1, r);
}
void update(int &u, int p, int l, int r, int x) {
  u = ++ id; sz[u] = sz[p] + 1;
  if(l == r) return ;
  int mid = (l + r) >> 1;
  if(x <= mid) {
    ch[u][1] = ch[p][1];
    update(ch[u][0], ch[p][0], l, mid, x);
  } else {
    ch[u][0] = ch[p][0];
    update(ch[u][1], ch[p][1], mid + 1, r, x);
  }
}
int query(int u, int v, int l, int r, int x) {
  if(l == r) return l;
  int mid = (l + r) >> 1, lsz = sz[ch[u][0]] - sz[ch[v][0]];
  if(lsz >= x) return query(ch[u][0], ch[v][0], l, mid, x);
  return query(ch[u][1], ch[v][1], mid + 1, r, x - lsz);
}
void dfs(int u) {
  d[u] = d[fa[u]] + 1; f[u][0] = fa[u];
  update(rt[u], rt[fa[u]], 1, uni.m, a[u]);
  for(int i = 1; i < lgn; i ++)
    if(!(f[u][i] = f[f[u][i - 1]][i - 1])) break ;
  for(int i = 0; i < (int) G[u].size(); i ++) dfs(G[u][i]);
}
int kth(int u, int k) {
  for(; k; k &= k - 1)
    u = f[u][lg[k & (-k)]];
  return u;
}
int main() {
  scanf("%d", &n);
  for(lgn = 1; (1 << lgn) <= n; lgn ++) ;
  for(int i = 0; i < lgn; i ++) lg[1 << i] = i;
  for(int i = 1; i <= n; i ++) {
    scanf("%d", fa + i);
    if(fa[i]) G[fa[i]].push_back(i);
  }
  for(int i = 1; i <= n; i ++) {
    scanf("%d", a + i); a[i] += a[fa[i]];
  }
  scanf("%d%d%d", &k, &l, &r);
  uni.init(a, n); build(rt[0], 1, uni.m); dfs(1);
  priority_queue<Node> pq;
  static int anc1[N], anc2[N], cnt[N];
  for(int i = 1; i <= n; i ++) if(d[i] >= l) {
    cnt[i] = min(d[i], r) - l + 1;
    anc1[i] = kth(i, l); anc2[i] = kth(i, min(d[i], r));
    anc1[i] = rt[anc1[i]];
    anc2[i] = anc2[i] == 0 ? 0 : rt[fa[anc2[i]]];
    pq.push((Node) {i, 1, uni[a[i]] - uni[query(anc1[i], anc2[i], 1, uni.m, 1)]});
  }
  for(int i = 1; i <= k; i ++) {
    Node u = pq.top(); pq.pop(); ans += u.val;
    if(! -- cnt[u.st]) continue ;
    // printf("ex %d,%d \n", u.st, uni[query(rt[anc1[u.st]], rt[fa[anc2[u.st]]], 0, uni.m, u.x + 1)]);
    pq.push((Node) {u.st, u.x + 1, uni[a[u.st]] - uni[query(anc1[u.st], anc2[u.st], 1, uni.m, u.x + 1)]});
  }
  printf("%lld\n", ans);
  return 0;
} 