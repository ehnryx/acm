#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int a; vector<int> b;
  while (cin >> a) {
    b.pb(a);
  }
  int i = 0;
  int c = 0;
  while (i >= 0 && i < b.size()) {
    int next = i + b[i];
    if (b[i] >= 3) b[i]--;
    else b[i]++;
    i = next;
    c++;
  }
  cout << c << nl;

  return 0;
}
