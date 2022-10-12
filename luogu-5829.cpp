#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;
const int N = 1e6 + 10;
char s[N];
int n, q, fail[N];
int f[N][21], d[N], logn;
int lca(int u, int v) {
   if(d[u] < d[v]) swap(u, v);
   int c = d[u] - d[v];
   for(int i = logn - 1; ~ i; i --)
      if(c >> i & 1) u = f[u][i];
   if(u == v) return u;
   for(int i = logn - 1; ~ i; i --) if(f[u][i] ^ f[v][i]) 
      u = f[u][i], v = f[v][i];
   return f[u][0];
}

int main() {
   scanf("%s%d", s + 1, &q); n = strlen(s + 1);
   fail[1] = 0;
   for(int i = 2; i <= n; i ++) {
      int j = fail[i - 1];
      for(; j && s[j + 1] != s[i]; j = fail[j]) ;
      fail[i] = s[j + 1] == s[i] ? j + 1 : 0;
   }
   for(logn = 1; (1 << logn) <= n + 1; ++ logn) ;
   for(int i = 1; i <= n; i ++) d[i] = d[fail[i]] + 1;
   for(int j = 0; j < logn; j ++)
      for(int i = 1; i <= n; i ++)
         f[i][j] = j ? f[f[i][j - 1]][j - 1] : fail[i];
   for(int i = 1; i <= q; i ++) {
      int x, y;
      scanf("%d%d", &x, &y); x = lca(fail[x], fail[y]);
      printf("%d\n", x);
   }
   return 0;
}