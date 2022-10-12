#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
typedef long long ll;
const int N = 103;
struct mat {
   ll a[N][N], n, m;
   mat operator * (const mat &b) {
      mat ans; ans.n = n; ans.m = b.m;
      rep(i, 1, ans.n) rep(j, 1, ans.m) {
         ans.a[i][j] = 0;
         rep(k, 1, m) {
            ans.a[i][j] |= a[i][k] & b.a[k][j];
         }
      }
      return ans;
   }
} fir, tr;
mat Pow(mat a, int b) {
   mat ans = a; b --;
   for(; b >= 1; b >>= 1, a = a * a)
      if(b & 1) ans = ans * a;
   return ans;
}
int n, k;
ll a[N], b[N];
int main() {
   scanf("%d%d", &n, &k);
   rep(i, 0, k - 1) scanf("%lld", a + i);
   rep(i, 0, k - 1) scanf("%lld", b + i);
   if(n <= k - 1) {
      printf("%lld\n", a[n]);
      return 0;
   }
   fir.n = 1; fir.m = tr.n = tr.m = k;
   rep(i, 1, k) fir.a[1][i] = a[k - i];
   rep(i, 1, k) tr.a[i][1] = b[k - i];
   ll all = 0;
   rep(i, 0, 62) all |= 1ll << i;
   rep(i, 1, k - 1) tr.a[i][i + 1] = all;
   fir = fir * Pow(tr, n - (k - 1));
   printf("%lld\n", fir.a[1][1]);
   return 0;
}