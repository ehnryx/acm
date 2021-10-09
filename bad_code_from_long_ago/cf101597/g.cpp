#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long long ld;
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
const ld EPS = 1e-13;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n;
  cin >> n;

  int x, y;
  vector<pt> fucked;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    fucked.push_back(pt(x,y));
  }
  int start = -1;
  for (int i = 0; i < n; i++) {
    if (cp(fucked[i]-fucked[(i+1)%n], fucked[(i+1)%n]-fucked[(i+2)%n]) != 0) {
      start = (i+1)%n;
      break;
    }
  }
  if (start == -1) {
    cout << n/2 << nl;
    return 0;
  }

  vector<pt> points;
  for (int i = 0; i < n; i++) {
    if (i == 0 || cp(fucked[(start+i)%n]-fucked[(start+i-1)%n], fucked[(start+i)%n]-fucked[(start+i+1)%n]) != 0)
      points.push_back(fucked[(start+i)%n]);
  }
  n = points.size();

  if (n % 2 == 1) {
    cout << "INFINITY" << nl;
  } 
  else {
    bool shit = false;
    for (int i = 0; i < n/2; i++) {
      if (cp(points[(i+1)%n]-points[i], points[(i+2)%n]-points[(i+1)%n]) < 0) {
        shit = true;
        break;
      }
      if (points[i]-points[(i+1)%n] + points[(i+n/2)%n]-points[(i+n/2+1)%n] != pt(0,0)) {
        shit = true;
        break;
      }
    }
    if (shit) {
      cout << "INFINITY" << nl;
    } else {
      cout << n/2 << nl;
    }
  }

  return 0;
}
