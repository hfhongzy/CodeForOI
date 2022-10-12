#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
const int N = 1e4 + 10;
struct Node {
   int y, l, r, op;
   bool operator < (const Node &b) const {
      return y < b.y;
   }
};
vector<Node> vec;
int q, num[N * 2], tag[N * 8], sum[N * 8];
void modify(int u, int l, int r, int ql, int qr, int v) {
   if(l == ql && r == qr) {
      tag[u] += v;
      sum[u] = tag[u] ? num[r + 1] - num[l] : (l == r ? 0 : sum[u << 1] + sum[u << 1 | 1]);
      return ;
   }
   int mid = (l + r) >> 1;
   if(qr <= mid) modify(u << 1, l, mid, ql, qr, v);
   else if(ql > mid) modify(u << 1 | 1, mid + 1, r, ql, qr, v);
   else {
      modify(u << 1, l, mid, ql, mid, v);
      modify(u << 1 | 1, mid + 1, r, mid + 1, qr, v);
   }
   sum[u] = tag[u] ? num[r + 1] - num[l] : sum[u << 1] + sum[u << 1 | 1];
}
int main() {
   scanf("%d", &q);
   int x1, y1, x2, y2;
   rep(i, 1, q) {
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      if(x1 > x2) swap(x1, x2);
      if(y1 > y2) swap(y1, y2);
      if(x1 == x2) x1 --, x2 ++;
      else y1 --, y2 ++;
      vec.pb((Node) {y1, x1, x2, 1});
      vec.pb((Node) {y2, x1, x2, -1});
      num[2 * i - 1] = x1; num[2 * i] = x2;
   }
   sort(num + 1, num + 2 * q + 1);
   *num = unique(num + 1, num + 2 * q + 1) - num - 1;
   for(int i = 0; i < 2 * q; i += 2) {
      vec[i].l = vec[i + 1].l = lower_bound(num + 1, num + *num + 1, vec[i].l) - num;
      vec[i].r = vec[i + 1].r = lower_bound(num + 1, num + *num + 1, vec[i].r) - num;
   }
   sort(vec.begin(), vec.end());
   ll ans = 0;
   for(int i = 0; i < (int) vec.size(); i ++) {
      if(i) ans += (ll) (vec[i].y - vec[i - 1].y) * sum[1];
      modify(1, 1, *num - 1, vec[i].l, vec[i].r - 1, vec[i].op);
   }
   printf("%lld\n", ans);
   return 0;
}