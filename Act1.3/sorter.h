#ifndef sorter_h
#define sorter_h

#include <iostream>
#include <vector>

template <typename T>
class Sorter
{
    public:
        Sorter() {};
        ~Sorter() {};

        void swap(int i, int j, std::vector<T> &arr)
        {
            T aux = arr[i];
            arr[i] = arr[j];
            arr[j] = aux; 
        };

        virtual void sort(std::vector<T> &arr) {};
};

template <typename T>
class SelectionSort : public Sorter<T>
{
    public:
    SelectionSort() {};
    ~SelectionSort() {};

    void sort(std::vector<T> &arr)
    {
        for (size_t i = 0; i < arr.size() - 1; i++)
        {
            size_t min = i;
            for (size_t j = i + 1; j < arr.size(); j++)
            {
                if(arr[j] < arr[min])
                    min = j;
            }
            Sorter<T>::swap(i, min, arr);
        }
        
    };
};

template <typename T>
class BubbleSort : public Sorter<T>
{
    public:
    BubbleSort() {};
    ~BubbleSort() {};

    void sort(std::vector<T> &arr)
    {
        bool swaped = false;
        for (size_t i = 0; i < arr.size() - 1; i++)
        {
            for (size_t j = 0; j < arr.size() - i - 1; j++)
            {
                if(arr[j] > arr[j+1])
                    Sorter<T>::swap(j, j+1, arr);
                    swaped = true;
            }
            if (swaped == false)
                break;
            
        }
        
        
    };
};

template <typename T>
class InsertionSort : public Sorter<T>
{
    public:
    InsertionSort() {};
    ~InsertionSort() {};

    void sort(std::vector<T> &arr)
    {
        int i, val, j;
        for (i = 1; i < arr.size(); i++)
        {
            val = arr[i];
            j = i - 1;
            while (j >= 0 && arr[j] > val)
            {
                arr[j+1] = arr[j];
                j = j - 1;
            }
            arr[j+1] = val;
        }
    };
};

template <typename T>
class MergeSort : public Sorter<T>
{
    public:
    MergeSort() {};
    ~MergeSort() {};

    void merge(std::vector<T> &arr, int left, int middle, int right)
    {
        int i, j, k;
        int num1 = middle - left + 1;
        int num2 = right - middle;

        std::vector<int> izq;
        std::vector<int> der;

        for (i = 0; i < num1; i++)
        {
            izq.push_back(arr[left + i]);
        }
        for (j = 0; j < num2; j++)
        {
            der.push_back(arr[middle + 1 + j]);
        }

        i = 0;
        j = 0;
        k = left;

        while(i < num1 && j < num2)
        {
            if(izq[i] <= der[j])
            {
                arr[k] = izq[i];
                i++;
            }
            else
            {
                arr[k] = der[j];
                j++;
            }
            k++;
        }

        while(i < num1)
        {
            arr[k] = izq[i];
            i++;
            k++;
        }

        while(j < num2)
        {
            arr[k] = der[j];
            j++;
            k++;
        }
    };

    void sort(std::vector<T> &arr, int left, int right)
    {
        if(left < right)
        {
            int middle = left + (right - left) / 2;

            sort(arr, left, middle);
            sort(arr, middle + 1, right);

            merge(arr, left, middle, right);
        }
    };
};

template <typename T>
class QuickSort : public Sorter<T>
{
    public: 
    QuickSort() {};
    ~QuickSort() {};

    int partition(std::vector<T> &arr, int low, int high)
    {
        T pivot = arr[high];
        int i = (low - 1);

        for (size_t j = low; j <= high - 1; j++)
        {
            if(arr[j] <= pivot)
            {
                i++;
                Sorter<T>::swap(i, j, arr);
            }
        }
        Sorter<T>::swap(i + 1, high, arr);
        return (i + 1);
    };

    void sort(std::vector<T> &arr, int low, int high)
    {
        if(low < high)
        {
            int index = partition(arr, low, high);

            sort(arr, low, index - 1);
            sort(arr, index + 1, high);
        }
    };

};

#endif