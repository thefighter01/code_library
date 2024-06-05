

const int M = 6e5+5;
ll INF = 1e8;

struct fen{
    int n;
    vector < int > t;
    void init(int _n){
        n = _n + 5;
        t = vector < int > (n + 5);
    }
    void upd(int i, int v){
        while (i <= n){
            t[i]+=v;
            i += i & -i;
        }
    }
    int sum (int i){
        int ans = 0;
        while (i) ans += t[i] , i-= i & -i;
        return ans;
    }
    int sum (int L , int R){
        return sum(R) - sum(L-1);
    }
};

set < int > pos[N];
int a[N];
int p;
vector < array < int , 2 > > changes;
fen t;
void upd (int num , int i){
    if (!num ) return;
    if (!pos[num].empty()) t.upd(* pos[num].begin(), -1);
    pos[num].emplace(i);
    t.upd(*pos[num].begin() , 1);
}
void del(int num , int i){
    if (!num) return;
    t.upd(* pos[num].begin() , -1);
    pos[num].erase(i);
    if (!pos[num].empty()) t.upd(*pos[num].begin() , 1);
}
void main_(int tc) {
    int q; cin >> q;  t.init(N);
    for (int i = 1; i <= q; ++i){
        char c ; cin >> c;
        if (c == '+'){
            int v ; cin >> v;
            ++p;
            if (a[p]) del(a[p] , p);
            changes.push_back({1 , a[p]});
            a[p] = v;
            upd(v, p);
        }
        else if (c == '-'){
            int k; cin >> k;
            p-=k;
            changes.push_back({-k , 0});
        }
        else if (c == '?'){
            cout << t.sum(p) << endl;
        }
        else {
            auto [x , y] = changes.back(); changes.pop_back();
            if (x < 0) p-=x;
            else{
                del(a[p] , p);
                a[p] = y;
                upd(y , p);
                --p;
            }
        }
    }





}

