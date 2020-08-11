//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "fool"

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

const vector<pair<char,int>> rank_values = {
  {'6', 0},
  {'7', 1},
  {'8', 2},
  {'9', 3},
  {'T', 4},
  {'J', 5},
  {'Q', 6},
  {'K', 7},
  {'A', 8},
};

const map<char,int> ranks(rank_values.begin(), rank_values.end());

vector<int> get(const vector<int>& v, int bm) {
  vector<int> res;
  for(int it : v) {
    if(bm & 1<<it) {
      res.push_back(it);
    }
  }
  return res;
}

int cover(const vector<int>& v, const vector<int>& o) {
  for(int i=0, j=0; i<v.size(); i++, j++) {
    while(j<o.size() && o[j]<=v[i]) {
      j++;
    }
    if(j == o.size()) {
      return (int)v.size() - i;
    }
  }
  return 0;
}

bool solve(char trump, int bm, const vector<map<char,vector<int>>> hand) {
  //cerr<<"solve "<<bitset<9>(bm)<<nl;
  int left = 0;
  for(const auto& [suit, cards] : hand[0]) {
    vector<int> put = get(cards, bm);
    int need = cover(put, get(hand[1].at(suit), bm));
    if(suit == trump && need > 0) return false;
    left += need;
  }
  int tcov = get(hand[1].at(trump), bm).size();
  int tput = get(hand[0].at(trump), bm).size();
  return left <= tcov - tput;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif
//*/

  int n;
  char trump;
  cin >> n >> trump;

  int base = 0;
  vector<map<char,vector<int>>> hand(2);
  for(int t=0; t<2; t++) {
    hand[t] = { {'S', {}} , {'D', {}}, {'C', {}}, {'H', {}} };
    for(int i=0; i<n; i++) {
      string s;
      cin >> s;
      int value = ranks.at(s[0]);
      if(s.back() == '*') {
        base |= 1 << value;
        s.pop_back();
      }
      hand[t][s[1]].push_back(value);
    }

    for(auto& [_, v] : hand[t]) {
      sort(v.begin(), v.end());
    }
  }

  for(int bm=0; bm<1<<9; bm++) {
    if((base & bm) != base) continue;
    if(solve(trump, bm, hand)) {
      cout << "COVER" << nl;
      return 0;
    }
  }
  cout << "TAKE" << nl;

  return 0;
}
