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

struct Line {
  int label; string command;
  string body, op;
  char var, a, b;
  int value, va, vb;
  bool empty;
  Line (int l, const string& s): label(l), command(s) {
    var = a = b = 0;
    empty = false;
  }
  void add_a(const string& s) {
    if (s[0]=='-'||isdigit(s[0])) va = stoi(s);
    else a = s[0];
  }
  void add_b(const string& s) {
    if (s[0]=='-'||isdigit(s[0])) vb = stoi(s);
    else b = s[0];
  }
};

bool compare(int a, const string& op, int b) {
  if (op=="=") return a==b;
  if (op=="<") return a<b;
  if (op==">") return a>b;
  if (op=="<=") return a<=b;
  if (op==">=") return a>=b;
  if (op=="<>") return a!=b;
  assert(false);
}

int calculate(int a, const string& op, int b) {
  if (op=="+") return a+b;
  if (op=="-") return a-b;
  if (op=="*") return a*b;
  if (op=="/") return a/b;
  assert(false);
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

  string _;

  int var[26];
  memset(var, 0, sizeof var);

  string s;
  vector<Line> line;

  while (getline(cin, s)) {
    istringstream ss(s);
    int label; string command;
    ss >> label >> command;
    line.push_back(Line(label,command));
    Line& cur = line.back();

    if (command[0] == 'L') {
      string num;
      ss >> cur.var >> _;
      ss >> num;
      cur.add_a(num);
      if (ss >> cur.op) {
        ss >> num;
        cur.add_b(num);
      } else {
        cur.empty = true;
      }
    }

    else if (command[0] == 'I') {
      string num;
      ss >> num;
      cur.add_a(num);
      ss >> cur.op;
      ss >> num;
      cur.add_b(num);
      ss >> _ >> _ >> cur.value;
    }

    else {
      if (s.back() == '"') {
        string body;
        getline(ss, body);
        cur.body = body.substr(2,body.size()-3);
      } else {
        ss >> cur.var;
      }
    }
  }

  int n = line.size();
  map<ll,int> index;
  for (int i=0; i<n; i++) {
    index[line[i].label] = i;
  }

  for (auto cur = index.begin(); cur != index.end(); ) {
    auto nxt = next(cur);
    const Line& it = line[cur->second];

    if (it.command[0] == 'L') {
      if (it.empty) {
        var[it.var-'A'] = (it.a ? var[it.a-'A'] : it.va);
      } else {
        var[it.var-'A'] = calculate(it.a ? var[it.a-'A'] : it.va, it.op, it.b ? var[it.b-'A'] : it.vb);
      }
    }

    else if (it.command[0] == 'I') {
      int a = (it.a ? var[it.a-'A'] : it.va);
      int b = (it.b ? var[it.b-'A'] : it.vb);
      if (compare(a, it.op, b)) {
        nxt = index.find(it.value);
      }
    }

    else {
      if (it.var) cout << var[it.var-'A'];
      else cout << it.body;
      if (it.command.back() == 'N') {
        cout << nl;
      }
    }

    cur = nxt;
  }

  return 0;
}
