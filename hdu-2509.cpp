#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
int n, a, x;
int main() {
  while(~ scanf("%d", &n)) {
    bool e = 1; x = 0;
    rep(i, 1, n) {
      scanf("%d", &a);
      if(a > 1) e = 0;
      x ^= a;
    }
    if(e) puts(x ? "No" : "Yes");
    else puts(x ? "Yes" : "No");
  }
  return 0;
}