#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const string hard_consonants = "bcdgknpt";
const set<char> hard(begin(hard_consonants), end(hard_consonants));

char get_hard(char c) {
  auto it = hard.lower_bound(tolower(c));
  if(it == hard.begin()) return isupper(c) ? toupper(*it) : *it;
  char a = isupper(c) ? toupper(*prev(it)) : *prev(it);
  char b = isupper(c) ? toupper(*it) : *it;
  return abs(a - c) <= abs(b - c) ? a : b;
}

string get_end(char c) {
  vector<pair<int,string>> v = {
    pair(abs(c - 'a'), "ah"),
    pair(abs(c - 'o'), "oh"),
    pair(abs(c - 'u'), "uh"),
  };
  return min_element(begin(v), end(v))->second;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  for(string s; cin >> s; ) {
    vector<string> syble;
    for(int i=0; i<s.size(); i++) {
      int j = s.find('-', i);
      if(j == -1) j = s.size();
      syble.push_back(s.substr(i, j-i));
      i = j;
    }
    if(!hard.count(tolower(syble[0].front()))) {
      syble[0].front() = get_hard(syble[0].front());
    }
    for(int i=1; i<syble.size(); i++) {
      for(char &c : syble[i]) {
        if(hard.count(c)) {
          c = tolower(syble[0].front());
        }
      }
    }
    if(hard.count(tolower(syble.back().back()))) {
      syble.push_back(get_end(tolower(syble.back().back())));
    }
    for(string out : syble) {
      cout << out;
    }
    cout << " ";
  }
  cout << nl;

  return 0;
}
