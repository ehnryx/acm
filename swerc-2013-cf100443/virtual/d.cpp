#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int N = 11;

#define nl '\n'

string a[N];

string revflip(const string& s) {
  string ans = s;
  reverse(ans.begin(), ans.end());
  for (char& c : ans) {
    if (c == 'L') c = 'R';
    else c = 'L';
  }
  return ans;
}

void pre() {
  a[0] = "";
  for (int i = 1; i < N; i++) {
    a[i] = a[i-1] + 'L';
    a[i] += revflip(a[i-1]);
    //cerr << a[i] << nl;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  pre();
  int T; cin >> T;
  for (int tt = 1; tt <= T; tt++) {
    int n; string s; cin >> n >> s;
    cout << "Case " << tt << ": ";
    if (a[min(n, N-1)].find(s) != -1) {
      cout << "Yes\n";
    } else cout << "No\n";
  }

  return 0;
}
