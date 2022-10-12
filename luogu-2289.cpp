#include <algorithm>
#include <iostream>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef __int128 ll;
const int H = 23333, N = 2e6 + 10;
struct HashTable {
   int nxt[N], hd[H], cnt, fir[N];
   ll sec[N];
   void clr() { cnt = 0; fill(hd, hd + H, -1); }
   void insert(int u, ll v) {
      int x = u % H;
      for(int i = hd[x]; ~ i; i = nxt[i])
         if(fir[i] == u) { sec[i] += v; return ; }
      cnt ++; fir[cnt] = u; sec[cnt] = v;
      nxt[cnt] = hd[x]; hd[x] = cnt;
   }
} h[2];
int n, m;
ll ans;
inline int bit(int st, int y) { //注意y的范围是[0, m]
   return st >> (2 * y) & 3;
}
inline int mdf(int st, int y, int z) { //st的y位改为z
   return st ^ ( (bit(st, y) ^ z) << (2 * y) );
}
inline int trans(int st, int y) { //y和y + 1改成0，其对应括号改变
   static int a[15], match[15];
   for(int i = 0; i <= m; i ++) {
      a[i] = st & 3; st >>= 2;
   }
   static int stk[15]; int top = 0;
   for(int i = 0; i <= m; i ++) if(a[i]) {
      if(a[i] == 1) stk[++ top] = i;
      else {
         match[i] = stk[top];
         match[stk[top]] = i;
         top --;
      }
   }
   if(a[y] == 1) a[match[y + 1]] = 1;
   else a[match[y]] = 2;
   a[y] = a[y + 1] = 0;
   int res = 0;
   for(int i = m; i >= 0; i --)
      res = (res << 2) + a[i];
   return res;
}
int main() {
   scanf("%d%d", &n, &m);
   if(n == 1 || m == 1) {
      puts("1"); return 0;
   }
   if(m > n) swap(n, m);
   int cur = 0; h[cur].clr(); h[cur].insert(0, 1);
   rep(i, 1, n) rep(j, 1, m) {
      cur ^= 1; h[cur].clr();
      rep(k, 1, h[cur ^ 1].cnt) {
         int st = h[cur ^ 1].fir[k]; ll val = h[cur ^ 1].sec[k];
         int p1 = bit(st, j - 1), p2 = bit(st, j);
         if(p1 == 0 && p2 == 0) {
            if(i < n && j < m) h[cur].insert(mdf(mdf(st, j - 1, 1), j, 2), val);
         } else if(p2 == 0) {
            if(i < n) h[cur].insert(st, val);
            if(j < m) h[cur].insert(mdf(mdf(st, j - 1, 0), j, p1), val);
         } else if(p1 == 0) {
            if(i < n) h[cur].insert(mdf(mdf(st, j - 1, p2), j, 0), val);
            if(j < m) h[cur].insert(st, val);
         } else if(p1 == 1 && p2 == 1) {
            h[cur].insert(trans(st, j - 1), val);
         } else if(p1 == 2 && p2 == 2) {
            h[cur].insert(trans(st, j - 1), val);
         } else if(p1 == 2 && p2 == 1) {
            h[cur].insert(mdf(mdf(st, j - 1, 0), j, 0), val);
         } else if(p1 == 1 && p2 == 2 && i == n && j == m) {
            ans += val; break ;
         }
      }
      if(j == m) {
         rep(k, 1, h[cur].cnt) h[cur].fir[k] <<= 2;
      }
   }
   static int a[50], t;
   ans *= 2;
   if(!ans) a[++ t] = 0;
   while(ans) {
      a[++ t] = ans % 10; ans /= 10;
   }
   for(int i = t; i >= 1; i --) putchar(a[i] + '0');
   return 0;
}