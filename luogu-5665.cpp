#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 4e7 + 5;
int n, ty, a[N], b[N], p[N], q[N], ql, qr;
ll s[N];
void gen() {
   const int mod = (1 << 30) - 1;
   int x, y, z, m, p, l, r, la = 0;
   scanf("%d%d%d%d%d%d", &x, &y, &z, b + 1, b + 2, &m);
   rep(i, 3, n) b[i] = ((ll)x * b[i - 1] + (ll)y * b[i - 2] + z) & mod;
   rep(i, 1, m) {
      scanf("%d%d%d", &p, &l, &r);
      rep(j, la + 1, p) a[j] = b[j] % (r - l + 1) + l;
      la = p;
   }
}
void print(__int128 x) {
   if(x) {
      print(x / 10);
      putchar(x % 10 + '0');
   }
}
ll F(int n) { return s[n] - s[p[n]]; }
int main() {
   freopen("partition.in", "r", stdin);
   freopen("partition.out", "w", stdout);
   scanf("%d%d", &n, &ty);
   if(ty == 1) gen();
   else rep(i, 1, n) scanf("%d", a + i);
   q[qr ++] = 0;
   rep(i, 1, n) {
      s[i] = s[i - 1] + a[i];
      while(qr - ql > 1 && s[i] >= F(q[ql + 1]) + s[q[ql + 1]]) ql ++;
      p[i] = q[ql];
      while(qr - ql > 0 && F(q[qr - 1]) + s[q[qr - 1]] >= F(i) + s[i]) qr --;
      q[qr ++] = i;
   }
   __int128 ans = 0;
   for(int u = n; u; u = p[u]) ans += (__int128)F(u) * F(u);
   print(ans);
   return 0;
}

namespace qwq {
    void main() {
        static bool f[50010];
        sort(a + 1, a + n + 1); //排序
        for(int i = 1; i <= 25001; i ++) f[i] = 0; //一开始所有数不能被表示
        f[0] = 1; //0当然可以被表示
        int ans = 0;
        for(int i = 1; i <= n; i ++) {
            if(f[a[i]]) continue ; //a[i]已经被表示了，不要这个货币
            ++ ans;
            for(int j = a[i]; j <= lim; j ++) //更新背包
                f[j] |= f[j - a[i]];

            bool fail = 0;
            for(int j = i + 1; j <= n; j ++)
                if(!f[a[j]]) fail = 1, j = n;
            if(!fail) { //所有数都能表示了，直接退出
                printf("%d\n", ans);
                return ;
            }
        }
    }
}