#include <bits/stdc++.h>
#define pb push_back
#define LOG(FMT...) fprintf(stderr, FMT);
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2e6 + 10;
char s[N], t[N], s2[N], t2[N];
int n, p[N], C[N], T[N], f[N];
bool vis[N];
int kmp(char *s, char *t, int n, int m) {
  static int f[N];
  int j = f[1] = 0;
  rep(i, 2, m) {
    for(; j && t[j + 1] != t[i]; j = f[j]);
    if(t[j + 1] == t[i]) ++ j;
    f[i] = j;
  }
  j = 0;
  rep(i, 1, n) {
    for(; j && t[j + 1] != s[i]; j = f[j]);
    if(t[j + 1] == s[i]) {
      ++ j;
      if(j == m) return i - m + 1;
    }
  }
  return -1;
}
void exgcd(int a, int b, int &x, int &y, int &g) {
  if(!b) { x = 1, y = 0, g = a; }
  else exgcd(b, a % b, y, x, g), y -= a / b * x;
}
int excrt(int n, int *a, int *p) { //x \equiv a_i \pmod {p_i}
  int c = a[1], d = p[1];
  rep(i, 2, n) {
    int x, y, g;
    exgcd(d, p[i], x, y, g);
    if((a[i] - c) % g) return -1;
    int t = p[i] / g;
    x = 1ll * x * ( (a[i] - c) / g ) % t;
    if(x < 0) x += t;
    int nx = t * d;
    c = (1ll * d * x + c) % nx; d = nx;
  }
  return c;
}
int main() {
  scanf("%s%s", s + 1, t + 1);
  n = strlen(s + 1);
  rep(i, 1, n) p[i & 1 ? (i + 1) / 2 : n / 2 + i / 2] = i;
  int e = 0;
  rep(i, 1, n) if(!vis[i]) {
    int l = 0;
    for(int u = i; !vis[u]; u = p[u]) {
      vis[u] = 1;
      s2[++ l] = s[u];
      t2[l] = t[u];
    }
    s2[l + 1] = t2[l + 1] = 0;
    static char ss[N];
    rep(i, 1, 2 * l) ss[i] = i <= l ? s2[i] : s2[i - l];
    C[++ e] = kmp(ss, t2, 2 * l, l);
    if(!~C[e]) { puts("-1"); return 0; }
    C[e] --;
    T[e] = kmp(ss + 1, s2, 2 * l, l);
  }
  printf("%d\n", excrt(e, C, T));
  return 0;
}