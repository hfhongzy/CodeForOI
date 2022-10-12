#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
char s[N];
int n, m, p;
namespace task {
bool ok[16];
ll c[N], s[N];
void main() {
  if(p == 2) ok[0] = ok[2] = ok[4] = ok[6] = ok[8] = 1;
  if(p == 5) ok[0] = ok[5] = 1;
  rep(i, 1, n) {
    c[i] = c[i - 1] + ok[::s[i]];
    s[i] = s[i - 1] + (ok[::s[i]] ? i : 0);
  }
  int l, r;
  rep(i, 1, m) {
    scanf("%d%d", &l, &r);
    printf("%lld\n", s[r] - s[l - 1] - (c[r] - c[l - 1]) * (l - 1));
  }
}
}
int a[N], num[N], B, cnt[N], pw[N];
ll ans[N], cur;
struct node {
  int l, r, id;
  bool operator < (const node &b) const {
    return l / B == b.l / B ? (l / B & 1 ? r > b.r : r < b.r) : l < b.l;
  }
} qs[N];
void add(int x) { cur += cnt[a[x]] ++; }
void del(int x) { cur -= -- cnt[a[x]]; }
int main() {
  scanf("%d%s%d", &p, s + 1, &m);
  n = strlen(s + 1);
  rep(i, 1, n) s[i] &= 15;
  if(p == 2 || p == 5) return task::main(), 0;
  pw[0] = 1;
  rep(i, 1, n) pw[i] = pw[i - 1] * 10ll % p;
  per(i, n, 1) a[i] = (a[i + 1] + (ll)pw[n - i] * s[i]) % p, num[i] = a[i];
  sort(num + 1, num + n + 2);
  rep(i, 1, n + 1) a[i] = lower_bound(num + 1, num + n + 2, a[i]) - num;
  B = max(1.0, n / sqrt(m ? m : 1));
  rep(i, 1, m) {
    scanf("%d%d", &qs[i].l, &qs[i].r);
    qs[i].r ++;
    qs[i].id = i;
  }
  sort(qs + 1, qs + m + 1);
  int l = qs[1].l, r = l - 1;
  rep(i, 1, m) {
    while(l > qs[i].l) add(-- l);
    while(r < qs[i].r) add(++ r);
    while(l < qs[i].l) del(l ++);
    while(r > qs[i].r) del(r --);
    ans[qs[i].id] = cur;
  }
  rep(i, 1, m)
    printf("%lld\n", ans[i]);
  return 0;
}