#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
struct Heap {
   int a[N], sz;
   Heap() { sz = 0; }
   void push(int x) {
      a[++ sz] = x;
      for(int u = sz; u > 1 && a[u] < a[u >> 1]; u >>= 1) {
         swap(a[u], a[u >> 1]);
      }
   }
   int top() { return a[1]; }
   void pop() {
      a[1] = a[sz --];
      for(int v, u = 1; u * 2 <= sz; u = v) {
         v = u * 2 + 1 > sz ? u * 2 : (a[u * 2] < a[u * 2 + 1] ? u * 2 : u * 2 + 1);
         if(a[u] <= a[v]) break ;
         swap(a[u], a[v]);
      }
   }
} q;
int n;
int main() {
   scanf("%d", &n);
   for(int i = 1; i <= n; i ++) {
      int op, x; scanf("%d", &op);
      if(op == 1 && ~ scanf("%d", &x)) q.push(x);
      if(op == 2) printf("%d\n", q.top());
      if(op == 3) q.pop();
   }
   return 0;
}