#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
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

  ll n;
  int T;
  cin >> T;
  while (T--) {
    cin >> n;
    if (n % 3 == 0) {
      cout << n/3 << " " << n/3 << " " << n/3 << nl;
    } else if (n % 4 == 0) {
      cout << n/4 << " " << n/4 << " " << n/2 << nl;
    } else if (n % 6 == 0) {
      cout << n/6 << " " << n/3 << " " << n/2 << nl;
    } else {
      cout << "IMPOSSIBLE" << nl;
    }
  }

  return 0;
}
