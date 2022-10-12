#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
#define debug(x) fprintf(stderr, "%s = %d\n", #x, x);
using namespace std;

const int N = 4e5 + 10;

mt19937 rd(time(0));
uniform_int_distribution<int> ran(0, 1);

int n, m, nxt[N], pre[N], p[N], out[N], in[N];
pair<int, int> e[N];
bool path(int x, int y) {
   while(x) {
      x = nxt[x];
      if(x == y) return 1;
   }
   return 0;
}
void print() {
   static bool use[N];
   rep(i, 1, n) use[nxt[i]] = 1;
   printf("%d\n", n);
   rep(i, 1, n) if(!use[i]) {
      for(int x = i; x; x = nxt[x]) {
         printf("%d ", x);
      }
      break ;
   }
   putchar('\n');
}
namespace LCT {

int ch[N][2], fa[N];
bool rev[N];
int dir(int u) {
   return ch[fa[u]][0] == u ? 0 : (ch[fa[u]][1] == u ? 1 : -1);
}
void rotate(int u) {
   int f = fa[u], d = dir(u);
   if(fa[u] = fa[f], ~ dir(f)) ch[fa[f]][dir(f)] = u;
   if(ch[f][d] = ch[u][d ^ 1]) fa[ch[u][d ^ 1]] = f;
   ch[u][d ^ 1] = f; fa[f] = u;
}
void pushd(int u) {
   if(rev[u]) {
      swap(ch[u][0], ch[u][1]);
      rev[ch[u][0]] ^= 1;
      rev[ch[u][1]] ^= 1;
      rev[u] = 0;
   }
}
int st[N];
void splay(int u) {
   int top = 0, v;
   for(v = u; ~ dir(v); v = fa[v]) st[top ++] = v;
   for(pushd(v); top --; pushd(st[top])) ;
   for(; ~ dir(u); rotate(u)) if(~ dir(fa[u]))
      rotate(dir(u) == dir(fa[u]) ? fa[u] : u);
}
void access(int u) {
   for(int v = 0; u; v = u, u = fa[u]) {
      splay(u); ch[u][1] = v;
   }
}
void mkroot(int u) {
   access(u); splay(u); rev[u] ^= 1;
}
void link(int u, int v) {
   if(u == v) return ;
   mkroot(u);
   if(!fa[u]) fa[u] = v;
}
void cut(int u, int v) {
   if(u == v) return ;
   mkroot(u); access(v); splay(v);
   if(ch[v][0] == u) {
      ch[v][0] = fa[u] = 0;
   }
}
void split(int u, int v) {
   mkroot(u); access(v); splay(u);
}
bool query(int u, int v) {
   mkroot(u); access(v); splay(v); return fa[u] > 0;
}

}
int main() {
   srand(time(0));
   scanf("%d%d", &n, &m);
   rep(i, 1, 10) scanf("%*d");
   rep(i, 1, m) scanf("%d%d", &e[i].fs, &e[i].sc), p[i] = i;
   rep(T, 1, 1) {
      rep(i, 1, n) nxt[i] = pre[i] = 0;
      int cnt = 0;
      rep(T2, 1, 10000000) {
         random_shuffle(p + 1, p + m + 1);
         rep(i, 1, m) {
            pair<int, int> E = e[p[i]];
            if(LCT::query(E.fs, E.sc)) { continue ; }
            if(!nxt[E.fs] && !pre[E.sc]) {
               cnt ++; nxt[E.fs] = E.sc; pre[E.sc] = E.fs;
               LCT::link(E.fs, E.sc);
               debug(cnt);
               if(cnt == n - 1) {
                  print(); exit(0);
               }
               continue ;
            }
            if(ran(rd)) continue ; 
            if(!nxt[E.fs] && pre[E.sc]) {
               nxt[pre[E.sc]] = 0;
               LCT::cut(pre[E.sc], E.sc);
               pre[E.sc] = E.fs;
               nxt[E.fs] = E.sc;
               LCT::link(E.fs, E.sc);
            } else if(nxt[E.fs] && !pre[E.sc]) {
               pre[nxt[E.fs]] = 0;
               LCT::cut(E.fs, nxt[E.fs]);
               nxt[E.fs] = E.sc;
               pre[E.sc] = E.fs;
               LCT::link(E.fs, E.sc);
            }
         }
      }
   }
   return 0;
}