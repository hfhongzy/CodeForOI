#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
#include <queue>
// #include "wiring.h"
#define fs first
#define sc second
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
const ll INF = 1e12;
struct edge {
   int ty; ll x, w, c;
   bool operator < (const edge &b) const {
      return x < b.x;
   }
};
priority_queue< pll, vector<pll>, greater<pll> > q[2];
ll min_total_length(vector<int> x, vector<int> y) {
   int n = (int) x.size(), m = (int) y.size();
   ll ans = (n + m) * INF;
   vector<edge> e;
   rep(i, 0, n - 1) {
      e.pb({0, x[i], -INF, 1});
      e.pb({0, x[i], 0, m - 1});
   }
   rep(i, 0, m - 1) {
      e.pb({1, y[i], -INF, 1});
      e.pb({1, y[i], 0, n - 1});
   }
   sort(e.begin(), e.end());
   q[0].push({1e18, 1e18}); q[1].push({1e18, 1e18});
   for(edge &x : e) {
      ll flow = 0;
      while(x.c && x.w + x.x + q[x.ty ^ 1].top().fs < 0) {
         pll t = q[x.ty ^ 1].top(); q[x.ty ^ 1].pop();
         ll f = min(t.sc, x.c);
         flow += f; t.sc -= f; x.c -= f;
         ans += f * (x.w + x.x + t.fs);
         q[x.ty].push({- (x.x + t.fs) - x.x, f});
         if(t.sc) q[x.ty ^ 1].push(t);
      }
      if(flow) q[x.ty ^ 1].push({- x.x - x.w, flow});
      if(x.c) q[x.ty].push({- x.x + x.w, x.c});
   }
   return ans;
}

int main() {
   int n, m;
   assert(2 == scanf("%d %d", &n, &m));

   vector<int> r(n), b(m);
   for(int i = 0; i < n; i++)
      assert(1 == scanf("%d", &r[i]));
   for(int i = 0; i < m; i++)
      assert(1 == scanf("%d", &b[i]));

   long long res = min_total_length(r, b);
   printf("%lld\n", res);

   return 0;
}
