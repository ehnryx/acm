#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Frac {
  ll n, d;
  Frac(ll a=0, ll b=1) {
    ll g = abs(__gcd(a,b));
    n = a/g; d = b/g;
    if(d<0) { n = -n; d = -d; }
  }
  //bool operator < (const Frac& o) const { return (ld)n/d < (ld)o.n/o.d; }
  //bool operator <= (const Frac& o) const { return (ld)n/d <= (ld)o.n/o.d; }
  //bool operator < (const Frac& o) const { return n*o.d < d*o.n; }
  //bool operator <= (const Frac& o) const { return n*o.d <= d*o.n; }
  bool operator < (const Frac& o) const { return (__int128)n*o.d < (__int128)d*o.n; }
  bool operator <= (const Frac& o) const { return (__int128)n*o.d <= (__int128)d*o.n; }
  Frac operator + (const Frac& o) const { return Frac(n*o.d + d*o.n, d*o.d); }
  Frac operator * (const Frac& o) const { return Frac(n*o.n, d*o.d); }
};

ostream& operator << (ostream& os, const Frac& f) {
  os << f.n / f.d;
  if(f.n % f.d) {
    os << " + " << f.n % f.d << "/" << f.d;
  }
  return os;
}

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
template <typename T> inline void read(T &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n; ll tot, sz;
  //cin >> n >> tot >> sz;
  read(n); read(tot); read(sz);

  vector<vector<int>> all(n);
  vector<int> vals;
  for(int i=0; i<n; i++) {
    int m;
    //cin >> m;
    read(m);
    all[i].resize(m);
    for(int j=0; j<m; j++) {
      //cin >> all[i][j];
      read(all[i][j]);
      vals.push_back(all[i][j]);
    }
    sort(all[i].begin(), all[i].end(), greater<int>());
  }
  sort(vals.begin(), vals.end());
  vals.resize(unique(vals.begin(), vals.end()) - vals.begin());

  function<Frac(ll)> calc = [=](ll lb) {
    //cerr << "CALC " << lb << nl;
    ll equal = 0;
    ll value = 0;
    ll used = 0;
    for(const auto& vec : all) {
      for(int it : vec) {
        if(it == lb) {
          equal++;
        } else if(it > lb) {
          value += it;
          used += sz;
        }
      }
    }

    Frac res(-1);
    for(int i=0; i<n; i++) {
      ll cur_equal = equal;
      ll cur_value = value;
      ll cur_used = used;
      for(int it : all[i]) {
        if(it == lb) {
          cur_equal--;
        } else if(it > lb) {
          cur_value -= it;
          cur_used -= sz;
        }
      }
      if(cur_used > tot) continue;
      //cerr<<"cur_equal = "<<cur_equal<<nl;
      //cerr<<"cur_value = "<<cur_value<<nl;
      //cerr<<"cur_used  = "<<cur_used <<nl;

      // use 0 from current
      res = max(res, Frac(cur_value + min(cur_equal, (tot - cur_used) / sz) * lb));
      //cerr << "use 0: " << Frac(cur_value + min(cur_equal, (tot - cur_used) / sz) * lb) << nl;

      ll sum = all[i][0];
      for(int j=1; j<=all[i].size(); j++) {
        // use j from current
        if(sum < j*lb) {
          int k = min(cur_equal, (tot - cur_used) / sz);
          Frac alpha(min(j*sz, tot - cur_used - k*sz), j*sz);
          Frac cur = alpha * Frac(sum) + Frac(k * lb + cur_value);
          res = max(res, cur);
          //cerr << "use "<<j<<": " << cur << " + " << Frac(cur_value) << nl;
          //cerr << "k = " << k << " and alpha = " << alpha << nl;
        } else {
          vector<ll> ks = {
            min(cur_equal, (tot - cur_used - j*sz + sz - 1) / sz), // ceiling
            //min(cur_equal, (tot - cur_used - j*sz) / sz), // floor
          };
          for(ll k : ks) {
            if(k < 0 || tot - cur_used - k*sz < 0) continue;
            Frac alpha(min(j*sz, tot - cur_used - k*sz), j*sz);
            Frac cur = alpha * Frac(sum) + Frac(k * lb + cur_value);
            res = max(res, cur);
            //cerr << "oth "<<j<<": " << cur << " + " << Frac(cur_value) << nl;
            //cerr << "k = " << k << " and alpha = " << alpha << nl;
          }
        }
        // update sum
        sum += all[i][j];
      }
    }
    //cerr << nl;
    return res;
  };

  int l = 0;
  int r = (int) vals.size() - 1;
  while(r-l > 2) {
    int m = (l+r) / 2;
    if(calc(vals[m]) <= calc(vals[m+1])) {
      l = m;
    } else {
      r = m+1;
    }
  }

  Frac ans = calc(vals[l]);
  for(int j=l+1; j<=r; j++) {
    ans = max(ans, calc(vals[j]));
  }
  cout << ans << nl;

  return 0;
}
