#include <algorithm>
#include <cstring>
#include <cstdio>
#define pii pair<int, int>
#define fs first
#define sc second
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
typedef long long ll;
using namespace std;
const int N = 2e5 + 10, NN = N * 30, MM = N * 100;
int n, sa[N], rk[N], cnt[N], t[N];
int h[N], lg[N], st[N][20];
char s[N];
void build() {
   int c = *max_element(s + 1, s + n + 1);
   fill(cnt + 1, cnt + c + 1, 0);
   rep(i, 1, n) cnt[rk[i] = s[i]] ++;
   rep(i, 1, c) cnt[i] += cnt[i - 1];
   rep(i, 1, n) sa[cnt[s[i]] --] = i;
   for(int num = 0, k = 1; k <= n; k <<= 1, c = num, num = 0) {
      rep(i, n - k + 1, n) t[++ num] = i;
      rep(i, 1, n) if(sa[i] > k) t[++ num] = sa[i] - k;
      fill(cnt + 1, cnt + c + 1, 0);
      rep(i, 1, n) cnt[rk[i]] ++;
      rep(i, 1, c) cnt[i] += cnt[i - 1];
      per(i, n, 1) sa[cnt[rk[t[i]]] --] = t[i];
      copy(rk + 1, rk + n + 1, t + 1); rk[sa[1]] = num = 1;
      rep(i, 2, n) {
         int u = sa[i - 1] + k <= n ? t[sa[i - 1] + k] : 0;
         int v = sa[i] + k <= n ? t[sa[i] + k] : 0;
         if(!(t[sa[i - 1]] == t[sa[i]] && u == v)) ++ num;
         rk[sa[i]] = num;
      }
      if(num == n) break ;
   }
   int k = 0;
   rep(i, 1, n) {
      if(rk[i] == 1) { h[1] = k = 0; continue ; }
      if(k) k --;
      int u = sa[rk[i] - 1];
      for(; i + k <= n && u + k <= n && s[i + k] == s[u + k]; k ++) ;
      h[rk[i]] = k;
   }
   lg[1] = 0;
   rep(i, 2, n) lg[i] = lg[i >> 1] + 1;
   rep(i, 1, n) st[i][0] = h[i];
   rep(j, 1, lg[n]) rep(i, 1, n - (1 << j) + 1)
      st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
}
int lcp(int x, int y) {
   if(x == y) return n - sa[x] + 1;
   x ++; int k = lg[y - x + 1];
   return min(st[x][k], st[y - (1 << k) + 1][k]);
}
pii search(int x, int len) {
   int l = 1, r = x, mid; pii ans(0, 0);
   while(l <= r) {
      mid = (l + r) >> 1;
      if(lcp(mid, x) >= len) r = (ans.fs = mid) - 1;
      else l = mid + 1;
   }
   l = x; r = n;
   while(l <= r) {
      mid = (l + r) >> 1;
      if(lcp(x, mid) >= len) l = (ans.sc = mid) + 1;
      else r = mid - 1;
   }
   return ans;
}

struct Edge { int v, nxt; } e[MM];
int na, nb, rt[N], Naid[N], Nbid[N], NaL[N], NbL[N];
int m, ec, hd[NN], idx, ls[NN], rs[NN];
pii Na[N], Nb[N];

void clr(int n) { fill(hd + 1, hd + n + 1, -1); ec = 0; }
int app() { hd[idx + 1] = -1; return ++ idx; }
void add(int u, int v) { e[ec] = (Edge) {v, hd[u]}; hd[u] = ec ++; }

void update(int p, int &u, int l, int r, int x, int A) {
   u = app();
   if(p) add(u, p);
   if(l == r) { ls[u] = rs[u] = 0; add(u, A); return ; }
   int mid = (l + r) >> 1;
   if(x <= mid) rs[u] = rs[p], update(ls[p], ls[u], l, mid, x, A);
   else ls[u] = ls[p], update(rs[p], rs[u], mid + 1, r, x, A);
   if(ls[u]) add(u, ls[u]);
   if(rs[u]) add(u, rs[u]);
}
void addedge(int u, int l, int r, int ql, int qr, int from) {
   if(!u) return ;
   if(l == ql && r == qr) { add(from, u); return ; }
   int mid = (l + r) >> 1;
   if(qr <= mid) return addedge(ls[u], l, mid, ql, qr, from);
   if(ql > mid) return addedge(rs[u], mid + 1, r, ql, qr, from);
   addedge(ls[u], l, mid, ql, mid, from);
   addedge(rs[u], mid + 1, r, mid + 1, qr, from);
}
int deg[NN];
ll pa[NN];
ll solve() {
   fill(deg + 1, deg + idx + 1, 0);
   fill(pa + 1, pa + idx + 1, 0);
   rep(i, 0, ec - 1) deg[e[i].v] ++;
   static int q[NN]; int ql = 0, qr = 0;
   rep(i, 1, idx) if(!deg[i]) {
      q[qr ++] = i; pa[i] = (i <= na ? NaL[i] : 0);
   }
   int cnt = 0;
   while(ql < qr) {
      int u = q[ql ++]; cnt ++;
      for(int i = hd[u]; ~ i; i = e[i].nxt) {
         int v = e[i].v;
         pa[v] = max(pa[v], pa[u] + (v <= na ? NaL[v] : 0));
         if(! --deg[v]) {
            q[qr ++] = v;
         }
      }
   }
   return cnt == idx ? *max_element(pa + 1, pa + idx + 1) : -1;
}
bool cmpa(int x, int y) { return NaL[x] > NaL[y]; }
bool cmpb(int x, int y) { return NbL[x] > NbL[y]; }
int main() {
   int test; scanf("%d", &test);
   rep(T, 1, test) {
      scanf("%s", s + 1); n = strlen(s + 1); build();
      scanf("%d", &na);
      rep(i, 1, na) scanf("%d%d", &Na[i].fs, &Na[i].sc), Naid[i] = i, NaL[i] = Na[i].sc - Na[i].fs + 1;
      sort(Naid + 1, Naid + na + 1, cmpa);
      scanf("%d", &nb);
      rep(i, 1, nb) scanf("%d%d", &Nb[i].fs, &Nb[i].sc), Nbid[i] = i, NbL[i] = Nb[i].sc - Nb[i].fs + 1;
      sort(Nbid + 1, Nbid + nb + 1, cmpb);
      clr(idx = na + nb);
      scanf("%d", &m);
      rep(i, 1, m) { int u, v; scanf("%d%d", &u, &v); add(u, na + v); }
      int pos = 1; rt[0] = 0;
      rep(i, 1, nb) {
         int B = Nbid[i];
         for(; pos <= na && NaL[ Naid[pos] ] >= NbL[B]; ++ pos) {
            update(rt[pos - 1], rt[pos], 1, n, rk[ Na[ Naid[pos] ].fs ], Naid[pos]);
         }
         pii p = search(rk[Nb[B].fs], NbL[B]);
         addedge(rt[pos - 1], 1, n, p.fs, p.sc, na + B);
      }
      printf("%lld\n", solve());
   }
   return 0;
}