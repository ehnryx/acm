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

struct Jedi {
  int id;
  vector<int> v;
  Jedi(int i, int a, int b, int c): id(i) {
    v = {a,b,c};
    sort(v.begin(), v.end());
  }
  bool operator < (const Jedi& other) const {
    return v[0] > other.v[0];
  }
  bool operator > (const Jedi& other) const {
    return v[1] > other.v[1];
  }
  bool beat(const Jedi& other) const {
    return v[2] >= other.v[1] && v[1] >= other.v[0];
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  int a, b, c;
  vector<Jedi> first, second;
  for (int i=1; i<=n; i++) {
    cin >> a >> b >> c;
    first.push_back({i,a,b,c});
    second.push_back({i,a,b,c});
  }
  sort(first.begin(), first.end());
  sort(second.begin(), second.end(), greater<Jedi>());

  vector<int> ans;
  for (int i=0; i<n; i++) {
    if (first[i].beat(first[0]) && first[i].beat(second[0])) {
      ans.push_back(first[i].id);
    }
  }

  sort(ans.begin(), ans.end());
  cout << ans.size() << nl;
  for (int it : ans) {
    cout << it << " ";
  }
  cout << nl;

  return 0;
}
