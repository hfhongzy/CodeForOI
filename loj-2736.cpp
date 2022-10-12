#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int N = 4e5 + 10;
const int M = 666;
int n, m, q, sz, a[N], L[N], R[N], B[N];
priority_queue<int> pq[M]; //值域
priority_queue< int, vector<int>, greater<int> > ipq[M]; //插入的 A
void build(int u) { //求值域
   while(pq[u].size()) pq[u].pop();
   rep(i, L[u], R[u]) {
      pq[u].push(a[i]);
   }
}
void push(int u) { //用插入的 A 建立序列，需要暴力改的时候再 push
   if(!ipq[u].size()) return ;
   rep(i, L[u], R[u]) {
      int t = ipq[u].top();
      if(t < a[i]) {
         ipq[u].pop();
         ipq[u].push(a[i]);
         a[i] = t;
      }
   }
   while(ipq[u].size()) ipq[u].pop();
}
void modify(int l, int r, int &v) {
   if(B[l] == B[r]) {
      push(B[l]);
      rep(i, l, r) {
         if(a[i] > v) {
            swap(v, a[i]);
         }
      }
      build(B[l]);
      return ;
   }
   push(B[l]);
   rep(i, l, R[B[l]]) {
      if(a[i] > v) {
         swap(v, a[i]);
      }
   }
   build(B[l]);
   rep(i, B[l] + 1, B[r] - 1) {
      int t = pq[i].top();
      if(t <= v) continue ;
      pq[i].pop(); pq[i].push(v); ipq[i].push(v); v = t;
   }
   push(B[r]);
   rep(i, L[B[r]], r) {
      if(a[i] > v) {
         swap(v, a[i]);
      }
   }
   build(B[r]);
}
int main() {
   scanf("%d%d", &n, &q);
   for(sz = 1; sz * sz <= n; sz ++) ;
   rep(i, 1, n) {
      scanf("%d", a + i);
      B[i] = (i - 1) / sz + 1;
      if(!L[B[i]]) L[B[i]] = i;
      R[B[i]] = i;
   }
   m = B[n];
   rep(i, 1, m) build(i);
   int l, r, v;
   rep(i, 1, q) {
      scanf("%d%d%d", &l, &r, &v);
      if(l <= r) modify(l, r, v);
      else modify(l, n, v), modify(1, r, v);
      printf("%d\n", v);
   }
   return 0;
}