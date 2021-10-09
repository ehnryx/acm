#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ld EPS = 1e-10;

ld sqr(ld x) { return x*x; }

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(10);

  int n, u, t;
  cin >> n >> u >> t;

  int w[n], v[n];
  int sum = 0;
  map<int,int> width;
  for (int i=0; i<n; i++) {
    cin >> w[i] >> v[i];
    sum += w[i];
    width[v[i]] += w[i];
  }

  if (t*u < sum) {
    cout << -1 << nl;
  }

  else {
    auto calc = [&] (ld lambda, ld vi, ld wi) {
      return wi/u/sqrt(1-sqr(u/(lambda-vi)));
    };
    auto get_tot = [&] (ld lambda) {
      ld tott = 0;
      for (const pii& it : width) {
        tott += calc(lambda, it.first, it.second);
      }
      return tott;
    };

    ld left = u + width.rbegin()->first;
    ld right = INF;
    cout << left << " " << right << endl;
    for (int i=0; i<100; i++) {
      ld mid = (left+right)/2;
      ld tott = get_tot(mid);
      if (tott*u < sum) {
        right = mid;
      } else {
        left = mid;
      }
    }

    cout << left << " " << right << endl;
    cerr << get_tot(left) << endl;
  }

  return 0;
}
