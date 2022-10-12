#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 3e5 + 10;
struct edge {
   int u, v, w;
   bool operator < (const edge &e) const {
      return w < e.w;
   }
} e[N];
int n, m, ans = N * 4;
int ch[N][2], fa[N], ID, mn[N];
bool rev[N], vis[N];
#define dir(u) ( ch[fa[u]][0] == u ? 0 : (ch[fa[u]][1] == u ? 1 : -1) )
inline void upd(int u) {
   int &ls = ch[u][0], &rs = ch[u][1]; mn[u] = u <= n ? N : u;
   if(ls && mn[u] > mn[ls]) mn[u] = mn[ls];
   if(rs && mn[u] > mn[rs]) mn[u] = mn[rs];
}
void rotate(int u) {
   int d = dir(u), f = fa[u];
   if(fa[u] = fa[f], ~ dir(f)) ch[fa[f]][dir(f)] = u;
   if(ch[f][d] = ch[u][d ^ 1]) fa[ch[f][d]] = f;
   fa[ch[u][d ^ 1] = f] = u; upd(f); //upd(u);
}
void pdown(int u) {
   if(!rev[u]) return ;
   rev[ch[u][0]] ^= 1; rev[ch[u][1]] ^= 1;
   swap(ch[u][0], ch[u][1]); rev[u] = 0;
}
int tp, st[N];
void splay(int u) {
   tp = 0; st[tp ++] = u;
   for(int v = u; ~ dir(v); v = fa[v]) st[tp ++] = fa[v];
   while(tp --) pdown(st[tp]);
   for(; ~ dir(u); rotate(u)) if(~ dir(fa[u]))
      rotate(dir(u) == dir(fa[u]) ? fa[u] : u);
   upd(u);
}
void access(int u) {
   for(int v = 0; u; v = u, u = fa[u]) {
      splay(u); ch[u][1] = v; upd(u);
   }
}
void mkroot(int u) {
   access(u); splay(u); rev[u] ^= 1;
}
void link(int u, int v) {
   mkroot(u); access(v); splay(v); fa[u] = v;
}
void cut(int u, int v) {
   mkroot(u); access(v); splay(v);
   fa[u] = ch[v][0] = 0; upd(v);
}
int ecnt;
void addedge(int u, int v, int ID) {
   mkroot(u); access(v); splay(v);
   if(!fa[u]) {
      link(ID, u); link(ID, v); ecnt ++;
      return ;
   }
   int de = mn[v] - n; vis[de] = 1;
   cut(e[de].u, de + n); cut(e[de].v, de + n);
   link(ID, u); link(ID, v);
}
int main() {
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= m; i ++) {
      scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
   }
   sort(e + 1, e + m + 1);
   int p = 1; ID = n;
   for(int i = 1; i <= m; i ++) {
      ID ++;
      if(e[i].u != e[i].v) {
         addedge(e[i].u, e[i].v, ID);
         while(vis[p]) p ++;
         if(ecnt == n - 1) ans = min(ans, e[i].w - e[p].w);
      } else vis[i] = 1;
   }
   printf("%d\n", ans);
   return 0;
}