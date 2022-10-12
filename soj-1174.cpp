#include <bits/stdc++.h>
#include "DAKLQW.h"
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 2e6 + 5;
namespace sam {

int la, id, lnk[N], len[N], endp[N], ch[N][2];
vector<int> G[N];
void init() { lnk[0] = -1; id = la = 0; ch[0][0] = ch[0][1] = -1; }
void extend(int c) {
  int u = ++ id, p = la;
  ch[u][0] = ch[u][1] = -1; len[u] = len[la] + 1; endp[u] = len[u];
  for(; ~ p && ch[p][c] == -1; p = lnk[p]) ch[p][c] = u;
  if(p == -1) lnk[u] = 0;
  else {
    int q = ch[p][c];
    if(len[q] == len[p] + 1) lnk[u] = q;
    else {
      int q0 = ++ id;
      ch[q0][0] = ch[q][0]; ch[q0][1] = ch[q][1];
      len[q0] = len[p] + 1; lnk[q0] = lnk[q];
      lnk[u] = lnk[q] = q0; endp[q0] = len[u];
      for(; ~ p && ch[p][c] == q; p = lnk[p])
        ch[p][c] = q0;
    }
  }
  la = u;
}

}
int solve(int l, int r) {
  int u = 0;
  rep(i, l, r) {
    u = sam::ch[u][getpos(i) - '0'];
    if(-1 == u) return -1;
  }
  return r - sam::endp[u] + 1;
}
int xpptxdy(int n, string t) {
  sam::init();
  for(int i = 0; i < (int)t.size(); i ++) sam::extend(t[i] - '0');
  for(int i = 1; i + 49 <= n; i += t.size() - 50) {
    int r = solve(i, i + 49);
    if(~r) return r;
  }
  return -1;
}