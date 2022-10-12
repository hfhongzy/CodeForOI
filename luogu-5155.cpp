#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, top, st[N];
ll v[N], f[N];
__int128 cross(int x, int y, int z) {
  return (y - x) * (__int128)(v[z] - v[x]) - (z - x) * (__int128)(v[y] - v[x]);
}
void write(ll x) {
  if(x <= 9) { putchar('0' + x); return ; }
  write(x / 10);
  putchar('0' + x % 10);
}
int main() {
  scanf("%d", &n);
  rep(i, 1, n) scanf("%lld", v + i), v[i] *= 100000;
  st[top = 1] = 0;
  rep(i, 1, n + 1) {
    while(top >= 2 && cross(st[top - 1], st[top], i) >= 0) -- top;
    st[++ top] = i;
  }
  int p = 1;
  rep(i, 1, n) {
    while(st[p + 1] <= i) ++ p;
    if(st[p] == i) f[i] = v[i];
    else {
      f[i] = (v[st[p + 1]] * (i - st[p]) + v[st[p]] * (st[p + 1] - i)) / (st[p + 1] - st[p]);
    }
  }
  rep(i, 1, n) {
    write(f[i]); putchar('\n');
  }
  return 0;
}