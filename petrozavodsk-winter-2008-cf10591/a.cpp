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

struct Range {
  int a, b, c;
  Range(){}
  Range(int a, int b, int c): a(a), b(b), c(c) {}
  int value(int x) const {
    if (x < a) return 2;
    else if (x < b) return 3;
    else if (x < c) return 4;
    else return 5;
  }
};

const int N = 100+1;

int score[N];
int exam[N];

#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("tests.in", "r", stdin);
  freopen("tests.out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> score[i];
  }

  vector<string> ans;

  while (n--) {
    string faculty;
    int k;

    getline(cin, faculty);
    getline(cin, faculty);
    cin >> k;
    for (int i = 1; i <= k; i++) {
      cin >> exam[i];
    }

    int sum = 0;
    int a, b, c;
    for (int i = 1; i <= k; i++) {
      cin >> a >> b >> c;
      sum += Range(a,b,c).value(score[exam[i]]);
    }

    int specs;
    cin >> specs;
    while (specs--) {
      string specialization;
      getline(cin, specialization);
      getline(cin, specialization);
      cin >> a;
      if (sum >= a) {
        ans.push_back(faculty + " " + specialization);
      }
    }
  }

  if (ans.empty()) {
    cout << "Army" << nl;
  } else {
    for (const string& s : ans) {
      cout << s << nl;
    }
  }

  return 0;
}
