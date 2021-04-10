#include <bits/stdc++.h>
using namespace std;

int64_t n, k, t, s;

main() {
  for(cin >> n; n--; ) {
    cin >> k;
    for(s=t=1; 9*t*s<k; t*=10,s++) k -= 9*t*s;
    k -= s>1;
    cout << to_string(t + k/s - t%2)[k%s] << '\n';
  }
}
