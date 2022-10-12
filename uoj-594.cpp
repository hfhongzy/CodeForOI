#include <bits/stdc++.h>
#define pb push_back
#define rep(i, j, k) for(int i = j; i <= k; ++ i)
#define per(i, j, k) for(int i = j; i >= k; -- i)
using namespace std;
const int n = 1e4;

int main() {
  // rep(i, -32, -1)
    // printf("SET %d %d\n", n + 2, i);
  printf("CMP 0 -22 -23\n");
  printf("JMP -23 tagA\n");
  printf("JMP -22 BadProblem\n");

  printf("tagA: CMP -22 0 -23\n");
  printf("JMP -23 tagB\n");
  printf("JMP -22 BadProblem\n");

  printf("tagB: CMP 1 -22 -23\n");
  printf("JMP -23 tagC\n");
  printf("JMP -22 BadProblem\n");

  printf("tagC: CMP -22 1 -23\n");

  for(int i = 1; i < n; i ++) {
    printf("%sADD -24 -23 -24\n", i == 1 ? "BadProblem: " : ""); //to get n-1
  }
  printf("ADD -24 -23 -25\n"); //to get n

  printf("HelloI: ADV -1 -3\n"); //num = s[i]
  printf("SET -1 -4\n"); //pos = i
  printf("ADD -1 -23 -2\n"); //j = i + 1

  printf("HelloJ: CMP -25 -2 -32\n");
  printf("JMP -32 ByeI\n"); //is n > j == false
  printf("ADV -2 -5\n"); //tmp = a[j]
  printf("CMP -3 -5 -32\n"); //?num > tmp
  printf("JMP -32 ByeJ\n"); //num < tmp, next
  printf("SET -5 -3\n"); //num = tmp
  printf("SET -2 -4\n"); //pos = j
  printf("ByeJ: ADD -23 -2 -2\n"); //j = j + 1
  printf("JMP -22 HelloJ\n"); //goto HelloJ

  printf("ByeI: ADV -1 -5\n"); //tmp = a[i]
  printf("COM -3 -1\n"); //a[i] = num
  printf("COM -5 -4\n"); //a[pos] = tmp;
  printf("ADD -1 -23 -1\n"); //i = i + 1
  printf("CMP -1 -24 -32\n");
  printf("JMP -32 HelloI\n"); //(i > n - 1) == false
  return 0;
}
/*
-1:i
-2:j
-3:num
-4:pos
-5:tmp
-22:0
-23:1
-24:n
-32:cmp

s[-22] = 0

s[-23] = (a[0] > 0)
if s[-23] == 0 goto tagA
goto BadProblem

tagA: s[-23] = (0 > a[0])
if s[-23] == 0 goto tagB
goto BadProblem

tagB: s[-23] = (0 > a[1])
if s[-23] == 0 goto tagC
goto BadProblem

tagC: s[-23] = (a[1] > 0)
BadProblem: 

ADD -> n


pos = i;
num = a[i];
j = i + 1;
s[-32] = (num > a[j])
if s[-32] == 0
  num = a[j]
  pos = j

j = j + 1;
s[-32] = (n > i)

i = i + 1;
if((n - 1 < i) == 0)
goto
*/