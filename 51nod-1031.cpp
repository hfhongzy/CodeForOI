#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
const int N = 1010, mod = 1e9 + 7;
int n, f[N];
int main() {
   f[0] = f[1] = 1; scanf("%d", &n);
   rep(i, 2, n) f[i] = (f[i - 1] + f[i - 2]) % mod;
   printf("%d\n", f[n]);
   return 0;
}