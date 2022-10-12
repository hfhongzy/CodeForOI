#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 2e5 + 18;
const ll INF = 1e18;
int n, t, a, b, x[N];
ll val[3][N << 2], tag[N << 2];
void upd(int u) {
   for(int i = 0; i < 3; i ++)
      val[i][u] = min(val[i][u << 1], val[i][u << 1 | 1]);
}
void build(int u, int l, int r) {
   if(l == r) {
      val[0][u] = abs(b - l);
      val[1][u] = val[0][u] - l;
      val[2][u] = val[0][u] + l;
      return ;
   }
   int mid = (l + r) >> 1;
   build(u << 1, l, mid);
   build(u << 1 | 1, mid + 1, r);
   upd(u);
}
void addtag(int u, ll v) {
   tag[u] += v;
   for(int i = 0; i < 3; i ++)
      val[i][u] += v;
}
void pdown(int u) {
   if(tag[u]) {
      addtag(u << 1, tag[u]);
      addtag(u << 1 | 1, tag[u]);
      tag[u] = 0;
   }
}
bool check(int u, int l, int r, int pos, ll v) {
   if(l == r) {
      if(val[0][u] > v) {
         val[0][u] = v;
         val[1][u] = val[0][u] - l;
         val[2][u] = val[0][u] + l;
         return 1;
      }
      return 0;
   }
   int mid = (l + r) >> 1; pdown(u);
   bool up = 0;
   if(pos <= mid) up = check(u << 1, l, mid, pos, v);
   else up = check(u << 1 | 1, mid + 1, r, pos, v);
   if(up) upd(u);
   return up;
}
ll query(int u, int l, int r, int ql, int qr, int k) {
   if(l == ql && r == qr) return val[k][u];
   int mid = (l + r) >> 1; pdown(u);
   if(qr <= mid) return query(u << 1, l, mid, ql, qr, k);
   if(ql > mid) return query(u << 1 | 1, mid + 1, r, ql, qr, k);
   return min(query(u << 1, l, mid, ql, mid, k), query(u << 1 | 1, mid + 1, r, mid + 1, qr, k));
}
int main() {
   scanf("%d%d%d%d", &n, &t, &a, &b);
   for(int i = 1; i <= t; i ++) {
      scanf("%d", x + i);
      if(x[i] == x[i - 1]) {
         i --; t --;
      }
   }
   x[0] = a; build(1, 1, n);
   for(int i = 1; i <= t; i ++) {
      ll tmp = query(1, 1, n, x[i], n, 2) - x[i];
      if(x[i] > 1) tmp = min(tmp, query(1, 1, n, 1, x[i] - 1, 1) + x[i]);
      addtag(1, abs(x[i] - x[i - 1]));
      check(1, 1, n, x[i - 1], tmp);
   }
   printf("%lld\n", val[0][1]);
   return 0;
}