#include<iostream>
#include <bits/stdc++.h>

using namespace std;
#define nd endl;
const int M = 100;

int readInt (int low , int high){
    cout << "Enter your menu choice in the range form [1 - 10]" << nd;
    int ch; cin >> ch;
    if (ch >= low && ch <= high) return ch;
    return readInt(low , high); // it can be done with do while manner instead of recursion but i love recursion
}
int showMenu(){
    cout << "Library Menu" << nd;
    cout << "1) add Book" << nd;
    cout << "2) search Books By Prefix" <<nd;
    cout << "3) print Who Borrowed Book By Name" <<nd;
    cout <<"4) print Library By Id" <<nd;
    cout <<"5) print Library By Name" <<nd;
    cout << "6) add User"<< nd;
    cout <<"7) user Borrow Book" <<nd;
    cout <<"8) user Return Book" << nd;
    cout <<"9) print Users" << nd;
    cout <<"10) Exit" << nd;
    return readInt(1 , 10);
}
class book{
private:
    int id;
    string name;
    int totalQuantity;
    int totalBorrowed;
public:
    book(){
        totalBorrowed = totalQuantity = 0;
        id = -1;
        name = "";
    }
    int getId() const {
        return id;
    }

    void setId(int id) {
        this->id = id;
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        this->name = name;
    }

    int getTotalQuantity() const {
        return totalQuantity;
    }

    void setTotalQuantity(int totalQuantity) {
        this->totalQuantity = totalQuantity;
    }

    int getTotalBorrowed() const {
        return totalBorrowed;
    }

    void setTotalBorrowed(int totalBorrowed) {
        this->totalBorrowed = totalBorrowed;
    }
    void read(){
        cout << "Enter book info : id , name and total quantity: " << nd;
        cin >> id >> name >> totalQuantity;
        totalBorrowed = 0;
    }
    bool borrow(int user_id){
        if (totalQuantity == totalBorrowed) return false;
        ++totalBorrowed;
        return true;
    }
    void return_copy(){
        assert(totalBorrowed > 0);
        --totalBorrowed;
    }
    bool has_prefix(string prefix){ // hay can we do kmp algo here ?
        int sz = (int) prefix.size();
        if ((int)name.size() < sz) return 0;
        for (int i = 0; i < sz; ++i) if (prefix[i] != name[i]) return 0;
        return 1;
    }
    void print(){
        cout << "id = " << id << " name " << name << " total_quantity " << totalQuantity<< " total_borrowed " <<totalBorrowed<< nd;
    }

};
bool compare_book_by_name(book &a , book & b){
    return a.getName() < b.getName();
}
bool compare_book_by_Id(book &a , book & b){
    return a.getId() < b.getId();
}

class user{
private:
    int user_id;
    string user_name;
    multiset<int > ids_books_taken_by_me;
public:
    user(){
        user_name = "";
        user_id = -1;
        ids_books_taken_by_me.clear();
    }

    int getUserId() const {
        return user_id;
    }

    void setUserId(int userId) {
        user_id = userId;
    }

    const string &getUserName() const {
        return user_name;
    }

    void setUserName(const string &userName) {
        user_name = userName;
    }

    void read(){
        cout << "Enter user name and nationl id" << nd;
        cin >> user_name >> user_id;
    }
    void borrow(int book_id){
        ids_books_taken_by_me.emplace(book_id);
    }
    void return_copy(int book_id){
        auto it = ids_books_taken_by_me.find(book_id);
        if (it == ids_books_taken_by_me.end()){
            cout << "User " << user_name << " never borrowed this book" << nd;
        }
        else {
            ids_books_taken_by_me.erase(it);
        }

    }
    bool is_borrowed(int book_id){
        return ids_books_taken_by_me.find(book_id) != ids_books_taken_by_me.end();
    }
    void print(){
        // books i borrowed already sorted in ms
        cout << "user " << user_name << " id " << user_id << " borrowed_books_ids"<< nd;
        for (auto &id : ids_books_taken_by_me) cout << id <<" ";
        cout << nd;
    }

};

class LibrarySystem{
private:
    int total_books;
    book books[M];
    int total_users;
    user users[M];
public:
    void run(){
        while(true){
            int ch = showMenu();
            if (ch == 1) {
                addBook();
            }
            else if (ch == 2){
                searchBooksByPrefix();
            }
            else if (ch == 3){
                printWhoBorrowedBookByName();
            }
            else if (ch == 4){
                printLibraryById();
            }
            else if (ch == 5){
                printLibraryByName();
            }
            else if (ch == 6){
                addUser();
            }
            else if (ch == 7){
                userBorrowBook();
            }
            else if (ch == 8){
                userReturnBook();
            }
            else if (ch == 9){
                printUsers();
            }
            else break;
        }
    }
    LibrarySystem(){
        total_books = total_users = 0;
    }

    int getTotalBooks() const {
        return total_books;
    }

    void setTotalBooks(int totalBooks) {
        total_books = totalBooks;
    }
    int getTotalUsers() const {
        return total_users;
    }

    void setTotalUsers(int totalUsers) {
        total_users = totalUsers;
    }
    void addBook(){
        books[total_books++].read();
    }

    void searchBooksByPrefix (){
        cout << "Enter book name prefix: " << nd;
        string prefix; cin >> prefix;
        int curCnt = 0;
        vector < string > cur;
        for (int i = 0; i < total_books ; ++i)
            if (books[i].has_prefix(prefix)) ++curCnt ,cur.push_back(books[i].getName());
        if (!curCnt) {
            cout << "No books with such prefix" << nd;
        }
        else {
            for (auto &i : cur) cout << i << nd;
        }
        cout <<nd;
    }
    int fnd_book_idx(string & s){
        int ans = -1;
        for (int i = 0; i < total_books; ++i){
            if (s == books[i].getName()){
                return i;
            }
        }
        return ans;
    }
    void printWhoBorrowedBookByName(){
        cout << "Enter a bookName" << nd;
        string bookName; cin >> bookName;

        int book_idx = fnd_book_idx(bookName); // i need some work here
        if (book_idx == -1){
            cout << "Invalid book Name" << nd;
            return;
        }
        if(books[book_idx].getTotalBorrowed() == 0){
            cout << "No borrowed copies" << nd;
        return;
        }
        for (int i = 0; i < total_users; ++i){
            if (users[i].is_borrowed(books[book_idx].getId())){
                cout << users[i].getUserName() << nd;
            }
        }
        cout << nd;
    }

    void printLibraryById(){
        sort(books , books+total_books , compare_book_by_Id);
        for (int i = 0;i < total_books; ++i) books[i].print();
        cout << nd;
    }


    void printLibraryByName(){
        sort(books , books+total_books , compare_book_by_name);
        for (int i = 0;i < total_books; ++i) books[i].print();
        cout << nd;
    }

    void addUser(){
        users[total_users++].read();
    }
    int fnd_user_idx(string &s){
        for (int i = 0; i < total_users; ++i)
            if (users[i].getUserName() == s) return i;
        return -1;
    }

    bool checkForUserNameAndBookName(int &user_idx , int &book_idx , int trials = 3){
        if(!trials) {
            user_idx = book_idx = -1;
            return 0;
        }
        string user_name , book_name;
        cout << "Enter User name and book name " << nd;
        cin >> user_name >> book_name;
        user_idx = fnd_user_idx(user_name);
        book_idx = fnd_book_idx(book_name);
        if (min(user_idx , book_idx) == -1) {
            cout << "Un valid book name or user name Please Try again " << nd;
            return checkForUserNameAndBookName(user_idx , book_idx , trials-1);
        }
        return 1;
    }

    void userBorrowBook(){
        int user_idx , book_idx;
        bool valid = checkForUserNameAndBookName(user_idx , book_idx);
        if(!valid) return;
        if(books[book_idx].borrow(user_idx)) {
            users[user_idx].borrow(books[book_idx].getId());
        }
        else {
            cout <<"this book is not available" << nd;
        }
    }

    void userReturnBook(){
        int user_idx, book_idx;
        bool valid = checkForUserNameAndBookName(user_idx , book_idx);
        if (!valid) return ;
        books[book_idx].return_copy();
        users[user_idx].return_copy(books[book_idx].getId());

    }

    void printUsers(){
        for (int i = 0; i < total_users ; ++i) users[i].print();
        cout << nd;
    }


};
void main_(int tc){
    LibrarySystem obj;
    obj.run();



}
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    int tt = 1, tc = 0;//cin >> tt;
    while (tt--) main_(++tc);
    return 0;
}



