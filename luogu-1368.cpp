#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 3e5 + 10;
int n, str[N];
int main() {
   scanf("%d", &n);
   for(int i = 0; i < n; i ++) scanf("%d", str + i);
   int p1 = 0, p2 = 1, k = 0;
   while(p1 < n && p2 < n && k < n) {
      if(str[(p1 + k) % n] == str[(p2 + k) % n]) k ++;
      else {
         if(str[(p1 + k) % n] > str[(p2 + k) % n]) p1 += k + 1;
         else p2 += k + 1;
         k = 0;
         if(p1 == p2) p2 ++;
      }
   }
   for(int i = min(p1, p2); i < n; i ++) printf("%d ", str[i]);
   for(int i = 0; i < min(p1, p2); i ++) printf("%d ", str[i]);
   putchar('\n');
   return 0;
}