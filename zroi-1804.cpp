#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 105;
int n, k, a[N][N];
namespace sub {
int p[N];
void main() {
  rep(i, 1, n) p[i] = i;
  do {
    bool mk = 1; int s = 0;
    rep(i, 1, n) {
      if(!~a[i][p[i]]) { mk = 0; break ; }
      s = (s + a[i][p[i]]) % k;
    }
    if(mk && !s) { puts("Yes"); return ; }
  } while(next_permutation(p + 1, p + n + 1));
  puts("No");
}
}

namespace sub2 {
int shift[20][1 << 20], dp[21][1 << 20], lg[1 << 20];
void main() {
  for(int i = 0; i < (1 << k); i ++)
    shift[0][i] = i;
  for(int i = 1; i < k; i ++) {
    for(int j = 0; j < (1 << k); j ++) {
      int u = j << 1;
      if(u >> k & 1) u ^= 1 | (1 << k);
      shift[i][j] = shift[i - 1][u];
      // printf("shift (t = %d) %d = %d\n", i, j, shift[i][j]);
    }
  }
  dp[0][0] = 1;
  for(int i = 0; i < n; i ++) lg[1 << i] = i;
  int U = (1 << n) - 1;
  for(int i = 1; i <= n; i ++) {
    for(int j = 0; j < (1 << n); j ++) if(dp[i - 1][j]) {
      for(int s = U ^ j; s; s &= s - 1) {
        int w = lg[s & (-s)];
        if(~a[i][w + 1]) {
          dp[i][j | (1 << w)] |= shift[a[i][w + 1]][dp[i - 1][j]];
        }
      }
    }
  }
  puts(dp[n][U] & 1 ? "Yes" : "No");
}
}
int main() {
  scanf("%d%d", &n, &k);
  rep(i, 1, n) rep(j, 1, n) scanf("%d", a[i] + j);
  // srand(time(0));
  // rep(i, 1, n) rep(j, 1, n) a[i][j] = rand() % k;
  if(n <= 10 && 0) {
    sub::main();
  } else if(n <= 20 && 0) {
    sub2::main();
  } else {
    static int p[N];
    rep(i, 1, n) p[i] = i;
    mt19937 mt(chrono::system_clock::now().time_since_epoch().count());
    int Lim = 1e6;
    rep(T, 1, Lim) {
      random_shuffle(p + 1, p + n + 1, [&](int x) {
        return mt() % x;
      });
      bool mk = 1; int s = 0;
      rep(i, 1, n) {
        if(!~a[i][p[i]]) { mk = 0; break ; }
        s = (s + a[i][p[i]]) % k;
      }
      if(mk && !s) { puts("Yes"); return 0; }
    }
    puts("No");
  }
  return 0;
}