#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
typedef long long ll;
using namespace std;
const int N = 1e5 + 10, mod = 1e4;
int n, t, m, f[N], s[N], a[N];
int main() {
   scanf("%d%d", &n, &t);
   rep(T, 1, t) {
      scanf("%d", &m);
      rep(i, 1, m) scanf("%d", s + i), a[i] = 0;
      s[m + 1] = 0; f[1] = 0;
      rep(i, 2, m) {
         int j = f[i - 1];
         for(; j && s[j + 1] != s[i]; j = f[j]) ;
         f[i] = s[j + 1] == s[i] ? j + 1 : 0;
      }
      for(int i = m; i; i = f[i]) a[i] = 1;
      int pw = 1, ans = 0;
      rep(i, 1, m) {
         pw = pw * n % mod;
         if(a[i]) (ans += pw) >= mod ? ans -= mod : 0;
      }
      printf("%04d\n", ans);
   }
   return 0;
}