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

bool isvowel(char c, char y = 'y') {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == y;
}

int sybles(string s) {
  // remove nonalpha
  while(!s.empty() && !isalpha(s.back())) {
    s.pop_back();
  }

  // tolower
  for(char& c : s) {
    c = tolower(c);
  }

  // replace qu with q, and replace y with x
  for(int i=1; i<size(s); i++) {
    if(s[i] == 'u' && s[i-1] == 'q') {
      s.erase(begin(s) + i);
    } else if(s[i-1] == 'y' && isvowel(s[i], 0)) {
      s[i-1] = 'x';
    }
  }

  if(!s.empty() && s.back() == 'e') {
    // remove trailing e
    if(size(s) >= 3 && s[size(s)-2] == 'l' && !isvowel(s[size(s)-3])) {
      // pass
    } else {
      s.pop_back();
    }
  } else if(size(s) >= 2 && s.back() == 's' && s[size(s)-2] == 'e') {
    // remove trailing es
    if(size(s) >= 4 && !isvowel(s[size(s)-3]) && !isvowel(s[size(s)-4])) {
      // pass
    } else {
      s.pop_back();
      s.pop_back();
    }
  }

  // count sybles
  int res = 0;
  s.push_back('z');
  for(int i=1; i<size(s); i++) {
    if(isvowel(s[i-1]) && !isvowel(s[i])) {
      res++;
    }
  }
  return max(res, 1);
}

void print_line(vector<string> all) {
  for(int i=0; i<size(all); i++) {
    if(i > 0) cout << " ";
    cout << all[i];
  }
  cout << nl;
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

  vector<string> words;
  vector<int> sum(1, 0);
  for(string s; cin >> s; ) {
    words.emplace_back(s);
    sum.push_back(sum.back() + sybles(s));
  }

  if(sum.back() != 17) {
    print_line(words);
  } else if(!count(begin(sum), end(sum), 5)) {
    print_line(words);
  } else if(!count(begin(sum), end(sum), 12)) {
    print_line(words);
  } else {
    // print haiku
    int i = find(begin(sum), end(sum), 5) - begin(sum);
    int j = find(begin(sum), end(sum), 12) - begin(sum);
    print_line(vector<string>(begin(words), begin(words) + i));
    print_line(vector<string>(begin(words) + i, begin(words) + j));
    print_line(vector<string>(begin(words) + j, end(words)));
  }


  return 0;
}
