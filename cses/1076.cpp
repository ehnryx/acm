#include <bits/stdc++.h>
using namespace std;

int n, k, i, a[1<<18], *x=a;

int main() {
  cin >> n >> k;
  while(x<a+k) cin >> *++x;
  multiset<int> s(a, ++k+a);
  auto m = next(begin(s), k--/2);
  for(cout << *m; cin >> *++x; cout << " " << *m) {
    i = *x < *m; n = *(x-k) < *m;
    s.insert(*x); auto r = s.upper_bound(*(x-k));
    (r == m ? m : r) = s.erase(--r);
    if(i^n) i ? m-- : m++;
  }
}
