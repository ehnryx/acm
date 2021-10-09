#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  map<string, int> score;
  score["yellow"] = 2;
  score["green"] = 3;
  score["brown"] = 4;
  score["blue"] = 5;
  score["pink"] = 6;
  score["black"] = 7;

  string s;
  vector<int> other;
  int red = 0;
  int ans = 0;

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> s;
    if (s == "red") {
      red++;
    }
    else {
      other.push_back(score[s]);
      ans += other.back();
    }
  }
  if (other.empty()) {
    cout << 1 << nl;
    return 0;
  }

  sort(other.begin(), other.end());
  ans += red * (1 + other.back());
  cout << ans << nl;

  return 0;
}
