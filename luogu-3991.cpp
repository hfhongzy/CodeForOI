#include <algorithm>
#include <cassert>
#include <cstdio>
#define rep(i, j, k) for(int i = j; i <= k; i ++)
#define per(i, j, k) for(int i = j; i >= k; i --)
using namespace std;
typedef long long ll;
template<typename T> void chkmax(T &x, const T &y) { if(x < y) x = y;  }
template<typename T> void chkmin(T &x, const T &y) { if(x > y) x = y;  }
const int N = 2e5 + 10;
int n, id, rt, ch[N][2], fa[N], li[4];
ll f[N][4][4], w[N][4][4], las, siz[N], sz[N];
void New(int *li, ll s) {
   id ++; siz[id] = s;
   rep(i, 0, 3) rep(j, i, 3) {
      w[id][i][j] = li[j] * s;
      if(j > i) chkmax(w[id][i][j], w[id][i][j - 1]);
   }
}
int split(int u, ll lsz) {
   if(lsz == siz[u]) return 0;
   static int tmp[4];
   ll rsz = siz[u] - lsz;
   rep(i, 0, 3) tmp[i] = (int) (w[u][i][i] / siz[u]);
   rep(i, 0, 3) rep(j, i, 3) {
      w[u][i][j] = 1ll * tmp[j] * lsz;
      if(j > i) chkmax(w[u][i][j], w[u][i][j - 1]);
   }
   siz[u] = lsz;
   New(tmp, rsz);
   return id;
}
void upd(int u) {
   int &ls = ch[u][0], &rs = ch[u][1];
   rep(i, 0, 3) rep(j, i, 3) f[u][i][j] = 0;
   rep(i, 0, 3) rep(j, i, 3) rep(k, j, 3) rep(l, k, 3)
      chkmax(f[u][i][l], f[ls][i][j] + w[u][j][k] + f[rs][k][l]);
   sz[u] = sz[ls] + sz[rs] + siz[u];
}
bool dir(int u) { return ch[fa[u]][1] == u; }
void rotate(int u) {
   int f = fa[u], d = dir(u);
   if(fa[u] = fa[f]) ch[fa[u]][dir(f)] = u;
   if(ch[f][d] = ch[u][d ^ 1]) fa[ch[f][d]] = f;
   ch[u][d ^ 1] = f; fa[f] = u; upd(f); upd(u);
}
void splay(int u) {
   for(; fa[u]; rotate(u)) if(fa[fa[u]])
      rotate(dir(u) == dir(fa[u]) ? fa[u] : u);
   rt = u;
}
int kth(ll k) {
   int u = rt;
   while(1) {
      if(k <= sz[ch[u][0]]) u = ch[u][0];
      else {
         k -= sz[ch[u][0]] + siz[u];
         if(k <= 0) break ;
         u = ch[u][1];
      }
   }
   return splay(u), u;
}
int main() {
   scanf("%d", &n);
   New(li, 1); New(li, 1); New(li, 1);
   ch[1][1] = 2; ch[2][1] = 3; fa[2] = 1; fa[3] = 2; rt = 1;
   upd(3); upd(2); upd(1);
   for(int a, b, c, s, T = 1; T <= n; T ++) {
      ll p; scanf("%lld%d%d%d%d", &p, li, li + 1, li + 2, &s); li[3] = *li;
      p += 2; New(li, s); int nw = id;
      int u = kth(p); //assert(u >= 1); printf("u = %d!\n", u);
      int t = p - sz[ch[u][0]];
      int y = split(u, t);
      int ls = ch[u][0], rs = ch[u][1]; //assert(ls >= 1 && rs >= 1);
      if(y) {
         ch[u][1] = 0; ch[nw][0] = u; fa[u] = nw;
         ch[nw][1] = y; fa[y] = nw;
         ch[y][1] = rs; fa[rs] = y;
         upd(u); upd(y); upd(nw); rt = nw;
      } else {
         ch[u][1] = 0; ch[nw][0] = u; fa[u] = nw;
         ch[nw][1] = rs; fa[rs] = nw;
         upd(u); upd(nw); rt = nw;
      }
      ll cur = 0;
      rep(i, 0, 3) rep(j, i, 3) chkmax(cur, f[rt][i][j]);
      printf("%lld\n", cur - las); las = cur;
   }
   return 0;
}