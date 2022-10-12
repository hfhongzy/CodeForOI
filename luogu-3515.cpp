#include <algorithm>
#include <cstdio>
#include <cmath>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 5e5 + 10;
int n, a[N], arr[N];
db ans1[N], ans2[N];
#define F(x, y) arr[y] + sqrt(x - y)
int great(int x, int y) { //y 比 x 优秀的最早时间
   if(F(n, x) > F(n, y)) return N;
   if(F(y, x) < F(y, y)) return y;
   int l = y, r = n, ans = N;
   while(l <= r) {
      int mid = (l + r) >> 1;
      if(F(mid, x) < F(mid, y)) r = (ans = mid) - 1;
      else l = mid + 1;
   }
   return ans;
}
void work(db *ans) {
   static int q[N], g[N]; //g[x] 表示 q[x] 强于 q[x - 1] 的时间
   int ql = 0, qr = 0;
   rep(i, 1, n) {
      while(qr - ql > 1 && g[ql + 1] < i) ql ++;
      if(ql < qr) ans[i] = F(i, q[ql]);
      // printf("%d!\n", q[ql]);
      while(ql < qr && g[qr - 1] > great(q[qr - 1], i)) qr --;
      q[qr ++] = i;
      if(qr - ql > 1) g[qr - 1] = great(q[qr - 2], i);
   }
}
int main() {
   scanf("%d", &n);
   rep(i, 1, n) scanf("%d", a + i);
   rep(i, 1, n) arr[i] = a[i];
   work(ans1);
   rep(i, 1, n) arr[i] = a[n - i + 1];
   work(ans2);
   rep(i, 1, n) {
      printf("%d\n", max(0, (int) ceil( max(ans1[i], ans2[n - i + 1]) ) - a[i]));
   }
   return 0;
}
