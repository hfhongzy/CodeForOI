#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
const int N = 1e4 + 10;
int ty[N], n;
vector<double> G[2];
int main() {
   int t; scanf("%d", &t);
   while(t --) {
      scanf("%d", &n);
      for(int i = 1; i <= n; i ++) scanf("%d", ty + i);
      G[0].clear(); G[1].clear();
      for(int i = 1; i <= n; i ++) {
         double x; scanf("%lf", &x);
         G[ty[i]].push_back(x);
      }
      sort(G[0].begin(), G[0].end());
      sort(G[1].begin(), G[1].end());
      for(int i = 0; i < (int) G[0].size(); i ++)
         cout << G[0][i] << ' ';
      puts("");
      for(int i = 0; i < (int) G[1].size(); i ++)
         cout << G[1][i] << ' ';
      puts("");
   }
   return 0;
}