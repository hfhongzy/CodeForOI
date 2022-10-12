#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e7 + 10;
char gc() {
   static char buf[1 << 15], *S, *T;
   if(S == T) T = (S = buf) + fread(buf, 1, 1 << 15, stdin);
   return S == T ? EOF : *S ++;
}
template<class T>
void read(T &x) {
   x = 0; bool na = 0; char c = gc();
   for(; c < '0' || c > '9'; c = gc()) na |= c == '-';
   for(; c >= '0' && c <= '9'; c = gc())
      x = x * 10 + (c & 15);
   if(na) x = -x;
}
int n, p[N], top, st[N], ch[N][2];

int main() {
   read(n);
   rep(i, 1, n) read(p[i]);
   rep(i, 1, n) {
      while(top && p[st[top]] > p[i]) {
         ch[i][0] = st[top --];
      }
      if(top) ch[st[top]][1] = i;
      st[++ top] = i;
   }
   ll al = 0, ar = 0;
   rep(i, 1, n) al ^= i * (ch[i][0] + 1ll), ar ^= i * (ch[i][1] + 1ll);
   printf("%lld %lld\n", al, ar);
   return 0;
}