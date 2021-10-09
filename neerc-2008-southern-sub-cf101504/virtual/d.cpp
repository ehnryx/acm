#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

struct Event {
  char c;
  string s;
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  vector<Event> events;
  unordered_set<string> all;
  for (int i=0; i<n; i++) {
    char c; string s;
    cin >> c >> s;
    events.push_back({c, s});
    all.insert(s);
  }

  string perm = "abcdef";
  vector<string> extra;
  for (int i=0; i<400; i++) {
    if (!all.count(perm)) {
      extra.push_back(perm);
    }
    next_permutation(perm.begin(), perm.end());
  }

  vector<string> ans;

  unordered_set<string> current;
  for (int i=0; i<n; i++) {
    const Event& it = events[i];
    if (it.c == '+') {
      if (current.count(it.s)) {
        ans.push_back("- "+it.s);
        current.erase(it.s);
      }
      current.insert(it.s);
      ans.push_back("+ "+it.s);
    }

    else if (it.c == '-') {
      if (!current.count(it.s)) {
        ans.push_back("+ "+it.s);
        current.insert(it.s);
      }
      current.erase(it.s);
      ans.push_back("- "+it.s);
    }

    else {
      int goal = stoi(it.s);
      int cur = current.size();

      if (cur > goal) {
        // just get the things
        unordered_set<string> seen;
        vector<int> ip, im;
        for (int j=i+1; j<n; j++) {
          if (events[j].c == '+') {
            if (!seen.count(events[j].s)) {
              seen.insert(events[j].s);
              ip.push_back(j);
            }
          } else if (events[j].c == '-') {
            if (!seen.count(events[j].s)) {
              seen.insert(events[j].s);
              im.push_back(j);
            }
          }
        }
        reverse(im.begin(), im.end());
        vector<string> unseen;
        for (const string& s : current) {
          if (!seen.count(s)) {
            unseen.push_back(s);
          }
        }

        // do the things
        for (int j : ip) {
          if (cur == goal) break;
          if (current.count(events[j].s)) {
            ans.push_back("- "+events[j].s);
            current.erase(events[j].s);
            cur--;
          }
        }
        for (const string& s : unseen) {
          if (cur == goal) break;
          if (current.count(s)) {
            ans.push_back("- "+s);
            current.erase(s);
            cur--;
          }
        }
        for (int j : im) {
          if (cur == goal) break;
          if (current.count(events[j].s)) {
            ans.push_back("- "+events[j].s);
            current.erase(events[j].s);
            cur--;
          }
        }
      }

      else if (cur < goal) {
        // just get the things
        unordered_set<string> seen;
        vector<int> im;
        for (int j=i+1; j<n; j++) {
          if (events[j].c == '+') {
            seen.insert(events[j].s);
          } else if (events[j].c == '-') {
            if (!seen.count(events[j].s)) {
              seen.insert(events[j].s);
              im.push_back(j);
            }
          }
        }

        // do the things
        for (int j : im) {
          if (cur == goal) break;
          if (!current.count(events[j].s)) {
            ans.push_back("+ "+events[j].s);
            current.insert(events[j].s);
            cur++;
          }
        }
        for (const string& s : extra) {
          if (cur == goal) break;
          if (!current.count(s)) {
            ans.push_back("+ "+s);
            current.insert(s);
            cur++;
          }
        }
      }
      ans.push_back("= "+it.s);
    }
  }

  cout << ans.size() << nl;
  for (const string& s : ans) {
    cout << s << nl;
  }

  return 0;
}
