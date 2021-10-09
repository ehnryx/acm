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

  int n, k;
  cin >> n >> k;

  int t;
  int max_t = 0;
  int count = 0;
  for (int i = 0; i < n; i++) {
    cin >> t;
    if (t > max_t) {
      max_t = t;
      count = 0;
    }
    if (t == max_t) {
      count++;
    }
  }

  int cur = 1 + n - count;
  while (cur < k) {
    cur += n;
    max_t++;
  }
  cout << max_t+1 << nl;

  return 0;
}
