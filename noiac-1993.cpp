#include <algorithm>
#include <cstdio>
#include <queue>
#include <set>
#define rep(i, j, k) for(int i = j, _k = k; i <= _k; ++ i)
#define per(i, j, k) for(int i = j, _k = k; i >= _k; -- i)
using namespace std;
const int N = 1e6 + 10;
int n, k, q, a[N];
namespace subtask {

int ans, f[N];
void solve(int l, int r) {
   if(l == r) return ;
   int mid = (l + r) >> 1;
   solve(l, mid); solve(mid + 1, r);
   rep(i, 1, min(k - 1, r - mid)) f[i] = i == 1 ? a[mid + 1] : max(f[i - 1], a[mid + i]);
   rep(i, 1, min(k - 1, mid - l + 1)) {
      ans = max(ans, a[mid - i + 1] + f[min(r - mid, k - i)]);
   }
}
void main() {
   ans = 0; solve(1, n); printf("%d\n", ans);
}

}
namespace sol {

int qu[N], qv[N], ans1;
bool use[N];
void solve1() {
   deque<int> Q;
   rep(i, 1, n) if(!use[i]) {
      while(Q.size() && i - Q.front() >= k) {
         Q.pop_front();
      }
      if(Q.size()) ans1 = max(ans1, a[i] + a[Q.front()]);
      while(Q.size() && a[Q.back()] <= a[i]) {
         Q.pop_back();
      }
      Q.push_back(i);
   }
}
multiset<int> S[N * 4];
int mx[N * 4], val[N * 4], ans[N * 4];
void calc(int u) {
   val[u] = S[u].empty() ? 0 : (* --S[u].end() + mx[u]);
}
void upd(int u) {
   ans[u] = max(val[u], max(ans[u << 1], ans[u << 1 | 1]));
}
bool upd2(int u) {
   int p = mx[u];
   mx[u] = max(mx[u << 1], mx[u << 1 | 1]);
   return p != mx[u];
}
void build(int u, int l, int r) {
   if(l == r) { mx[u] = a[l]; return ; }
   int mid = (l + r) >> 1;
   build(u << 1, l, mid);
   build(u << 1 | 1, mid + 1, r);
   upd2(u); ans[u] = 0;
}
void modify(int u, int l, int r, int ql, int qr, int pre, int val) { //pre = -1
   if(l == ql && r == qr) {
      if(~ pre) S[u].erase(S[u].lower_bound(pre));
      S[u].insert(val);
      calc(u); upd(u);
      return ;
   }
   int mid = (l + r) >> 1;
   if(qr <= mid) modify(u << 1, l, mid, ql, qr, pre, val);
   else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, pre, val);
   else {
      modify(u << 1, l, mid, ql, mid, pre, val);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr, pre, val);
   }
   upd(u);
}
void modify(int u, int l, int r, int p, int val) { //pre = -1
   if(l == r) { mx[u] = val; calc(u); upd(u); return ; }
   int mid = (l + r) >> 1;
   if(p <= mid) modify(u << 1, l, mid, p, val);
   else modify(u << 1 | 1, mid + 1, r, p, val);
   if(upd2(u)) calc(u);
   upd(u);
}
void main() {
   rep(i, 1, q) {
      scanf("%d%d", qu + i, qv + i); use[qu[i]] = 1;
   }
   solve1();
   build(1, 1, n);
   rep(i, 1, n) if(use[i]) {
      if(i > 1) modify(1, 1, n, max(1, i - (k - 1)), i - 1, -1, a[i]);
      if(i < n) modify(1, 1, n, i + 1, min(n, i + (k - 1)), -1, a[i]);
   }
   printf("%d\n", max(ans[1], ans1));
   rep(i, 1, q) {
      int x = qu[i], y = qv[i];
      if(x > 1) modify(1, 1, n, max(1, x - (k - 1)), x - 1, a[x], y);
      if(x < n) modify(1, 1, n, x + 1, min(n, x + (k - 1)), a[x], y);
      a[x] = y; modify(1, 1, n, x, y);
      printf("%d\n", max(ans[1], ans1));
   }
}

}
int main() {
   scanf("%d%d%d", &n, &k, &q);
   rep(i, 1, n) scanf("%d", a + i);
   if(q == 0) subtask::main();
   else sol::main();
   return 0;
}