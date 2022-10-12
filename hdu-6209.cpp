#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef long long ll;
typedef long double db;
const int LIM = 1e5;
int test, k;
int main() {
  scanf("%d", &test);
  while(test --) {
    scanf("%d", &k);
    db v = pow((db)k, (db)2.0 / 3);
    ll la = (ll)floor(v), lb = 1, ra = (ll)ceil(v), rb = 1;
    while(lb + rb <= LIM) {
      if(la + ra < v * (lb + rb)) {
        int l = 1, r = (LIM - lb) / rb, x = 1;
        while(l <= r) {
          int mid = (l + r) >> 1;
          if(la + mid * ra < v * (lb + mid * rb)) l = (x = mid) + 1;
          else r = mid - 1;
        }
        la += x * ra;
        lb += x * rb;
      } else {
        int l = 1, r = (LIM - rb) / lb, x = 1;
        while(l <= r) {
          int mid = (l + r) >> 1;
          if(ra + mid * la > v * (rb + mid * lb)) l = (x = mid) + 1;
          else r = mid - 1;
        }
        ra += x * la;
        rb += x * lb;
      }
    }
    if(2 * v * lb * rb > la * rb + ra * lb) {
      swap(la, ra); swap(lb, rb);
    }
    printf("%lld/%lld\n", la, lb);
  }
  return 0;
}