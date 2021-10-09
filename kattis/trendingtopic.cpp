#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  vector<unordered_map<string,int>> days;
  unordered_map<string,int> cnt;
  map<int,set<string>> ans;

  string line;
  while (getline(cin,line)) {
    if (line == "<text>") {
      days.push_back(unordered_map<string,int>());
      unordered_map<string,int>& cur = days.back();
      while (getline(cin,line), line != "</text>") {
        istringstream ss(line);
        string s;
        while (ss >> s) {
          if (s.size() > 3) {
            ans[cnt[s]].erase(s);
            cur[s]++;
            cnt[s]++;
            cerr << "add to " << s << nl;
          }
        }
      }
      if (days.size() > 7) {
        const unordered_map<string,int>& del = days[days.size()-8];
        for (const pair<string,int>& it : del) {
          ans[cnt[it.first]].erase(it.first);
          cnt[it.first] -= it.second;
          cerr << "sub " << it.second << " from " << it.first << nl;
          ans[cnt[it.first]].insert(it.first);
        }
      }
      for (const pair<string,int>& it : cur) {
        ans[cnt[it.first]].insert(it.first);
      }
    }
    else if (line.size() > 3) {
      istringstream ss(line);
      string _; int n;
      ss >> _ >> n;
      cout << "<top " << n << ">" << nl;
      for (auto it=ans.rbegin(); it!=ans.rend() && n>0; it++) {
        n -= it->second.size();
        for (const string& s : it->second) {
          cout << s << " " << it->first << nl;
        }
      }
      cout << "</top>" << nl;
    }
  }

  return 0;
}
