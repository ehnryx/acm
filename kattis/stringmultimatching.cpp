#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';

////////////////////////////////////////////////////////////////////////
// Aho-Corasick String Matching -- O(n + m + numMatches)
// WARNING: all pattern strings must be different; patterns 0-indexed
// USAGE:
//  0. AhoCorasick trie;
//  1. trie.insert(pattern) to insert patterns
//  2. trie.build() to build links once all words are inserted
//  3. auto matches = trie.match(string) to find words in string
//*!
struct AhoCorasick {
  struct Node {
    Node *par, *end, *p;
    unordered_map<char,Node*> ch;
        int id;
    Node(Node* u=0): par(u), id(-1) {}
  };

  Node* root;
  vector<int> len;
  int wcnt;
  AhoCorasick(): root(new Node), wcnt(0) {}

  void insert(const string& s) {
    Node* u = root;
    for (char c : s) {
      if (!u->ch.count(c)) u->ch[c] = new Node(u);
      u = u->ch[c];
    }
    assert(u->id==-1); u->id = wcnt++;
    len.push_back(s.size());
  }

  void build() {
    queue<pair<char,Node*>> bfs; bfs.push({0,root});
    while (!bfs.empty()) {
      char c; Node* u; tie(c,u) = bfs.front(); bfs.pop();
      for (const auto& i : u->ch) bfs.push(i);
      u->p = u->end = root;
      if (u!=root) {
        Node* v = u->par->p;
        while (v!=root && !v->ch.count(c)) v = v->p;
        if (v->ch.count(c) && v->ch[c]!=u) u->p = v->ch[c];
        u->end = (u->id==-1 ? u->p->end : u);
      }
    }
  }

  vector<vector<int>> match(const string& s) {
    vector<vector<int>> m(wcnt, vector<int>());
    Node* u = root;
    for (int i=0; i<s.size(); i++) {
      while (u!=root && !u->ch.count(s[i])) u = u->p;
      if (u->ch.count(s[i])) u = u->ch[s[i]];
      for (Node* v=u; v->end!=root; v=v->p) {
        v = v->end; // get matches
                m[v->id].push_back(i-len[v->id]+1);
      }
    }
    return m;
    }
};
//*/

int main() {
  ios::sync_with_stdio(0);

  for (int n; cin>>n; ) {
    AhoCorasick trie;
    string s;
    getline(cin,s);
    for (int i=0; i<n; i++) {
      getline(cin,s);
      trie.insert(s);
    }
    trie.build();
    getline(cin,s);
    auto m = trie.match(s);
    for (int i=0; i<n; i++) {
      for (int j : m[i]) {
        cout << j << " ";
      }
      cout << nl;
    }
  }

  return 0;
}
