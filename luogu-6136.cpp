#include <algorithm>
#include <random>
#include <cstdio>
#include <ctime>
using namespace std;
const int N = 2e6 + 10;
mt19937 rd(time(0));
static char buf[1 << 17], *S = buf, *T = buf;
char gc() {
   if(S == T) {
      T = (S = buf) + fread(buf, 1, 1 << 17, stdin);
      if(S == T) return EOF;
   }
   return *S ++;
}
int read() {
   int x = 0; char c = gc();
   for(; c < '0' || c > '9'; c = gc()) ;
   for(; c >= '0' && c <= '9'; c = gc())
      x = x * 10 + (c & 15);
   return x;
}
struct fhq_treap {

int rt, id, rnd[N], w[N], ch[N][2], sz[N];
void init() { rt = id = 0; }
void upd(int u) {
   sz[u] = sz[ch[u][0]] + sz[ch[u][1]] + 1;
}
int newnode(int val) {
   id ++; ch[id][0] = ch[id][1] = 0;
   w[id] = val; rnd[id] = rd(); sz[id] = 1;
   return id;
}
int merge(int u, int v) {
   if(!u || !v) return u | v;
   if(rnd[u] < rnd[v]) {
      ch[u][1] = merge(ch[u][1], v);
      return upd(u), u;
   }
   ch[v][0] = merge(u, ch[v][0]);
   return upd(v), v;
}
void split(int u, int val, int &l, int &r) {
   if(!u) { l = r = 0; return ; }
   if(w[u] <= val) {
      l = u; split(ch[u][1], val, ch[u][1], r); upd(l);
   } else {
      r = u; split(ch[u][0], val, l, ch[u][0]); upd(r);
   }
}
void insert(int val) {
   int l, r; split(rt, val, l, r);
   rt = merge(merge(l, newnode(val)), r);
}
void remove(int val) {
   int l, l2, r;
   split(rt, val, l, r);
   split(l, val - 1, l, l2);
   rt = merge(merge(l, merge(ch[l2][0], ch[l2][1])), r);
}
int rnk(int val) {
   int l, r; split(rt, val - 1, l, r);
   int res = sz[l] + 1; rt = merge(l, r);
   return res;
}
int kth(int k, int st = 0) {
   int u = st ? st : rt;
   while(1) {
      if(k <= sz[ch[u][0]]) u = ch[u][0];
      else {
         k -= sz[ch[u][0]] + 1;
         if(k <= 0) break ;
         u = ch[u][1];
      }
   }
   return w[u];
}
int pre(int val) {
   int l, r; split(rt, val - 1, l, r);
   int res = kth(sz[l], l); rt = merge(l, r);
   return res;
}
int nxt(int val) {
   int l, r; split(rt, val, l, r);
   int res = kth(1, r); rt = merge(l, r);
   return res;
}

} t;
int main() {
   t.init();
   int n = read(), test = read();
   for(int i = 1; i <= n; i ++) {
      t.insert(read());
   }
   int ans = 0;
   for(int op, x, la = 0; test --; ) {
      op = read(); x = la ^ read();
      if(op == 1) t.insert(x);
      if(op == 2) t.remove(x);
      if(op == 3) la = t.rnk(x);
      if(op == 4) la = t.kth(x);
      if(op == 5) la = t.pre(x);
      if(op == 6) la = t.nxt(x);
      if(op >= 3) ans ^= la;
   }
   printf("%d\n", ans);
   return 0;
}