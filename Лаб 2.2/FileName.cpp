#include<iostream>
#include<vector>
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

stats bubble_sort(vector<int>& arr)
{
    stats st;
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
    return st;
}

stats bubble_sort_iter(vector<int>::iterator& begin, vector<int>::iterator& end)
{
    stats st;
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
    return st;
}

stats shell_sort(vector<int>& arr)
{
    stats st;
    for (int gap = arr.size() / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < arr.size(); i += 1)
        {
            int tmp = arr[i];
            st.copy_count++;
            int j;
            st.comparison_count++;
            for (j = i; j >= gap && arr[j - gap] > tmp; j -= gap)
            {
                st.comparison_count++;
                arr[j] = arr[j - gap];
                st.copy_count++;
            }
            arr[j] = tmp;
        }
    }
    return st;
}

stats shell_sort_iter(vector<int>::iterator begin, vector<int>::iterator end)
{
    stats st;
    int size = distance(begin, end);
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < size; i++)
        {
            auto tmp = *(begin + i);
            st.copy_count++;
            int j;
            st.comparison_count++;
            for (j = i; j >= gap && *(begin + j - gap) > tmp; j -= gap)
            {
                st.comparison_count++;
                *(begin + j) = *(begin + j - gap);
                st.copy_count++;
            }
            *(begin + j) = tmp;
        }
    }
    return st;
}

size_t lcg()
{
    static size_t x = 0;
    x = (1021 * x + 24631) % 116640;
    return x;
}

int main()
{
    stats st, st1, st2;
	vector<int> arr, arr1;
    double seconds = 0;

    //int n = 5;
    //clock_t start = clock();
    //for (size_t i = 0; i < n; ++i)
    //{
    //    vector<int> arr;
    //    arr.reserve(10000);
    //    for (size_t j = 0; j < 10000; ++j)
    //    {
    //        arr.push_back(lcg());
    //    }
    //    vector<int>::iterator it_begin = arr.begin();
    //    vector<int>::iterator it_end = arr.end();
    //    it_begin = shell_sort_iter(it_begin, it_end, st);
    //}
    //clock_t end = clock();
    //seconds += (double)(end - start) / CLOCKS_PER_SEC;

    //cout << "TIME: " << seconds << endl << "AVERAGE TIME: " << seconds / n << endl << "COMPARISON: " << st.comparison_count / n << endl << "COPY: " << st.copy_count / n << endl;

    //cout << endl << endl;


    //chrono::time_point<std::chrono::system_clock> start, end;

    //start = chrono::system_clock::now();
    //for (size_t i = 0; i < n; ++i)
    //{
    //    vector<int> arr;
    //    arr.reserve(10000);
    //    for (size_t j = 0; j < 10000; ++j)
    //    {
    //        arr.push_back(lcg());
    //    }
    //    arr = shell_sort(arr, st);
    //}
    //end = chrono::system_clock::now();
    //chrono::duration<double> elapsed_seconds = end - start;

    //cout << "TIME: " << elapsed_seconds.count() << endl << "AVERAGE TIME: " << elapsed_seconds.count() / n << endl << "COMPARISON: " << st.comparison_count / n << endl << "COPY: " << st.copy_count / n << endl;
    //cout << endl << endl;

    //start = chrono::system_clock::now();
    //for (size_t i = 0; i < n; ++i)
    //{
    //    vector<int> arr;
    //    arr.reserve(10000);
    //    for (size_t j = 0; j < 10000; ++j)
    //    {
    //        arr.push_back(lcg());
    //    }
    //    vector<int>::iterator it_begin = arr.begin();
    //    vector<int>::iterator it_end = arr.end();
    //    it_begin = shell_sort_iter(it_begin, it_end, st1);
    //}
    //end = chrono::system_clock::now();
    //chrono::duration<double> elapsed_seconds1 = end - start;

    //cout << "TIME: " << elapsed_seconds1.count() << endl << "AVERAGE TIME: " << elapsed_seconds1.count() / n << endl << "COMPARISON: " << st1.comparison_count / n << endl << "COPY: " << st1.copy_count / n << endl;
    //cout << endl << endl;

    //start = chrono::system_clock::now();
    //for (size_t i = 0; i < n; ++i)
    //{
    //    vector<int> arr;
    //    arr.reserve(10000);
    //    for (size_t j = 0; j < 10000; ++j)
    //    {
    //        arr.push_back(lcg());
    //    }
    //    st2 = shell_sorting(arr);
    //}
    //end = chrono::system_clock::now();
    //chrono::duration<double> elapsed_seconds2 = end - start;

    //cout << "TIME: " << elapsed_seconds2.count() << endl << "AVERAGE TIME: " << elapsed_seconds2.count() / n << endl << "COMPARISON: " << st2.comparison_count / n << endl << "COPY: " << st2.copy_count / n << endl;
    //cout << endl << endl;

    //arr = { 9, 7, 3, 2, 5, 6, 1, 10, 4, 8 };
    //arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    //arr = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    //stats stt;
    //stt = shell_sort(arr);
    //stt = bubble_sort(arr);
    //cout << "COMPARISON: " << stt.comparison_count << endl << "COPY: " << stt.copy_count << endl;
    //arr = shell_sort(arr, st);

    //vector<int>::iterator it_begin = arr.begin();
    //vector<int>::iterator it_end = arr.end();
    //it_begin = shell_sort_iter(it_begin, it_end, st);

    //for (auto& i : arr)
    //{
    //    cout << i << endl;
    //}

	return 0;
}