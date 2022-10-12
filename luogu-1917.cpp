#include <iostream>
using namespace std;

char c[10][10];
int cnt, a, b;

int main() {
  for(int i = 1; i <= 3; i ++)
    for(int j = 1; j <= 3; j ++)
      cin >> c[i][j], cnt += (c[i][j] != '-');
  if(cnt <= 1) {
    cout << "Dont know." << endl;
  } else if(cnt == 2) {
    if(c[2][1] == 'X' || c[2][3] == 'X' || c[1][2] == 'X' || c[3][2] == 'X')
      cout << "xiaoa will win." << endl;
    else
      cout << "Dont know." << endl;
  } else if(cnt == 3) {
    if((c[1][1] == 'X' && c[3][3] == 'O') ||
      (c[1][1] == 'O' && c[3][3] == 'X') ||
      (c[1][3] == 'X' && c[3][1] == 'O') ||
      (c[1][3] == 'O' && c[3][1] == 'X'))
      cout << "Dont know." << endl;
    else
      cout << "xiaoa will win." << endl;
  }
  cout << cnt << endl;
  return 0;
}