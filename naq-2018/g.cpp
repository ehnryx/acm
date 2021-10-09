#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  int n;
  cin >> n;
  string s, t;
  cin >> t;
  s = "R"+t+"R";
  //cerr << s << nl;

  bool right = (s.back() == 'R');
  s.push_back(0);
  vector<int> v;
  for (int i=s.size()-2; i>=0; i--) {
    if (s[i] != s[i+1]) {
      v.push_back(1);
    } else {
      v.back()++;
    }
  }

  vector<int> ans;
  int minv = n+1;
  for (int i=0; i<v.size(); i++) {
    //cerr << i << ": " << v[i] << nl;
    if (right) {
      int lb = minv-v[i]+1;
      //cerr << "right: " << minv << " -> " << lb << nl;
      for (int i=minv-1; i>=lb; i--) {
        ans.push_back(i);
      }
      minv = lb;
    } else {
      int lb = minv-v[i]-1;
      //cerr << "left: " << minv << " -> " << lb << nl;
      for (int i=lb; i<minv; i++) {
        ans.push_back(i);
      }
      minv = lb;
    }
    right = !right;
  }
  reverse(ans.begin(), ans.end());

  for (int it : ans) {
    cout << it << nl;
  }

  return 0;
}
