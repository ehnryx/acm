//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  for(int n; cin >> n && n; ) {
    vector<pair<string,string>> order;
    unordered_map<string,unordered_map<string,string>> memo;
    unordered_map<string,unordered_map<string,int>> rank;
    for(int i=0; i<n; i++) {
      string first, last, bib;
      cin >> first >> last >> bib;
      order.push_back(make_pair(last + ", " + first, bib));
    }
    sort(order.begin(), order.end());
    unordered_map<string,map<int,vector<string>>> times;
    for(int i=0; i<3*n; i++) {
      string bib, s, t;
      cin >> bib >> s >> t;
      memo[bib][s] = t;
      int h = stoi(t.substr(0, 2));
      int m = stoi(t.substr(3, 2));
      times[s][60*h+m].push_back(bib);
    }
    for(const auto& it : times) {
      string s = it.first;
      int rk = 1;
      for(const auto& jt : it.second) {
        for(const string& bib : jt.second) {
          rank[bib][s] = rk;
        }
        rk += jt.second.size();
      }
    }
    cout << left << setw(20) << "NAME";
    cout << right << setw(10) << "BIB";
    cout << right << setw(10) << "SPLIT1";
    cout << right << setw(10) << "RANK";
    cout << right << setw(10) << "SPLIT2";
    cout << right << setw(10) << "RANK";
    cout << right << setw(10) << "FINISH";
    cout << right << setw(10) << "RANK";
    cout << nl;
    for(const auto& [name, bib] : order) {
      cout << left << setw(20) << name;
      cout << right << setw(10) << bib;
      cout << right << setw(10) << memo[bib]["S1"];
      cout << right << setw(10) << rank[bib]["S1"];
      cout << right << setw(10) << memo[bib]["S2"];
      cout << right << setw(10) << rank[bib]["S2"];
      cout << right << setw(10) << memo[bib]["F"];
      cout << right << setw(10) << rank[bib]["F"];
      cout << nl;
    }
    cout << nl;
  }

  return 0;
}
