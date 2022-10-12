#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
#define uint dont_crash_please
using namespace std;
typedef long long ll;
typedef unsigned uint;
const int N = 2e6 + 10;
uint seed = chrono::system_clock::now().time_since_epoch().count();
mt19937 ran(seed);
int n, k, m;
char a[N], b[N];
uint val[N], sum[N];
ll w[N], c[N], L[N], R[N];
int main() {
   scanf("%d%d%d%s", &n, &k, &m, a + 1);
   rep(i, 1, n) a[i] &= 15;
   rep(i, 0, k - 1) val[i] = ran();
   rep(i, 1, n + 1) {
      L[i] = w[i % k];
      sum[i] = sum[i - 1];
      b[i] = a[i] ^ a[i - 1];
      c[i] = c[i - 1];
      if(b[i]) {
         sum[i] ^= val[i % k];
         ll t = w[i % k];
         w[i % k] = i - t;
         c[i] = c[i] + i - 2 * t;
      }
      R[i] = w[i % k];
   }
   int l, r;
   rep(i, 1, m) {
      scanf("%d%d", &l, &r);
      uint t = sum[r] ^ sum[l];
      if(a[l]) t ^= val[l % k];
      if(a[r]) t ^= val[(r + 1) % k];
      if(t) puts("-1");
      else {
         ll res = c[r] - c[l];
         if(a[l]) {
            res += 2 * R[l] - l;
         }
         if(a[r]) {
            res += - 2 * L[r + 1] + r + 1;
         }
         printf("%lld\n", res / k);
      }
   }
   return 0;
}