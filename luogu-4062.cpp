#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
int n, a[N], cnt[N * 2], num[N];
bool use[N];
ll ans;
void solve(int l, int r) {
   if(l == r) { ans ++; return ; }
   int mid = (l + r) >> 1;
   solve(l, mid); solve(mid + 1, r);
   *num = 0;
   rep(i, l, r) use[a[i]] = 0;
   per(i, mid, l) {
      if(++ cnt[a[i]] > (mid - i + 1) / 2 && !use[a[i]]) {
         use[a[i]] = 1; num[++ *num] = a[i];
      }
   }
   rep(i, l, mid) cnt[a[i]] = 0;
   rep(i, mid + 1, r) {
      if(++ cnt[a[i]] > (i - mid) / 2 && !use[a[i]]) {
         use[a[i]] = 1; num[++ *num] = a[i];
      }
   }
   rep(i, mid + 1, r) cnt[a[i]] = 0;
   rep(k, 1, *num) {
      int x = num[k], c = 0, up = 0, dn = N;
      per(i, mid, l) {
         if(x == a[i]) c ++;
         int t = i + 2 * c;
         cnt[t] ++; up = max(up, t); dn = min(dn, t);
      }
      per(i, up - 1, dn) cnt[i] += cnt[i + 1];
      c = 0;
      rep(i, mid + 1, r) {
         if(x == a[i]) c ++;
         int lw = max(dn, i + 1 - 2 * c + 1);
         if(lw <= up) {
            ans += cnt[lw];
         }
      }
      rep(i, dn, up) cnt[i] = 0;
   }
}
int main() {
   scanf("%d%*d", &n);
   rep(i, 1, n) scanf("%d", a + i), a[i] ++;
   solve(1, n);
   printf("%lld\n", ans);
   return 0;
}