#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
int n, fa[N], a[N], b[N], num[N], ans[N], sz[N];
double k;
int mn[N * 4], tag[N * 4];
bool vis[N];
void addtag(int u, int t) {
  mn[u] += t; tag[u] += t;
}
void pd(int u) {
  if(tag[u]) {
    addtag(u << 1, tag[u]);
    addtag(u << 1 | 1, tag[u]);
    tag[u] = 0;
  }
}
void build(int u, int l, int r) {
  if(l == r) { mn[u] = b[l]; return ; }
  int mid = (l + r) >> 1;
  build(u << 1, l, mid);
  build(u << 1 | 1, mid + 1, r);
  mn[u] = min(mn[u << 1], mn[u << 1 | 1]);
}
void modify(int u, int l, int r, int ql, int qr, int x) { //f[ql to qr] += x
  if(l == ql && r == qr) { addtag(u, x); return ; }
  int mid = (l + r) >> 1; pd(u);
  if(qr <= mid) {
    modify(u << 1, l, mid, ql, qr, x);
  } else if(ql > mid) {
    modify(u << 1 | 1, mid + 1, r, ql, qr, x);
  } else {
    modify(u << 1, l, mid, ql, mid, x);
    modify(u << 1 | 1, mid + 1, r, mid + 1, qr, x);
  }
  mn[u] = min(mn[u << 1], mn[u << 1 | 1]);
}
int query(int u, int l, int r, int sz) { //min i, min f[1 to i] < sz
  if(l == r) return l;
  int mid = (l + r) >> 1; pd(u);
  if(mn[u << 1] < sz) return query(u << 1, l, mid, sz);
  return query(u << 1 | 1, mid + 1, r, sz);
}
int main() {
  scanf("%d%lf", &n, &k);
  rep(i, 1, n) { fa[i] = (int)floor(i / k); scanf("%d", a + i); }
  per(i, n, 1) { sz[i] ++; sz[fa[i]] += sz[i]; }
  sort(a + 1, a + n + 1);
  int c = 0;
  rep(i, 1, n) {
    if(a[i] != a[i - 1]) {
      c ++; num[c] = a[i];
    }
    b[c] ++;
  }
  per(i, n, 1) b[i] += b[i + 1];
  build(1, 1, n);
  vis[0] = 1;
  rep(i, 1, n) {
    if(!vis[fa[i]]) {
      modify(1, 1, n, 1, ans[fa[i]], sz[fa[i]] - 1);
      vis[fa[i]] = 1;
    }
    int v = mn[1] >= sz[i] ? n : query(1, 1, n, sz[i]) - 1;
    modify(1, 1, n, 1, v, - sz[i]);
    ans[i] = v;
  }
  rep(i, 1, n) printf("%d%c", num[ans[i]], " \n"[i == n]);
  return 0;
}