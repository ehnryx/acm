#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

map<string,int> dict;
struct Team {
  int solved, t, id;
  int wa[20];
  Team(int s, int t, int id) {
    this->solved = s;
    this->t = t;
    this->id = id;
    memset(wa, 0, sizeof(wa));
  }
  bool operator > (const Team& other) const {
    if (solved != other.solved) return solved > other.solved;
    else if (t != other.t) return t < other.t;
    else return id < other.id;
  }
  void insert(char pb, int time, string verdict) {
    if (verdict == "NO") wa[pb-'A']++;
    else {
      solved++;
      t += time + wa[pb-'A']*20;
    }
    //cerr << "solved: " << solved << " time: " << t << nl;
  }
};
struct Sub {
  string team;
  char pb;
  int time;
  string verd;
  Sub(string team, char pb, int time, string verd) {
    this->team = team;
    this->pb = pb;
    this->time = time;
    this->verd = verd;
  }
  bool operator < (const Sub& other) const {
    if (time != other.time) return time < other.time;
    else return dict[team] < dict[other.team];
  }
};

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  int n, m, p;
  string s, verdict;
  char pb;
  int time;
  vector<Team> teams;
  vector<Sub> subs;
  cin >> n >> m >> p;
  for (int i = 0; i < n; i++) {
    cin >> s;
    dict.insert(pair<string,int>(s, i));
    teams.push_back(Team(0, 0, i));
  } 
  for (int i = 0; i < m; i++) {
    cin >> s >> pb >> time >> verdict;
    subs.push_back(Sub(s, pb, time, verdict));
  } sort(subs.begin(), subs.end());

  bool istop = true;
  int ans = 0;
  int leader = 0;
  for (int i = 0; i < m; i++) {
    //cerr << subs[i].team << ": " << dict[subs[i].team] << " at " << subs[i].time << nl;
    int curr = dict[subs[i].team];
    teams[curr].insert(subs[i].pb, subs[i].time, subs[i].verd);
    if (teams[curr] > teams[leader])
      leader = curr;
    if (i == 0) {
      ans += subs[i].time;
    }
    else if (istop) {
      ans += subs[i].time - subs[i-1].time;
    }
    if (leader != 0) 
      istop = false;
    else 
      istop = true;
  }
  if (istop == true) {
    ans += 300 - subs.back().time;
  }
  cout << ans << nl;

  return 0;
}
