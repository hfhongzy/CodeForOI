#include <bits/stdc++.h>
int n, k, a;
int main() {
  scanf("%d%d", &n, &k); a = (n - k) >> 1;
  for(int i = 1, r = a + 1; i <= n; i ++, r = r == 1 ? a + 1 : r - 1)
    putchar('0' + (r == 1));
  return 0;
}