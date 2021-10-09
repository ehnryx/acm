#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(chrono::high_resolution_clock::now().time_since_epoch().count()); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

const int N = 5e5 + 7;
int arr[3][N];
int diff[3][3][N], eq[3][3][N];
int d, n[3];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  while (cin >> d >> n[0] >> n[1] >> n[2]) {
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < n[j]; i++) {
        cin >> arr[j][i];
      }
    }

    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        if (j == k)
          continue;

        for (int i = 0, l = 0, r = 0, le = 0, re = 0; i < n[j]; i++) {
          while (le < n[k] && arr[k][le] < arr[j][i]) {
            le++;
          }
          while (re < n[k] && arr[k][re] <= arr[j][i]) {
            re++;
          }
          eq[j][k][i] = re-le;

          while (l < n[k] && arr[k][l] <= arr[j][i]) {
            l++;
          }
          while (r < n[k] && arr[k][r] <= arr[j][i] + d) {
            r++;
          }
          diff[j][k][i] = r-l;
        }
      }
    }

    ll ans = 0;
    for (int j = 0; j < 3; j++) {
      for (int i = 0, p1 = (j+1)%3, p2 = (j+2)%3; i < n[j]; i++) {
        ans += (ll) diff[j][p1][i] * diff[j][p2][i];
        ans += (ll) diff[j][p1][i] * eq[j][p2][i];
      }
    }
    for (int i = 0; i < n[0]; i++) {
      ans += (ll) eq[0][1][i] * eq[0][2][i];
    }
    cout << ans << nl;
  }

  return 0;
}
