#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n;
  cin >> n;

  vector<ldouble> fib;
  vector<ldouble> shit;
  fib.push_back(0); fib.push_back(1);
  for (int i = 2; i <= n; i++) {
    fib.push_back(fib[i-1]+fib[i-2]);
  }
  shit.push_back(0); shit.push_back(1);
  shit.push_back(3); shit.push_back(12);
  for (int i = 4; i <= n; i++) {
    shit.push_back(shit[i-1] + shit[i-2] + shit[i-3]/(i-3) + (i+2)*fib[i-1]/2 + (5*i-4)*fib[i-2]/2);
  }
  for (int i = 0; i <= n; i++) {
    cout << i << ": " << shit[i] << nl;
  }
  vector<ldouble> sum;
  sum.push_back(0);
  for (int i = 1; i <= n; i++) {
    sum.push_back(sum[i-1] + shit[i]);
  }
  cout << "SUM: " << nl;
  for (int i = 0; i <= n; i++) {
    cout << i << ": " << sum[i];
    if (sqrt(sum[i]) - floor(sqrt(sum[i])) == 0) cout << " sqr";
    cout << nl;
  }
  vector<ldouble> diff;
  cout << "DIFF: " << nl;
  for (int i = 1; i <= n; i++) {
    diff.push_back(shit[i] - shit[i-1]);
    cout << i << ": " << diff.back();
    if (sqrt(diff.back()) - floor(sqrt(diff.back())) == 0) cout << " sqr";
    cout << nl;
  }
  cout << "DDIFF: " << nl;
  for (int i = 1; i < n; i++) {
    cout << i << ": " << diff[i] - diff[i-1] << nl;
  }

  return 0;
}
