#include <bits/stdc++.h>
using namespace std;
namespace Map {
   
const int mod = 76543;
const int N = 1e5 + 10;
int cnt, hd[mod], nxt[N], fir[N], sec[N];
void clr() {
   fill(hd, hd + mod, -1); cnt = 0;
}
void ins(int x, int y) {
   int k = x % mod;
   fir[cnt] = x; sec[cnt] = y; nxt[cnt] = hd[k]; hd[k] = cnt ++; 
}
int find(int x) {
   for(int i = hd[x % mod]; ~ i; i = nxt[i])
      if(fir[i] == x) return sec[i];
   return -1;
}

}
int gcd(int x, int y) {
   return y ? gcd(y, x % y) : x;
}
void exgcd(int a, int b, int &x, int &y, int &g) {
   if(!b) x = 1, y = 0, g = a;
   else exgcd(b, a % b, y, x, g), y -= x * (a / b);
}
int qpow(int a, int b, int p) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % p)
      if(b & 1) ans = 1ll * ans * a % p;
   return ans;
}
int inv(int a, int p) { //ax + py = 1
   int x, y, g;
   exgcd(a, p, x, y, g);
   return (x % p + p) % p;
}
int logM(int a, int b, int p) { //a^x = b (mod p), (a, p) = 1
   Map::clr();
   int m = (int) ceil(sqrt(p + 0.5));
   int aM = qpow(a, m, p), t = 1;
   for(int i = 0; i <= m; i ++) {
      if(-1 == Map::find(t)) Map::ins(t, i);
      t = 1ll * t * aM % p;
   }
   int q = b, inv_a = inv(a, p), ans = -1;
   for(int i = 0; i < m; i ++) {
      if(~ (t = Map::find(q))) {
         int r = t * m + i;
         if(ans == -1 || ans > r) ans = r;
      }
      q = 1ll * q * inv_a % p;
   }
   return ans;
}
int exlogM(int a, int b, int p) {
   int d = gcd(a, p), t = 0, tt = 1;
   while(d > 1) {
      if(b % d) return -1;
      b /= d; p /= d; t ++; tt = 1ll * tt * (a / d) % p;
      if(tt == b) return t;
      d = gcd(a, p);
   }
   b = 1ll * b * inv(tt, p) % p;
   tt = logM(a, b, p);
   return tt == -1 ? -1 : tt + t;
}
int main() {
   for(int a, p, b; scanf("%d%d%d", &a, &p, &b), a || b || p; ) {
      a = (a % p + p) % p; b = (b % p + p) % p;
      int ans = exlogM(a, b, p);
      if(~ ans) printf("%d\n", ans);
      else puts("No Solution");
   }  
   return 0;
}