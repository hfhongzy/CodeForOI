#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e6 + 10;
struct pam {
  int fail, len, d, st, fa, dir, nxt[26];
} t[N];
char s[N];
int n, id, la, rk[N];
void clr(int u) { t[u].st = 0; }
void init() {
  s[0] = -1; la = n = 0; id = 1;
  t[0].len = -1; clr(0); clr(1);
}
int find(int u) {
  while(s[n - t[u].len] != s[n + 1]) u = t[u].fail;
  return u;
}
void append(int c) {
  int u = find(la);
  if(t[u].st >> c & 1) la = t[u].nxt[c];
  else {
    t[u].st ^= 1 << c;
    t[u].nxt[c] = la = ++ id; clr(la); t[la].fa = u; t[la].dir = c;
    t[la].len = t[u].len + 2;
    int v = u ? t[find(t[u].fail)].nxt[c] : 1;
    t[la].d = t[t[la].fail = v].d + 1;
  }
  n ++;
}
string ans;
void out(int u) {
  string c; c += char('a' + t[u].dir);
  if(t[u].len > 2) {
    out(t[u].fa);
    ans.insert(0, c);
    ans.push_back(t[u].dir + 'a');
  } else {
    ans.push_back(t[u].dir + 'a');
    if(t[u].len == 2) ans.push_back(t[u].dir + 'a');
  }
}
int main() {
  freopen("str.in", "r", stdin);
  freopen("str.out", "w", stdout);
  ll opt;
  scanf("%*d%lld%s", &opt, s + 1); init();
  for(int i = 1; s[i]; i ++) append(s[i] - 'a');
  printf("%d\n", id - 1);
  // return 0;
  int k = opt % (id - 1); //[0, id-1)
  static int ord[N];
  for(int i = 0; i < id - 1; i ++) ord[i] = i + 2;
  sort(ord, ord + id - 1, [&](int x, int y) {
    return t[x].len < t[y].len;
  });
  for(int i = 0, j; i < id - 1 && i <= k; i = j + 1) {
    j = i;
    while(j + 1 < id - 1 && t[ord[j + 1]].len == t[ord[i]].len) j ++;
    sort(ord + i, ord + j + 1, [&](int x, int y) {
      return t[x].dir < t[y].dir || (t[x].dir == t[y].dir && rk[t[x].fa] < rk[t[y].fa]);
    });
    for(int k = i; k <= j; k ++) rk[ord[k]] = k;
  }
  out(ord[k]);
  puts(ans.c_str());
  return 0;
}