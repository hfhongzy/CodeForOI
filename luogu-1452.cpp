#include <algorithm>
#include <vector>
#include <cstdio>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;

typedef long long ll;

const int N = 5e4 + 10;

struct point {
   int x, y;
   int size() { return x * x + y * y; }
   bool operator < (const point &b) const { return x < b.x || (x == b.x && y < b.y); }
   point operator - (const point &b) { return (point) {x - b.x, y - b.y}; }
   int operator * (const point &b) { return x * b.y - y * b.x; }
} a[N], st[N];
int n, top;
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
   rep(i, 1, n) scanf("%d%d", &a[i].x, &a[i].y);
   convex();
   // printf("%d!\n", top);
   int ans = 0;
   if(top <= 3) {
      rep(i, 1, top) rep(j, i + 1, top) ans = max(ans, (st[i] - st[j]).size());
   } else {
      st[top + 1] = st[1];
      int j = 2;
      rep(i, 1, n) {
         while((st[i] - st[i + 1]) * (st[j] - st[i + 1]) < (st[i] - st[i + 1]) * (st[j + 1] - st[i + 1])) {
            j = j == top ? 1 : j + 1;
         }
         ans = max(ans, (st[i] - st[j]).size());
         ans = max(ans, (st[i + 1] - st[j]).size());
      }
   }
   printf("%d\n", ans);

   return 0;
}