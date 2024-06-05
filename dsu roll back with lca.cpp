struct dsu{
    int n;
    vector < int > par , sz;
    stack < pair < int & , int > > history;
    void init(int _n){
        n = _n+ 5; history = stack < pair < int & , int > > ();
        par = sz = vector < int > (n +5, 1);
        iota(all(par) , 0);
    }
    int findp(int u){
        if (u == par[u]) return u;
        return findp(par[u]);
    }
    int work(int u , int v){
        u = findp(u) , v = findp (v);
        if (u == v) return 0;
        if(sz[u] < sz[v]) swap(u , v);
        history.push({par[v] , par[v]});
        history.push({sz[u] , sz[u]});
        par[v] = u , sz[u]+=sz[v];
        return 1;
    }
    int event() {return (int) history.size();}
    void suck(int cur){
        while((int) history.size() >  cur){
            history.top().first = history.top().second;
            history.pop();
        }
    }
};
int n;
vector < vector < int > > g , anc;
vector < int > dep;
void init(){
    cin >> n; dep = vector <int > (n +5);
    g = vector < vector < int > > (n + 5);
    anc = vector < vector < int > > (n +5 , vector < int > (LOG + 5));
}

int kth (int u , int k){
    for (int i = LOG-1; ~i ;--i) if (k & (1 << i)) u = anc[u][i];
    return u;
}

int lca(int u , int v){
    if (dep[v] > dep[u]) swap(u , v);
    u = kth(u , dep[u] - dep[v]);
    if (u ==v ) return u;
    for (int i = LOG-1; ~i; --i) if (anc[u][i] ^ anc[v][i]) u = anc[u][i] , v = anc[v][i];
    assert(anc[u][0] == anc[v][0] && u ^ v);
    return anc[u][0];
}
void dfs(int node , int p = 1){
    anc[node][0] = p;
    for (int L = 1; L < LOG; ++L) anc[node][L] = anc[anc[node][L-1]][L-1];
    for (auto &ch : g[node]){
        if (ch == p) continue;
        dep[ch] = 1 + dep[node];
        dfs(ch , node);
    }
}
