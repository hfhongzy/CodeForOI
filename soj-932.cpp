#include <bits/stdc++.h>
#define LOG(FMT...) fprintf(stderr, FMT)
#define pb push_back
#define fs first
#define sc second
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
int test, n, k, a[N], s[N];
bool mark[N], tag[N];
pair<int, int> kmp(int num) {
  static int f[128];
  f[1] = 0; tag[1] = 0;
  for(int i = 2; i <= n; i ++) {
    int j = f[i - 1];
    tag[i] = 0;
    for(; j && s[j + 1] != s[i]; j = f[j]) ;
    f[i] = s[j + 1] == s[i] ? j + 1 : 0;
  }
  int c = 0;
  for(int u = f[n]; u >= 1; u = f[u]) tag[u] = 1, c ++;
  for(int i = 1; i <= n; i ++) if(!tag[i] && mark[i]) return make_pair(2e9, 2e9);
  return make_pair(c, num);
}
int main() {
  scanf("%d", &test);
  while(test --) {
    scanf("%d%d", &n, &k);
    fill(mark + 1, mark + n + 1, 0);
    rep(i, 1, k) scanf("%d", a + i), mark[a[i]] = 1;
    if(k == 0) {
      if(n == 1) puts("a");
      else {
        rep(i, 1, n - 1) putchar('a');
        putchar('b');
        putchar('\n');
      }
      continue ;
    }
    pair<int, int> res(2e9, 2e9);
    for(int i = 0; i < (1 << n); i ++) {
      for(int j = 0; j < n; j ++) s[n - j] = i >> j & 1;
      res = min(res, kmp(i));
    }
    for(int j = n - 1; ~j; j --) putchar('a' + (res.sc >> j & 1));
    putchar('\n');
  }
  return 0;
}