#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef double db;
const int N = 2e5 + 10;

const db eps = 1e-9;
#define lt(x, y) ((x) < (y) - eps)
#define gt(x, y) ((x) > (y) + eps)
#define leq(x, y) ((x) <= (y) + eps)
#define geq(x, y) ((x) >= (y) - eps)
#define eq(x, y) (leq(x, y) && geq(x, y))
#define cross(u, v, w) ((v - u).det(w - u))
struct point {
  db x, y;
  void in_int() { int a, b; scanf("%d%d", &a, &b); x = a; y = b; }
  db norm() { return sqrt(x * x + y * y); }
  db norm2() { return x * x + y * y; }
  point operator + (point b) { return (point) {x + b.x, y + b.y}; }
  point operator - (point b) const { return (point) {x - b.x, y - b.y}; }
  point operator - () const { return (point) {-x, -y}; }
  void operator += (point b) { *this = *this + b; }
  void operator -= (point b) { *this = *this - b; }
  db operator * (point b) { return x * b.x + y * b.y; }
  point operator * (db b) { return (point) {x * b, y * b}; }
  point operator / (db b) { return (point) {x / b, y / b}; }
  db det(point b) { return x * b.y - y * b.x; }
  bool operator < (point b) { return lt(x, b.x) || (leq(x, b.x) && lt(y, b.y)); }
  bool operator == (point b) { return eq(x, b.x) && eq(y, b.y); }
};
struct line {
  point u, v, w;
  point vec() const { return v - u; }
} L[N];
bool operator < (line a, line b) {
  point u = a.vec(), v = b.vec();
  if(lt(u.y, 0) ^ lt(v.y, 0)) return lt(u.y, 0);
  if(gt(u.det(v), 0)) return 1;
  return eq(u.det(v), 0) && gt(u.x, 0) && lt(v.x, 0);
}
int n, tot;
multiset<line> S;
point intersect(line a, line b) {
  a.v -= a.u; b.v -= b.u;
  db k = b.v.det(a.u - b.u) / a.v.det(b.v);
  return a.u + a.v * k;
}
bool check(line a, line b) { //a -> b
  point u = a.vec(), v = b.vec();
  return lt(u.det(v), 0) || (eq(u.det(v), 0) && lt(u * v, 0));
}
void ins(line a) {
  S.insert(a);
  auto it = S.lower_bound(a), itl = it, itr = it; itr ++;
  if(itl != S.begin()) {
    itl --;
    if(itr != S.end()) {
      tot -= check(*itl, *itr);
    }
    tot += check(*itl, a);
  }
  if(itr != S.end()) {
    tot += check(a, *itr);
  }
}
void del(line a) {
  auto it = S.lower_bound(a), itl = it, itr = it; itr ++;
  if(itl != S.begin()) {
    itl --;
    if(itr != S.end()) {
      tot += check(*itl, *itr);
    }
    tot -= check(*itl, a);
  }
  if(itr != S.end()) {
    tot -= check(a, *itr);
  }
  S.erase(it);
}
bool check() {
  return tot == 0 && !check(*--S.end(), *S.begin());
}
int main() {
  scanf("%d", &n);
  rep(i, 1, n + 1) {
    L[i].u.in_int();
    L[i].v.in_int();
  }
  rep(i, 1, n) L[i].w = intersect(L[n + 1], L[i]);
  sort(L + 1, L + n + 1, [&](line a, line b) {
    return lt(a.w.x, b.w.x);
  });
  point P = (L[1].w + L[2].w) * 0.5;
  rep(i, 1, n) {
    if(lt((L[i].v - L[i].u).det(P - L[i].u), 0)) {
      swap(L[i].u, L[i].v);
    }
    ins(L[i]);
  }
  putchar('0'); putchar('0' ^ check());
  rep(i, 2, n - 1) {
    del(L[i]);
    swap(L[i].u, L[i].v);
    ins(L[i]);
    // for(auto it = S.begin(); it != S.end(); it ++) {
      // printf("vec = (%.1f, %.1f)\n", it->vec().x, it->vec().y);
    // }
    // printf("i = %d, tot = %d\n", i, tot);
    putchar('0' ^ check());
  }
  putchar('0');
  putchar('\n');
  return 0;
} 