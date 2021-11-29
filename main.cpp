#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<time.h>
#include<random>
#include<fstream>
#include<chrono>
#include<list>
#include<iterator>
#include<array>

using namespace std;

// 1
void push_back_average(list<double>&UserList) {
    double res = 0.0;
    for (auto& temp : UserList)
        res += temp;

    UserList.push_back(res/UserList.size());
    return;
}

// 2
class Matrix {
private:
    array<array<double, 3>, 3> matrix;
public:
    Matrix() {
        for (size_t i = 0; i < 3; i++)
            for (size_t j = 0; j < 3; j++)
                matrix[i][j] = double(rand() % 20 + 1);
    }
    Matrix(array<array<double, 3>, 3> matrix) :matrix(matrix) {}
    double determinant() {
        return	matrix[0][0]*matrix[1][1]*matrix[2][2]
                  +matrix[0][1]*matrix[1][2]*matrix[2][0]
                  +matrix[0][2]*matrix[1][0]*matrix[2][1]
                  -matrix[0][2]*matrix[1][1]*matrix[2][0]
                  -matrix[0][0]*matrix[1][2]*matrix[2][1]
                  -matrix[0][1]*matrix[1][0]*matrix[2][2];
    }
    auto& getMatrix() { return matrix; }
    ~Matrix() {}
};
ostream& operator<<(ostream& os, Matrix& matrix) {
    auto& m = matrix.getMatrix();

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++)
            os << m[i][j] << '\t';
        os << '\n';
    }
    return os;
}

// 3
class MyInterator:public iterator<input_iterator_tag,int,const int*,const int&>
{
public:
    int* value;

    int& operator*() { return *value; }

    MyInterator& operator++() {
        value++;
        return *this;
    }

    bool operator!=(const MyInterator& it) { return value != it.value; }

    MyInterator(int* value) :value(value) { }
    MyInterator(const MyInterator& t) {
        this->value = t.value;
    }
    ~MyInterator() { value = nullptr; }
};
template<size_t _size>
class MyArray{
public:
    int arr[_size];
    MyArray(){}
    MyInterator begin(){return MyInterator(arr);}
    MyInterator end(){return MyInterator(arr+_size);}
    ~MyArray(){}
};

int main(){
    srand(time(0));
    // 1
    {
        list<double> MyList;
        for (size_t i = 0; i < 10; i++) MyList.push_back(double(rand() % 10 + 1));
        cout << "--------befor--------\n";
        for (auto& temp : MyList) cout << temp << '\t';
        push_back_average(MyList);
        cout << "\n--------after--------\n";
        for (auto& temp : MyList) cout << temp << '\t';
        cout << "\n\n";
    }

    // 2
    {
        Matrix matrix;
        cout << matrix;
        cout << "determinant := " << matrix.determinant() << "\n\n";
    }

    // 3
    {
       MyArray<5> arr;
       for(auto&it:arr) it = rand()%10+1;
       for(auto &it:arr) cout<<it<<' ';
       cout<<endl;
    }

    return 0;
}