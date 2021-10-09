#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0);

  double a, b, c, d, m, t;
  
  while (cin >> a >> b >> c >> d >> m >> t) {
    double left, mid, right;
    left = 0;
    right = t/(m*c);
    while (right - left > 1e-6) {
      mid = (left + right) / 2;
      if (a*mid*mid*mid + b*mid*mid + c*mid + d > t/m)
        right = mid;
      else 
        left = mid;
    }
    cout << fixed << setprecision(2) << ((int)(mid * 100)) / 100.0 << '\n';
  }

  return 0;
}
