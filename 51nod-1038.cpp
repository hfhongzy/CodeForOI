#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
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

int gcd(int a, int b) {
   return b ? gcd(b, a % b) : a;
}
void exgcd(int a, int b, int &x, int &y, int &g) {
   if(!b) x = 1, y = 0, g = a;
   else exgcd(b, a % b, y, x, g), y -= a / b * x;
}
int qpow(int a, int b, int p) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % p)
      if(b & 1) ans = 1ll * ans * a % p;
   return ans;
}
int inv(int a, int p) {
   int x, y, g; exgcd(a, p, x, y, g);
   return g == 1 ? (x % p + p) % p : -1;
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
struct ModRoot {
   int g;
   operator int() const { return g; }
   int get(int p) { //p is prime
      vector<int> vec; vec.clear(); int x = p - 1;
      for(int i = 2; i * i <= x; i ++) {
         if(x % i == 0) {
            vec.push_back(i);
            while(x % i == 0) x /= i;
         }
      }
      if(x > 1) vec.push_back(x);
      for(int i = 2; i < p; i ++) {
         bool mark = 1;
         for(int v : vec) {
            if(qpow(i, (p - 1) / v, p) == 1) {
               mark = 0; break ;
            }
         }
         if(mark) return g = i;
      }
      return g = 0;
   }
} g;
vector<int> residue(int A, int B, int p) { //x^a = b (mod p), p is prime
   vector<int> ans; g.get(p); B = logM(g, B, p); //tA = B (mod p - 1)
   int t, t0, r; exgcd(A, p - 1, t, t0, r);
   if(B % r) return ans;
   const int st = (p - 1) / r;
   for(t = (1ll * t * (B / r) % st + st) % st; t < p - 1; t += st) {
      ans.push_back(qpow(g, t, p));
   }
   sort(ans.begin(), ans.end());
   return ans;
}
int main() {
   int test; scanf("%d", &test);
   while(test --) {
      int a, b, p;
      scanf("%d%d%d", &p, &a, &b);
      vector<int> ans = residue(a, b, p);
      if(!ans.size()) printf("No Solution");
      for(int v : ans) printf("%d ", v);
      putchar('\n');
   }
   return 0;
}