#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 605;
int n, D1, D2, c[2][N][N], cnt[2][2];
void solve(int c[N][N], int d) {
  int k = 0;
  while(d % 4 == 0) d /= 4, ++ k;
  if(d % 4 == 3) return ;
  rep(i, 0, n - 1) rep(j, 0, n - 1)
    c[i][j] = d % 4 == 1 ? (i >> k & 1) ^ (j >> k & 1) : (i >> k & 1);
}
int main() {
  cin >> n >> D1 >> D2;
  int m = n * n;
  n *= 2;
  solve(c[0], D1); solve(c[1], D2);
  rep(i, 0, n - 1) rep(j, 0, n - 1)
    ++cnt[c[0][i][j]][c[1][i][j]];
  rep(i, 0, 1) rep(j, 0, 1)
    if(cnt[i][j] >= m) {
      int w = 0;
      rep(x, 0, n - 1) rep(y, 0, n - 1)
        if(c[0][x][y] == i && c[1][x][y] == j && w < m)
          ++w, printf("%d %d\n", x, y);   
      return 0;
    }
  return 0;
}