#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

struct Runner {
  string name;
  double first, other;
  Runner(string n, double f, double o):
    name(n), first(f), other(o) {}
  bool operator < (const Runner& o) const {
    return other < o.other;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;
  vector<Runner> runners;
  for(int i=0; i<n; i++) {
    string name;
    double first, other;
    cin >> name >> first >> other;
    runners.emplace_back(name, first, other);
  }

  pair<double,vector<string>> best(1e19, {});
  for(int i=0; i<n; i++) {
    vector<Runner> others = runners;
    others.erase(others.begin() + i);
    sort(others.begin(), others.end());

    vector<string> names = {runners[i].name};
    double time = runners[i].first;
    for(int j=0; j<3; j++) {
      time += others[j].other;
      names.push_back(others[j].name);
    }
    best = min(best, make_pair(time, names));
  }

  cout << best.first << nl;
  for(string s : best.second) {
    cout << s << nl;
  }

  return 0;
}
