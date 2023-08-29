#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "string/min_rotation.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

//// duval

//vector<int> lyndon_factors(const vector<int>& s) {
//  const int n = s.size();
//  vector<int> factors;
//  for (int start = 0; start < n; ) {
//    factors.push_back(start);
//    int compare = start;
//    int i = start + 1;
//    while (i < n and s[compare] <= s[i]) {
//      if (s[compare] < s[i]) {
//        compare = start;
//      } else {
//        compare++;
//      }
//      i++;
//    }
//    while (start <= compare) {
//      factors.push_back(start);
//      start += i - compare;
//    }
//  }
//  return factors;
//}

//// min_rotation via duval

//int min_rotation(const vector<int>& a) {
//  vector<int> a2 = a;
//  a2.insert(end(a2), begin(a), end(a));
//  auto lf = lyndon_factors(a2);
//  while(lf.back() >= size(a)) lf.pop_back();
//  return lf.back();
//}

vector<int> sanitize(int n) {
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  sort(begin(a), end(a));
  vector<int> d(n);
  adjacent_difference(begin(a), end(a), begin(d));
  d.front() = a.front() - a.back() + 360'000;
  rotate(begin(d), begin(d) + min_rotation(d), end(d));
  return d;
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  auto a = sanitize(n);
  auto b = sanitize(n);
  if(a == b) {
    cout << "possible" << nl;
  } else {
    cout << "impossible" << nl;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
