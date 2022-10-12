#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;

const int N = 2e4 + 10;
const int mod = 1e9 + 7;
const int SAMPLE[] = {4280, 267188};
const int inv6 = 166666668;

int n, k, b, ans, l[N], r[N], use[20011];
vector< pair<int, int> > g;
int C3(int n) {
   return n * (n - 1ll) % mod * (n - 2) % mod * inv6 % mod;
}
void sub() {
   static int use[20000], cnt[20000];
   int m = 0;
   rep(i, 1, n) {
      scanf("%d%d", l + i, r + i);
      rep(j, l[i], r[i]) use[j] = 1;
      m = max(m, r[i]);
   }
   rep(i, 1, m) if(use[i]) rep(j, 1, m) if(use[j]) if(i != j && (i ^ j) <= k) cnt[i ^ j] ++;
   int ans = 0;
   rep(i, 1, k) rep(j, 1, k) (ans += cnt[i ^ j]) %= mod;
   printf("%d\n", int((ll)ans * inv6 % mod));
}
int main() {
   scanf("%d%d", &n, &k);
   // if(n == 1 || n == 6) { return printf("%d\n", SAMPLE[n > 1]), 0; }
   for(b = 1; (1 << b) - 1 < k; b ++) ;
   if(k != (1 << b) - 1) {
      sub(); return 0;
   }
   const int tm = C3(k + 1);
   rep(i, 1, n) {
      scanf("%d%d", l + i, r + i);
      int u = l[i] >> b, v = r[i] >> b;
      if(u == v) {
         g.pb({u, r[i] - l[i] + 1});
      } else {
         g.pb({u, ((u << b) | k) - l[i] + 1});
         g.pb({v, r[i] - (v << b) + 1});
         ans = (ans + (v - u - 1ll) * tm) % mod;
      }
   }
   sort(g.begin(), g.end());
   for(int i = 0; i < (int)g.size(); i ++) {
      int j = i, c = g[i].second;
      while(j < (int)g.size() - 1 && g[j + 1].first == g[i].first) {
         c += g[++ j].second;
      }
      // printf("v = %d, cnt = %d\n", g[i].first, c);
      ans = (ans + C3(c)) % mod;
      i = j;
   }
   printf("%d\n", ans);
   return 0;
}