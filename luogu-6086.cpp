#include <algorithm>
#include <cstdio>
using namespace std;

#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
template<typename T> void chkmax(T &x, const T &y) { if(x < y) x = y; }
template<typename T> void chkmin(T &x, const T &y) { if(x > y) x = y; }
typedef long long ll;
const int N = 5e6 + 10;
int n, ty, f[N], d[N], p[N];
void code() {
   rep(i, 1, n - 1) {
      scanf("%d", f + i); d[f[i]] ++;
   }
   int j = 1;
   rep(i, 1, n - 2) {
      while(d[j]) j ++;
      p[i] = f[j];
      while(! -- d[p[i]] && p[i] < j) p[i + 1] = f[p[i]], i ++;
   }
   ll ans = 0;
   rep(i, 1, n - 2) ans ^= 1ll * i * p[i];
   printf("%lld\n", ans);
}
void decode() {

}
int main() {
   scanf("%d%d", &n, &ty);
   if(ty == 1) code(); else decode();
   return 0;
}