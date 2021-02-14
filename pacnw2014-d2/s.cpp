#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;


int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<string> ballot(n);
    vector<int> cnt(26), alive(26);
    for(int i=0; i<n; i++) {
      cin >> ballot[i];
      cnt[ballot[i][0] - 'A'] += 1;
      for(char c : ballot[i]) {
        alive[c - 'A'] = true;
      }
    }

    bool done = false;
    vector<string> ans;
    while(!ballot.empty()) {
      int most = max_element(cnt.begin(), cnt.end()) - cnt.begin();
      if(2 * cnt[most] > ballot.size()) {
        ans.push_back(string(1, 'A' + most));
        done = true;
        break;
      }

      string rem;
      int best = INF;
      for(int i=0; i<26; i++) {
        if(!alive[i]) continue;
        if(cnt[i] < best) {
          best = cnt[i];
          rem.clear();
        }
        if(cnt[i] == best) {
          rem.push_back('A' + i);
        }
      }
      sort(rem.begin(), rem.end());
      ans.push_back(rem);

      fill(cnt.begin(), cnt.end(), 0);
      fill(alive.begin(), alive.end(), 0);
      vector<string> new_ballots;
      for(const string& s : ballot) {
        string add;
        for(char c : s) {
          if(find(rem.begin(), rem.end(), c) == rem.end()) {
            add.push_back(c);
            alive[c - 'A'] = true;
          }
        }
        if(!add.empty()) {
          new_ballots.push_back(add);
          cnt[add[0] - 'A'] += 1;
        }
      }
      ballot = move(new_ballots);
    }

    if(!done) {
      ans.push_back("no winner");
    }

    cout << ans[0];
    for(int i=1; i<ans.size(); i++) {
      cout << " -> " << ans[i];
    }
    cout << nl;
  }

  return 0;
}
