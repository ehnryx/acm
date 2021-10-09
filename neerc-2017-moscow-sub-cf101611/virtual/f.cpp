#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

typedef tuple<int,int,int,string> cmp;

struct Team {
  string name;
  int n;
  vector<bool> ac;
  vector<int> sub;
  int score, tot, last;

  Team(string s): name(s), n(0), score(0), tot(0), last(0) {}

  void add(char c, int a, int t) {
    n++;
    ac.push_back(c == '+');
    sub.push_back(a);
    if (c == '+') {
      score += 1;
      tot += t + 20*(a-1);
      last = max(last, t);
    }
  }

  cmp best() const {
    int bscore = score;
    int btot = tot;
    int blast = last;
    for (int i=0; i<n; i++) {
      if (!ac[i]) {
        bscore += 1;
        btot += 20*sub[i] + 240;
        blast = max(blast, 240);
      }
    }
    return cmp(-bscore, btot, blast, name);
  }

  cmp cur() const {
    return cmp(-score, tot, last, name);
  }
};


int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, m, k;
  cin >> n >> m >> k;

  vector<Team> frozen;
  for (int i=0; i<m; i++) {
    string s;
    cin >> s;
    frozen.push_back(Team(s));
    for (int j=0; j<n; j++) {
      char c; int a, t;
      cin >> c >> a >> t;
      frozen.back().add(c,a,t);
    }
  }

  vector<Team> done;
  unordered_set<string> subset;
  for (int i=0; i<k; i++) {
    string s;
    cin >> s;
    subset.insert(s);
    done.push_back(Team(s));
    for (int j=0; j<n; j++) {
      char c; int a, t;
      cin >> c >> a >> t;
      done.back().add(c,a,t);
    }
  }

  bool good = true;
  for (int i=0; i<m; i++) {
    if (!subset.count(frozen[i].name)) {
      good &= frozen[i].cur() > done[k-1].cur() || done[0].cur() > frozen[i].best();
    }
  }

  if (good) {
    cout << "Leaked" << nl;
  } else {
    cout << "Fake" << nl;
  }

  return 0;
}
