#include <bits/stdc++.h>
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 5050;
int n, m, k, p[N], lp[N];
vector<int> G[N];
bool use[N];
bool match(int u) {
  for(int v : G[u]) if(!use[v]) {
    use[v] = 1;
    if(!p[v] || match(p[v])) {
      p[v] = u; lp[u] = v; return 1;
    }
  }
  return 0;
}
int solve() {
  int ans = 0;
  rep(i, 1, n) {
    fill(use + 1, use + m + 1, 0);
    if(match(i)) ans ++;
  }
  return ans;
}
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t; cin >> t >> k;
  vector<string> ps(t), ss(t), pre(t), suf(t);
  vector<int> u(t), v(t);
  string s;
  rep(i, 0, t - 1) {
    cin >> s;
    ps[i] = pre[i] = s.substr(0, k);
    ss[i] = suf[i] = s.substr(s.size() - k, k);
  }
  sort(ps.begin(), ps.end());
  sort(ss.begin(), ss.end());
  auto ps_end = unique(ps.begin(), ps.end());
  auto ss_end = unique(ss.begin(), ss.end());
  n = ps_end - ps.begin(); m = ss_end - ss.begin();
  rep(i, 0, t - 1) {
    u[i] = lower_bound(ps.begin(), ps_end, pre[i]) - ps.begin() + 1;
    v[i] = lower_bound(ss.begin(), ss_end, suf[i]) - ss.begin() + 1;
    G[u[i]].pb(v[i]);
  }
  cout << solve() << endl;
  queue<int> q;
  vector<bool> L(n + 1, 1), R(m + 1);
  rep(i, 1, n) if(!lp[i]) q.push(i), L[i] = 0;
  while(q.size()) {
    int u = q.front(); q.pop();
    for(int v : G[u]) {
      R[v] = 1;
      if(p[v] && L[p[v]]) {
        L[p[v]] = 0; q.push(p[v]);
      }
    }
  }
  vector<vector<int>> gl(n + 1), gr(m + 1);
  rep(i, 0, t - 1) {
    if(L[u[i]]) {
      gl[u[i]].pb(i + 1);
    } else {
      gr[v[i]].pb(i + 1);
    }
  }
  rep(i, 1, n) if(gl[i].size()) {
    cout << gl[i].size();
    for(int v : gl[i]) {
      cout << ' ' << v;
    }
    cout << endl;
  }
  rep(i, 1, m) if(gr[i].size()) {
    cout << gr[i].size();
    for(int v : gr[i]) {
      cout << ' ' << v;
    }
    cout << endl;
  }
  return 0;
}