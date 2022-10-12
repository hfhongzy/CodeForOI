#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long double db;
const int N = 1e6 + 10;
int n;
db ans, pd[N], s[N];
void solve(int l, int r, int ql, int qr) {
   if(l > r) return ;
   int mid = (l + r) >> 1, g = 0;
   db cur = 0;
   rep(i, ql, min(mid - 1, qr)) {
      db c = (s[mid] - s[i]) * pd[mid] / pd[i];
      if(cur < c) { cur = c; g = i; }
   }
   ans = max(ans, cur);
   // cout << "mid = " << mid << ' ' << cur << endl;
   solve(l, mid - 1, ql, g);
   solve(mid + 1, r, g, qr);
}
int main() {
   scanf("%d", &n);
   pd[0] = 1;
   rep(i, 1, n) {
      int w; scanf("%d", &w);
      db p = w / 1e6;
      s[i] = s[i - 1] + p / (1.0 - p);
      pd[i] = pd[i - 1] * (1.0 - p);
   }
   solve(1, n, 0, n - 1);
   int res = int(ans * 1e6);
   printf("%d\n", res);
   return 0;
}
