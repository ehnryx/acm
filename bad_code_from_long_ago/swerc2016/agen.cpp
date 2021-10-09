#include <bits/stdc++.h>
using namespace std;

int main() {
  cout << 20 << endl;
  for (int i = 0; i < 20; i++) {
    cout << 1 + rand()%1000 << endl;
  }
  cout << rand()%40001 - 20000 << " " << rand()%40001 - 20000 << endl;
  return 0;
}
