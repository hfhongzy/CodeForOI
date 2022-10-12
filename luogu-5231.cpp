#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 2e7 + 10;
int la, id, lnk[N], len[N], ch[N][4], w[N];
int Map[256];
void init() {
  lnk[0] = -1; id = la = 0; fill(ch[0], ch[0] + 4, -1);
}
void extend(int c) {
  int u = ++ id, p = la;
  fill(ch[u], ch[u] + 4, -1); len[u] = len[la] + 1;
  for(; ~ p && ch[p][c] == -1; p = lnk[p]) ch[p][c] = u;
  if(p == -1) lnk[u] = 0;
  else {
    int q = ch[p][c];
    if(len[q] == len[p] + 1) lnk[u] = q;
    else {
      int q0 = ++ id;
      copy(ch[q], ch[q] + 4, ch[q0]);
      len[q0] = len[p] + 1; lnk[q0] = lnk[q];
      lnk[u] = lnk[q] = q0;
      for(; ~ p && ch[p][c] == q; p = lnk[p])
        ch[p][c] = q0;
    }
  }
  la = u; w[u] = 1;
}
char str[N], s[N];
int main() {
  Map['E'] = 0; Map['S'] = 1; Map['W'] = 2; Map['N'] = 3;
  int n, m;
  scanf("%d%d", &n, &m);
  scanf("%s", str + 1); init();
  for(int i = 1; i <= n; i ++) extend(Map[str[i]]);
  for(int i = 1; i <= m; i ++) {
    scanf("%s", s + 1);
    int u = 0, ans = 0;
    for(int j = 1; s[j]; j ++) {
      if(!~ch[u][Map[s[j]]]) break ;
      ans ++; u = ch[u][Map[s[j]]];
    }
    printf("%d\n", ans);
  }
  return 0;
}