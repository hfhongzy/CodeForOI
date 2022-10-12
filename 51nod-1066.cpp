#include <bits/stdc++.h>
int main() {
  int test; scanf("%d", &test);
  while(test --) {
    int n, k;
    scanf("%d%d", &n, &k);
    puts(n % (k + 1) != 0 ? "A" : "B");
  }
  return 0;
}