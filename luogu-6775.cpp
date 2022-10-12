#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 505;
const int B = 2500000;
struct node { int x, id; };
int n, m, k, d[N];
bitset<5000006> f[N];
void solve(vector<node> v, int m) {
  rep(T, 1, m) {
    int x = -1;
    rep(i, 0, int(v.size()) - 1)
      if(v[i].x > 0 && (!~x || v[x].x > v[i].x))
        x = i;
    if(v[x].x >= k) {
      printf("%d %d\n", v[x].id, k);
      v[x].x -= k;
    } else {
      int y = -1;
      rep(i, 0, int(v.size()) - 1)
        if(x != i && v[i].x > 0 && (!~y || v[y].x < v[i].x))
          y = i;
      printf("%d %d %d %d\n", v[x].id, v[x].x, v[y].id, k - v[x].x);
      v[y].x -= k - v[x].x;
      v[x].x = 0;
    }
  }
}
int main() {
  int test;
  scanf("%d", &test);
  f[0][B] = 1;
  rep(T, 1, test) {
    scanf("%d%d%d", &n, &m, &k);
    rep(i, 1, n) scanf("%d", d + i);
    if(m >= n - 1) {
      vector<node> v;
      rep(i, 1, n) v.pb({d[i], i});
      solve(v, m);
      continue ;
    }
    rep(i, 1, n) {
      int z = d[i] - k;
      f[i] = f[i - 1] | (z > 0 ? f[i - 1] << z : f[i - 1] >> (-z));
    }
    if(!f[n][B - k]) { puts("-1"); continue; }
    vector<node> v1, v2;
    for(int i = n, sz = B - k; i >= 1; i --) {
      if(f[i - 1][sz]) {
        v2.pb({d[i], i});
      } else {
        sz -= d[i] - k;
        v1.pb({d[i], i});
      }
    }
    solve(v1, int(v1.size()) - 1);
    solve(v2, int(v2.size()) - 1);
  }
  return 0;
}