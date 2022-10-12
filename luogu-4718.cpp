#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
using ll = long long;

const int M = 262143;
struct HashMap {
  int hd[M + 5], nxt[M + 5], fir[M + 5], sec[M + 5], id;
  void insert(int x, int y) {
    int z = x & M;
    id ++; fir[id] = x; sec[id] = y; nxt[id] = hd[z]; hd[z] = id;
  }
  int find(int x) {
    int z = x & M;
    for(int i = hd[z]; i; i = nxt[i])
      if(fir[i] == x) return sec[i];
    return -1;
  }
  void clear() {
    for(int i = 1; i <= id; i ++)
      hd[fir[i] & M] = 0;
    id = 0;
  }
} H;
int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}
void exgcd(int a, int b, int &x, int &y, int &g) {
  if(!b) x = 1, y = 0, g = a;
  else exgcd(b, a % b, y, x, g), y -= a / b * x;
}
int qpow(int a, int b, int p) {
  int c = 1;
  for(; b >= 1; b >>= 1, a = (ll)a * a % p)
    if(b & 1) c = (ll)c * a % p;
  return c;
}
int inv(int n, int p) {
  int x, y, g;
  exgcd(n, p, x, y, g);
  assert(g == 1);
  return (x % p + p) % p;
}
int logM(int a, int b, int p) { //a^x \equiv b \pmod {p}
  //a^{im} = b a^{-j}
  H.clear();
  int m = (int)ceil(sqrt(p));
  int aI = inv(a, p), z = b, t = 0;
  for(int i = 0; i < m; i ++) {
    if(!~H.find(z)) H.insert(z, i);
    z = (ll)z * aI % p;
  }
  int aM = qpow(a, m, p); z = 1;
  for(int i = 0; i <= m; i ++) {
    if(~(t = H.find(z)))
      return i * m + t;
    z = (ll)z * aM % p;
  }
  return -1;
}
int exlogM(int a, int b, int p) {
  if(b == 1 || p == 1) return 0;
  int d = gcd(a, p), t = 0, z = 1;
  while(d > 1) {
    if(b % d) return -1;
    b /= d; p /= d; z = (ll)z * (a / d) % p; t ++;
    if(z == b) return t;
    d = gcd(a, p);
  }
  d = logM(a, (ll)b * inv(z, p) % p, p);
  return ~d ? d + t : -1;
}
int main() {
  int a, b, p;
  while(scanf("%d%d%d", &a, &p, &b), a) {
    a = (a % p + p) % p; b = (b % p + p) % p;
    int z = exlogM(a, b, p);
    if(z == -1) puts("No Solution");
    else printf("%d\n", z);
  }
  return 0;
}