#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1.1e7 + 10;
int n, f[N * 2];
char s[N * 2], t[N];
int main() {
   scanf("%s", t + 1);
   int maxr = 0, mid = 0;
   n = strlen(t + 1);
   s[1] = '#';
   rep(i, 1, n) {
      s[i * 2] = t[i];
      s[i * 2 + 1] = '#';
   }
   n = n * 2 + 1;
   rep(i, 1, n) {
      f[i] = i < maxr ? min(maxr - i, f[2 * mid - i]) : 1;
      for(; i + f[i] <= n && i - f[i] >= 1 && s[i + f[i]] == s[i - f[i]]; f[i] ++) ;
      if(i + f[i] > maxr) { maxr = i + f[i]; mid = i; }
   }
   printf("%d\n", -1 + *max_element(f + 1, f + n + 1));
   return 0;
}