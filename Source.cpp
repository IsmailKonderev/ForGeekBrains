#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<time.h>
#include<random>
#include<fstream>
#include<chrono>

using namespace std;


class Timer
{
private:
	using clock_t = chrono::high_resolution_clock;
	using second_t = chrono::duration<double, ratio<1> >;

	chrono::time_point<clock_t> m_beg;
	double elapsed() const
	{
		return chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}

public:
	Timer(){}

	void start() {
		m_beg = clock_t::now();
	}
	double end() const {
		return elapsed() * 1000.0;
	}
};



template<typename T>
void Swap(T* const ptr1,T* const ptr2) {
	T temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
	return;
}

template<typename T>
void SortPointers(vector<T*>& arr) {
	sort(arr.begin(), arr.end(), [](T* first, T* second) {return (*first) < (*second); });
	return;
}

// 3
bool check_symbol(char ch) {
	if (ch == 'A' || ch == 'a' || ch == 'E' || ch == 'e' || 
		ch == 'I' || ch == 'i' || ch == 'O' || ch == 'o' || 
		ch == 'U' || ch == 'u' || ch == 'Y' || ch == 'y') return true;
	return false;
}

int main() {
	srand(time(0));
	Timer t;

	// 1
	{
		int a = rand()%10+1;
		int b = rand()%10+1;

		int* const ptr1 = &a;
		int* const ptr2 = &b;


		cout << "-----------before-----------\n";
		cout << "a := " << a << "\t &a := " << &a << '\n';
		cout << "b := " << b << "\t &b := " << &b << '\n';

		Swap(ptr1, ptr2);

		cout << "------------after-----------\n";
		cout << "a := " << a << "\t &a := " << &a << '\n';
		cout << "b := " << b << "\t &b := " << &b << '\n';

		cout << "\n\n";
	}

	// 2
	{
		int test_arr[20];
		vector <int*> test_v;
		for (int i = 0; i < 20; i++) {
			test_arr[i] = rand() % 100;
			test_v.push_back(&(test_arr[i]));
			cout << test_arr[i] << "  ";
		}
		cout << '\n';
		SortPointers(test_v);
		for (auto& it : test_v) cout << *it << "  ";
		cout << "\n\n";
	}
	
	// 3
	{
		fstream file("War_and_Piece.txt", ios::in);
		if (!file.is_open()) { cout << "File Error\n"; return -1; }
		vector<string> text;
		string words;
		while (!file.eof()) {
			file >> words;
			text.push_back(words);
		}
		file.close();

		const char* symbols = "AaEeIiOoUuYy\0";

		// 3.1
		{
			t.start();
			unsigned int res = 0;
			count_if(text.begin(), text.end(), [&res,symbols](string& word) {
				size_t index_s = 0;
				while (symbols[index_s] != '\0') {
					size_t pos = 0;
					while (true) {
						pos = word.find(symbols[index_s], pos);
						if (pos == string::npos) break;
						res++;
						pos++;
					}
					index_s++;
				}
				return false;
			});
			cout << "count_if and find \t:= " << res << " time : = "<<t.end()<<'\n';
		}

		// 3.2
		{
			t.start();
			unsigned int res = 0;
			count_if(text.begin(), text.end(), [&res, symbols](string& word) {
				for (size_t i = 0; i < word.size(); i++)
					if (check_symbol(word[i])) res++;
				return false;
				});
			cout << "count_if and for \t:= " << res << " time : = " << t.end() << '\n';
		}

		// 3.3
		{
			t.start();
			unsigned int res = 0;

			for (auto& word : text) {
				size_t index_s = 0;
				while (symbols[index_s] != '\0') {
					size_t pos = 0;
					while (true) {
						pos = word.find(symbols[index_s],pos);
						if (pos == string::npos) break;
						pos++;
						res++;
					}
					index_s++;
				}
			}
			cout << "for and find \t\t:= " << res << " time : = " << t.end() << '\n';
		}

		// 3.4
		{
			t.start();
			unsigned int res = 0;
			for (auto& word : text) 
				for (size_t i = 0; i < word.size(); i++)
					if (check_symbol(word[i])) res++;
			cout << "for and for \t\t:= " << res << " time : = " << t.end() << '\n';
		}
	}

	return 0;
}