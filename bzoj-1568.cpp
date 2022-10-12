#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int M = 5e4;
struct seg {
   int id;
   db k, b;
   db val(db x) { return k * x + b; }
} a[(M + 10) * 4];
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
db query(int u, int l, int r, int x) {
   if(l == r) return a[u].val(x);
   int mid = (l + r) >> 1;
   return max(a[u].val(x), x <= mid ? query(u << 1, l, mid, x) : query(u << 1 | 1, mid + 1, r, x));
}
int main() {
   scanf("%d", &q);
   char op[10];
   rep(Q, 1, q) {
      scanf("%s", op);
      if(*op == 'Q') {
         int x; scanf("%d", &x);
         printf("%lld\n", (long long) (query(1, 1, M, x) / 100.0));
      } else {
         db k, b; scanf("%lf%lf", &b, &k); b -= k;
         modify(1, 1, M, (seg) {1, k, b});
      }
   }
   return 0;
}