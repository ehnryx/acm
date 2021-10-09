#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define nl '\n'



int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int a, b, c, n;
  cin >> a >> b >> c >> n;
  int z = min(a, min(b, c));
  int sum = a+b+c;
  cout << (n >= 3 && sum >= n && z >= 1 ? "YES" : "NO") << "\n";

  return 0;
}
