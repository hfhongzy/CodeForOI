#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 5e4 + 10, L = 3 * N, B = 410;
int n, m, q, a[N], b[N], qi[N], qx[N];
int sz, bel[L], bg[B], ed[B], tag[B];
int sum[L], pos[L];
ll cur, las[B];
int fnd(int x) { return lower_bound(pos + 1, pos + m + 1, x) - pos; }
inline int fx(const int &x) { return x > 0 ? x : -x; }
struct Node {
   int sum, pos;
   bool operator < (const Node &b) const { return sum < b.sum; }
} arr[L];
ll Sp[L], P[L];
ll gP(int l, int r) {
   int u = bel[l];
   return l == bg[u] ? P[r] : P[r] - P[l - 1];
}
ll gSp(int l, int r) {
   int u = bel[l];
   return (l == bg[u] ? Sp[r] : Sp[r] - Sp[l - 1]) + tag[u] * gP(l, r);
}
void rebuild(int u) { //pos[i] * |sum[i]|
   cur -= las[u]; las[u] = 0;
   for(int i = bg[u]; i <= ed[u]; i ++) {
      sum[i] += tag[u];
      las[u] += (ll) fx(sum[i]) * pos[i];
      arr[i] = (Node) {sum[i], pos[i]};
   }
   sort(arr + bg[u], arr + ed[u] + 1);
   for(int i = bg[u]; i <= ed[u]; i ++) {
      Sp[i] = (ll) arr[i].sum * arr[i].pos; P[i] = arr[i].pos;
      if(i != bg[u]) { Sp[i] += Sp[i - 1]; P[i] += P[i - 1]; }
   }
   cur += las[u]; tag[u] = 0;
}
void build() {
   sz = max(1, (int) sqrt(m));
   for(int i = 1; i <= m; i ++) {
      bel[i] = (i - 1) / sz + 1;
      if(!bg[bel[i]]) bg[bel[i]] = i;
      ed[bel[i]] = i;
   }
   for(int i = 1; i <= bel[m]; i ++) rebuild(i);
}
void modify(int x, int val) {
   for(int i = x; i <= ed[bel[x]]; i ++) sum[i] += val;
   rebuild(bel[x]);
   for(int i = bel[x] + 1; i <= bel[m]; i ++) {
      int l = bg[i], r = ed[i], k = r + 1; tag[i] += val;
      for(int ql = l, qr = r; ql <= qr; ) {
         int mid = (ql + qr) >> 1;
         if(arr[mid].sum + tag[i] >= 0) qr = (k = mid) - 1;
         else ql = mid + 1;
      }
      cur -= las[i]; las[i] = 0;
      if(k <= r) las[i] += gSp(k, r);
      if(k > l) las[i] -= gSp(l, k - 1);
      cur += las[i];
   }
}
int main() {
   scanf("%d", &n);
   for(int i = 1; i <= n; i ++) {
      scanf("%d", a + i);
      pos[i] = a[i];
   }
   for(int i = 1; i <= n; i ++) {
      scanf("%d", b + i);
      pos[n + i] = b[i];
   }
   scanf("%d", &q);
   for(int i = 1; i <= q; i ++) {
      scanf("%d%d", qi + i, qx + i);
      pos[2 * n + i] = qx[i];
   }
   m = 2 * n + q;
   sort(pos + 1, pos + m + 1);
   m = unique(pos + 1, pos + m + 1) - pos - 1;
   for(int i = 1; i <= n; i ++) a[i] = fnd(a[i]);
   for(int i = 1; i <= n; i ++) b[i] = fnd(b[i]);
   for(int i = 1; i <= q; i ++) qx[i] = fnd(qx[i]);
   for(int i = 1; i < m; i ++) pos[i] = pos[i + 1] - pos[i];
   pos[m] = 0;
   for(int i = 1; i <= n; i ++) sum[a[i]] ++, sum[b[i]] --;
   for(int i = 1; i <= m; i ++) sum[i] += sum[i - 1];
   build();
   printf("%lld\n", cur);
   for(int i = 1; i <= q; i ++) {
      modify(a[qi[i]], -1);
      modify(a[qi[i]] = qx[i], 1);
      printf("%lld\n", cur);
   }
}