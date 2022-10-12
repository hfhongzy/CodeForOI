#include <algorithm>
#include <cstring>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
const int N = 1e4 + 3;
char s[N];
int mod, n, f[N], t[N];
inline int upd(int x, int y) {
   return x + y >= mod ? x + y - mod : x + y;
}
int main() {
   scanf("%s%d", s + 1, &mod);
   n = strlen(s + 1);
   rep(i, 0, n) f[i] = 1;
   rep(i, 1, n) {
      copy(f, f + n + 1, t);
      rep(j, 1, n) if(s[i] == s[j]) {
         f[j] = upd(f[j], f[j - 1]);
      } else {
         f[j] = upd(f[j], upd(f[j - 1], mod - t[j - 1]));
      }
   }
   printf("%d\n", f[n]);
   return 0;
}