#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
int n, m, ans, w[20];
int main() { 
   scanf("%d%d", &n, &m);
   rep(i, 0, n - 1) {
      scanf("%d", w + i);
   }
   rep(i, 0, (1 << n) - 1) {
      ll sw = 0;
      rep(j, 0, n - 1) if(i >> j & 1) sw += w[j];
      if(sw < m) {
         bool tag = 1;
         rep(j, 0, n - 1) if(!(i >> j & 1) && sw + w[j] < m) {
            tag = 0; break ;
         }
         if(tag) ans ++;
      }
   }
   printf("%d\n", ans);
   return 0;
}

