#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
struct pam {
  int fail, len, d, st, half, nxt[4];
} t[N];
char s[N];
int n, id, la, ID[256], f[N];
void clr(int u) { t[u].st = 0; }
void init() {
  s[0] = -1; la = n = 0; id = 1;
  t[0].len = -1; clr(0); clr(1);
  t[0].half = t[1].half = 0;
}
int find(int u) {
  while(s[n - t[u].len] != s[n + 1]) u = t[u].fail;
  return u;
}
int find2(int u, int m) {
  while((t[u].len + 2) * 2 > m || s[n - t[u].len] != s[n + 1]) u = t[u].fail; //printf("%d!!\n", u);
  return u;
}
void append(int c) {
  int u = find(la);
  if(t[u].st >> c & 1) la = t[u].nxt[c];
  else {
    t[u].st |= 1 << c;
    t[u].nxt[c] = la = ++ id; clr(la);
    t[la].len = t[u].len + 2;
    int v = u ? t[find(t[u].fail)].nxt[c] : 1;
    t[la].d = t[t[la].fail = v].d + 1;
    t[la].half = u ? t[find2(t[u].half, t[la].len)].nxt[c] : 1;
  }
  n ++;
}
int main() {
  ID['A'] = 0; ID['T'] = 1; ID['G'] = 2; ID['C'] = 3;
  int test;
  scanf("%d", &test);
  while(test --) {
    init();
    scanf("%s", s + 1);
    for(int i = 1; s[i]; i ++) append(ID[s[i]]);
    queue<int> q; q.push(1); f[1] = 1;
    int ans = n;
    while(q.size()) {
      int u = q.front(); q.pop();
      int h = t[u].half;
      if(!(t[h].len & 1)) f[u] = min(f[u], f[h] + t[u].len / 2 - t[h].len + 1);
      ans = min(ans, f[u] + n - t[u].len);
      for(int i = 0; i < 4; i ++) if(t[u].st >> i & 1) {
        int v = t[u].nxt[i];
        f[v] = f[u] + 1; q.push(v);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}