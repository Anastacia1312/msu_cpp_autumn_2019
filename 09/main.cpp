#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <iterator>
#define type_size 1024*1024

using namespace std;

template <class MinHeap, class Out>

void merge_files (MinHeap& heap, Out& output)
{
    while(!heap.empty())
    {
        auto seq = heap.top();
        heap.pop();
        auto tmp = *seq.first++;
        output.write(reinterpret_cast<char *>(&tmp), sizeof(uint64_t));
        if (seq.first != seq.second)
            heap.emplace(seq);
    }
}

int main()
{
    auto *vec = new uint64_t [type_size];
    ifstream input ("input.txt", ios::binary | ios::in);
    while (input)
    {
        uint64_t tmp;
        input.read(reinterpret_cast<char *>(&tmp), sizeof(uint64_t));
        cout << tmp << ' ';
    }
    input.close();
    cout << endl;
    input.open("input.txt", ios::binary | ios::in);
    size_t qty = 0;
    vector<string> name;
    while (input)
    {
        input.read(reinterpret_cast<char *>(vec), type_size);
        auto size_in = input.gcount();
        if (size_in > 0) {
            for (int i = 0; i < 2; ++i)
            {
                stringstream str;
                str << qty;
                name.emplace_back();
                str >> name[qty++];
            }
            
            std::thread thr_1([vec, size_in]()
            {
                sort(vec, vec + (size_in / (2 * sizeof(uint64_t))));
            });
            
            std::thread thr_2([vec, size_in]()
            {
                sort(vec + size_in / (2 * sizeof(uint64_t)), vec + size_in / sizeof(uint64_t));
            });
            
            thr_1.join();
            thr_2.join();
            for (size_t i = 0; i < size_in / sizeof(uint64_t); ++i)
                cout << vec[i] << ' ';
            cout << endl;
            ofstream output;
            output.open(name[qty - 2]);
            for (size_t i = 0; i < size_in / (2 * sizeof(uint64_t)); ++i)
                output << vec[i] << ' ';
            output.close();
            output.open(name[qty - 1]);
            for (size_t i = size_in / (2 * sizeof(uint64_t)); i < size_in / sizeof(uint64_t); ++i)
                output << vec[i] << ' ';
            output.close();
        }
    }
    input.close();
    ofstream output("output.txt", ios::binary);
    vector <ifstream> files (qty);
    typedef istream_iterator<uint64_t> it;
    typedef pair<it, it> seq;
    
    auto increase = [](const seq& left, const seq& right)
    {
        return *left.first > *right.first;
    };
    
    priority_queue<seq, vector<seq>, decltype(increase)> heap(increase);
    auto count = qty;
    while (count--)
    {
        files[count].open(name[count]);
        heap.emplace(it(files[count]), it());
    }
    merge_files(heap, output);
    for(size_t i = 0; i < qty; ++i)
    {
        files[i].close();
        remove(name[i].c_str());
    }
    output.close();
    input.open("output.txt");
    while(input)
    {
        uint64_t tmp;
        input.read(reinterpret_cast<char *>(&tmp), sizeof(uint64_t));
        cout << tmp << ' ';
    }
    cout << endl;
    input.close();
    delete[] vec;
    cout << "Ok" << endl;
    return 0;
}