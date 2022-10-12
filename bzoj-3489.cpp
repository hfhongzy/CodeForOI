#include <algorithm>
#include <cctype>
#include <cstdio>
using namespace std;
#define CI const int &
#define RI register int
#define Tp template <typename T>
class IO {
	private :
      static const int S = 1 << 21;
      #define tc() (A == B && (B = (A = Fin) + fread(Fin, 1, S, stdin), A == B) ? EOF : *A ++)
      #define pc(ch) (Ftop != Fend ? *Ftop++ = ch : (fwrite(Fout, 1, S, stdout), *(Ftop = Fout) ++ = ch))
      char Fin[S], Fout[S], *A, *B, *Ftop, *Fend; int pt[15];
	public :
      inline IO() { Ftop = Fout; Fend = Fout + S; }
      Tp inline void read(T &x) {
         x = 0; char ch; while(!isdigit(ch = tc()));
         while(x = x * 10 + (ch & 15), isdigit(ch = tc()));
      }
      Tp inline void write(T x) {
         RI ptop = 0; while(pt[++ ptop] = x % 10, x /= 10);
         while(ptop) pc(pt[ptop --] + 48); pc('\n');
      }
      inline void flush() {
         fwrite(Fout, 1, Ftop - Fout, stdout);
      }
     	#undef tc
      #undef pc
} io;
const int N = 1e5 + 5;
struct info { int w, val, x[3], xl[3], xr[3], ch[2]; } p[N];
int n, q, rt, cmpd;
bool operator < (const info &a, const info &b) {
	return a.x[cmpd] == b.x[cmpd] ? (a.x[(cmpd + 1) % 3] == b.x[(cmpd + 1) % 3] ? a.x[(cmpd + 2) % 3] == b.x[(cmpd + 2) % 3] : a.x[(cmpd + 1) % 3] < b.x[(cmpd + 1) % 3]) : a.x[cmpd] < b.x[cmpd];
}
void upd(int u, int v) {
	p[u].val = max(p[u].val, p[v].val);
	for(int i = 0; i < 3; i ++) {
		p[u].xl[i] = min(p[u].xl[i], p[v].xl[i]);
		p[u].xr[i] = max(p[u].xr[i], p[v].xr[i]);
	}
}
int build(int l, int r, int d = 0) {
	int u = (l + r) >> 1; cmpd = d;
	nth_element(p + l, p + u, p + r + 1); p[u].val = p[u].w;
	for(int i = 0; i < 3; i ++) p[u].xl[i] = p[u].xr[i] = p[u].x[i];
	if(l < u) upd(u, p[u].ch[0] = build(l, u - 1, (d + 1) % 3));
	if(u < r) upd(u, p[u].ch[1] = build(u + 1, r, (d + 1) % 3));
	return u;
}
//[0, l - 1] [l, r] [r + 1, n + 1]
int ql, qr, ans;
void query(int u) {
	if(u == 0 || p[u].val <= ans || ql - 1 < p[u].xl[0] || qr < p[u].xl[1] || ql - 1 > p[u].xr[1] || qr + 1 > p[u].xr[2]) return ;
	if(p[u].xr[0] < ql && ql <= p[u].xl[1] && p[u].xr[1] <= qr && qr < p[u].xl[2]) { ans = p[u].val; return ; }
	if(p[u].x[0] < ql && ql <= p[u].x[1] && p[u].x[1] <= qr && qr < p[u].x[2]) ans = max(ans, p[u].w);
	query(p[u].ch[0]); query(p[u].ch[1]);
}
int main() {
	freopen("input", "r", stdin);
	io.read(n); io.read(q);
	for(int i = 1; i <= n; i ++) p[i].x[2] = n + 1, p[i].x[1] = i;
	static int pos[N];
	for(int i = 1; i <= n; i ++) {
		io.read(p[i].w);
		p[i].x[0] = pos[p[i].w]; p[p[i].x[0]].x[2] = i; pos[p[i].w] = i;
	}
	rt = build(1, n);
	for(int l, r, i = 1; i <= q; i ++) {
		io.read(l); io.read(r);
		ql = (l + ans) % n + 1; qr = (r + ans) % n + 1;
		if(ql > qr) swap(ql, qr);
		ans = 0; query(rt); io.write(ans);
	}
	io.flush();
	return 0;
}