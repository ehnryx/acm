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

  int n;
  cin >> n;

  ll lb, rb;
  ll bound = 0;
  map<ll,ll> a;
  ll x, y;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    y++;
    a[x] = max(a[x], y);
    if (y > bound) {
      bound = y;
      lb = x;
    }
    if (y == bound) {
      rb = x;
    }
  }

  ll circ, sz, area;
  circ = sz = area = 0;

  ll cur, prev;
   
  cur = 0;
  prev = -INF;
  for (auto it = a.begin(); it != a.end(); it++) {
    area += (it->first - prev) * cur;
    if (cur > 0) {
      circ += it->first - prev;
    }
    if (it->second > cur) {
      circ += it->second - cur;
      cur = it->second;
    }
    prev = it->first;
    
    if (it->first == lb) {
      break;
    }
  }

  cur = 0;
  prev = INF;
  for (auto it = a.rbegin(); it != a.rend(); it++) {
    area += (prev - it->first) * cur;
    if (cur > 0) {
      circ += prev - it->first;
    }
    if (it->second > cur) {
      circ += it->second - cur;
      cur = it->second;
    }
    prev = it->first;

    if (it->first == rb) {
      break;
    }
  }

  circ += (rb-lb+1);
  area += (rb-lb+1) * bound;

  cout << circ + 4 << " " << circ + 2 << " " << area << nl;;

  return 0;
}
