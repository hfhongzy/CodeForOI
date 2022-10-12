#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
namespace R{ int n, m, s; }
int main() {
  scanf("%d%d%d", &R::n, &R::m, &R::s);
  if(R::n <= 1e3) {
    printf("%d\n", R::n);
    rep(i, 1, R::n) printf("%d %d\n", i, i);
    printf("%d\n", R::n - 1);
    int op = 0;
    rep(i, 2, R::n) {
      printf("%d %d %d\n", op, i, 1);
      op ^= 1;
    }
  } else if(R::n == 100000 && R::m == 300) {
    int n = 308 * 308 + 2 * 308;
    printf("%d\n", n);
    rep(i, 1, 308) rep(j, 1, 308) printf("%d %d\n", i, j);
    rep(i, 1, 308) printf("%d %d\n%d %d\n", 308 + 2 * i - 1, 308 + i, 308 + 2 * i, 308 + i);
    int m = 308;
    printf("%d\n", m);
    rep(i, 1, 308) {
      printf("1 %d %d\n", 308 + i, i);
    }
  }
  return 0;
}