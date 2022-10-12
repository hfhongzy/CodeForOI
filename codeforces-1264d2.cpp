#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int N = 1e6 + 5;
int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
char s[N];
int n, c, inv[N], C[N], C2[N], A[N], B[N], D[N];
void init(int n, int *C) {
  if(n < 0) return ;
  C[0] = 1;
  rep(i, 1, n) C[i] = (ll)C[i - 1] * inv[i] % mod * (n - i + 1ll) % mod;
  rep(i, 1, n) C[i] = add(C[i - 1], C[i]);
}
int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  inv[1] = 1;
  rep(i, 2, n) inv[i] = (mod - mod / i) * (ll)inv[mod % i] % mod;
  per(i, n, 1) D[i] = D[i + 1] + (s[i] == '?');
  rep(i, 1, n) A[i] = A[i - 1] + (s[i - 1] == '(');
  per(i, n, 1) B[i] = B[i + 1] + (s[i + 1] == ')');
  c = D[1];
  init(c, C); init(c - 1, C2);
  int ans = 0;
  rep(i, 1, n) {
    if(s[i] == '(') {
      int t = B[i] + D[i] - A[i] - 1;
      if(t >= 0) ans = add(ans, C[min(c, t)]);
    }
    if(s[i] == '?') {
      int t = B[i] + D[i + 1] - A[i] - 1;
      if(t >= 0) ans = add(ans, C2[min(c - 1, t)]);
    }
  }
  printf("%d\n", ans);
  return 0;
}