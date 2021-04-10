#include <bits/stdc++.h>
using namespace std;

int64_t t, x, y, r;

main() {
  cin >> t; while(t--) {
    cin >> x >> y;
    r = max(x,y);
    cout << (r % 2 ?
      r > y ? y + (r-1)*(r-1) : r*r - x + 1 :
      r > y ? r*r - y + 1 : x + (r-1)*(r-1)) << '\n';
  }
}
