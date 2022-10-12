#include <bits/stdc++.h>
#define fs first
#define sc second
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, m, r, k, a[N], b[N], c[N];
priority_queue< pair<ll, int> > pq;
int main() {
  scanf("%d%d%d%d", &n, &m, &r, &k);
  rep(i, 1, n) a[i] = min(i, n - r + 1) - max(1, i - r + 1) + 1;
  rep(i, 1, n) c[i] = m;
  rep(i, 1, m) b[i] = min(i, m - r + 1) - max(1, i - r + 1) + 1;
  sort(a + 1, a + n + 1);
  sort(b + 1, b + m + 1);
  rep(i, 1, n) pq.push(make_pair((ll)a[i] * b[m], i));
  double ans = 0;
  rep(i, 1, k) {
    ans += pq.top().fs;
    int x = pq.top().sc;
    if(--c[x] > 0) {
      pq.push(make_pair((ll)a[x] * b[c[x]], x));
    }
    pq.pop();
  }
  ans /= (n - r + 1) * (m - r + 1.0);
  printf("%.10f\n", ans);
  return 0;
}