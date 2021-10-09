#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef int ld;
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

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n;
  cin >> n;

  int x, y;
  vector<pt> points;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    points.push_back(pt(x,y));
  }

  int maxx, minx, maxy, miny;
  maxx = maxy = -INF;
  minx = miny = INF;

  int left, right;
  pt line;

  // cw
  //cerr << "CW" << nl;
  left = right = 0;
  for (int i = 1; i <= n; i++) {
    line = points[i%n]-points[i-1];
    if (cp(line, points[(i+1)%n]-points[i%n]) > 0) {
      left++;
      right = 0;
    }
    else {
      right++;
      left = 0;
    }

    if (left == 2) {
      //cerr << "line: " << line << nl;
      if (line.real() == 0) {
        if (line.imag() < 0) 
          minx = min(minx, points[i-1].real());
        else 
          maxx = max(maxx, points[i-1].real());
      } else {
        if (line.real() > 0)
          miny = min(miny, points[i-1].imag());
        else
          maxy = max(maxy, points[i-1].imag());
      }
    } 
  }

  reverse(points.begin(), points.end());

  // ccw
  //cerr << "CCW" << nl;
  left = right = 0;
  for (int i = 1; i <= n; i++) {
    line = points[i%n]-points[i-1];
    if (cp(line, points[(i+1)%n]-points[i%n]) > 0) {
      left++;
      right = 0;
    }
    else {
      right++;
      left = 0;
    }

    if (right == 2) {
      //cerr << "line: " << line << nl;
      if (line.real() == 0) {
        if (line.imag() < 0) 
          maxx = max(maxx, points[i-1].real());
        else 
          minx = min(minx, points[i-1].real());
      } else {
        if (line.real() > 0)
          maxy = max(maxy, points[i-1].imag());
        else
          miny = min(miny, points[i-1].imag());
      }
    }
  }
  //cerr << minx << " " << maxx << "    " << miny << " " << maxy << nl;

  if (minx >= maxx && miny >= maxy) cout << "SAFETY" << nl;
  else cout << "DANGER" << nl;

  return 0;
}
