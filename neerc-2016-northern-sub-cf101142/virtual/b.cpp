#include <bits/stdc++.h>
using namespace std;
#define problem_name "problem"

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

void print(const vector<char>& s) {
  for (char c : s) {
    cout << c;
  }
  cout << nl;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(problem_name ".in", "r", stdin);
  freopen(problem_name ".out", "w", stdout);
#endif

  int n, x, y;
  cin >> n >> x >> y;

  vector<char> ans;

  if (x+y >= n+4) {
    for (int i=0; i<n-y+2; i++) {
      ans.push_back('B');
    }
    for (int i=0; i<n-x+2; i++) {
      ans.push_back('G');
    }
    int left = n - (n-y+2) - (n-x+2);
    if (left % 4 != 0) {
      cout << "Impossible" << nl;
    } else {
      for (int i=0; i<left; i+=4) {
        ans.push_back('B');
        ans.push_back('B');
        ans.push_back('G');
        ans.push_back('G');
      }
      print(ans);
    }
  }

  else if (x+y == n+2) {
    if (x < y) {
      if (y == n - (x-2)) {
        for (int i=0; i<x-1; i++) {
          ans.push_back('B');
          ans.push_back('G');
        }
        int left = n - 2*(x-1);
        for (int i=0; i<left; i++) {
          ans.push_back('G');
        }
        print(ans);
      } else {
        cout << "Impossible" << nl;
      }
    }
    else {
      if (x == n - (y-2)) {
        for (int i=0; i<y-1; i++) {
          ans.push_back('G');
          ans.push_back('B');
        }
        int left = n - 2*(y-1);
        for (int i=0; i<left; i++) {
          ans.push_back('B');
        }
        print(ans);
      } else {
        cout << "Impossible" << nl;
      }
    }
  }

  else if (x+y == n) {
    if (x == y) {
      for (int i=0; i<n; i+=2) {
        ans.push_back('B');
        ans.push_back('G');
      }
      print(ans);
    }
    else if (x == n) {
      for (int i=0; i<n; i++) {
        ans.push_back('B');
      }
      print(ans);
    }
    else if (y == n) {
      for (int i=0; i<n; i++) {
        ans.push_back('G');
      }
      print(ans);
    }
    else {
      cout << "Impossible" << nl;
    }
  }

  else {
    cout << "Impossible" << nl;
  }

  return 0;
}
