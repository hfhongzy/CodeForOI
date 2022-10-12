#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> poly;
const int N = 262144 + 10, mod = 998244353;
const int inv3 = (mod + 1) / 3, inv2 = (mod + 1) / 2;
int add(int x, int y) { return (x += y) >= mod ? x - mod : x; }
int dec(int x, int y) { return x - y < 0 ? x - y + mod : x - y; }
int qpow(int a, int b) {
  int ans = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % mod)
    if(b & 1) ans = (ll)ans * a % mod;
  return ans;
}
int rev[N], W[N];
int getn(int len) { int n = 1; while(n < len) n <<= 1; return n; } //[0, len - 1]
void prework(int n) {
  for(int i = 1; i < n; i <<= 1) {
    W[i] = 1;
    int w = qpow(3, (mod - 1) / (i << 1));
    for(int j = 1; j < i; j ++)
      W[i + j] = (ll)W[i + j - 1] * w % mod;
  }
}
void NTT(int *a, int n, int op) {
  for(int i = 1; i < n; i ++)
    if(i < (rev[i] = (rev[i >> 1] >> 1) | (i & 1 ? n >> 1 : 0)))
      swap(a[i], a[rev[i]]);
  for(int i = 1; i < n; i <<= 1) {
    for(int j = 0; j < n; j += i << 1) {
      for(int k = 0; k < i; k ++) {
        int q = (ll)W[i + k] * a[j + k + i] % mod;
        a[j + k + i] = add(a[j + k], mod - q); a[j + k] = add(a[j + k], q);
      }
    }
  }
  if(op == 1) return ;
  reverse(a + 1, a + n);
  int inv = mod - (mod - 1) / n;
  for(int i = 0; i < n; i ++) a[i] = (ll)a[i] * inv % mod;
}
int f[N] = {1}, a[N], b[N], c[N];
void solve(int l, int r) {
  if(l == r) {
    if(l % 3 == 1) f[l] = (f[l] + (ll)inv3 * f[(l - 1) / 3]) % mod;
    return ;
  }
  int mid = (l + r) >> 1;
  solve(l, mid);
  if(l) {
    int n = getn(2 * (r - l) + 1);
    for(int i = 0; i < n; i ++) a[i] = i <= mid - l ? f[l + i] : 0;
    for(int i = 0; i < n; i ++) b[i] = i <= r - l ? f[i] : 0;
    for(int i = 0; i < n; i ++) c[i] = 0;
    for(int i = 0; i <= r - l; i ++) c[i << 1] = f[i];
    NTT(a, n, 1); NTT(b, n, 1); NTT(c, n, 1);
    for(int i = 0; i < n; i ++) a[i] = a[i] * (((ll)b[i] * b[i] + c[i]) % mod) % mod * inv2 % mod;
    NTT(a, n, -1);
    for(int i = mid + 1; i <= r; i ++)
      f[i] = add(f[i], a[i - l - 1]);
  } else {
    int n = getn(2 * (r - l) + 1);
    for(int i = 0; i < n; i ++) a[i] = i <= mid - l ? f[l + i] : 0;
    for(int i = 0; i < n; i ++) c[i] = 0;
    for(int i = 0; i <= r - l; i ++) c[i << 1] = f[i];
    NTT(a, n, 1); NTT(c, n, 1);
    for(int i = 0; i < n; i ++) a[i] = a[i] * (((ll)a[i] * a[i] % mod * inv3 + c[i]) % mod) % mod * inv2 % mod;
    NTT(a, n, -1);
    for(int i = mid + 1; i <= r; i ++)
      f[i] = add(f[i], a[i - l - 1]);
  }
  solve(mid + 1, r);
}
int main() {
  int n; scanf("%d", &n); prework(2 * n + 1); solve(0, n);
  printf("%d\n", f[n]);
  return 0;
}