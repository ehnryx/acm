#include <bits/stdc++.h>
using namespace std;
#define nl endl
int main() {
  map<double,int> m;
  m[0] = 1;
  m[3] = 6;
  m[8.5] = 7;
  cout << m.size() << nl;
  auto it = m.begin();
  cout << it->first << " " << it->second << nl;
  it++;
  cout << it->first << " " << it->second << nl;
  m[2.3] = 67;
  cout << it->first << " " << it->second << nl;
  it--;
  cout << it->first << " " << it->second << nl;
  m[2.4] = 23689;
  cout << it->first << " " << it->second << nl;


  return 0;
}
