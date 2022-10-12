#include <bits/stdc++.h>
const int N = 748550 + 10;
int n, k, l, a[N], b[N];
int main() {
  int test; scanf("%d", &test);
  for(int T = 1; T <= test; T ++) {
    scanf("%d%d", &n, &k);
    l = a[1] = b[1] = 1;
    int t = 0;
    while(b[l] < n) {
      a[l + 1] = b[l] + 1;
      while(a[l + 1] > 1ll * k * a[t + 1]) t ++;
      b[l + 1] = t ? b[t] + a[l + 1] : a[l + 1];
      l ++;
    }
    printf("Case %d: ", T);
    if(a[l] == n) {
      puts("lose");
      continue ;
    }
    int ans = 0;
    for(; l && n; l --) {
      if(n >= a[l]) {
        n -= a[l]; ans = a[l];
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}