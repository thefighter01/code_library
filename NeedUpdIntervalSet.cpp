#include<iostream>
#include<cstring>
#include<vector>
#include<set>
using namespace std;
using LL = long long;
struct Node{
    int l, r;
    mutable int v;
    bool operator<(const Node &t) const{
        return l < t.l;
    }
};
set<Node> s;
 
const int N = 1e9;
 
auto split(int pos){
    if (pos > N) return s.end();
    Node t = {pos, -1, 0};
    auto it = s.lower_bound(t);
    if (it != s.end() && it->l == pos) return it;
    it--;
    int l = it->l, r = it->r;
    int v = it->v;
    s.erase(it);
    s.insert({l, pos - 1, v});
    return s.insert({pos, r, v}).first;
}
 
int main(){
 
#ifdef LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
 
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);
 
    int n, m;
    cin >> n >> m;
    vector<int> x(n + 1), cnt(n + 1);
    vector<LL> t(n + 1);
    vector<int> id;
    for(int i = 1; i <= n; i++)
        cin >> x[i] >> t[i], id.push_back(i);
    sort(id.begin(), id.end(), [&](int a, int b){
        return x[a] < x[b];
    });
    s.insert({0, N, 0});
    
    auto update = [&](int l, int r, int id){
        auto itr = split(r + 1);
        auto itl = split(l);
        s.erase(itl, itr);
        s.insert({l, r, id});
    };
 
    int mx = -1;
    for(int i = 0; i < n; i++){
        int l = max(mx + 1, x[id[i]]);
        int r = min(x[id[i]] + t[id[i]], 1LL * N);
        if (l <= r){
            update(l, r, id[i]);
        }
        mx = max(mx, r);
    }
    multiset<pair<int, int> > mos;
 
    while(m--){
        int pos, sz;
        cin >> pos >> sz;
        auto it = prev(s.lower_bound({pos + 1, -1, 0}));
        if (it->v == 0){
            mos.insert({pos, sz});
            continue;
        }
        
        int id = it->v;
        t[id] += sz;
        cnt[id] += 1;
        int l = x[id], r = min(x[id] + t[id], 1LL * N);
        if (it != s.begin()){
            l = max(l, prev(it)->r + 1);
        }
        update(l, r, id);
 
        while(!mos.empty()){
            auto it = mos.lower_bound({l, 0});
            if (it != mos.end() && it->first <= r){
                t[id] += it->second;
                cnt[id] += 1;
                r = min(x[id] + t[id], 1LL * N);
                update(l, r, id);
                mos.erase(it);
            }
            else break;
        }
    }
 
    for(int i = 1; i <= n; i++){
        cout << cnt[i] << ' ' << t[i] << '\n';
    }
 
}
// https://codeforces.com/contest/609/problem/F
