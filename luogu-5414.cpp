#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 110;
int sum, ans, n, a[N], dp[N];
int main() {
   int t; scanf("%d", &t);
   while(t --) {
      scanf("%d", &n); sum = 0;
      for(int i = 1; i <= n; i ++) {
         scanf("%d", a + i); sum += a[i];
      }
      ans = a[1];
      for(int i = 1; i <= n; i ++) {
         dp[i] = a[i];
         for(int j = 1; j < i; j ++) if(a[j] <= a[i]) {
            dp[i] = max(dp[i], dp[j] + a[i]);
         }
         ans = max(ans, dp[i]);
      }
      printf("%d\n", - ans + sum);
   }
   return 0;
}