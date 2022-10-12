#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
const ll INF = 1e17;
int a[N], n, k, cnt[N], L = 1, R = 0;
ll g[N], f[N], cur;
void query(int l, int r) {
   while(L > l) cur += cnt[a[-- L]] ++;
   while(R < r) cur += cnt[a[++ R]] ++;
   while(L < l) cur -= -- cnt[a[L ++]];
   while(R > r) cur -= -- cnt[a[R --]];
}
void solve(int l, int r, int ql, int qr) {
   if(l > r) return ;
   int qm = 0, mid = (l + r) >> 1; f[mid] = INF;
   for(int i = ql; i <= min(mid - 1, qr); i ++) {
      query(i + 1, mid);
      ll c = g[i] + cur;
      if(c < f[mid]) { f[mid] = c; qm = i; }
   }
   solve(l, mid - 1, ql, qm); solve(mid + 1, r, qm, qr);
}
int main() {
   scanf("%d%d", &n, &k);
   for(int i = 1; i <= n; i ++) scanf("%d", a + i);
   g[0] = 0; fill(g + 1, g + n + 1, INF);
   for(int i = 1; i <= k; i ++) {
      f[0] = INF; solve(1, n, 0, n - 1);
      copy(f, f + n + 1, g);
   }
   printf("%lld\n", g[n]);
   return 0;   
}