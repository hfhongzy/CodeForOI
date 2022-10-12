#include <algorithm>
#include <cstdio>
#include <cmath>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
int n, m, op;
db solve1() { return m == 1 ? n : (pow(m, n) - 1) / (m - 1); }
db solve2() {
   db ans = 0, t = 1;
   rep(i, 1, n) { t *= m / (m - i + 1.0); ans += t; }
   return ans;
}
int main() {
   for(int t; ~ scanf("%d", &t); ) {
      while(t --) {
         scanf("%d%d%d", &op, &m, &n);
         printf("%.8f\n", op == 0 ? solve1() : solve2());
      }
   }
   return 0;
}