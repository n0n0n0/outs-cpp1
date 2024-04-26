#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dispv(vector<int> v) {
    cout << "Vector is: [";
    for(auto i: v) {
        cout << i;
    }
    cout << "]\n";
}

void dispv_rev(vector<int> v) {
    cout << "Vector reverse is: [";
    for(auto it = v.rbegin(), end = v.rend(); it != end; ++it) {
        cout << *it;
    }
    cout << "]\n";
}

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    if(m == 0) {
        nums1 = std::move(nums2);
    } else if(n > 0 && m > 0) {
        vector<int> nums3;
        nums3.reserve(m+n);
        auto it1 = nums1.begin(), it2 = nums2.begin();
        auto e1 = it1+m, e2 = it2+n;
        //int i1 = 0, i2 = 0;
        do {
            cout << "it1: " << (*it1) << " i2: " << (*it2) << "\n"; 
            if((*it1) < (*it2)) {
                nums3.push_back(*it1);
                ++it1;
                //++i1;
            } else {
                nums3.push_back(*it2);
                ++it2;
                //++i2;
            }
            //if((i1 == m) && (i2 == n))
            if((it1 == e1) && (it2 == e2))
                break;
            //else if(i1 == m) {
            else if(it1 == e1) {
                std::copy(it2, e2, std::back_inserter(nums3));
                break;
            //} else if(i2 == n) {
            } else if(it2 == e2) {    
                std::copy(it1, e1, std::back_inserter(nums3));
                break;
            }
        } while(true);

        nums1 = nums3;
    }
}

void merge2(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    nums1.resize(m);
    nums2.resize(n);
    nums1.insert(nums1.end(), nums2.begin(), nums2.end());
    std::sort(nums1.begin(), nums1.end());
}

int removeElement(vector<int>& nums, int val) {
    int k = 0, n = nums.size();
    auto it = nums.begin(), end = nums.end()-1;
    while(it < end) {
        if(*it == val && *end != val) {
            cout << "first("<<(*it)<<") == v && second("<<(*end)<<") != v: swap, first++, end--, k: " 
                << k+1 << "\n";
            std::iter_swap(it, end);
            ++k;
            ++it;
            --end;
        } else if(*it != val && *end != val) {
            cout << "first("<<(*it)<<") != v && second("<<(*end)<<") != v: first++, k: " 
            << k << " \n";
            // --end;
            ++it;
        } else if(*it != val && *end == val) {
            cout << "first("<<(*it)<<") != v && second("<<(*end)<<") == v: first++, end--, k: " 
            << k+1 << " \n";
            ++it;
            ++k;
            --end;
        } else if(*end == val && *it == val) {
            cout << "first("<<(*it)<<") == v && second("<<(*end)<<") == v: swap, end--, k: "
            << k+1 << "\n";
            ++k;
            --end;
        }

        dispv(nums);
    }
    if(it == end && *it == val) ++k; 
    nums.resize(n - k);
    return n - k;
}

int removeDuplicates(vector<int>& nums) {
    int k = 0, n = nums.size();
    if(n < 2) return n; // 0 for empty, 1 for 1 el
    auto it = nums.begin(), end = nums.end();
    while(it != end-1) {
        if(*it == *(it+1)) {
            for(auto it2 = it+1; it2 != end-1; ++it2) {
                std::iter_swap(it2, it2+1);
            }
            --end;
            ++k;
        } else
            ++it;
    }
    return k;
}

int main(int, char**){
    std::cout << "Hello, from leetvec1!\n";

    vector<int> nums1{1,2,3,0,0,0},
        nums2{2,5,6};
    merge2(nums1, 3, nums2, 3);

    dispv(nums1);

    vector<int> nums3{1},
        nums4;
    merge2(nums3, 1, nums4, 0);
    dispv(nums3);

    vector<int> nums5,
        nums6{1};
    merge2(nums5, 0, nums6, 1);
    dispv(nums5);

    vector<int> nums7{2,0},
        nums8{1};
    merge2(nums7, 1, nums8, 1);
    dispv(nums7);

    vector<int> v1{3, 2, 2, 3};
    int k1 = removeElement(v1, 3);
    cout << " remove 3 count: " << k1 << "\n";
    dispv(v1);

    vector<int> v2{0,1,2,2,3,0,4,2};
    cout << "Original vector: \n";
    dispv(v2);
    dispv_rev(v2);
    cout << "Find and delete element: 2 \n";
    int k2 = removeElement(v2, 2);
    cout << " remove 2 count: " << k2 << "\n";
    dispv(v2);

    vector<int> v3{4,5};
    int k3 = removeElement(v3, 5);
    cout << " remove 5 count: " << k3 << "\n";
    dispv(v3);

    vector<int> v4{2,2,3};
    cout << "Original vector: \n";
    dispv(v4);
    cout << "Find and delete element: 2 \n";
    int k4 = removeElement(v4, 2);
    cout << " remove 2 count: " << k4 << "\n";
    dispv(v4);

    //vector<int> v5{0,0,1,2,2,3,4,5,5,5,6};
    vector<int> v5{0,0,1,1,1,2,2,3,3,4};
    cout << "Original vector: \n";
    dispv(v5);
    cout << "Delete duplicate elements \n";
    int k5 = removeDuplicates(v5);
    cout << " remove duplicates count: " << k5 << "\n";
    dispv(v5);
}
