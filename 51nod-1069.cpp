#include <bits/stdc++.h>
int n, a, z;
int main() {
  scanf("%d", &n);
  while(n --) scanf("%d", &a), z ^= a;
  puts(z ? "A" : "B");
  return 0;
}