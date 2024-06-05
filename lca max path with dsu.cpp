
const int M = 6e5+5;
ll INF = 1e18;

int n, qs;
vector < vector < array< int , 2 >> > anc;
vector < vector < array < int , 3 > > > g; // node , capacity , toll value
vector <  array < int , 4>  >  edges;
vector < int > e ,dep;
void init(){
    g = vector < vector < array < int , 3 >> >  (n+5);
    dep =  e =  vector < int > (n+5);
    anc = vector < vector < array < int , 2 > > > (n+5 , vector < array < int , 2 > > (LOG+1, {0 , 0}));
}
void dfs(int node , int pa = 0){
    for (auto &[ch , c , t ] : g[node]){
        if(ch == pa) continue;
        dep[ch] = 1 + dep[node];
        anc[ch][0][0] = node; anc[ch][0][1] = t;
        for (int L = 1; L < LOG ; ++L){
            int p = anc[ch][L-1][0];
            anc[ch][L][0] = anc[p][L-1][0];
            anc[ch][L][1] = max(anc[p][L-1][1] , anc[ch][L-1][1]);
        }
        dfs(ch , node);
    }
}


array < int , 2 >  kth (int node , int k){
    array < int , 2 > ans = {node , 0};
    for (int L = LOG-1; L >= 0; L--){
        if (k & (1 << L)){
            ans[1] = max (ans[1] , anc[node][L][1]);
            ans[0] = anc[node][L][0];
            node = ans[0];
        }
    }
    return ans;
}
array < int , 2 > lca (int u, int v){
    if (dep[u] < dep[v]) swap(u, v);
    auto ans = kth(u , dep[u] - dep[v]);
    u = ans[0];
    if (u == v) return ans;
    for (int L = LOG - 1 ; L >= 0 ; --L){
        if (anc[u][L][0] ^ anc[v][L][0]){
            ans[1] = max ({ans[1] , anc[u][L][1] , anc[v][L][1]});
            u = anc[u][L][0] , v = anc[v][L][0];
        }
    }
    ans[1] = max ({ans[1] , anc[u][0][1] , anc[v][0][1]});
    assert (anc[u][0][0] == anc[v][0][0] && u ^ v);
    ans[0] = anc[u][0][0];
    return ans;
}

struct dsu{
    int n;
    vector < int > par , sz ,mxt ;
    vector < array < int, 2 > > mxe;
    void init (int _n){
        n = _n+5; mxe = vector < array < int ,2 > > (n+5);
        par = sz = vector< int > (n+5 , 1); mxt = vector < int > (n+5);
        for (int i = 1 ; i <= _n; ++ i) mxe[i] = {e[i] , i} , par[i] = i ;
    }
    int findp (int u){
        if (u == par[u]) return u;
        return par[u] = findp(par[u]);
    }
    void merge (int u, int v){
        if (mxe[u][0] == mxe[v][0]) {
            mxt[u] = max(mxt[u], lca(mxe[u][1], mxe[v][1])[1]);
            mxt[u] = max(mxt[u], mxt[v]);
        }
        else if (mxe[u][0] < mxe[v][0]){
            mxe[u] = max(mxe[u], mxe[v]);
            mxt[u] = mxt[v];
        }
    }
    int work (int u, int v){
        u = findp(u) , v = findp(v);
        if (u == v) return 0;
        if (sz[u] < sz[v]) swap (u , v);
        merge (u , v);
        sz[u]+= sz[v]; par[v] = u;
        return 1;
    }
};
void main_(int tc) {
    cin >> n >> qs; init();
    for (int i = 1; i <= n; ++ i) cin >> e[i];
    for (int i =1 ; i < n; ++ i){
        edges.emplace_back();
        auto &[u , v , c, t] = edges.back();
        cin>> u >> v >> c >> t;
        g[u].push_back({v , c, t});
        g[v].push_back({u, c, t});

    }
    assert((int)edges.size() == n-1);
    dfs(1);
    vector < array < int , 3 > > q(qs);
    vector < array < int , 2 > > ans(qs);   int curL = 0;
    for (auto &[node , v , idx] : q) cin >> v >> node, idx = curL++;
    sort(all(edges),[&] (array < int , 4> &x , array < int , 4 > &y){
        return x[2] > y[2];
    });
    sort (all (q) , [&] (array < int ,3 > & x , array < int , 3 > & y){
        return x[1] > y[1];
    });
    dsu ds; ds.init(n); curL = 0;
    for (auto &[node , capacity , idx] : q){
        while (curL < n-1 && edges[curL][2] >= capacity){
            auto &[u , v , c, t] = edges[curL];
            ds.work(u , v);
            ++curL;
        }
        int parent = ds.findp(node);
        ans[idx][0] = ds.mxe[parent][0];
        ans[idx][1] = max (lca(node , ds.mxe[parent][1])[1] , ds.mxt[parent]);

    }
    for (int i = 0 ; i < qs; ++i) cout << ans[i][0] << " " << ans[i][1] <<nd;









}
