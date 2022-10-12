#include <algorithm>
#include <vector>
#include <cstdio>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;
typedef double db;

const int N = 2000 + 10;

struct point {
   db x, y;
   db size() { return x * x + y * y; }
   bool operator < (const point &b) const { return x < b.x || (x == b.x && y < b.y); }
   point operator - (const point &b) { return (point) {x - b.x, y - b.y}; }
   db operator * (const point &b) { return x * b.y - y * b.x; }
} a[N], st[N];
int n, top;
db t[N];
void convex() {
   sort(a + 1, a + n + 1);
   st[top = 1] = a[1];
   rep(i, 2, n) {
      while(top >= 2 && (a[i] - st[top - 1]) * (st[top] - st[top - 1]) <= 0) top --;
      st[++ top] = a[i];
   }
   int z = top - 1;
   per(i, n - 1, 1) {
      while(top - z >= 2 && (st[top] - a[i]) * (st[top - 1] - a[i]) <= 0) top --;
      st[++ top] = a[i];
   }
   top --;
}
int main() {
   scanf("%d", &n);
   rep(i, 1, n) scanf("%lf%lf", &a[i].x, &a[i].y);
   convex();
   db ans = 0;
   if((n = top) <= 2) goto output;
   st[n + 1] = st[1]; st[0] = st[n];
   rep(u, 1, n) {
      int j = u == n ? 1 : u + 1;
      rep(i, 2, n - 2) {
         int v = (u + i - 1) % n + 1;
         while((st[v] - st[u]) * (st[j] - st[u]) < (st[v] - st[u]) * (st[j + 1] - st[u])) {
            j = j == n ? 1 : j + 1;
         }
         t[i] = (st[v] - st[u]) * (st[j] - st[u]);
      }
      j = u == 1 ? n : u - 1;
      per(i, n - 2, 2) {
         int v = (u + i - 1) % n + 1;
         while((st[j] - st[u]) * (st[v] - st[u]) < (st[j - 1] - st[u]) * (st[v] - st[u])) {
            j = j == 1 ? n : j - 1;
         }
         ans = max(ans, t[i] + (st[j] - st[u]) * (st[v] - st[u]));
      }
   }
   output:
   printf("%.3f\n", ans / 2.0);
   return 0;
}