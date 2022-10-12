#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 5e5 + 10, mod = 1e9 + 7;
int n, k;
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = 1ll * a * a % mod)
    if(b & 1) ans = 1ll * ans * a % mod;
  return ans;
}
// int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }
int phi(int n) {
  int ans = n;
  for(int i = 2; i * i <= n; i ++) if(n % i == 0) {
    ans = ans / i * (i - 1);
    while(n % i == 0) n /= i;
  }
  if(n > 1) ans = ans / n * (n - 1);
  return ans;
}
struct mat {
  int a[2][2];
  void init(int x, int y, int z, int w) {
    a[0][0] = x; a[0][1] = y; a[1][0] = z; a[1][1] = w;
  }
  mat operator * (const mat &b) {
    mat ans;
    for(int i = 0; i < 2; i ++) {
      for(int j = 0; j < 2; j ++) {
        ans.a[i][j] = 0;
        for(int k = 0; k < 2; k ++) {
          (ans.a[i][j] += 1ll * a[i][k] * b.a[k][j] % mod) %= mod;
        }
      }
    }
    return ans;
  }
};
mat mpow(mat a, int b) {
  mat ans = a; b --;
  for(; b >= 1; b >>= 1, a = a * a)
    if(b & 1) ans = ans * a;
  return ans;
}
int solve(int n, int k) {
  if(n == 1) return 0;
  if(n == 2) return k * (k - 1ll) % mod;
  mat fir; fir.init(k * (k - 1ll) % mod, 0, 0, 0);
  mat tr; tr.init(k - 2, 1, k - 1, 0);
  fir = fir * mpow(tr, n - 2);
  return fir.a[0][0];
}
int main() {
  while(~ scanf("%d%d", &n, &k)) {
    int ans = 0;
    for(int i = 1; i * i <= n; i ++) if(n % i == 0) {
      (ans += 1ll * phi(n / i) * solve(i, k - 1) % mod) %= mod;
      if(n / i != i) {
        (ans += 1ll * phi(i) * solve(n / i, k - 1) % mod) %= mod;
      }
    }
    printf("%d\n", (int) (1ll * k * ans % mod * qpow(n, mod - 2) % mod));
  }
  return 0;
}