#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
typedef long long ll;
namespace eertree{
  struct Node {
    int i, j, sz, suf;
    int to[26];
  };
  Node tree[MAXN];
  int f[MAXN], cnt[MAXN];
  int currNode, n;
  string s;
  int newNode(int l, int r){
    Node &no = tree[++n];
    f[n] = 0;
    no.i = l, no.j = r, no.sz = r-l+1;
    memset(no.to, 0, sizeof(no.to));
    return n;
  }
  void init(){
    n = 0;
    newNode(0, -2);
    tree[1].suf = 1;
    newNode(0, -1);
    tree[2].suf = 1;
    currNode = 1;
    s.clear();
  }
  int getId(char c){
    return c-'a';
  }
  // O(1) amortized
  void add(char c){
    int tmp = currNode, idx = s.size(), idC = getId(c);
    s += c;
    while (true) { 
      int sz = tree[tmp].sz; 
      if (idx - sz >= 1 and s[idx] == s[idx-sz-1]) 
        break;
      tmp = tree[tmp].suf; 
    } 
    if(tree[tmp].to[idC] != 0) { 
      currNode = tree[tmp].to[idC];
    }else{
      currNode = newNode(idx - (tree[tmp].sz + 2) + 1, idx);
      tree[tmp].to[idC] = currNode;
      tmp = tree[tmp].suf;
      if (tree[currNode].sz == 1) {
        tree[currNode].suf = 2;
      }else{
        while (true) { 
          int sz = tree[tmp].sz; 
          if (idx-sz >= 1 and s[idx] == s[idx-sz-1]) 
            break; 
          tmp = tree[tmp].suf; 
        } 
        tree[currNode].suf = tree[tmp].to[idC];
      }
    }
    f[currNode]++;
  }
  //Returns the total of distinct palindrome substrings
  int size(){
    return n - 2;
  }
  // Calculates the number of equal palindromes and saves in cnt
  // Returns the total of palindrome substrings
  ll precompute(){
    ll ans = 0;
    for(int i=0; i<=n; i++) cnt[i] = f[i];
    for(int i=n; i>=3; i--){
      ans += cnt[i];
      cnt[tree[i].suf] += cnt[i];
    }
    return ans;
  }
  int count(int id){
    return cnt[id];
  }
  //O(N^2)
  void show(){
    ll ans = precompute();
    cout << "Total Palindrome Substrings: " << ans << endl;
    cout << "Total of distinct palindrome substrings: " << size() << endl;
    for(int i=3; i <= n; i++)
      cout << s.substr(tree[i].i, tree[i].sz) << ": " << cnt[i] << endl;
  }
};