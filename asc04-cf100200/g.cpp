//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(4);

#ifdef ONLINE_JUDGE
  freopen("ranking.in", "r", stdin);
  freopen("ranking.out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<string> name(n+1);
  getline(cin, name[0]);
  int namelen = 0;
  for(int i=1; i<=n; i++) {
    getline(cin, name[i]);
    namelen = max(namelen, (int)name[i].size());
    //cerr<<name[i]<<nl;
  }
  vector<ld> ans(n+1);
  vector<int> take(n+1);

  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    //cerr<<"DO CONTEST "<<i<<nl;
    int k;
    cin >> k;
    //cerr<<"teams: "<<k<<endl;
    vector<int> cur(k);
    for(int j=0; j<k; j++) {
      cin >> cur[j];
      take[cur[j]]++;
    }

    int problems;
    cin >> problems;
    int runs;
    cin >> runs;
    vector<int> penalty(n+1);
    vector<int> score(n+1);
    vector<vector<int>> attempt(n+1, vector<int>(problems));
    vector<vector<bool>> done(n+1, vector<bool>(problems));
    //cerr<<"runs: "<<runs<<nl;
    int maxscore = 0;
    for(int j=0; j<runs; j++) {
      int team; char p; int t; char c;
      cin >> team >> p >> t >> c;
      //cerr<<"@ run "<<team<<" "<<p<<" "<<t<<" "<<c<<nl;
      if(c == '-') {
        attempt[team][p-'A']++;
      } else if(!done[team][p-'A']) {
        done[team][p-'A'] = true;
        score[team]++;
        penalty[team] += t + attempt[team][p-'A'] * 20;
        maxscore = max(maxscore, score[team]);
      }
    }
    //cerr<<"done runs"<<nl;

    vector<tuple<int,int,int>> order;
    for(int j : cur) {
      order.emplace_back(-score[j], penalty[j], j);
      //cerr<<j<<" -> problems: "<<score[j]<<"  penalty: "<<penalty[j]<<nl;
    }
    sort(order.begin(), order.end());

    vector<int> rank(n+1);
    int currank = 1;
    pair<int,int> pre(-1, -1);
    int prej = -1;
    for(auto [s, p, j] : order) {
      if(make_pair(s, p) == pre) {
        rank[j] = rank[prej];
      } else {
        rank[j] = currank;
      }
      pre = make_pair(s, p);
      prej = j;
      currank++;
    }

    for(int j : cur) {
      ld rawscore = maxscore ? (ld) score[j] / maxscore : (ld) 0;
      ld res = rawscore * (2*k-2) / (rank[j] + k-2);
      //cerr<<"team "<<j<<":  rawscore: "<<rawscore<<"  score: "<<res<<"  rank: "<<rank[j]<<nl;
      ans[j] += res;
    }
    //cerr<<nl;
  }

  vector<pair<ld,string>> out;
  for(int i=1; i<=n; i++) {
    if(take[i] > 0) ans[i] /= take[i];
    out.emplace_back(ans[i], name[i]);
  }
  sort(out.begin(), out.end(), [](const auto& a, const auto& b) {
    return a.first > b.first || (a.first == b.first && a.second < b.second);
  });

  for(auto [score, team] : out) {
    cout << left << setw(namelen) << team << " " << score << nl;
  }

  return 0;
}
