#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ ";
  for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
  os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

const int N = 1e5 + 1;
const int Q = 1e5 + 1;

struct DSU {
  int root[N];
  DSU() { memset(root, -1, sizeof root); }
  int find(int i) {
    if (root[i] == -1) return i;
    return root[i] = find(root[i]);
  }
  void link(int i, int j) {
    if (find(i) != find(j))
      root[find(i)] = find(j);
  }
};

DSU dsu;

struct Query {
  int id, left, right;
  Query() {}
  Query(int i, int l, int r): id(i), left(l), right(r) {}
  bool operator < (const Query& other) const {
    if (dsu.find(left) == dsu.find(other.left))
      return right < other.right;
    else
      return dsu.find(left) < dsu.find(other.left);
  }
};
ostream& operator << (ostream& os, const Query& it) {
  return os << "(" << it.id << ": " << it.left << " -- " << it.right << ")";
}

struct Trie {
  struct Node {
    int count;
    map<char, Node*> next;
    Node() { count = 0; }
  };

  int size;
  int ccount[26];
  Node* root;
  Trie() {
    root = new Node;
    size = 0;
    memset(ccount, 0, sizeof ccount);
  }

  void insert(const string& s) {
    //cerr << "INSERTING " << s << endl;
    Node* cur = root;
    for (int i = 0; i < s.size(); i++) {
      if (!cur->next.count(s[i]))
        cur->next[s[i]] = new Node;
      cur = cur->next[s[i]];
      cur->count++;
      if (cur->count == 1) {
        size++;
        if (i > 0)
          ccount[s[i]-'a']++;
      }
    }
  }

  void remove(const string& s) {
    Node* cur = root;
    for (int i = 0; i < s.size(); i++) {
      cur = cur->next[s[i]];
      cur->count--;
      if (cur->count == 0) {
        size--;
        if (i > 0)
          ccount[s[i]-'a']--;
      }
    }
  }
};

struct Memo {
  Trie prefix, suffix;
  vector<string> arr;
  vector<string> rev;

  void add_string(string s) {
    arr.push_back(s);
    reverse(s.begin(), s.end());
    rev.push_back(s);
  }

  void move_left(int start, int end) {
    if (start < end) {
      for ( ; start < end; start++) {
        //cerr << "left: remove " << start << " --> " << arr[start] << endl;
        prefix.remove(arr[start]);
        suffix.remove(rev[start]);
      }
    }
    else {
      for (start--; start >= end; start--) {
        //cerr << "left: insert " << start << " --> " << arr[start] << endl;
        prefix.insert(arr[start]);
        suffix.insert(rev[start]);
      }
    }
  }

  void move_right(int start, int end) {
    if (start < end) {
      for (start++; start <= end; start++) {
        //cerr << "right: insert " << start << " --> " << arr[start] << endl;
        prefix.insert(arr[start]);
        suffix.insert(rev[start]);
      }
    }
    else {
      for ( ; start > end; start--) {
        //cerr << "right: remove " << start << " --> " << arr[start] << endl;
        prefix.remove(arr[start]);
        suffix.remove(rev[start]);
      }
    }
  }

  ll query() {
    ll subs = 0;
    for (int i = 0; i < 26; i++)
      subs += prefix.ccount[i] * suffix.ccount[i];
    //cerr << endl << "QUERY" << endl;
    //cerr << "prefix size: " << prefix.size << endl;
    //cerr << "suffix size: " << suffix.size << endl;
    //cerr << "subs: " << subs << endl << endl;
    return 1LL * prefix.size * suffix.size - subs;
  }
};

Memo memo;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n, q;
  cin >> n >> q;

  int sumlen = 0;
  string s;
  for (int i = 0; i < n; i++) {
    cin >> s;
    memo.add_string(s);
    sumlen += s.size();
  }

  // init DSU
  int curlen, limlen, curroot;
  limlen = sqrt(sumlen);
  curlen = 0;
  curroot = 0;
  for (int i = 0; i < n; i++) {
    if (curlen > limlen) {
      curlen = 0;
      curroot = i;
    }
    dsu.link(curroot, i);
    curlen += memo.arr[i].size();
  }

  // get queries
  vector<Query> queries;
  int a, b;
  for (int i = 0; i < q; i++) {
    cin >> a >> b;
    queries.push_back(Query(i,a-1,b-1));
  }
  sort(queries.begin(), queries.end());

  // do queries
  ll ans[q];
  int left, right;
  left = 0;
  right = -1;
  for (const Query& it : queries) {
    //cerr << endl << "PROCESSING " << it << endl;
    if (it.right >= left) {
      //cerr << "moving right first" << endl;
      memo.move_right(right, it.right);
      memo.move_left(left, it.left);
    }
    else {
      //cerr << "moving left first" << endl;
      memo.move_left(left, it.left);
      memo.move_right(right, it.right);
    }
    right = it.right;
    left = it.left;
    ans[it.id] = memo.query();
    //cerr << "answer to query " << it.id << " is " << ans[it.id] << endl;
  }

  for (int i = 0; i < q; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}
