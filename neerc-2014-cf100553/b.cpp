#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
constexpr char nl = '\n';

#define FNAME "burrito"

struct Burrito {
  ll g, a, b, idx;
  bool operator< (const Burrito& o) const {
    return a*o.b < o.a*b;
  }
};

const int N = 100100;
const ld EPS = 1e-10;
ll A, B;
ld amt[N];
int n;

int main() {
  string __fname = FNAME;
#ifdef ONLINE_JUDGE
  freopen(FNAME ".in", "r", stdin);
  freopen(FNAME ".out", "w", stdout);
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n >> A >> B;
  vector<Burrito> v;
  for (int i=0; i<n; ++i) {
    ll g,a,b;
    cin >> g >> a >> b;
    v.push_back({g, a, b, i});
  }
  sort(v.rbegin(), v.rend());
  ll asum = 0, bsum = 0;
  ld aextra = 0;
  for (auto& [g, a, b, idx] : v) {
    if ((B-bsum) < g*b) {
      ld si = (ld) (B-bsum)/b;
      bsum += si*b;
      aextra = si*a;
      amt[idx] = si;
      break;
    } else {
      bsum += b*g;
      asum += a*g;
      amt[idx] = g;
    }
  }

  if (asum + aextra + EPS < A) {
    cout << "-1 -1\n";
    return 0;
  }
  cout << fixed << setprecision(10) << asum + aextra << " " << bsum << "\n";
  for (int i=0; i<n; ++i) {
    cout << amt[i];
    if (i != n-1) {
      cout << " ";
    }
  }
  cout << "\n";

  return 0;
}
