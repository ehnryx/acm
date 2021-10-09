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

pii prob[1001];
ld ivexp[1001][1001];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(13);

  int n;
  cin >> n;

  int a, b;
  prob[1] = pii(1,0);
  for (int i = 2; i <= n; i++) {
    cin >> a >> b;
    prob[i] = pii(a,b);
  }

  ivexp[1][0] = 0;
  for (int i = 2; i <= n; i++) {
    ivexp[i][prob[i].second] = ivexp[i-1][0] + 1;
    cerr << i << " " << prob[i].second << ": " << ivexp[i][prob[i].second] << nl;
    for (int j = prob[i].second-1; j >= 0; j--) {
      ld p = (ld)prob[i].first / (prob[i].first + prob[i].second - j);
      cerr << "p: " << p << nl;
      ivexp[i][j] = ivexp[i-1][0] + p + (1-p)*(1 + ivexp[i][j+1]);
      cerr << i << " " << j << ": " << ivexp[i][j] << nl;
    }
  }

  cout << ivexp[n][0] << nl;

  return 0;
}
