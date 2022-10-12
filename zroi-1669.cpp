#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int tr[5][24] = {
   {6, 7, 12, 13, 5, 11, 16, 17, 14, 8, 4, 10, 18, 19, 15, 9, 20, 21, 22, 23, 0, 1, 2, 3}, //up
   {1, 3, 0, 2, 23, 22, 4, 5, 6, 7, 21, 20, 10, 11, 12, 13, 18, 16, 19, 17, 15, 14, 9, 8}, //down
   {1, 0, 3, 2, 9, 8, 7, 6, 5, 4, 15, 14, 13, 12, 11, 10, 17, 16, 19, 18, 21, 20, 23, 22}, //1
   {18, 19, 16, 17, 10, 11, 12, 13, 14, 15, 4, 5, 6, 7, 8, 9, 2, 3, 0, 1, 22, 23, 20, 21}, //2
   {2, 3, 0, 1, 5, 4, 22, 23, 9, 8, 11, 10, 20, 21, 15, 14, 18, 19, 16, 17, 12, 13, 6, 7} 
};
typedef unsigned long long ull;
int vis[256], col[256], dfn;
struct node {
   int a[26]; ull val;
   void stdize() {
      ++ dfn;
      int c = 0;
      rep(i, 0, 23) {
         if(vis[a[i]] != dfn) {
            vis[a[i]] = dfn;
            col[a[i]] = ++ c;
         }
         a[i] = col[a[i]];
      }
      val = 0;
      rep(i, 0, 23) {
         val = val * 2333 + a[i];
      }
   }
   void read() {
      char op[10];
      int c = 0;
      rep(i, 1, 8) {
         scanf("%s", op);
         for(int j = 0; op[j]; j ++) {
            a[c ++] = op[j];
         }
      }
      stdize();
   }
   bool operator == (node b) const {
      rep(i, 0, 23) if(a[i] != b.a[i]) return 0;
      return 1;
   }
   bool operator < (node b) const {
      // rep(i, 0, 23) if(a[i] != b.a[i]) return a[i] < b.a[i];
      return val < b.val;
   }
   node trans(int id) {
      node ans;
      rep(i, 0, 23) ans.a[i] = a[tr[id][i]];
      ans.stdize();
      return ans;
   }
} a, b, q[1000005];
map<node, bool> Map;

int main() {
   int t; scanf("%d", &t);
   while(t --) {
      map<node, bool>().swap(Map);
      a.read(); b.read();
      int r = 0; q[r ++] = a; Map[a] = 1;
      bool mark = 0;
      for(int l = 0; l < r; l ++) {
         node cur = q[l];
         if(cur == b) { mark = 1; break ; }
         rep(k, 0, 4) {
            node nxt = cur.trans(k);
            if(!Map.count(nxt)) {
               Map[nxt] = 1;
               q[r ++] = nxt;
            }
         }
      }
      puts(mark ? "yes" : "no");
   }
   return 0;
}
/*
1
  46
  16
543513
624421
  35
  53
  26
  12
  44
  26
165235
414122
  53
  35
  61
  36
*/