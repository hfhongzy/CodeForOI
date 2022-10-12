#include <bits/stdc++.h>
#include "explore.h"
#define fs first
#define sc second
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
typedef unsigned long long ull;
typedef double db;
namespace task1 {

vector<ull> A, B;
vector<int> S;
void main(int n, int m) {
   rep(i, 1, m) S.pb(i);
   rep(i, 1, n) A.pb(1ll << i);
   B = Query(A, S);
   rep(i, 1, n) {
      rep(j, i + 1, n) if(B[i - 1] >> j & 1) {
         Report(i, j);
         if(! -- m) return ;
      }
   }
}

}
mt19937_64 rd(time(0));
uniform_int_distribution<ull> ran(0, (1ull << 63) - 1);
namespace task2 {

const int N = 5e4 + 20;
const int M = 3e5 + 10;

ull w[N];
vector<ull> A, B;
vector<int> S;
pair<ull, int> pa[N];
set< pair<int, int> > rp;
void report(int x, int y) {
   if(x == y) return ;
   if(x > y) swap(x, y);
   if(!rp.insert(make_pair(x, y)).sc) {
      return ;
   }
   Report(x, y);
}
void main(int n, int m) {
   srand(time(0));
   static int edge[M];
   rep(i, 1, m) edge[i] = i;
   A.clear();
   rep(i, 1, n) w[i] = ran(rd), A.pb(w[i]), pa[i] = make_pair(w[i], i);
   sort(pa + 1, pa + n + 1);
   rep(T, 1, 50) {
      int m0 = ran(rd) % m + 1;
      S.clear();
      random_shuffle(edge + 1, edge + m + 1);
      rep(i, 1, m0) S.pb(edge[i]);
      B = Query(A, S);
      queue<int> q;
      rep(i, 1, n) {
         pair<ull, int> p = *lower_bound(pa + 1, pa + n + 1, make_pair(B[i - 1], 0));
         if(p.fs == B[i - 1]) {
            report(p.sc, i);
            q.push(p.sc);
            B[p.sc - 1] ^= w[i];
            B[i - 1] ^= w[p.sc - 1];
         }
      }
      while(q.size()) {
         int u = q.front(); q.pop();
         pair<ull, int> p = *lower_bound(pa + 1, pa + n + 1, make_pair(B[u - 1], 0));
         if(p.fs == B[u - 1]) {
            report(p.sc, u);
            q.push(p.sc);
            B[p.sc - 1] ^= w[u];
            B[u - 1] ^= w[p.sc - 1];
         }
      }
   }
}

}
void Solve(int n, int m) {
   if(n == 20 || n == 60) task1::main(n, m);
   else task2::main(n, m);
}