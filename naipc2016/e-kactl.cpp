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

typedef complex<ld> C;
typedef vector<ld> vd;
void fft(vector<C>& a) {
	int n = a.size(), L = 31 - __builtin_clz(n);
	static vector<complex<ld>> R(2, 1);
	//static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); //rt.resize(n);
		auto x = polar(1.0L, PI / k);
    for (int i=k; i<2*k; i++) /*rt[i] =*/ R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vector<int> rev(n);
  for (int i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  for (int i = 0; i < n; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) for (int j = 0; j < k; j++) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (ld *)&R[j+k], y = (ld *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(a.size() + b.size() - 1);
	int L = 32 - __builtin_clz(res.size()), n = 1 << L;
	vector<C> in(n), out(n);
	copy(a.begin(), a.end(), in.begin());
  for (int i = 0; i < b.size(); i++) in[i].imag(b[i]);
	fft(in);
  for (auto& x : in) x *= x;
  for (int i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
  for (int i = 0; i < res.size(); i++) res[i] = imag(out[i]) / (4 * n);
	return res;
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
