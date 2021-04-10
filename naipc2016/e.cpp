#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

constexpr ld PI = M_PIl;

template <bool dit = 0> void fft(vector<pt>& a) {
  static vector<pt> w(2, 1); int n = a.size();
  for (static int k = 2; k < n; k *= 2) {
    w.resize(n, 1); pt c = polar((ld)1, PI/k * (dit ? -1 : 1));
    for (int i = k+1; i < 2*k; i++) w[i] = i&1 ? w[i/2]*c : w[i/2]; }
  for (int t = 1; t < n; t *= 2) {
    int k = (dit ? t : n/2/t);
    for (int i = 0; i < n; i += k*2) for (int j = 0; j < k; j++) {
      pt &c = a[i+j], &d = a[i+j+k], e = w[j+k], f = d;
      d = (dit ? c - (f = f*e) : (c-f)*e); c += f;
    }
  }
}
vector<ld> conv(vector<ld> a, vector<ld> b) {
  if(a.empty() || b.empty()) return {};
  int len = a.size() + b.size() - 1, n = 1 << (32 - __builtin_clz(len));
  vector<pt> v(n); copy(a.begin(), a.end(), v.begin());
  for(int i=0; i<b.size(); i++) v[i].imag(b[i]);
  fft(v); for(auto& x : v) { x *= x; } fft<1>(v);
  vector<ld> out(len); for(int i=0; i<len; i++) out[i] = imag(v[i])/2/n;
  return out;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  string s;
  cin >> s;
  int n = s.size();
  vector<ld> a, b;
  for(char c : s) {
    a.push_back(c == 'A');
    b.push_back(c == 'B');
  }
  reverse(a.begin(), a.end());
  vector<ld> c = conv(a, b);
  for(int i=1; i<=n-1; i++) {
    cout << llround(c[n-1-i]) << nl;
  }

  return 0;
}
