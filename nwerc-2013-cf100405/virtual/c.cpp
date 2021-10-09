#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

map<string,int> value;
void init() {
  for (int i = 2; i <= 10; i++) {
    value[to_string(i)] = i;
    value["A"] = 11;
    value["J"] = value["Q"] = value["K"] = 10;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int n, m;
  while (cin >> n >> m) {
    string s;
    vector<int> vals;
    for (int i = 0; i < n; i++) {
      cin >> s;
      vals.push_back(value[s]);
    }

    set<int> go;
    for (int it : vals) {
      go.insert(m);
      m += it;
    }
    m -= vals.back();

    vector<ld> prob(m+420, 0);
    for (int i = 1; i <= 10; i++) {
      prob[i] = (ld)1/10;
    }

    for (int i = 1; i < m; i++) {
      if (go.count(i)) {
        prob[m] += prob[i];
      } else {
        for (const pair<string,int>& it : value) {
          prob[i + it.second] += (ld)1/13 * prob[i];
        }
      }
    }

    cout << prob[m] << nl;
  }

  return 0;
}
