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

class Students
{
private:
    struct Data
    {
        string name;
        string last_name;
        double average;
    };
    vector<Data> group;

    void generate_heap(size_t i, size_t size)
    {
        size_t largest = i;
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;

        if (left < size && group[left] > group[largest])
        {
            largest = left;
        }

        if (right < size && group[right] > group[largest])
        {
            largest = right;
        }

        if (largest != i)
        {
            Data tmp = group[i];
            group[i] = group[largest];
            group[largest] = tmp;
            generate_heap(largest, size);
        }
    }
public:
    Students() = default;

    Students(const Students& a) = default;

    ~Students() = default;

    Students& operator = (const Students& s) = default;

    void add(string& name, string& last_name, double average)
    {
        group.push_back({ name, last_name, average });
    }

    friend ostream& operator << (ostream& out, const Students& s)
    {
        for (const auto& i : s.group)
        {
            cout << i.last_name << " " << i.name << " " << i.average;
            cout << endl;
        }
        return out;
    }

    friend bool operator > (const Data& d1, const Data& d2)
    {
        if (d1.last_name == d2.last_name && d1.name == d2.name) return d1.average > d2.average;
        if (d1.last_name == d2.last_name) return d1.name > d2.name;
        else return d1.last_name > d2.last_name;
    }

    void bubble_sort()
    {
        for (int i = 0; i < group.size() - 1; ++i)
        {
            bool flag = true;
            for (int j = 0; j < group.size() - i - 1; ++j)
            {
                if (group[j] > group[j + 1])
                {
                    flag = false;
                    Data tmp = group[j];
                    group[j] = group[j + 1];
                    group[j + 1] = tmp;
                }
            }
            if (flag) break;
        }
    }

    void shell_sort()
    {
        for (int gap = group.size() / 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < group.size(); i++)
            {
                auto tmp = group[i];
                int j;
                for (j = i; j >= gap && group[j - gap] > tmp; j -= gap)
                {
                    group[j] = group[j - gap];
                }
               group[j] = tmp;
            }
        }
    }

    void heap_sort()
    {
        for (int i = group.size() / 2 - 1; i >= 0; i--)
        {
            generate_heap(i, group.size());
        }

        for (int i = group.size() - 1; i >= 0; i--)
        {
            Data tmp = group[0];
            group[0] = group[i];
            group[i] = tmp;
            generate_heap(0, i);
        }
    }
};

stats bubble_sort(string& str) // сортировка строк
{
    stats st;
    for (int i = 0; i < str.size() - 1; ++i)
    {
        bool flag = true;
        for (int j = 0; j < str.size() - i - 1; ++j)
        {
            st.comparison_count++;
            if (str[j] > str[j + 1])
            {
                flag = false;
                swap(str[j], str[j + 1]);
                st.copy_count++;
            }
        }
        if (flag) break;
    }
    return st;
}

stats shell_sort(string& str) // сортировка строк
{
    stats st;
    for (int gap = str.size() / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < str.size(); i++)
        {
            int tmp = str[i];
            st.copy_count++;
            int j;
            st.comparison_count++;
            for (j = i; j >= gap && str[j - gap] > tmp; j -= gap)
            {
                st.comparison_count++;
                str[j] = str[j - gap];
                st.copy_count++;
            }
            str[j] = tmp;
        }
    }
    return st;
}

void generate_heap(string& str, size_t i, size_t size, stats& st) // сортировка строк
{
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    st.comparison_count++;
    if (left < size && str[left] > str[largest])
    {
        largest = left;
    }

    st.comparison_count++;
    if (right < size && str[right] > str[largest])
    {
        largest = right;
    }

    st.comparison_count++;
    if (largest != i)
    {
        swap(str[i], str[largest]);
        st.copy_count++;
        generate_heap(str, largest, size, st);
    }
}

stats heap_sort(string& str) // сортировка строк
{
    stats st;
    for (int i = str.size() / 2 - 1; i >= 0; i--)
    {
        generate_heap(str, i, str.size(), st);
    }

    for (int i = str.size() - 1; i >= 0; i--)
    {
        swap(str[0], str[i]);
        st.copy_count++;
        generate_heap(str, 0, i, st);
    }
    return st;
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
    }

    st.comparison_count++;
    if (right < size && arr[right] > arr[largest])
    {
        largest = right;
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
    }

    st.comparison_count++;
    if (right < size && *(begin + right) > *(begin + largest))
    {
        largest = right;
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
 //   stats st, st1;
	//vector<int> arr;
 //   double seconds = 0;
 //   size_t compare = 0, copy = 0;
 //   int n = 100000;

 //   chrono::time_point<std::chrono::system_clock> start, end;

 //   for (size_t i = 0; i < 100; ++i)
 //   {
 //       vector<int> arr;
 //       arr.reserve(n);
 //       for (size_t j = 0; j < n; ++j)
 //       {
 //           arr.push_back(lcg());
 //       }
 //       //st1 = shell_sort(arr);
 //       //reverse(arr.begin(), arr.end());
 //       start = chrono::system_clock::now();
 //       st = shell_sort(arr);
 //       end = chrono::system_clock::now();
 //       chrono::duration<double> elapsed_seconds = end - start;
 //       copy += st.copy_count;
 //       compare += st.comparison_count;
 //       seconds += elapsed_seconds.count();
 //   }
 //
 //   cout << "TIME: " << seconds << endl << "AVERAGE TIME: " << seconds / 100 << endl << "COMPARISON: " << compare / 100 << endl << "COPY: " << copy / 100 << endl;
 //   cout << endl << endl;

    string str = "fedcba";
    stats s;
    s = bubble_sort(str);
    cout << "Bubble sort: " << str << endl;

    string str1 = "fedcba";
    stats s1;
    s1 = shell_sort(str1);
    cout << "Shell sort: " << str1 << endl;

    string str2 = "fedcba";
    stats s2;
    s2 = heap_sort(str2);
    cout << "Heap sort: " << str2 << endl << endl;

    string last_name = "Semykin";
    string name = "Stepan";
    double a = 5;

    string last_name1 = "Gorshenin";
    string name1 = "Dmitry";
    double a1 = 4.9;

    string last_name2 = "Kunenkov";
    string name2 = "Ivan";
    double a2 = 4.9;

    string last_name3 = "Pribylov";
    string name3 = "Alexander";
    double a3 = 4.7;

    string last_name4 = "Marinin";
    string name4 = "Andrey";
    double a4 = 4;

    string last_name5 = "Semykin";
    string name5 = "Alexey";
    double a5 = 4;

    string last_name6 = "Semykin";
    string name6 = "Alexey";
    double a6 = 3;

    Students students;
    students.add(name6, last_name6, a6);
    students.add(name1, last_name1, a1);
    students.add(name2, last_name2, a2);
    students.add(name3, last_name3, a3);
    students.add(name5, last_name5, a5);
    students.add(name4, last_name4, a4);
    students.add(name, last_name, a);

    cout << students << endl << endl;
    //students.bubble_sort();
    //students.shell_sort();
    students.heap_sort();
    cout << students << endl << endl;

	return 0;
}