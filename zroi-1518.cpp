#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
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
const int N = 510;
int n, m, q, k1, k2, p[N];
int main() {
   read(n); read(m);
   int u, v;
   rep(i, 1, m) {
      read(u); read(v);
   }
   read(q);
   int cnt = 0;
   rep(i, 1, q) {
      read(k1);
      rep(j, 1, k1) {
         read(p[j]);
         p[j] = (p[j] + cnt - 1) % n + 1;
      }
      read(k2)
      rep(j, 1, k2) {
         read(s); read(t);
         s = (s + cnt - 1) % n + 1;
         t = (t + cnt - 1) % n + 1;
         int ans = 0;
         cnt += ans;
      }
   }
   return 0;
}