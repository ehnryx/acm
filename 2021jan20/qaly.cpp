#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n;
  cin >> n;
  vector<double> a(n), b(n);
  for(int i=0; i<n; i++) {
    cin >> a[i] >> b[i];
  }
  transform(a.begin(), a.end(), b.begin(), a.begin(), multiplies<double>());
  cout << accumulate(a.begin(), a.end(), (double) 0) << nl;

  return 0;
}
