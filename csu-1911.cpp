#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 1 << 18 | 5;
int n, m;
ll a[N], b[N];
int bin() {
   static char s[25];
   scanf("%s", s + 1); int x = 0;
   for(int i = 1; s[i]; i ++) 
      x = (x << 1) + s[i] - '0';
   return x;
}
void fwtor(ll *a) {
   for(int i = 1; i < m; i <<= 1)
      for(int j = 0; j < m; j += i << 1)
         for(int k = 0; k < i; k ++)
            a[j + k + i] += a[j + k];
}
void Ifwtor(ll *a) {
   for(int i = 1; i < m; i <<= 1)
      for(int j = 0; j < m; j += i << 1)
         for(int k = 0; k < i; k ++)
            a[j + k + i] -= a[j + k];
}
int main() {
   int p, n, test, t = 0; scanf("%d", &test);
   while(test --) {
      scanf("%d%d", &p, &n); m = 1 << n;
      for(int i = 0; i < m; i ++) a[i] = b[i] = 0;
      for(int i = 0; i < p; i ++) {
         a[bin()] ++;
      }
      for(int i = 0; i < p; i ++) {
         b[bin()] ++;
      }
      fwtor(a); fwtor(b);
      for(int i = 0; i < m; i ++) a[i] *= b[i];
      Ifwtor(a);
      printf("Case #%d:\n", ++ t);
      int q; scanf("%d", &q);
      while(q --) {
         printf("%lld\n", a[bin()]);
      }
   }
   return 0;
}