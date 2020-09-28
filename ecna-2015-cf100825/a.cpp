//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const int N = 100;
int m[N], x[N], y[N], z[N], vx[N], vy[N], vz[N];
int lx[N], ly[N], lz[N];

ll egcd(ll a, ll b, ll& x, ll &y) { if (!b) {x=1; y=0; return a;}
  // to ensure d>=0: x=sgn(a);y=0;return abs(a);       ^^^^^^^^
  ll d = egcd(b, a%b, y, x); y -= x * (a/b); return d; }

bool chin_rem(ll a1, ll m1, ll a2, ll m2, ll& A, ll& M) {
  ll X1, X2, d = egcd(m1, m2, X1, X2); if (a1 % d != a2 % d) return 0;
  M = m1/d*m2, A = ((X1*(a2/d)%m2*m1 + X2*(a1/d)%m1*m2 + a1%d)%M + M)%M;
  return 1; }

ll inverse(ll n, ll m) {
  ll x, y;
  egcd(n, m, x, y);
  return (x % m + m) % m;
}

int rewrite(int a, int b, int m) {
  if(b == 0) return 0;
  return (a * inverse(b, m) % m + m) % m;
}

tuple<int,int,int> solve(int a1, int b1, int m1, int a2, int b2, int m2) {
  //cerr<<"CHIN REM "<<a1<<" "<<b1<<" "<<m1<<" and "<<a2<<" "<<b2<<" "<<m2<<nl;
  a1 = (a1 % m1 + m1) % m1;
  b1 = (b1 % m1 + m1) % m1;
  a2 = (a2 % m2 + m2) % m2;
  b2 = (b2 % m2 + m2) % m2;
  if(b1 == 0 && a1 != 0) return make_tuple(0, 0, 0);
  if(b2 == 0 && a2 != 0) return make_tuple(0, 0, 0);
  int g1 = abs(__gcd(b1, m1));
  int g2 = abs(__gcd(b2, m2));
  if(a1 % g1 || a2 % g2) return make_tuple(0, 0, 0);
  int v1 = rewrite(a1/g1, b1/g1, m1/g1);
  int v2 = rewrite(a2/g2, b2/g2, m2/g2);
  ll A, M;
  //cerr<<"CRT "<<v1<<" "<<m1/g1<<" and "<<v2<<" "<<m2/g2<<nl;
  if(chin_rem(v1, m1/g1, v2, m2/g2, A, M)) {
    //cerr<<"ok"<<nl;
    return make_tuple(A, 1, M);
  } else {
    return make_tuple(0, 0, 0);
  }
}

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

  int n, nx, ny, nz;
  cin >> n >> nx >> ny >> nz;
  for(int i=0; i<n; i++) {
    cin >> m[i] >> x[i] >> y[i] >> z[i] >> vx[i] >> vy[i] >> vz[i];
  }
  memcpy(lx, x, sizeof lx);
  memcpy(ly, y, sizeof ly);
  memcpy(lz, z, sizeof lz);

  vector<int> have(n);
  iota(have.begin(), have.end(), 0);
  for(;;) {
    int mt = INF;
    for(int i : have) {
      for(int j : have) {
        if(i == j) break;
        int fx = x[i] - x[j];
        int fy = y[i] - y[j];
        int fz = z[i] - z[j];
        int gx = vx[j] - vx[i];
        int gy = vy[j] - vy[i];
        int gz = vz[j] - vz[i];
        auto [a, b, mod] = solve(fx, gx, nx, fy, gy, ny);
        if(mod) {
          tie(a, b, mod) = solve(fz, gz, nz, a, b, mod);
        }
        if(mod) {
          mt = min(mt, a);
        }
      }
    }
    if(mt == INF) break;

    map<tuple<int,int,int>,vector<int>> pts;
    for(int i : have) {
      x[i] = (x[i] + (ll) vx[i] * mt % nx + nx) % nx;
      y[i] = (y[i] + (ll) vy[i] * mt % ny + ny) % ny;
      z[i] = (z[i] + (ll) vz[i] * mt % nz + nz) % nz;
      pts[make_tuple(x[i], y[i], z[i])].push_back(i);
    }

    bool hit = false;
    for(const auto& [_, idx] : pts) {
      if(idx.size() > 1) {
        hit = true;
        int s = idx[0];
        for(int i=1; i<idx.size(); i++) {
          m[s] += m[idx[i]];
          vx[s] += vx[idx[i]];
          vy[s] += vy[idx[i]];
          vz[s] += vz[idx[i]];
          have.erase(find(have.begin(), have.end(), idx[i]));
        }
        vx[s] /= (int)idx.size();
        vy[s] /= (int)idx.size();
        vz[s] /= (int)idx.size();
      }
    }

    if(hit) {
      memcpy(lx, x, sizeof lx);
      memcpy(ly, y, sizeof ly);
      memcpy(lz, z, sizeof lz);
    }
  }

  vector<vector<int>> out;
  for(int i=0; i<have.size(); i++) {
    int j = have[i];
    out.push_back({-m[j], lx[j], ly[j], lz[j], vx[j], vy[j], vz[j]});
  }
  sort(out.begin(), out.end());

  cout << out.size() << nl;
  for(int i=0; i<out.size(); i++) {
    out[i][0] = -out[i][0];
    cout << "P" << i << ":";
    for(int it : out[i]) {
      cout << " " << it;
    }
    cout << nl;
  }

  return 0;
}
