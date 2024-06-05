#include <bits/stdc++.h>
#define pb push_back
#define F first
#define S second
#define MP make_pair
#define all(x) x.begin(),x.end()
#define Hagry ios::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
 
using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vpi = vector <pair<int, int>>;
using vvi = vector <vector<int>>;
 
const int N = 2e5 + 5;
 
// Not well tested
const ll OO = 1e18 + 5;
const ll maxN = 1e9 + 5;
struct Line {
    ll m, c;
    Line() : m(0), c(-OO) {}
    Line(ll m, ll c) : m(m), c(c) {}
};
 
ll sub(ll x, Line l) {
    return x * l.m + l.c;
}
 
// Persistent Li Chao
struct Node {
    // range I am responsible for
    Line line;
    Node *left, *right;
 
    Node() {
        left = right = NULL;
    }
 
    Node(ll m, ll c) {
        line = Line(m, c);
        left = right = NULL;
    }
 
    void extend(int l, int r) {
        if (left == NULL && l != r) {
            left = new Node();
            right = new Node();
        }
    }
 
    Node* copy(Node* node){
        Node* newNode = new Node;
        newNode->left = node->left;
        newNode->right = node->right;
        newNode->line = node->line;
        return newNode;
    }
 
    Node* add(Line toAdd, int l, int r) {
        assert(l <= r);
        int mid = (l + r) / 2;
        Node* cur = copy(this);
        if (l == r) {
            if (sub(l, toAdd) > sub(l, cur->line))
                swap(toAdd, cur->line);
            return cur;
        }
        bool lef = sub(l, toAdd) > sub(l, cur->line);
        bool midE = sub(mid+1, toAdd) > sub(mid+1, cur->line);
        if(midE)
            swap(cur->line, toAdd);
        cur->extend(l, r);
        if(lef != midE)
            cur->left = cur->left->add(toAdd, l, mid);
        else
            cur->right = cur->right->add(toAdd, mid+1, r);
        return cur;
    }
 
    Node* add(Line toAdd) {
        return add(toAdd, 0, maxN-1);
    }
 
    ll query(ll x, int l, int r) {
        int mid = (l + r) / 2;
        if (l == r || left == NULL)
            return sub(x, line);
        extend(l, r);
        if (x <= mid)
            return max(sub(x, line), left->query(x, l, mid));
        else
            return max(sub(x, line), right->query(x, mid+1, r));
    }
 
    ll query(ll x) {
        return query(x, 0, maxN-1);
    }
 
    void clear() {
        if (left != NULL) {
            left->clear();
            right->clear();
        }
        delete this;
    }
};
Node* tree[N];
int par[N];
vector<pl> Queries[N];
vi childs[N];
ll PR[N], bonus[N], ans[N];
 
void dfs(int u){
    tree[u] = tree[par[u]]->add(Line(PR[u], bonus[u]));
    for(auto que:Queries[u]){
        ans[que.F] = tree[u]->query(que.S);
    }
    for(auto e:childs[u]){
        dfs(e);
    }
}
 
 
void TC(){
    int n, q;
    cin >> n >> q;
 
    int id, Pid;
    for(int i=0; i<n; ++i){
        cin >> id >> Pid;
        cin >> PR[id] >> bonus[id];
        par[id] = Pid;
        childs[Pid].pb(id);
    }
    int D;
    for(int i=0; i<q; ++i){
        cin >> id >> D;
        Queries[id].push_back({1ll*i, 1ll*D});
    }
    bonus[0] = -OO;
    tree[0] = new Node(0, -OO);
    dfs(0);
 
    for(int i=0; i<q; ++i){
        cout << ans[i] << "\n";
    }
}
 
int32_t main() {
#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin); freopen("output.out", "w", stdout);
#endif
    Hagry
    int t = 1;
//    cin >> t;
    while (t--) {
        TC();
        cout << '\n';
    }
    return 0;
}
