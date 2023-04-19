#include<iostream>
#include<vector>
#include<ctime>
#include<iterator>
#include<chrono>

using namespace std;

struct stats 
{
	size_t comparison_count = 0;
	size_t copy_count = 0;
};

void swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap1(vector<int>::iterator& begin, vector<int>::iterator& end)
{
    auto tmp = begin;
    begin = end;
    end = tmp;
}


vector<int>& bubble_sort(vector<int>& arr, stats& st)
{
    for (int i = 0; i < arr.size() - 1; ++i)
    {
        bool flag = true;
        for (int j = 0; j < arr.size() - i - 1; ++j)
        {
            st.comparison_count++;
            if (arr[j] > arr[j + 1])
            {
                flag = false;
                swap(arr[j], arr[j + 1]);
                st.copy_count++;
            }
        }
        if (flag) break;
    }
    return arr;
}

vector<int>::iterator bubble_sort_iter(vector<int>::iterator begin, vector<int>::iterator end, stats& st)
{
    for (auto i = begin; i != end - 1; ++i)
    {
        bool flag = true;
        for (auto j = begin; j != end - 1; ++j)
        {
            st.comparison_count++;
            if (*j > *(j + 1))
            {
                flag = false;
                swap(*j, *(j + 1));
                st.copy_count++;
            }
        }
        if (flag) break;
    }
    return begin;
}



size_t lcg()
{
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

int main()
{
    stats st;
	vector<int> arr, arr1;
    double seconds = 0;

    /*clock_t start = clock();
    for (size_t i = 0; i < 3; ++i)
    {
        vector<int> arr;
        arr.reserve(10000);
        for (size_t j = 0; j < 10000; ++j)
        {
            arr.push_back(lcg());
        }
        vector<int>::iterator it_begin = arr.begin();
        vector<int>::iterator it_end = arr.end();
        it_begin = bubble_sort_iter(it_begin, it_end, st);
    }
    clock_t end = clock();
    seconds += (double)(end - start) / CLOCKS_PER_SEC;

    cout << "TIME: " << seconds << endl << "AVERAGE TIME: " << seconds / 100 << endl << "COMPARISON: " << st.comparison_count / 100 << endl << "COPY: " << st.copy_count / 100 << endl;*/

    chrono::time_point<std::chrono::system_clock> start, end;

    start = chrono::system_clock::now();
    for (size_t i = 0; i < 5; ++i)
    {
        vector<int> arr;
        arr.reserve(10000);
        for (size_t j = 0; j < 10000; ++j)
        {
            arr.push_back(lcg());
        }
        arr = bubble_sort(arr, st);
    }
    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

    cout << "TIME: " << elapsed_seconds.count() << endl << "AVERAGE TIME: " << elapsed_seconds.count() / 5 << endl << "COMPARISON: " << st.comparison_count / 100 << endl << "COPY: " << st.copy_count / 100 << endl;

	return 0;
}