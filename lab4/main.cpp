#include <iostream>
#include <vector>

using namespace std;

int kth_selection(const vector<int>& v, size_t k);
vector<string> subsets(size_t n);

int kth_selection(const vector<int> &v, size_t k) {
    int pivot = v[0];
    vector<int> left;
    vector<int> mid;
    vector<int> right;
    for(auto it = v.begin(); it != v.end(); ++it){
        if (*it < pivot)
            left.push_back(*it);
        else if (*it == pivot)
            mid.push_back(*it);
        else if(*it > pivot)
            right.push_back(*it);
    }
    if(left.size() > k)
        return kth_selection(left, k);
    else if(left.size() + mid.size() > right.size())
        return pivot;
    else if(right.size() > k)
        return kth_selection(right, k);
}
vector<string> subsets(size_t n){

}

int main() {
    vector<int> v= {2,3,1,0,4,2,1,3};
    cout << kth_selection(v, 3) << endl;
    return 0;
}