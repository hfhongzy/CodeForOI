#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
char gc() {
   // return getchar();
   static char buf[1 << 17], *S, *T;
   if(S == T) T = (S = buf) + fread(buf, 1, 1 << 17, stdin);
   return S == T ? EOF : *S ++;
}
template<class T> void read(T &x) {
   x = 0; char c = gc(); bool na = 0;
   for(; c < '0' || c > '9'; c = gc()) na |= c == '-';
   for(; c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
   if(na) x = -x;
}

const int N = 1e6 + 10;
const int mod = 998244353;
const int inv2 = (mod + 1) >> 1;
int qpow(int a, int b) {
   int ans = 1;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
void upd(int &x, int y) {
   (x += y) >= mod ? x -= mod : 0;
}
int n, ans, pa, p[N], pos[N], q[N], pre[N], invn;
bool vis[N];

struct BIT {
   
int bit[N];
void clr() { fill(bit + 1, bit + n + 1, 0); }
void ins(int u) {
   for(; u <= n; u += u & (-u)) {
      upd(bit[u], 1);
   }
}
int qry(int u) {
   int ans = 0;
   for(; u >= 1; u &= u - 1) {
      upd(ans, bit[u]);
   }
   return ans;
}

} B;
int main() {
   read(n);
   rep(i, 1, n) read(p[i]), pos[p[i]] = i;
   rep(i, 1, n) read(q[i]);
   rep(i, 1, n) if(~ q[i]) vis[q[i]] = 1;
   rep(i, 1, n) pre[i] = pre[i - 1] + (vis[i] == 0);
   invn = qpow(pre[n], mod - 2);
   rep(i, 1, n) {
      upd(pa, B.qry(p[i]));
      B.ins(p[i]);
   }
   B.clr();

   int cnt = 0;
   rep(i, 1, n) {
      if(q[i] == -1) {
         pa = (pa + 1ll * cnt * inv2) % mod;
         cnt ++;
      } else {
         upd(pa, B.qry(q[i]));
         B.ins(q[i]);
         pa = (pa + 1ll * pre[q[i]] * invn % mod * cnt) % mod;
      }
   }
   cnt = 0;
   per(i, n, 1) {
      if(q[i] == -1) {
         cnt ++;
      } else {
         pa = (pa + 1ll * (pre[n] - pre[q[i]]) * invn % mod * cnt) % mod;
      }
   }
   B.clr();

   cnt = 0;
   rep(i, 1, n) {
      int x = pos[i];
      if(q[x] == -1) {
         pa = (pa + 1ll * cnt * inv2) % mod;
         cnt ++;
      } else {
         upd(pa, B.qry(q[x]));
         B.ins(q[x]);
         pa = (pa + 1ll * pre[q[x]] * invn % mod * cnt) % mod;
      }
   }
   cnt = 0;
   per(i, n, 1) {
      int x = pos[i];
      if(q[x] == -1) {
         cnt ++;
      } else {
         pa = (pa + 1ll * (pre[n] - pre[q[x]]) * invn % mod * cnt) % mod;
      }
   }
   ans = inv2 * (pa - n * (n - 1ll) / 2 % mod + mod) % mod;
   printf("%d\n", ans);
   return 0;
}