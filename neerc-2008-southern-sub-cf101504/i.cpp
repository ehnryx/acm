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

struct Team {
  string name;
  int rank;
  int solves;
  int penalty;
  bool self;
  vector<int> pb;

  Team(vector<string>& line, string& team, int problems): self(false) {
    rank = stoi(line[0]);
    for (int i=0; i<problems; i++) {
      if (line.back()[0] == '.') pb.push_back(0);
      else if (line.back()[0] == '-') pb.push_back(stoi(line.back()));
      line.pop_back();
      while (!isspace(team.back())) team.pop_back();
      while (isspace(team.back())) team.pop_back();
    }
    sort(pb.begin(), pb.end());

    penalty = stoi(line.back());
    line.pop_back();
    while (!isspace(team.back())) team.pop_back();
    while (isspace(team.back())) team.pop_back();
    solves = stoi(line.back());
    line.pop_back();
    while (!isspace(team.back())) team.pop_back();
    while (isspace(team.back())) team.pop_back();

    int start = 0;
    while (!isspace(team[start])) start++;
    while (isspace(team[start])) start++;
    name = team.substr(start);
  }

  bool operator < (const Team& o) const {
    if (solves != o.solves) return solves > o.solves;
    if (penalty != o.penalty) return penalty < o.penalty;
    return self > o.self;
  }

  int fill(int problems, int left) {
    if (left < problems.size()) {
    }
  }
};

struct Contest {
  int n, problems, balloons;
  int self;
  vector<Team> teams;

  Contest(const string& header): n(0) {
    istringstream ss(header);
    vector<string> line;
    for (string s; ss >> s; ) {
      line.push_back(s);
    }
    problems = line.size() - 4;
  }

  bool add_team(string& team) {
    ++n;
    istringstream ss(team);
    vector<string> line;
    for (string s; ss >> s; ) {
      line.push_back(s);
    }
    if (line.size() == 1) {
      balloons = stoi(line[0]);
      return false;
    } else {
      teams.push_back(Team(line, team, problems));
      return true;
    }
  }

  void add_self(const string& s) {
    for (int i=0; i<n; i++) {
      if (team[i].name == s) {
        team.self = true;
        self = i;
        break;
      }
    }
  }

  int win() const {
    vector<Team> temp = teams;
    int cur = balloons;
    cur -= temp[i].fill_win(problems, cur);
    for (int i=0; i<n && cur>0; i++) {
      cur -= temp[i].fill_win(problems, cur);
    }
    get_rank(temp);
  }

  int lose() const {
    vector<Team> temp = teams;
  }

  int get_rank(vector<Team>& temp) {
    sort(temp.begin(), temp.end());
    for (int i=0; i<n; i++) {
      if (temp[i].self) {
        return i+1;
      }
    }
    assert(false);
  }
};

void solve(const string& header) {
  Contest cur(header);
  string s;
  getline(cin, s);
  while (cur.add_team(s)) {
    getline(cin, s);
  }
  getline(cin, s);
  cur.add_self(s);
  cout << cur.win() << " " << cur.lose() << nl;
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  for (string header; getline(cin, header); ) {
    solve(header);
  }

  return 0;
}
