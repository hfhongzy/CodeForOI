#include <algorithm>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int H = 23333, N = 2e6 + 10, M = 105, mod = 20110520;
struct HashTable {
   int nxt[N], hd[H], cnt, fir[N], sec[N];
   void clr() { cnt = 0; fill(hd, hd + H, -1); }
   void insert(int u, int v) {
      int x = u % H;
      for(int i = hd[x]; ~ i; i = nxt[i])
         if(fir[i] == u) { (sec[i] += v) %= mod; return ; }
      cnt ++; fir[cnt] = u; sec[cnt] = v;
      nxt[cnt] = hd[x]; hd[x] = cnt;
   }
} h[2];
int n, m, ex, ey, ans;
char tmp[M][M], str[M][M], mp[M][M];
inline int bit(int st, int y) { //注意y的范围是[0, m]
   return st >> (2 * y) & 3;
}
inline int mdf(int st, int y, int z) { //st的y位改为z
   return st ^ ( (bit(st, y) ^ z) << (2 * y) );
}
int main() {
   scanf("%d%d", &n, &m);
   rep(i, 1, n) scanf("%s", tmp[i] + 1);
   if(m <= n) {
      rep(i, 1, n) rep(j, 1, m) str[i][j] = tmp[i][j];
   } else {
      rep(i, 1, n) rep(j, 1, m) str[j][i] = tmp[i][j];
      swap(n, m);
   }
   rep(i, 1, n) {
      rep(j, 1, m) if(str[i][j] == '_') {
         ex = i; ey = j; mp[i][j] = 1;
      }
   }
   int cur = 0; h[cur].clr(); h[cur].insert(0, 1);
   rep(i, 1, ex) rep(j, 1, m) {
      cur ^= 1; h[cur].clr();
      rep(k, 1, h[cur ^ 1].cnt) {
         int st = h[cur ^ 1].fir[k], val = h[cur ^ 1].sec[k];
         int p1 = bit(st, j - 1), p2 = bit(st, j);
         if(!mp[i][j]) {
            if(p1 == 0 && p2 == 0) {
               h[cur].insert(st, val);
            }
            continue ;
         }
         if(p1 == 0 && p2 == 0) {
            if(mp[i + 1][j]) h[cur].insert(mdf(st, j - 1, 1), val);
            if(mp[i][j + 1]) h[cur].insert(mdf(st, j, 1), val);
            if(mp[i + 1][j] && mp[i][j + 1]) h[cur].insert(mdf(mdf(st, j - 1, 2), j, 2), val);
         } else if(p2 == 0) {
            if(p1 == 1) {
               if(mp[i][j + 1]) h[cur].insert(mdf(mdf(st, j - 1, 0), j, 1), val);
               if(mp[i + 1][j]) h[cur].insert(mdf(st, j - 1, 2), val);
            } else {
               if(i == ex && j == ey) (ans += val) %= mod;
               if(mp[i][j + 1]) h[cur].insert(mdf(mdf(st, j - 1, 0), j, 2), val);
               h[cur].insert(mdf(st, j - 1, 0), val);
            }
         } else if(p1 == 0) {
            if(p2 == 1) {
               if(mp[i][j + 1]) h[cur].insert(mdf(st, j, 2), val);
               if(mp[i + 1][j]) h[cur].insert(mdf(mdf(st, j, 0), j - 1, 1), val);
            } else {
               if(i == ex && j == ey) (ans += val) %= mod;
               if(mp[i + 1][j]) h[cur].insert(mdf(mdf(st, j, 0), j - 1, 2), val);
               h[cur].insert(mdf(st, j, 0), val);
            }
            
         } else if(p1 == 1 && p2 == 1) {
            if(i == ex && j == ey) (ans += val) %= mod;
            h[cur].insert(mdf(mdf(st, j - 1, 0), j, 0), val);
         }
      }
      if(j == m) {
         rep(k, 1, h[cur].cnt) h[cur].fir[k] <<= 2;
      }
   }
   printf("%d\n", ans);
   return 0;
}