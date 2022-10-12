#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 5e6 + 10;
int a, b, c, d, e, f;
int main() {
   int t; scanf("%d", &t);
   while(t --) {
      scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f);
      if(a == 0) {
         puts((b == 0 && c > 0) || d == 0 ? "FON" : "MEI");
      } else if(c == 0) {
         puts(d == 0 ? "FON" : "MEI");
      } else if(e == 0) {
         puts(b && d && f ? "MEI" : "FON");
      } else {
         puts(b * d * f > a * c * e ? "MEI" : "FON");
      }
   }
   return 0;
}
