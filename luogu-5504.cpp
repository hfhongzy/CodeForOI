#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, a[N], d[N], cnt[N];
vector<int> st[N];
ll f[N];
ll F(int x, int len) {
   return f[x - 1] + (ll)a[x] * len * len;
}
int calc(int x, int y) { //x > y, y better time
   int l = d[y], r = cnt[a[x]], ans = r + 1;
   while(l <= r) {
      int mid = (l + r) >> 1;
      if(F(x, mid - d[x] + 1) <= F(y, mid - d[y] + 1)) {
         r = (ans = mid) - 1;
      } else {
         l = mid + 1;
      }
   }
   return ans;
}
int main() {
   scanf("%d", &n);
   rep(i, 1, n) {
      scanf("%d", a + i);
      d[i] = ++ cnt[a[i]];
   }
   #define STK(i) s[(int)s.size() + i]
   rep(i, 1, n) {
      auto &s = st[a[i]];
      while(s.size() >= 2 && calc(STK(-1), STK(-2)) <= calc(i, STK(-1))) {
         s.pop_back();
      }
      s.push_back(i);
      while(s.size() >= 2 && calc(STK(-1), STK(-2)) <= d[i]) {
         s.pop_back();
      }
      int j = STK(-1);
      f[i] = F(j, d[i] - d[j] + 1);
   }
   #undef STK
   printf("%lld\n", f[n]);
   return 0;
}
//f[i] = f[j - 1] + a[i] * (d[i] - d[j] + 1)^2, a[i] = a[j]