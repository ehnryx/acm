#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
constexpr char nl = '\n';

#define FNAME "epic"

const int N = 50500;
const int R = 1, P=2, S=3;

struct Node {
  int type;
  int edge[4];
  int next(int t) {
    return edge[t];
  }
};

Node me[N], them[110];
vector<int> members[N];
int par[N];
int n;
int zz;

int multipar(int u, int height) {
  for (int i=0; i<height; ++i) {
    u = par[u];
  }
  return u;
}

int ctoi(char c) {
  if (c == 'R') {
    return R;
  } else if (c == 'P') {
    return P;
  } else if (c == 'S') {
    return S;
  }
  return 0;
}
const string RPS_STRING = "RPS";
char itoc(int i) {
  if (i < 1 || i > 3) {
    return ' ';
  }
  return RPS_STRING[i-1];
}

int add_nxt(int pre, int edge_id, const vector<int>& mem) {
  int u = ++zz;
  par[u] = pre;
  for (auto& x : mem) {
    members[u].push_back(x);
  }
  me[pre].edge[edge_id] = u;
  return u;
}

int aggregate_type(const vector<int>& mem) {
  int type = 0;
  for (auto& x : mem) {
    if (!type) {
      type = them[x].type;
    } else {
      if (type != them[x].type) {
        return 0;
      }
    }
  }
  return type;
}

int opp(int t) {
  return t%3+1;
}

unordered_map<int, int> solve_seen;
void solve(int here, int there) {
  solve_seen.clear();
  solve_seen[there] = here;
  int ohere = here;
  int q = 0;
  while(true) {
    //cerr << "      SOLVING " << there << " (" << othere << ")" << endl;
    int their_choice = them[there].type;
    me[here].type = opp(their_choice);
    there = them[there].edge[me[here].type];

    if (solve_seen.count(there)) {
      me[here].edge[their_choice] = solve_seen[there];
      break;
    } else {
      me[here].edge[their_choice] = ++zz;
      here = zz;
      solve_seen[there] = here;
    }
  }
}

queue<int> q;
vector<int> v[4];
void split(int u, int type) {
  me[u].type = type;
  for (int i=0; i<4; ++i) {
    v[i].clear();
  }
  //cerr << " ! " << members[u].size() << endl;
  for (auto& x : members[u]) {
    v[them[x].type].push_back(them[x].next(type));
    //cerr << " -> " << them[x].type << endl;
  }
  for (int i=1; i<4; ++i) {
    if (v[i].size()) {
      int w = add_nxt(u, i, v[i]);
      //cerr << " new " << w << endl;
      q.push(w);
    }
  }
}

int main() {
  string __fname = FNAME;
#ifdef ONLINE_JUDGE
  freopen(FNAME ".in", "r", stdin);
  freopen(FNAME ".out", "w", stdout);
#endif
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i=1; i<=n; ++i) {
    string type;
    cin >> type;
    int a, b, c;
    cin >> a >> b >> c;
    them[i].type = ctoi(type[0]);
    //cerr << " !! " << them[i].type << endl;
    them[i].edge[1] = a;
    them[i].edge[2] = b;
    them[i].edge[3] = c;
    members[1].push_back(i);
  }

  zz = 1;
  q.push(1);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    if (members[u].size() == 1) {
      solve(u, members[u][0]);
      continue;
    }
    int atype = aggregate_type(members[u]);
    if (atype) {
      int pre100 = multipar(u, n);
      if (pre100 && members[u].size() == members[pre100].size()) {
        solve(u, members[u][0]);
        continue;
      } else {
        split(u, opp(atype));
      }
    } else {
      split(u, R);
    }
  }
  ++zz;
  cout << zz << "\n";
  for (int i=1; i<zz; ++i) {
    cout << itoc(me[i].type);
    for (int j=1; j<=3; ++j) {
      cout << " " << (me[i].edge[j] ? me[i].edge[j] : zz);
    }
    cout << "\n";
  }
  cout << "R " << zz << " " << zz << " " << zz << "\n";

  return 0;
}

/*
 * 
 * 
2
R 1 1 2
P 2 2 1
 * 
 * 
 * 5
 * R 2 3 5
 * P 2 5 5
 * S 5 4 5
 * P 3 5 5
 * R 5 5 5
 *
 *
 *
 */
