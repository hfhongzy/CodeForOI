#include <algorithm>
#include <cstdio>
#include <vector>
#define fs first
#define sc second
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, mod = 1e9 + 7;
int n, m, x[N], y[N], l[N], r[N], p[N];
int rt, sum[N * 32], id, ls[N * 32], rs[N * 32];
void ins(int &u, int l, int r, int x, int y) {
   if(!u) u = ++ id;
   (sum[u] += y) %= mod;
   if(l == r) return ;
   int mid = (l + r) >> 1;
   if(x <= mid) ins(ls[u], l, mid, x, y);
   else ins(rs[u], mid + 1, r, x, y);
}
int qry(int u, int l, int r, int qr) {
   if(!u || l > qr) return 0;
   if(r <= qr) return sum[u];
   int mid = (l + r) >> 1;
   return (qry(ls[u], l, mid, qr) + qry(rs[u], mid + 1, r, qr)) % mod;
}
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, n) scanf("%d", x + i);
   rep(i, 1, m) scanf("%d", y + i);
   int j = 1; y[0] = 2e9;
   rep(i, 1, n) {
      while(j < m && y[j] < x[i]) j ++;
      if(y[j] > x[i] && y[j - 1] < x[i]) {
         l[i] = x[i] - y[j - 1];
         r[i] = y[j] - x[i];
      }
      p[i] = i;
   }
   sort(p + 1, p + n + 1, [&](int i, int j) {
      return l[i] < l[j] || (l[i] == l[j] && r[i] > r[j]);
   });
   int ans = 1;
   rep(i, 1, n) {
      int x = r[p[i]];
      if(!x || (r[p[i]] == r[p[i - 1]] && l[p[i]] == l[p[i - 1]])) continue ;
      int f = 1 + qry(rt, 1, 1e9, x - 1);
      ins(rt, 1, 1e9, x, f);
      (ans += f) %= mod;
   }
   printf("%d\n", ans);
   return 0;
}