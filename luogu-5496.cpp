#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;

struct pam {
  int fail, len, d, st, nxt[26];
} t[N];
char s[N];
int n, id, la;
void clr(int u) { t[u].st = 0; }
void init() {
  s[0] = -1; la = n = 0; id = 1;
  t[0] = (pam){0, -1, 0};
  t[1] = (pam){0, 0, 0};
  clr(0); clr(1);
}
int find(int u) {
  while(s[n - t[u].len] != s[n + 1]) u = t[u].fail;
  return u;
}
void insert(int c) {
  int u = find(la);
  if(t[u].st >> c & 1) la = t[u].nxt[c];
  else {
    t[u].st ^= 1 << c;
    t[u].nxt[c] = la = ++ id; clr(la);
    t[la].len = t[u].len + 2;
    int v = u ? t[find(t[u].fail)].nxt[c] : 1;
    t[la].d = t[t[la].fail = v].d + 1;
  }
  n ++;
}
int main() {
  scanf("%s", s + 1); init();
  int ans = 0;
  for(int i = 1; s[i]; i ++) {
    insert(s[i] = (s[i] - 'a' + ans) % 26);
    printf("%d ", ans = t[la].d);
  }
  return 0;
}