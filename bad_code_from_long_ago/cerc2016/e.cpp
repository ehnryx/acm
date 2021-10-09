#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  unordered_set<int> seen;
  int ans = 0;
  int m = 1000;
  int k, n;
  cin >> k >> n;
  for (int a = 1; a <= m; a++) {
    for (int b = a+1; b <= m; b++) {
      for (int c = b+1; c <= m; c++) {
        if (!seen.count(a) && !seen.count(b) && !seen.count(c))
        if (a*a + b*b + c*c == k*(a*b + b*c + c*a) + 1) {
          cout << a << " " << b << " " << c << nl;
          ans++;
          if (ans == n)
            return 0;
          seen.insert(a);
          seen.insert(b);
          seen.insert(c);
        }
      }
    }
  }
  cout << "RIP" << nl;

  return 0;
}
