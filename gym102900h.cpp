#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n, k, a[N], b[N], u[N], v[N];
ll solve(int x) {
  rep(i, 0, k - 1) u[i] = (a[i] + n - x) % n;
  rep(i, 0, k - 1) v[i] = (b[i] + n - x) % n;
  sort(u, u + k); sort(v, v + k);
  int a1 = 0, a2 = 0;
  rep(i, 0, k - 1) {
    if(u[i] < v[i]) {
      a1 = max(a1, v[i] - u[i]);
    } else {
      a2 = max(a2, u[i] - v[i]);
    }
  }
  return 2ll * min(a1, a2) + max(a1, a2);
}
int main() {
  int test;
  scanf("%d", &test);
  while(test --) {
    scanf("%d%d", &n, &k);
    rep(i, 0, k - 1) scanf("%d", a + i);
    rep(i, 0, k - 1) scanf("%d", b + i);
    // sort(a, a + k); sort(b, b + k);
    ll ans = n;
    rep(i, 0, k - 1) ans = min(ans, solve(a[i]));
    rep(i, 0, k - 1) ans = min(ans, solve(b[i]));
    printf("%lld\n", ans);
  }
  return 0;
}