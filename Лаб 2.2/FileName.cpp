#include<iostream>
#include<vector>
#include<iterator>
#include<chrono>
#include<string>

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
        for (int i = gap; i < arr.size(); i++)
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
    size_t size = distance(begin, end);
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

void generate_heap(vector<int>& arr, size_t i, size_t size, stats& st)
{
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    st.comparison_count++;
    if (left < size && arr[left] > arr[largest])
    {
        largest = left;
        st.copy_count++;
    }

    st.comparison_count++;
    if (right < size && arr[right] > arr[largest])
    {
        largest = right;
        st.copy_count++;
    }

    st.comparison_count++;
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        st.copy_count++;
        generate_heap(arr, largest, size, st);
    }
}

stats heap_sort(vector<int>& arr)
{
    stats st;
    for (int i = arr.size() / 2 - 1; i >= 0; i--)
    {
        generate_heap(arr, i, arr.size(), st);
    }

    for (int i = arr.size() - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        st.copy_count++;
        generate_heap(arr, 0, i, st);
    }
    return st;
}

void generate_heap(vector<int>::iterator begin, size_t i, size_t size, stats& st)
{
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    st.comparison_count++;
    if (left < size && *(begin + left) > *(begin + largest))
    {
        largest = left;
        st.copy_count++;
    }

    st.comparison_count++;
    if (right < size && *(begin + right) > *(begin + largest))
    {
        largest = right;
        st.copy_count++;
    }

    st.comparison_count++;
    if (largest != i)
    {
        swap(*(begin + i), *(begin + largest));
        st.copy_count++;
        generate_heap(begin, largest, size, st);
    }
}

stats heap_sort_iter(vector<int>::iterator& begin, vector<int>::iterator& end)
{
    size_t size = distance(begin, end);
    stats st;
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        generate_heap(begin, i, size, st);
    }

    for (int i = size - 1; i >= 0; i--)
    {
        swap(*begin, *(begin + i));
        st.copy_count++;
        generate_heap(begin, 0, i, st);
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
    size_t compare = 0, copy = 0;
    int n = 1000;

    chrono::time_point<std::chrono::system_clock> start, end;

    for (size_t i = 0; i < 100; ++i)
    {
        vector<int> arr;
        arr.reserve(n);
        for (size_t j = 0; j < n; ++j)
        {
            arr.push_back(lcg());
        }
        start = chrono::system_clock::now();
        st = shell_sort(arr);
        end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end - start;

        copy += st.copy_count;
        compare += st.comparison_count;
        seconds += elapsed_seconds.count();
    }
 
    cout << "TIME: " << seconds << endl << "AVERAGE TIME: " << seconds / 100 << endl << "COMPARISON: " << compare / 100 << endl << "COPY: " << copy / 100 << endl;
    cout << endl << endl;

    //chrono::time_point<std::chrono::system_clock> start, end;

    //for (size_t i = 0; i < n; ++i)
    //{
    //    vector<int> arr;
    //    arr.reserve(100000);
    //    for (size_t j = 0; j < 100000; ++j)
    //    {
    //        arr.push_back(lcg());
    //    }
    //    vector<int>::iterator it_begin = arr.begin();
    //    vector<int>::iterator it_end = arr.end();
    //    start = chrono::system_clock::now();
    //    st = shell_sort_iter(it_begin, it_end);
    //    end = chrono::system_clock::now();
    //    chrono::duration<double> elapsed_seconds = end - start;
    //    seconds += elapsed_seconds.count();
    //}

    //cout << "TIME: " << seconds << endl << "AVERAGE TIME: " << seconds / n << endl << "COMPARISON: " << st.comparison_count / n << endl << "COPY: " << st.copy_count / n << endl;
    //cout << endl << endl;

    //arr = { 9, 7, 3, 2, 5, 6, 1, 10, 4, 8 };
    //arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    //arr = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    //stats stt;

    //stt = shell_sort(arr);
    //stt = bubble_sort(arr);
    //stt = heap_sort(arr);

    //vector<int>::iterator it_begin = arr.begin();
    //vector<int>::iterator it_end = arr.end();

    //stt = shell_sort_iter(it_begin, it_end);
    //stt = bubble_sort_iter(it_begin, it_end);
    //stt = heap_sort_iter(it_begin, it_end);

    /*cout << "COMPARISON: " << stt.comparison_count << endl << "COPY: " << stt.copy_count << endl;
    for (auto& i : arr)
    {
        cout << i << endl;
    }*/

	return 0;
}