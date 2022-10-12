#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 205;
int n, a, k;
int sg(int n) {
  if(n < k) return 0;
  int x = n / k;
  if(n % k == 0) return x;
  int t = (n - x * k) / (x + 1);
  return t ? sg(n - t * (x + 1)) : sg(n - x - 1);
}
int main() {
  scanf("%d", &n);
  int z = 0;
  rep(i, 1, n) {
    scanf("%d%d", &a, &k);
    z ^= sg(a);
  }
  puts(z ? "Takahashi" : "Aoki");
  return 0;
}