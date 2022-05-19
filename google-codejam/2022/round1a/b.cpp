#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
namespace {
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
}

using ll = long long;
using ld = long double;
using pt = complex<ld>;
random_device _rd; mt19937 rng(_rd());

constexpr char nl = '\n';

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ", " << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os << "[ "; for (const T& it : v) { os << it << " , "; }
  return os << ']';
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) { os << it << " , "; }
  return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) { os << it << " , "; }
  return os << '}';
}

template <class T, class U>
istream& operator >> (istream& is, pair<T,U>& v) {
  return is >> v.first >> v.second;
}
template <int i, class... Ts>
istream& read_tuple_impl(istream& is, tuple<Ts...>& v) {
  if constexpr (i == 0) return is;
  else return read_tuple_impl<i-1>(is, v) >> get<i-1>(v);
}
template <class... Ts>
istream& operator >> (istream& is, tuple<Ts...>& v) {
  return read_tuple_impl<sizeof...(Ts)>(is, v);
}

template <class T = int>
vector<T> read_array(int n, int s=0) {
  vector<T> a(n + 2*s);
  for(int i=0; i<n; i++) {
    cin >> a[s+i];
  }
  return a;
}

template <class T = int>
vector<vector<T>> read_grid(int n, int m, int s=0, int t=0) {
  vector a(n + 2*s, vector<T>(m + 2*t));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> a[s+i][t+j];
    }
  }
  return a;
}

void solve_case();
void initialize();

////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  initialize();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    auto start = chrono::steady_clock::now();
    //cout << "Case #" << cc << ": ";
    solve_case();
    if(argc > 1 && argv[1][0] == 't') {
      cerr << "Time: " << (chrono::steady_clock::now() - start) / 1.0s << "s" << nl << nl;
    }
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

int mask[20];

void solve_case() {

  int n;
  cin >> n;
  assert(n == 100);

  int done = 0;
  for(int t=1; t<1e9; t*=10) {
    for(int i=1; i<=9; i++) {
      cout << t*i << " ";
      done++;
    }
  }
  vector<int> other;
  for(int i=101; done<n; i++, done++) {
    cout << i << " ";
    other.push_back(i);
  }
  cout << endl;

  for(int i=0; i<n; i++) {
    int v;
    cin >> v;
    other.push_back(v);
  }
  //cerr << "other: " << other << nl;

  ll sum = accumulate(begin(other), end(other), (ll)0);
  ll have = 0;
  vector<int> ans;
  for(int v : other) {
    if(2 * (have + v) <= sum) {
      have += v;
      ans.push_back(v);
    }
  }
  ll rest = sum - have;

  ll diff = rest - have;
  assert(diff < 2e9);
  assert(diff % 2);

  for(int t=1e8; t>=1; t/=10) {
    int num = diff / t;
    assert(num < 20);
    int sgn = 1;
    if(num == 0) {
      num = 1;
      sgn = -1;
    } else if(num % 2 == 0) {
      num -= 1;
    }
    for(int i=1; i<=9; i++) {
      if(mask[num] & 1<<i) {
        if(sgn == 1) {
          ans.push_back(i * t);
        }
      } else {
        if(sgn == -1) {
          ans.push_back(i * t);
        }
      }
    }
    diff -= num * t * sgn;
  }

  for(int v : ans) {
    cout << v << " ";
  }
  cout << endl;

  return;
}

void initialize() {
  for(int bm=0; bm<1<<10; bm++) {
    int sum = 0;
    for(int i=1; i<=9; i++) {
      if(bm & 1<<i) {
        sum += i;
      } else {
        sum -= i;
      }
    }
    if(0 <= sum && sum < 20) {
      mask[sum] = bm;
    }
  }
  for(int i=0; i<20; i++) {
    if(i % 2 == 0) continue;
    assert(mask[i]);
  }
}

