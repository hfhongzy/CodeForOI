#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
struct flow {
  int id, w;
  bool operator < (const flow &b) const {
    return w < b.w;
  }
};
int n, m, k, L, a[N], s[N], c[N], x[N], q[N];
int use[N], d[N], st[N];
ll ans[N];
vector<int> v[N];
priority_queue<flow> pq;
vector<flow> tq;
vector<pair<int, int>> flows;
int main() {
  scanf("%d%d%d", &n, &m, &k);
  rep(i, 1, n) scanf("%d%d%d%d", a + i, s + i, c + i, x + i);
  rep(i, 1, k) scanf("%d", q + i), L = max(L, q[i]);
  rep(i, 1, n) {
    d[i] = x[i] ? min(L, (c[i] + x[i] - 1) / x[i]) : L;
    v[d[i]].pb(i);
    st[i] = c[i] - (d[i] - 1) * x[i];
  }
  ll cur = 0;
  int mf = 0;
  per(i, L, 1) {
    tq.clear();
    for(int u : v[i]) pq.push({u, a[u] + s[u]});
    int flow = 0;
    while(pq.size() && flow < m) {
      int u = pq.top().id; pq.pop();
      if(!use[u]) {
        cur += a[u] + s[u];
        pq.push({u, a[u]});
        use[u] = 1;
        flows.pb(mp(1, a[u] + s[u]));
        flow ++;
      } else {
        int tmp = st[u] - use[u] + x[u] * (d[u] - i);
        if(tmp) {
          tmp = min(tmp, m - flow);
          cur += (ll)a[u] * tmp;
          flow += tmp;
          use[u] += tmp;
          flows.pb(mp(tmp, a[u]));
        }
        if(x[u] || st[u] > use[u]) tq.pb({u, a[u]});
      }
    }
    mf += flow;
    for(auto u : tq) pq.push(u);
  }
  sort(flows.begin(), flows.end(), [&](pair<int, int> a, pair<int, int> b) {
    return a.sc < b.sc;
  });
  ans[L] = cur;
  int pos = 0;
  per(i, L - 1, 1) {
    while(mf > i * m) {
      int t = min(flows[pos].fs, mf - i * m);
      flows[pos].fs -= t;
      cur -= (ll)flows[pos].sc * t;
      mf -= t;
      if(!flows[pos].fs) ++ pos;
    }
    ans[i] = cur;
  }
  rep(i, 1, k) printf("%lld\n", ans[q[i]]);
  return 0;
}