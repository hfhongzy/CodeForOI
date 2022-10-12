#include <cstdio>

const int A = 59713600; //sqrt(2)
const int mod = 1e9 + 7;

int qpow(int a, int b) {
   int ans = 1; a = (a % mod + mod) % mod;
   for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
      if(b & 1) ans = 1ll * ans * a % mod;
   return ans;
}
int read() {
   int x = 0; char c = getchar();
   for(; c < '0' || c > '9'; c = getchar()) ;
   for(; c >= '0' && c <= '9'; c = getchar())
      x = (x * 10ll + (c & 15)) % (mod - 1);
   return x;
}
int main() {
   int n = read();
   int ans = 1ll * qpow(A + A, mod - 2) * (qpow(1 + A, n) - qpow(1 - A, n) + mod) % mod;
   printf("%d\n", ans);
   return 0;
}