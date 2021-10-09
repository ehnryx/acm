#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const char nl = '\n';
const int INF = 0x3f3f3f3f;

const int N = 50;
unordered_set<int> dp[N][N];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  string s;
  for (int cs=1; ; cs++) {
    cin >> s;
    if (s[0] == '0') break;


    int n = s.size();
    for (int l=1; l<=n; l++) {
      for (int i=0; i+l-1<n; i++) {
        int j=i+l-1;
        dp[i][j].clear();
        if (l == 1) {
          if (s[i] == 'I') dp[i][j].insert(1);
          else if (s[i] == 'V') dp[i][j].insert(5);
          else if (s[i] == 'X') dp[i][j].insert(10);
          else if (s[i] == 'L') dp[i][j].insert(50);
          else if (s[i] == 'C') dp[i][j].insert(100);
        } else {
          for (int k=1; k<l; k++) {
            for (int a : dp[i][i+k-1]) {
              for (int b : dp[i+k][j]) {
                if (a < b) dp[i][j].insert(b-a);
                else dp[i][j].insert(a+b);
              }
            }
          }
        }
      }
    }

    vector<int> ans;
    for (int i : dp[0][n-1]) {
      ans.push_back(i);
    }
    sort(ans.begin(), ans.end());

    cout << "Case " << cs << ": ";
    for (int i : ans) {
      cout << i << " ";
    }
    cout << nl;
  }

  return 0;
}
