#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 1e4 + 10;
int test, n, a[N];
int main() {
  scanf("%d", &test);
  rep(T, 1, test) {
    scanf("%d", &n);
    int x = 0;
    rep(i, 1, n) {
      scanf("%d", a + i);
      if(i % 6 == 0 || i % 6 == 2 || i % 6 == 5) x ^= a[i];
    }
    printf("Case %d: %s\n", T, x ? "Alice" : "Bob");
  }
  return 0;
}