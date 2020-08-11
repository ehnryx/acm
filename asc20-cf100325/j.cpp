//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "unreachable"

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

vector<string> all;
vector<int> nxt;

bool is_assign(int&, int&);
bool is_return(int&, int&);
bool read_block(int&, int&, bool, bool);
bool read_statement(int&, int&, bool, bool);
bool read_if(int&, int&, bool, bool);

bool is_assign(int& i, int& line) {
  if(all[nxt[i]] != "=") return false;
  int end = nxt[nxt[nxt[i]]];
  assert(all[end] == ";");
  line += end - i - 3;
  i = end;
  return true;
}

bool is_return(int& i, int& line) {
  int end = nxt[nxt[i]];
  if(all[i] != "return" || all[end] != ";") return false;
  line += end - i - 2;
  i = end;
  return true;
}

bool read_if(int& i, int& line, bool ok, bool out) {
  while(all[++i] != ")") line += (all[i] == "\n");
  while(all[++i] == "\n") line++;
  bool if_ok = read_statement(i, line, ok, out);
  pair<int,int> after_if(i, line);

  while(all[++i] == "\n") line++;
  if(all[i] == "else") {
    while(all[++i] == "\n") line++;
    return read_statement(i, line, ok, out) || if_ok;
  } else {
    tie(i, line) = after_if;
    return true;
  }
}

bool read_statement(int& i, int& line, bool ok, bool out) {
  if(!ok && out) {
    cout << "line " << line << ": unreachable statement" << nl;
  }

  if(all[i] == "{") {
    return read_block(i, line, ok, out && ok);
  } if(is_assign(i, line)) {
    return ok;
  } else if(is_return(i, line)) {
    return false;
  } else {
    assert(all[i] == "if");
    return read_if(i, line, ok, out && ok);
  }
}

bool read_block(int& i, int& line, bool ok, bool out) {
  while(all[++i] == "\n") line++;
  if(all[i] == "}") return ok;
  ok &= read_statement(i, line, ok, out);
  return read_block(i, line, ok, out);
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  string token;
  for(char c; (c = getchar()) != EOF; ) {
    if(isalpha(c)) {
      token.push_back(c);
    } else {
      if(!token.empty()) {
        all.push_back(token);
      }
      token.clear();
      if(c == '\n' || !isspace(c)) {
        all.push_back(string(1, c));
      }
    }
  }
  all.resize(all.size() + 7, string(1, '\n'));

  nxt.resize(all.size());
  iota(nxt.begin(), nxt.end(), 1);
  int last = all.size() - 6;
  for(int i=all.size()-7; i>=0; i--) {
    if(all[i] == "\n") continue;
    nxt[i] = last;
    last = i;
  }

  int line = 1;
  for(int i = 0; ; i++) {
    line += (all[i] == "\n");
    if(all[i] == "{") {
      read_block(i, line, true, true);
      break;
    }
  }

  return 0;
}
