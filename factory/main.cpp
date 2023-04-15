#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <functional>


class ISorter {
public:
    virtual void Sort(std::vector<int>&) = 0;
};


class BubbleSorter: public ISorter {
public:
    void Sort(std::vector<int>& array) {
        for (int i = 0; i < array.size()-1; i++) {
            for (int j = 0; j < array.size()-1; j++) {
                if (array[j] > array[(int64_t) j+1]) {
                    int temp = array[j];
                    array[j] = array[(int64_t) j+1];
                    array[(int64_t) j+1] = temp;
                }
            }
        }
    }
};


class ShellSorter : public ISorter {
public:
    void Sort(std::vector<int>& array) {
        for (int gap = array.size() / 2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < array.size(); i += 1)
            {
                int temp = array[i];
                int j;
                for (j = i; j >= gap && array[(int64_t) j - gap] > temp; j -= gap)
                    array[j] = array[(int64_t) j - gap];
                array[j] = temp;
            }
        }
    }
};


class SortFactory {
public:
    enum Sorters
    {
        BUUBLE_SORT,
        SHELL_SORT
    };
public:
    SortFactory() {}

    ISorter* GetSort(SortFactory::Sorters type) {
        switch (type)
        {
        case SortFactory::BUUBLE_SORT:
            return (ISorter*) new BubbleSorter();
        case SortFactory::SHELL_SORT:
            return (ISorter*) new ShellSorter();
        }
    }
};


std::vector<int> CreateRandomArray(int n) {
    std::random_device r;
    std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
    std::mt19937 eng(seed);

    std::uniform_int_distribution<int> dist(1, 100);
    std::vector<int> v(n);

    generate(v.begin(), v.end(), std::bind(dist, eng));
    return v;
}

void PrintArray(const std::vector<int>& array) {
    for (auto item : array)
        std::cout << item << " ";
    std::cout << std::endl;
}


int main()
{
    auto array_1 = CreateRandomArray(50);
    auto array_2 = CreateRandomArray(50);
    SortFactory factory;

    auto shellSort = factory.GetSort(SortFactory::SHELL_SORT);
    auto bubbleSort = factory.GetSort(SortFactory::BUUBLE_SORT);

    shellSort->Sort(array_1);
    bubbleSort->Sort(array_2);

    PrintArray(array_1);
    PrintArray(array_2);
}
