#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 2e7 + 10;
char a[N], b[N];
int z[N], p[N], n, m;
ll ans1, ans2;
int main() {
   scanf("%s%s", a + 1, b + 1);
   n = strlen(a + 1); m = strlen(b + 1);
   z[1] = m;
   for(int i = 2, l = 0, r = 0; i <= m; i ++) {
      z[i] = i <= r ? min(z[i - l + 1], r - i + 1) : 0;
      while(i + z[i] <= m && b[i + z[i]] == b[z[i] + 1]) z[i] ++;
      if(i + z[i] - 1 > r) { l = i; r = i + z[i] - 1; }
   }
   for(int i = 1; i <= m; i ++) ans1 ^= i * (z[i] + 1ll);

   for(int i = 1, l = 0, r = 0; i <= n; i ++) {
      p[i] = i <= r ? min(z[i - l + 1], r - i + 1) : 0;
      while(i + p[i] <= n && a[i + p[i]] == b[p[i] + 1]) p[i] ++;
      if(i + p[i] - 1 > r) { l = i; r = i + p[i] - 1; }
   }
   for(int i = 1; i <= n; i ++) ans2 ^= i * (p[i] + 1ll);
   printf("%lld\n%lld\n", ans1, ans2);
   return 0;
}