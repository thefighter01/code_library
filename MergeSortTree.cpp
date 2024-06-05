class the_best_is_still_yet_to_come{
private:
    using node= pair<pair<ll,ll> ,ll>;
 
    vector<vector<node>> tree;///2d array of node
 
   vector<node> sort(vector<node> a , vector<node> b){// be careful Don't pass it by ref
       for (auto & i : a){
           i.first.second = arr[i.second].first * i.first.first;
       }
       for (auto & i : b){
           i.first.second = arr[i.second].first * i.first.first;
       }
       vector<node> ret;
       int i  , j ; i = j = 0;
 
       while (i <(int)a.size() && j < (int)b.size()){
         a[i].first.first > b[j].first.first ? ret.emplace_back(b[j++]): ret.emplace_back(a[i++]);
       }
       while (i < (int)a.size()){
           ret.emplace_back(a[i++]);
       }
       while (j < (int)b.size()){
           ret.emplace_back(b[j++]);
       }
       for (int ii = 1; ii <(int)ret.size(); ++ii){
           ret[ii].first.second += ret[ii-1].first.second;
       }
 
       return ret;
 
   }
 
  vector<node> alone(int i){
      return {{{arr[i].second , arr[i].first* arr[i].second }, i}};
 
  }
public:
    int parent ;
    void S(int x){
        parent = x;
        while (popcount(parent) != 1) ++ parent;
        tree = vector< vector<node> > (2*parent);
    }
 
    void fill(int n , int node_low , int node_high ){
      if (node_high- node_low == 1){
          if (node_low < nn) {
              tree[n] = alone(node_low);
          }
          return;
      }
 
      int mid = node_low + node_high >> 1;
      fill(2*n+1 , node_low , mid);
      fill(2*n+2 , mid , node_high);
      tree[n] = sort(tree[2*n+1] , tree[2*n+2]);
  }
 
  ll get(int n , int node_low , int node_high , int l , int r , int w1 , int w2){
 // cout <<n<<' '<<node_low<<' '<<node_high <<' '<<l<<' '<<r<<nd;
      if (node_low >= r || l >= node_high) return 0;
      if (r >= node_high && node_low >= l){
       //   lol;
        ll L , R ; L = R = -1;
         ll st= 0 , end = (int)tree[n].size()-1;
 
         while (st <= end){
             ll mid = st + end >> 1;
             if (tree[n][mid].first.first >= w1){
                 L = mid; end = mid-1;
             }else{
                 st = mid+1;
             }
         }
        // pp;
          if (L == -1) return 0;
         /// R = (int)tree[n].size()-1;
         st = 0 , end = (int)tree[n].size()-1;
          while (st <= end){
              ll mid = st + end>> 1;
              if (tree[n][mid].first.first <= w2){
                  R = mid; st = mid+1;
              }
              else{
                  end = mid-1;
              }
          }
          //assert(R>= 0);
          if (R == -1) return 0;
 
          ll kk = (L ? tree[n][L-1].first.second : 0);
          ll kkk = tree[n][R].first.second;
        ///  cout <<L<<' '<<R<<' '<<n<<' '<<w1<<' '<<w2<<"iii "<<kkk-kk<<nd;
          return kkk-kk;
      }
      ll mid = node_low + node_high >> 1;
      ll op1 = get(2*n+1 , node_low , mid , l , r , w1 , w2);
      ll op2 = get(2*n+2 , mid , node_high , l , r , w1 , w2);
      return op1+op2;
   }
 
   ll get (ll l , ll r , ll w1 , ll w2){
       return get(0 , 0 , parent , l , r+1 , w1 , w2);
   }
   void print_um_el_tree(){
        for (int i = 0;i< 2 *parent ; ++i){
            cout <<i<<" oooooooooo  "<<nd;
            for (auto &el  : tree[i]){
                cout <<el.first.first<<' '<<el.first.second<<' '<<el.second<<"         "<<nd;
            }
        }
    }
 
 
};
