#include <bits/stdc++.h>
using namespace std;


const char nl = '\n';
using ll = long long;
using ld = long double;


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(6);

  int n, m;
  cin >> n >> m;
  int sum = 0;
  for(int i=0; i<m; i++) {
    int v;
    cin >> v;
    sum += v;
  }

  cout << (sum - (n - m) * 3) / (ld)n << " " << (sum + (n - m) * 3) / (ld)n << nl;

  return 0;
}
