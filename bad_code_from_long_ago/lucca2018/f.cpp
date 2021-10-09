#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef ll ld;
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

struct Hash {
  size_t operator() (const pt& p) const {
    hash<int> h;
    return h(p.real()) ^ h(p.imag());
  }
};

inline bool seg_x_seg(const pt& a, const pt& b, const pt& c, const pt& d) {
  if (a.real() != b.real()) {
    if (min(a.real(), b.real()) <= c.real() 
        && c.real() <= max(a.real(), b.real())
        && min(c.imag(), d.imag()) <= a.imag()
        && a.imag() <= max(c.imag(), d.imag()))
      return true;
  }
  else {
    if (min(a.imag(), b.imag()) <= c.imag() 
        && c.imag() <= max(a.imag(), b.imag())
        && min(c.real(), d.real()) <= a.real()
        && a.real() <= max(c.real(), d.real())) 
      return true;
  }
  return false;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n;
  cin >> n;

  int a, b;
  vector<pt> arr;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    arr.push_back(pt(a,b));
  }

  unordered_map<pt, pt, Hash> right, down;

  for (int i = 0; i < n; i++) {
    if (arr[i].real() == arr[(i+1)%n].real()) {
      int x = arr[i].real();
      vector<int> y;
      for (int j = (i+1)%2; j < n; j+=2) {
        if (seg_x_seg(arr[i], arr[(i+1)%n], arr[j], arr[(j+1)%n])) {
          y.push_back(arr[j].imag());
        }
      }
      sort(y.begin(), y.end());

      for (int i = 1; i < y.size(); i++) {
        if (y[i] > y[i-1]) {
          down[pt(x, y[i])] = pt(x, y[i-1]);
        } else {
          down[pt(x, y[i-1])] = pt(x, y[i]);
        }
      }
    }

    else {
      int y = arr[i].imag();
      vector<int> x;
      for (int j = (i+1)%2; j < n; j+=2) {
        if (seg_x_seg(arr[i], arr[(i+1)%n], arr[j], arr[(j+1)%n])) {
          x.push_back(arr[j].real());
        }
      }
      sort(x.begin(), x.end());

      for (int i = 1; i < x.size(); i++) {
        if (x[i] > x[i-1]) {
          right[pt(x[i], y)] = pt(x[i-1], y);
        } else {
          right[pt(x[i-1], y)] = pt(x[i], y);
        }
      }
    }
  }

  int ans = 0;

  for (const pair<pt,pt>& base : right) {
    if (down.count(base.first) && down.count(base.second)) {
      pt e = down[base.second];
      pt d = down[base.first];
      if (right.count(d) && right[d] == e) {
        ans++;
      }
    }
  }

  cout << ans << nl;

  return 0;
}
