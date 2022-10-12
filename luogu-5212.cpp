#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 8e6 + 5;
namespace lct {

#define mktag(u, v) tag[u] += v, w[u] += v
int tag[N], fa[N], ch[N][2], w[N];
int dir(int u) { return ch[fa[u]][0] == u ? 0 : (ch[fa[u]][1] == u ? 1 : -1); }
void down(int u) {
  int &t = tag[u];
  if(t) { mktag(ch[u][0], t); mktag(ch[u][1], t); t = 0; }
}
void rot(int u) {
  int f = fa[u], d = dir(u);
  if(fa[u] = fa[f], ~dir(f)) ch[fa[u]][dir(f)] = u;
  if((ch[f][d] = ch[u][d ^ 1]) > 0) fa[ch[f][d]] = f;
  ch[u][d ^ 1] = f; fa[f] = u;
}
int st[N];
void splay(int u) {
  int t = 0;
  for(int v = u; ~dir(v); v = fa[v]) st[t ++] = fa[v];
  while(t --) down(st[t]);
  for(down(u); ~dir(u); rot(u)) if(~dir(fa[u]))
    rot(dir(u) == dir(fa[u]) ? fa[u] : u);
}
void access(int u) {
  for(int v = 0; u; v = u, u = fa[u]) {
    splay(u); ch[u][1] = v;
  }
}
void link(int u, int v) {
  access(u); splay(v); fa[v] = u;
  splay(u); mktag(u, w[v]);
}
void cut(int u, int v) {
  access(u); splay(v); fa[v] = 0;
  splay(u); mktag(u, -w[v]);
}
void add(int u, int val) {
  access(u); splay(u); mktag(u, val);
}
int query(int u) {
  splay(u); return w[u];
}

}
int la, id, ch[N][2], lnk[N], len[N];
void init() { la = id = 0; fill(ch[0], ch[0] + 2, -1); lnk[0] = -1; }
void extend(int c) {
  int u = ++ id, p = la;
  len[u] = len[la] + 1; fill(ch[u], ch[u] + 2, -1);
  for(; ~p && !~ch[p][c]; p = lnk[p]) ch[p][c] = u;
  if(!~p) {
    lnk[u] = 0;
    lct::link(1, u + 1);
  } else {
    int q = ch[p][c];
    if(len[q] == len[p] + 1) {
      lnk[u] = q;
      lct::link(q + 1, u + 1);
    } else {
      int q0 = ++ id;
      len[q0] = len[p] + 1; copy(ch[q], ch[q] + 2, ch[q0]);
      lnk[q0] = lnk[q]; lct::link(lnk[q0] + 1, q0 + 1);

      lct::cut(lnk[q] + 1, q + 1);
      lnk[q] = q0;
      lct::link(lnk[q] + 1, q + 1);

      lnk[u] = q0; lct::link(lnk[u] + 1, u + 1);
      for(; ~p && ch[p][c] == q; p = lnk[p]) ch[p][c] = q0;
    }
  }
  la = u;
  lct::add(u + 1, 1);
}
char s[N], op[32];
void decode(char *s, int m, int z) {
  for(int i = 0; i < m; i ++) {
    z = (z * 131 + i) % m; swap(s[z], s[i]);
  }
}
int main() {
  int q, lans = 0; scanf("%d", &q);
  scanf("%s", s);
  init();
  for(int i = 0; s[i]; i ++) extend(s[i] - 'A');
  while(q --) {
    scanf("%s%s", op, s);
    int m = strlen(s);
    decode(s, m, lans);
    if(*op == 'A') {
      for(int i = 0; i < m; i ++) extend(s[i] - 'A');
    }
    if(*op == 'Q') {
      int u = 0; bool ok = 1;
      for(int i = 0; i < m; i ++) {
        u = ch[u][s[i] - 'A'];
        if(!~u) {
          ok = 0; break ;
        }
      }
      int c = ok ? lct::query(u + 1) : 0;
      lans ^= c;
      printf("%d\n", c);
    }
  }
  return 0;
} 
/*
LCT 维护 link 树，需要维护叶子数量
link/cut 到根链加链减
u 到根链加: access(u), tag[rt] += v;
询问 u：access, splay
*/