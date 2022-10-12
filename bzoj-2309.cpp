#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
struct node { int l, r; } a[N];
int n;
ll ans;
void solve(int l, int r, int ql, int qr) {
   if(l > r) return ;
   int mid = (l + r) >> 1, g = 0;
   ll cur = -(1ll << 60);
   rep(i, ql, min(mid - 1, qr)) {
      ll c = (a[mid].r - a[i].l) * ll(a[i].r - a[mid].l);
      if(cur < c) {
         cur = c; g = i;
      }
   }
   ans = max(ans, cur);
   solve(l, mid - 1, ql, g);
   solve(mid + 1, r, g, qr);
}
int main() {
   scanf("%d", &n);
   rep(i, 1, n) scanf("%d%d", &a[i].l, &a[i].r);
   sort(a + 1, a + n + 1, [&](node x, node y) { return x.r < y.r; });
   int m = 0;
   rep(i, 1, n) {
      while(m && a[i].l <= a[m].l) {
         ans = max(ans, (a[m].r - a[m].l) * ll(a[i].r - a[i].l));
         m --;
      }
      a[++ m] = a[i];
   }
   // cerr << "m = " << m << endl;
   if(m > 1) solve(2, m, 1, m - 1);
   printf("%lld\n", ans);
   return 0;
}
