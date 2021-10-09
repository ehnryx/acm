#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
int main() {
  cout << "500 1000 499 499" << nl;
  for (int i = 2; i <= 500; i++) cout << i << " "; cout << nl;
  for (int i = 1; i <= 499; i++) cout << i << " "; cout << nl;
  for (int i = 1; i <= 500; i++) cout << i << " ";
  for (int i = 250; i >= 1; i--) cout << 2*i << " ";
  for (int i = 250; i >= 1; i--) cout << 2*i-1 << " "; cout << nl;
  for (int i = 1; i < 1000; i++) cout << 1+rand()%1000 << " "; cout << nl;
  return 0;
}
