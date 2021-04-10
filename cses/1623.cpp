#include <bits/stdc++.h>
using namespace std;

int64_t n, m, s, i, a[42], r = 1e12;

main() {
  cin >> n;
  for( ; i<n; ) cin >> a[i++];
  for( ; m<1<<n; m++, r = min(r, abs(s)))
    for(s=i=0; i<n; i++) s += m&1<<i ? a[i] : -a[i];
  cout << r;
}
