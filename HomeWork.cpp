#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<list>
#include<algorithm>
#include<math.h>
#include<iterator>
#include<numeric>

using namespace std;

// 1
template<class t_cont,class t_value>
void insert_sorted(t_cont& arr,const t_value value){
    // the variable (it) will have iterator which point out on element > value
    auto it = find_if(arr.begin(),arr.end(),[value](t_value th)->bool {return th>value;});
    if(it==arr.end()) arr.push_back(value);
    else arr.insert(it,value);
    
}

int main(){

    srand(time(NULL));

    // 1
    {
        vector<int> test1{1,3,4,5}; // insert in the middle
        deque<int> test2{};         // empty
        list<int> test3{1,2,3,4};   // insert in the end
        
        // vector
        for(auto& it : test1) cout<<it<<' ';
        cout<<"insert -> 2  res := ";
        insert_sorted(test1,2);
        for(auto& it : test1) cout<<it<<' ';
        cout<<"\n\n";

        // deque
        for(auto& it : test2) cout<<it<<' ';
        cout<<"\tinsert -> 1  res := ";
        insert_sorted(test2,1);
        for(auto& it : test2) cout<<it<<' ';
        cout<<"\n\n";
        
        // list
        for(auto& it : test3) cout<<it<<' ';
        cout<<"insert -> 5  res := ";
        insert_sorted(test3,5);
        for(auto& it : test3) cout<<it<<' ';
        cout<<"\n\n";

    }

    // 2
    {
        vector<double> arr_A(100);
        generate(arr_A.begin(),arr_A.end(),[]()->double {return (rand()%900+100) / 100.0;});
        cout<<"A := ";
        copy(arr_A.begin(),arr_A.end(),ostream_iterator<double>{cout, "  "});
        cout<<'\n';
        
        vector<int> arr_B(100);
        transform(arr_A.begin(),arr_A.end(),arr_B.begin(),[](int value)->int{return value;});
        cout<<"B := ";
        copy(arr_B.begin(),arr_B.end(),ostream_iterator<int>{cout, "  "});
        cout<<'\n';

        double res =0;
        res = inner_product(arr_A.begin(),arr_A.end(),arr_B.begin(),0.0,plus<>(),minus<>());
        cout<<"Signal Error:= "<<res<<'\n';
    }

    return 0;
}