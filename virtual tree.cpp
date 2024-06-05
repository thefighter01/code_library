int n ,c[N] , dfn;
ll cnt[N];
ll ans;
vector<int > dep , st , en , good;
vector <int > g[N] , fake[N] , nodes[N] , anc[N];
bool is_anc(int u , int v){
    return st[u] <= st[v] && en[u] >= en[v];
}

int kth (int u , int k){
    for (int i = 0; i < LOG; ++i) if (k & (1 << i)) u = anc[u][i];
    return u;
}
int lca (int u , int v){
    if (dep[u] < dep[v]) swap(u , v);
    u = kth(u  , dep[u] - dep[v]);
    if (u == v) return u;
    for (int i = LOG -1; ~i ; --i) if (anc[u][i] ^ anc[v][i]) u = anc[u][i] , v = anc[v][i];
    assert(u ^ v && anc[u][0] == anc[v][0]);
    return anc[u][0];
}
void dfs0(int node , int p){
    anc[node][0] = p; st[node] = ++dfn;
    for (int L = 1; L < LOG; ++L) anc[node][L] = anc[anc[node][L-1]][L-1];
    for (auto &ch : g[node]){
        if (ch == p) continue;
        dep[ch] = 1 + dep[node];
        dfs0(ch , node);
    }
    en[node]= dfn;
}
void init(){
   cin >> n; ans = dfn = 0; dep = st = en = good = vector <int > (n+5);
   for (int i = 1; i <=n; ++i){
       cin >> c[i];
       fake[i].clear();g[i].clear(); nodes[i].clear();
       anc[i] = vector <int > (LOG);
   }
   for (int i= 1; i <= n; ++i) nodes[c[i]].emplace_back(i);
   for (int u , v, i = 1; i < n; ++i){
       cin >> u >> v;
       g[u].push_back(v);
       g[v].push_back(u);
   }
   dfs0(1 , 1);
}

void dfs(int node , int p = 0){
    ll sm  , k ; sm = k = 0;
    for (auto &ch : fake[node]){
        if (ch == p) continue;
        dfs(ch  , node);
        sm+=cnt[ch];
        k+= cnt[ch]* cnt[ch];
    }
    if (good[node]){
        ans+= sm;
        cnt[node] = 1;
    }
    else {
        ans+= (sm * sm - k) / 2;
        cnt[node]+=sm;
    }
}
void solve(vector<int > & a){
    sort(all(a) , [&](int u , int v){
        return st[u] < st[v];
    });
    int sz = (int) a.size();
    for (auto &i : a) good[i] = 1;
    for (int i = 1; i < sz; ++i) a.emplace_back(lca(a[i-1] , a[i]));
    sort(all(a) , [&](int u , int v){
        return st[u] < st[v];
    }); a.resize(unique(all(a))-a.begin());
    sz = (int)a.size();
    vector<int > sta= {a[0]};
    for (int i = 1; i < sz; ++i){ assert(!sta.empty());
        while(!is_anc(sta.back() , a[i])){
            fake[sta[(int)sta.size()-2]].push_back(sta.back());
            sta.pop_back();
        }
        sta.emplace_back(a[i]);
    }
    while ((int)sta.size() > 1){
        fake[sta[(int)sta.size()-2]].emplace_back(sta.back());
        sta.pop_back();
    }
    assert(!sta.empty());
    dfs(sta[0]  , 0);
    for (auto &u : a){
        fake[u].clear();
        good[u] = cnt[u] = 0;
    }
}
void main_(int tc){
    init();
    for (int cc = 1; cc <= n; ++cc){
        if (!nodes[cc].empty()) solve(nodes[cc]);
    }
    cout << ans << nd;




}
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    int tt = 1, tc = 0;cin >> tt;
    while (tt--) main_(++tc);
    return 0;
}
// look at my code
// my code is amazing


