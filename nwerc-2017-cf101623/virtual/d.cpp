#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

unordered_map<string, vector<string>> correct, incorrect;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n; cin >> n;
  vector<string> sentence(n);
  for (auto& s : sentence) cin >> s;
  int m; cin >> m;
  for (int i = 0; i < m; i++) {
    string d, e, c; cin >> d >> e >> c;
    if (c[0] == 'c') correct[d].push_back(e);
    else incorrect[d].push_back(e);
  }
  ll ans1 = 1, tot = 1; vector<string> ans;
  for (const string& s : sentence) {
    if (correct[s].size() + incorrect[s].size() == 1) {
      if (correct[s].size() == 1) ans.push_back(correct[s][0]);
      else ans.push_back(incorrect[s][0]);
    }
    ans1 *= correct[s].size();
    tot *= correct[s].size() + incorrect[s].size();
  }
  if (tot == 1) {
    for (const string& s : ans) cout << s << " ";
    cout << nl;
    if (ans1 == 1) cout << "correct\n";
    else cout << "incorrect\n";
  } else {
    cout << ans1 << " correct\n" << tot - ans1 << " incorrect\n";
  }

  return 0;
}
