#include <bits/stdc++.h>
int main() {
  int test, n, m;
  scanf("%d", &test);
  while(test --) {
    scanf("%d%d", &n, &m);
    int c = n - (n + m - 1) / m;
    puts(c & 1 ? "0" : "1");
  }
  return 0;
}