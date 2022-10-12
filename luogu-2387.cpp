#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 2e5 + 10;
struct edge {
   int u, v, a, b;
   bool operator < (const edge &e) const {
      return a < e.a;
   }
} e[N];
int n, m, A, ans = N * 4;
int ch[N][2], fa[N], ID, eu[N], ev[N], mx[N], mp[N], w[N];
bool rev[N];
#define dir(u) ( ch[fa[u]][0] == u ? 0 : (ch[fa[u]][1] == u ? 1 : -1) )
inline void upd(int u) {
   int &ls = ch[u][0], &rs = ch[u][1]; mx[u] = w[u]; mp[u] = u;
   if(ls && mx[u] < mx[ls]) { mp[u] = mp[ls]; mx[u] = mx[ls]; }
   if(rs && mx[u] < mx[rs]) { mp[u] = mp[rs]; mx[u] = mx[rs]; }
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
   mkroot(u); access(v); splay(v);
   // assert(!fa[u]); // !
   fa[u] = v;
}
void cut(int u, int v) {
   mkroot(u); access(v); splay(v);
   // assert(ch[v][0] == u); // !
   fa[u] = ch[v][0] = 0; upd(v);
}
void addedge(int u, int v, int w) {
   // printf("(%d, %d, %d)!\n", u, v, w);
   mkroot(u); access(v); splay(v);
   if(!fa[u]) {
      ID ++; eu[ID] = u; ev[ID] = v; ::w[ID] = w;
      link(ID, u); link(ID, v);
      return ;
   }
   if(mx[v] <= w) return ;
   int de = mp[v];
   cut(eu[de], de); cut(ev[de], de);
   ID ++; eu[ID] = u; ev[ID] = v; ::w[ID] = w;
   link(ID, u); link(ID, v);
}
int query(int u, int v) {
   mkroot(u); access(v); splay(v);
   return fa[u] ? mx[v] : 4 * N;
}
int main() {
   scanf("%d%d", &n, &m);
   for(int i = 1; i <= m; i ++) {
      scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].a, &e[i].b);
      A = max(A, e[i].a);
   }
   sort(e + 1, e + m + 1);
   int pos = 1; ID = n;
   for(int a = 1; a <= A && a < ans; a ++) {
      int p = pos;
      for(; e[pos].a == a; pos ++) {
         addedge(e[pos].u, e[pos].v, e[pos].b);
      }
      if(p < pos) {
         ans = min(ans, a + query(1, n));
      }
   }
   if(ans >= N * 4) ans = -1;
   printf("%d\n", ans);
   return 0;
}
