#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2e5 + 10;
int n, q, k, t, pos, a[N], p[N], cntR[N], cntL[N], posR[N], posL[N], rk[N];
char s[N];
int jump(int mid) {
   int z = (mid + 1) / 2;
   if(s[p[k]] == 'L') {
      if(mid & 1) return cntR[k] - z + 1 <= 0 ? -1 : posR[ cntR[k] - z + 1 ];
      return cntL[k] + z > *posL ? -1 : posL[ cntL[k] + z ];
   }
   if(!(mid & 1)) return cntR[k] - z <= 0 ? -1 : posR[ cntR[k] - z ];
   return cntL[k] + z > *posL ? -1 : posL[ cntL[k] + z ];
}
bool check(int mid) {
   int x = jump(mid), y = jump(mid - 1);
   if(x == -1 || y == -1) return 0;
   if(abs(a[p[y]] - a[p[x]]) > t * 2) return 0;
   pos = x;
   return 1;
}
int main() {
   scanf("%d%d", &n, &q);
   rep(i, 1, n) {
      scanf("%d", a + i);
      p[i] = i;
   }
   scanf("%s", s + 1);
   sort(p + 1, p + n + 1, [&](int x, int y) {
      return a[x] < a[y];
   });
   rep(i, 1, n) {
      rk[p[i]] = i;
      cntL[i] = cntL[i - 1] + (s[p[i]] == 'L');
      cntR[i] = cntR[i - 1] + (s[p[i]] == 'R');
   }
   rep(i, 1, n)
      if(s[p[i]] == 'R') posR[++ *posR] = i;
      else posL[++ *posL] = i;
   
   rep(i, 1, q) {
      scanf("%d%d", &k, &t); k = rk[k];
      int l = 1, r = n - 1, mid, res = k;
      while(l <= r) {
         mid = (l + r) >> 1;
         if(check(mid)) {
            l = mid + 1;
            res = pos;
         } else {
            r = mid - 1;
         }
      }
      res = abs(s[p[res]] == 'L' ? a[p[res]] - t : a[p[res]] + t);
      printf("%d\n", res);
   }
   return 0;
}