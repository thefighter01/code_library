 struct dsu {
        int n;
        vector<int > par ,sz;
        void init(int _n){
            n = _n+5;
            par = sz = vector<int > (n+5 , 1);
            iota(all(par) , 0);
        }
        int findp(int u){
            if (u == par[u]) return par[u];
            return par[u] = findp(par[u]);
        }
        int work (int u , int v){
            u = findp(u) , v = findp(v);
            if (u == v) return 0;
            if (sz[u] < sz[v]) swap(u , v);
            sz[u]+=sz[v]; par[v] = u;
            return 1;
        }
    };
