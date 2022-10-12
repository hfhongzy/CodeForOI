#include <bits/stdc++.h>
using namespace std;
const int N = 2510;
char s[N], t[N];
int d[N], sum[N];
int main() {
   int T, n;
   scanf("%d", &T);
   while(T --) {
      scanf("%s%s", s + 1, t + 1);
      n = strlen(s + 1) + 1;
      for(int i = 1; i <= n; i ++)
         d[i] = ((s[i] - t[i] + 10) % 10 - (s[i - 1] - t[i - 1] + 10) % 10 + 10) % 10;
      sort(d + 1, d + n + 1);
      sum[n + 1] = 0;
      for(int i = n; i >= 1; i --) sum[i] = sum[i + 1] + 10 - d[i];
      int p = 0;
      for(int i = 0; i <= n; i ++) {
         p += d[i];
         if(p == sum[i + 1]) {
            printf("%d\n", p);
            break ;
         }
      }
   }
   return 0;
}