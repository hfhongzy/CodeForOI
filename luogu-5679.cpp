#include <algorithm>
#include <iostream>
#include <bitset>
#include <cstdio>
using namespace std;
const int N = 2e4 + 5;
int n, a[N], cnt[N];
bitset<20003> L, R;
int main() {
   int t; scanf("%d", &t);
   while(t --) {
      scanf("%d", &n);
      for(int i = 1; i <= n; i ++) scanf("%d", a + i);
      L.reset(); R.reset(); bool ans = 0;
      for(int i = 1; i <= n; i ++) cnt[a[i]] = 0;
      for(int i = 1; i <= n; i ++) cnt[a[i]] ++, R[a[i]] = 1;
      for(int i = 1; i <= n; i ++) {
         if(1 == cnt[a[i]] --) R[a[i]] = 0;
         if(2 * a[i] < 20000) {
            if(((L >> (20000 - 2 * a[i])) & R).count()) {
               ans = 1; break ;
            }
         } else {
            if(((L << (2 * a[i] - 20000)) & R).count()) {
               ans = 1; break ;
            }
         }
         L[20000 - a[i]] = 1;
      }
      puts(ans ? "YES" : "NO");
   }
   return 0;
}