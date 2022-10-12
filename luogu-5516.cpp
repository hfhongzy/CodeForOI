#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using db = double;
const int N = 2048;
int n = 26, m, a[N];
char s[N];
db f[N];
int main() {
  scanf("%s", s + 1);
  int t = strlen(s + 1);
  rep(i, 1, t) a[s[i] - 'A' + 1] ++;
  rep(i, 1, n) m = max(m, a[i]);
  rep(i, 1, m)
    f[i] = f[i - 1] - (t - 1.0) / (t - i + 1);
  rep(i, 2, m) f[i] += f[i - 1];
  db ans = 0;
  rep(i, 1, n) ans += f[a[i]];
  ans += t * (t - 1);
  printf("%.1f\n", ans);
  return 0;
}