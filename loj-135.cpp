#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1 << 11 | 4;
ll s1[N][N], s2[N][N], s3[N][N], s4[N][N];
int n, m;
void add(int x, int y, ll z) { //a[x, n][y, m] += z
   if(x == 0 || y == 0) return ;
   for(int i = x; i <= n; i += i & (-i)) {
      for(int j = y; j <= m; j += j & (-j)) {
         s1[i][j] += z;
         s2[i][j] += x * z;
         s3[i][j] += y * z;
         s4[i][j] += x * y * z;
      }
   }
}
ll qry(int x, int y) { //a[1, x][1, y]
   ll res1 = 0, res = 0;
   for(int i = x; i; i &= i - 1) {
      for(int j = y; j; j &= j - 1) {
         res += s1[i][j];
         res1 += - (y + 1) * s2[i][j] - (x + 1) * s3[i][j] + s4[i][j];
      }
   }
   return res * (x + 1) * (y + 1) + res1;
}
int main() {
   scanf("%d%d", &n, &m);
   int op, x1, y1, x2, y2; ll x;
   while(~ scanf("%d", &op)) {
      if(op == 1) {
         scanf("%d%d%d%d%lld", &x1, &y1, &x2, &y2, &x);
         add(x1, y1, x); add(x2 + 1, y1, -x); add(x1, y2 + 1, -x); add(x2 + 1, y2 + 1, x);
      }
      if(op == 2) {
         scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
         printf("%lld\n", qry(x2, y2) - qry(x1 - 1, y2) - qry(x2, y1 - 1) + qry(x1 - 1, y1 - 1));
      }
    }
    return 0;
}