#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int M = 39989, M2 = 1e9;
struct Pair {
   db first; int second;
   bool operator < (const Pair &b) const {
      return fabs(first - b.first) < 1e-10 ? second > b.second : first < b.first;
   }
} t[M + 10];
struct seg {
   int id;
   db k, b;
   db val(db x) { return k * x + b; }
} a[(M + 10) << 2];
int q;
void modify(int u, int l, int r, seg x) {
   if(!a[u].id) { a[u] = x; return ; }
   int mid = (l + r) >> 1;
   db l1 = a[u].val(l), r1 = a[u].val(r), l2 = x.val(l), r2 = x.val(r);
   if(l1 >= l2 && r1 >= r2) return ;
   if(l2 >= l1 && r2 >= r1) { a[u] = x; return ; }
   db cr = (x.b - a[u].b) / (a[u].k - x.k);
   if(cr <= mid) {
      if(r1 >= r2) modify(u << 1, l, mid, x);
      else modify(u << 1, l, mid, a[u]), a[u] = x;
   } else {
      if(r1 <= r2) modify(u << 1 | 1, mid + 1, r, x);
      else modify(u << 1 | 1, mid + 1, r, a[u]), a[u] = x;
   }
}
void modify(int u, int l, int r, int ql, int qr, seg x) {
   if(l == ql && r == qr) { modify(u, l, r, x); return ; }
   int mid = (l + r) >> 1;
   if(qr <= mid) modify(u << 1, l, mid, ql, qr, x);
   else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, x);
   else {
      modify(u << 1, l, mid, ql, mid, x);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr, x);
   }
}
Pair query(int u, int l, int r, int x) {
   if(l == r) return (Pair) {a[u].val(x), a[u].id};
   int mid = (l + r) >> 1;
   return max((Pair) {a[u].val(x), a[u].id}, x <= mid ? query(u << 1, l, mid, x) : query(u << 1 | 1, mid + 1, r, x));
}
int main() {
   scanf("%d", &q);
   int op, k, x1, y1, x2, y2, lans = 0, cnt = 0;
   rep(Q, 1, q) {
      scanf("%d", &op);
      if(op == 0) {
         scanf("%d", &k);
         k = (k + lans - 1) % M + 1;
         printf("%d\n", lans = query(1, 1, M, k).second);
      } else {
         scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
         x1 = (x1 + lans - 1) % M + 1;
         x2 = (x2 + lans - 1) % M + 1;
         y1 = (y1 + lans - 1) % M2 + 1;
         y2 = (y2 + lans - 1) % M2 + 1;
         if(x1 > x2) { swap(x1, x2); swap(y1, y2); }
         if(x1 == x2) {
            t[x1] = max(t[x1], (Pair) {(db) max(y1, y2), ++ cnt});
            continue ;
         }
         db k = 1.0 * (y2 - y1) / (x2 - x1);
         db b = y2 - k * x2;
         modify(1, 1, M, x1, x2, (seg) {++ cnt, k, b});
      }
   }
   return 0;
}