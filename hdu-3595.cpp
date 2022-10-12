#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1024;
bool vis[N][N];
int st[N][N];
void solve(int a, int b) {
  if(vis[a][b]) return ;
  vis[a][b] = 1;
  if(!a || !b) { st[a][b] = 0; return ; }
  int k = b / a;
  if(k == 1) {
    solve(b - a, a);
    st[a][b] = st[b - a][a] + 1;
    return ;
  }
  int x = b - k * a, y = a;
  if(x > y) swap(x, y);
  solve(x, y);
  if(!(st[x][y] & 1)) {
    st[a][b] = st[x][y] + 1;
  } else {
    x = b - (k - 1) * a; y = a;
    if(x > y) swap(x, y);
    solve(x, y);
    st[a][b] = st[x][y] + 1;
  }
}
int main() {
  int n, a, b;
  while(~ scanf("%d", &n)) {
    int mx = 0;
    rep(i, 1, n) {
      scanf("%d%d", &a, &b);
      if(a > b) swap(a, b);
      solve(a, b);
      mx = max(mx, st[a][b]);
    }
    puts(mx & 1 ? "MM" : "GG");
  }
  return 0;
}