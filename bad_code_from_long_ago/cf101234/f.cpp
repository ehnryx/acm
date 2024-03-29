#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

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




int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n;
  cin >> n;

  int a[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(a, a+n);

  if (n % 2 == 0) {
    int ans[n];
    for (int i = 0; i < n/2; i++) {
      ans[2*i] = a[i];
      ans[2*i+1] = a[i+n/2];
    }
    for (int i = 0; i < n; i++) {
      cout << ans[i] << " ";
    }
    cout << nl;
  }

  else {
    int first[n], second[n];
    for (int i = 0; i < n/2; i++) {
      first[2*i] = a[i];
      first[2*i+1] = a[i+n/2+1];
      second[2*i+1] = a[i+1];
      second[2*i+2] = a[i+n/2+1];
    }
    first[n/2] = a[n/2];
    second[0] = a[0];

    int ansf, anss;
    ansf = anss = 2*INF;
    for (int i = 1; i < n; i++) {
      ansf = min(ansf, abs(first[i] - first[i-1]));
      anss = min(anss, abs(second[i] - second[i-1]));
    }
    if (ansf > anss) {
      for (int i = 0; i < n; i++) {
        cout << first[i] << " ";
      }
      cout << nl;
    } else {
      for (int i = 0; i < n; i++) {
        cout << second[i] << " ";
      }
      cout << nl;
    }
  }

  return 0;
}
