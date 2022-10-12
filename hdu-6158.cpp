#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
typedef double db;
const db eps = 1e-12;
const db pi = acos(-1.0);
db r1, r2;
int n;
int main() {
  int test;
  scanf("%d", &test);
  while(test --) {
    scanf("%lf%lf%d", &r1, &r2, &n);
    if(r1 > r2) swap(r1, r2);
    db x1 = 1 / (2.0 * r2), x2 = 1 / (2.0 * r1);
    db x = (x1 + x2) / 2, r = (x2 - x1) / 2, y = 0;
    db ans = 0, tmp = 0;
    for(int i = 1; i <= n; i ++) {
      if(i % 2 == 0) {
        y += 2 * r;
      }
      db d = sqrt(x * x + y * y);
      tmp = pow(r / ((d + r) * (d - r)), 2);
      if(tmp * pi < eps) break ;
      ans += tmp;
    }
    ans *= pi;
    printf("%.5f\n", ans);
  }
  return 0;
}