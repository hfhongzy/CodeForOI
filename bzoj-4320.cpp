#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int B = 1 << 9;
const int N = 3e5;
const int INF = 1e9;
int n, ans[B + 5], osuf[(N >> 9) + 5], isuf[N + 5];
//[id * B, (id + 1) * B)
int qmin(int x) { return min(isuf[x], osuf[x >> 9]); }
int main() {
  scanf("%d", &n);
  char op[5];
  int x;
  fill(ans, ans + B + 1, B);
  fill(osuf, osuf + (N >> 9) + 1, INF);
  fill(isuf, isuf + N + 1, INF);
  rep(T, 1, n) {
    scanf("%s%d", op, &x);
    if(*op == 'A') {
      rep(i, 1, B) ans[i] = min(ans[i], x % i);
      int id = x >> 9;
      per(i, id - 1, 0) osuf[i] = min(osuf[i], x);
      rep(i, (id << 9), x) isuf[i] = min(isuf[i], x);
    }
    if(*op == 'B') {
      if(x <= B) printf("%d\n", ans[x]);
      else {
        int res = INF;
        for(int i = 0; i <= N; i += x) {
          int q = qmin(i);
          if(q < i + x)
            res = min(res, q - i);
        }
        printf("%d\n", res);
      }
    }
  }
  return 0;
}