#include "fun.h"
#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
// int hoursRequired(int, int);
// int attractionsBehind(int, int);
const int N = 1e5 + 10;
int t, d[N], sz[N], p[3];
vector<int> son, ans, v[3];
bool ok() {
  int x = v[0].size() - p[0], y = v[1].size() - p[1], z = v[2].size() - p[2];
  int w = max(x, max(y, z));
  return 2 * w - (x + y + z) >= 0;
}
int pop(int last) {
  int mp = -1;
  rep(i, 0, t - 1) if(i != last && p[i] < v[i].size()) {
    if(mp == -1 || d[ v[mp][p[mp]] ] < d[ v[i][p[i]] ] ) mp = i;
  }
  ans.pb(v[mp][p[mp]]); p[mp] ++; return mp;
}
vector<int> createFunTour(int n, int q) {
  int rt = 0;
  rep(i, 0, n - 1) {
    sz[i] = attractionsBehind(0, i);
    if(n - sz[i] <= n / 2 && sz[rt] > sz[i]) rt = i;
  }
  rep(i, 0, n - 1) if((d[i] = hoursRequired(rt, i)) == 1) son.pb(i);
  if(n == 2) return vector<int>{0, 1};
  t = son.size();
  // cerr << "t = " << t << endl;
  rep(i, 0, n - 1) if(i != rt) {
    bool tag = 0;
    rep(j, 0, t - 2) if(hoursRequired(i, son[j]) <= d[i]) { tag = 1; v[j].pb(i); break ; }
    if(!tag) v[t - 1].pb(i);
  }
  rep(i, 0, t - 1) sort(v[i].begin(), v[i].end(), [&](int x, int y) {
    return d[x] > d[y] || (d[x] == d[y] && x < y);
  });
  int z = -1;
  if(t == 3) {
    while(!ok()) z = pop(z);
    int id = ~z && p[z] < v[z].size() ? v[z][p[z]] : -1;
    rep(i, 0, 2) v[i].erase(v[i].begin(), v[i].begin() + p[i]);
    sort(v, v + 3, [&](auto x, auto y) { return x.size() > y.size(); });
    vector<int> v2(v[1].size() + v[2].size());
    merge(v[1].begin(), v[1].end(), v[2].begin(), v[2].end(), v2.begin(), [&](int x, int y) {
      return d[x] > d[y] || (d[x] == d[y] && x < y);
    });
    v[1] = v2; p[1] = p[0] = 0; t --;
    if(~ id) {
      z = 1;
      for(int u : v[0]) if(id == u) { z = 0; break ; }
      if(v[z][0] != id) z = -1;
    } else {
      z = v[1].size() > v[0].size() ? 0 : (v[1].size() < v[0].size() ? 1 : -1);
    }
  } else {
    z = v[1].size() > v[0].size() ? 0 : (v[1].size() < v[0].size() ? 1 : -1);
  }
  while(ans.size() < n - 1) z = pop(z);
  ans.pb(rt);
  return ans;
}