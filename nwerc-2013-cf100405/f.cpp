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

const vector<int> greg_pls_stop_with_your_stupid_calendar = { 420, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1 };

bool isleap(int y) {
  if (y%400 == 0) return true;
  if (y%100 == 0) return false;
  return y%4 == 0;
}

int days(int m, int y) {
  if (m == 2) return isleap(y) ? 29 : 28;
  else return greg_pls_stop_with_your_stupid_calendar[m] ? 31 : 30;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  string s;
  while (cin >> s) {
    int y = stoi(s.substr(0,4));
    int m = stoi(s.substr(5,2));
    int d = stoi(s.substr(8,2));

    int leap = 0;
    for (int i = 201; i < y; i++) {
      if (i%100 == 0 && !isleap(i)) leap++;
    }
    if (m > 2 && y%100 == 0 && !isleap(y)) {
      leap++;
    }

    d += leap + 1;
    while (d > days(m, y)) {
      d -= days(m, y);
      m++;
      if (m > 12) {
        y++;
        m = 1;
      }
    }

    cout << y << '-' << setw(2) << setfill('0') << m << '-' << setw(2) << setfill('0') << d << nl;
  }

  return 0;
}
