#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
double a[8], p = 1, s;
int main() {
  rep(i, 1, 7) scanf("%lf", a + i), s += a[i];
  if(s < 7) return puts("0.000"), 0;
  rep(i, 1, 7) p *= a[i] / (s - i + 1) * i;
  p *= s - 6;
  printf("%.3f\n", p);
  return 0;
}