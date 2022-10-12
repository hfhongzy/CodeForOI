#include <bits/stdc++.h>
#define pb push_back
#define debug(...) fprintf(stderr, __VA_ARGS__);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5e6 + 10;
const int S = 16777226;
struct node {
  int x, y;
};
int read(int n) {
  int z = 0, id = 0;
  rep(i, 1, n + 1) rep(j, 1, n) { int x; scanf("%d", &x); z |= x << id; id ++; }
  rep(i, 1, n) rep(j, 1, n + 1) { int x; scanf("%d", &x); z |= x << id; id ++; }
  return z;
}
node op[S];
int pre[S];
bool vis[S];
int n;
int work(int st, int x, int y, int z, int w) { //up right down left
  //x = w, y = x, z = y, w = z
  int t = st;
  if((t >> x & 1) != (st >> w & 1)) t ^= 1 << x;
  if((t >> y & 1) != (st >> x & 1)) t ^= 1 << y;
  if((t >> z & 1) != (st >> y & 1)) t ^= 1 << z;
  if((t >> w & 1) != (st >> z & 1)) t ^= 1 << w;
  // assert(__builtin_popcount(t) == __builtin_popcount(st));
  return t;
}
int main() {
  scanf("%d", &n);
  if(n > 3) {
    puts("NO"); return 0;
  }
  vector<node> ans;
  int a = read(n), b = read(n);
  // printf("%d -> %d\n", a, b);
  queue<int> q; q.push(a); vis[a] = 1;
  while(q.size()) {
    int u = q.front(); q.pop();
    // assert(u < S);
    if(u == b) {
      puts("YES");
      while(u != a) ans.pb(op[u]), u = pre[u];
      reverse(ans.begin(), ans.end());
      printf("%d\n", (int)ans.size());
      for(auto x : ans) printf("%d %d 0\n", x.x, x.y);
      return 0;
    }
    rep(x, 1, n) rep(y, 1, n) {
      int up = (x - 1) * n + y - 1;
      int left = n * (n + 1) + (x - 1) * (n + 1) + y - 1;
      // printf("x,y = %d,%d, up right down left=%d %d %d %d\n", x, y, 1+up, 1+left + 1, 1+up + n, 1+left);
      // if(x == n && y == n) return 0;
      int v = work(u, up, left + 1, up + n, left);
      if(!vis[v]) {
        vis[v] = 1; q.push(v); pre[v] = u; op[v] = node{x, y};
      }
    }
  }
  // int c = 0;
  // for(int i = 0; i < S; i ++) if(vis[i]) c ++;
  // cerr << "c = " << c << endl;
  // puts("NO");
  return 0;
}
/*
3
0 1 0
1 0 0
1 1 1
0 0 0
0 0 0 0
0 0 0 1
1 1 0 1
1 1 1
1 1 0
1 0 0
1 0 0
0 0 0 0
0 0 0 0
0 0 1 1
*/