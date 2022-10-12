#include <bits/stdc++.h>
#define fs first
#define sc second
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef pair<int, int> pii;
char gc() {
   static char buf[1 << 17], *S, *T;
   if(S == T) T = (S = buf) + fread(buf, 1, 1 << 17, stdin);
   return S == T ? EOF : *S ++;
}
template<class T> void read(T &x) {
   x = 0; char c = gc(); bool na = 0;
   for(; c < '0' || c > '9'; c = gc()) na |= c == '-';
   for(; c >= '0' && c <= '9'; c = gc()) x = x * 10 + (c & 15);
   if(na) x = -x;
}
const int N = 1e5 + 10;
const int S = 545;
const int C = N / S + 10;
int n, m, vl, vr, tag[C], p[N];
pii a[N], t1[N], t2[N];
void build(int id) {
   int Bl = id * S, Br = min(n, Bl + S - 1);
   sort(a + Bl, a + Br + 1);
}
void addB(int l, int r, int k) { //border
   int Bl = l / S * S, Br = min(n, Bl + S - 1);
   int n1 = 0, n2 = 0;
   rep(i, Bl, Br) {
      a[i].fs += tag[l / S];
      if(l <= a[i].sc && a[i].sc <= r) {
         a[i].fs += k; t1[++ n1] = a[i];
      } else t2[++ n2] = a[i];
      p[a[i].sc] = a[i].fs;
   }
   tag[l / S] = 0;
   merge(t1 + 1, t1 + n1 + 1, t2 + 1, t2 + n2 + 1, a + Bl);
}
void add(int l, int r, int k) {
   if(l / S == r / S) { addB(l, r, k); return ; }
   addB(l, l / S * S + S - 1, k);
   addB(r / S * S, r, k);
   rep(i, l / S + 1, r / S - 1) tag[i] += k;
}
int calcB(int l, int r, int k) {
   int c = 0; k -= tag[l / S];
   rep(i, l, r) if(p[i] < k) c ++;
   return c;
}
int calc(int l, int r, int k) { //count < k
   if(l / S == r / S) return calcB(l, r, k);
   int c = calcB(l, l / S * S + S - 1, k) + calcB(r / S * S, r, k);
   rep(i, l / S + 1, r / S - 1) {
      int ql = i * S, qr = ql + S - 1;
      if(a[ql].fs + tag[i] >= k) { continue ; }
      if(a[qr].fs + tag[i] < k) { c += S; continue ; }
      while(ql <= qr) {
         int mid = (ql + qr) >> 1;
         if(a[mid].fs + tag[i] < k) ql = mid + 1;
         else qr = mid - 1;
      }
      c += ql - i * S;
   }
   return c;
}

int query(int l, int r, int k) {
   int ql = vl, qr = vr, mid, ans;
   while(ql <= qr) {
      mid = (0ll + ql + qr) >> 1;
      if(calc(l, r, mid) < k) ql = (ans = mid) + 1;
      else qr = mid - 1;
   }
   return ans;
}
int main() {
   read(n); read(m); a[0] = pii(p[0] = -2147483640, 0);
   rep(i, 1, n) read(p[i]), a[i] = pii(p[i], i);
   vl = *min_element(p + 1, p + n + 1);
   vr = *max_element(p + 1, p + n + 1);
   for(int i = 0; i * S <= n; i ++) build(i);
   int op, l, r, k;
   rep(i, 1, m) {
      read(op); read(l); read(r); read(k);
      if(op == 1) printf("%d\n", k <= r - l + 1 ? query(l, r, k) : -1);
      if(op == 2) { k < 0 ? vl += k : vr += k; add(l, r, k); }
   }
   return 0;
}