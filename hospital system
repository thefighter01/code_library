/*
a simple hospital system consists of n number of specializations and for each one of them there is only m places avaible
we can do operation like this 
add patient and if he is urgent 1 else 0
print all patients for all specialization 
dr ask for patinets form specific specialization
*/

#include<iostream>
#include <bits/stdc++.h>
using namespace std;
#define nd endl;
int n ,m;   // n = the number of specializations , m = the number of valid spots
vector < deque<pair <string , int >  > > a;
void init(){
    cout << "Enter the number of specialization and the number of spots for each one" << nd;
    cin >>n >> m;
    a = vector < deque< pair < string , int >  > > (n+1);
}

int show(){
    cout << "Enter ur choice :" << nd;
    cout << "1) Add new patient" << nd;
    cout << "2) Print all patients" << nd;
    cout << "3) Get next patient" << nd;
    cout << "4) Exit" << nd;
    int ch; cin >> ch;
    return ch;
}

void addPatient(){
    cout << "Enter specialization, name, status :" << nd;
    int spe, status;
    string name;
    cin >> spe >> name >> status;
    int sz = (int) a[spe].size();
    if (sz >= m){
        cout << "Sorry we can't add more patients for this specialization" <<nd;
    }
    else{
        if (status) a[spe].push_front({name, status});
        else a[spe].push_back({name , status});
    }

}
void print(){
    cout << "********************************************" << nd;
    for (int i = 1; i <= n; ++i){
        int sz = (int)a[i].size();
        if (!sz) continue;
        cout << "There are "<< sz << " patients in specialization " << i << nd;
        for (auto &[name , status] : a[i]){
            cout << name << " " <<(status ? "urgent" : "regular") << nd;
        }
        cout << nd;
    }
}
void getNextPatient(){
    cout << "Enter specialization " << nd;
    int spe;cin >> spe;
    int sz = a[spe].size();
    if (!sz){
        cout << "there is no patients in this specialization" << nd;
    }
    else{
        cout << a[spe][0].first << " please go with the Dr" << nd;
        a[spe].pop_front();
    }
}

void hospitalSystem(int tc) {
    init();
    while(true) {
        int choice = show();

        if (choice == 1) {
            addPatient();
        } else if (choice == 2) {
            print();
        } else if (choice == 3) {
            getNextPatient();
        } else {
            break;
        }
    }





}
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    int tt = 1, tc = 0;//cin >> tt;
    while (tt--) hospitalSystem(++tc);
    return 0;
}
