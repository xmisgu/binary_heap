#include <iostream>
#include <string>
#include <sstream>


template <typename T>
class DynamicArr {
private:
    unsigned int arr_size;
    unsigned int num_of_elements;
    T* array;
public:
    DynamicArr() {
        arr_size = 1; //array size
        num_of_elements = 0; //number of elements in array
        array = new T[arr_size];
    }

    ~DynamicArr() {
        delete[] array;
    }

    void add_element(const T& new_data) {
        if (arr_size == num_of_elements) make_arr_bigger();

        array[num_of_elements] = new_data;
        num_of_elements++;
    }

    void make_arr_bigger() {
        arr_size = arr_size * 2;
        T* tmp_arr = new T[arr_size];

        for (unsigned int i = 0; i < num_of_elements; i++) {
            tmp_arr[i] = array[i];
        }

        delete[] array;
        array = tmp_arr;
    }

    T find_element(unsigned int i) {
        if (i < num_of_elements) {
            return array[i];
        }
        else {
            abort();
        }
    }

    void swap_data(unsigned int i, const T& new_data) {
        if (i < num_of_elements) {
            array[i] = new_data;
        }
        else {
            abort();
        }
    }

    void sort() {
        T tmp;
        bool flag;
        for (int i = 0; i < num_of_elements - 1; i++) {
            flag = 0;
            for (int j = 0; j < num_of_elements - i - 1; j++) {
                if (array[j] > array[j + 1]) {
                    tmp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = tmp;
                    flag = 1;
                }
            }
            if (!flag) break;
        }
    }

    void delete_all() {
        delete[] array;
        arr_size = 1;
        num_of_elements = 0;
        array = new T[arr_size];
    }

    std::string display_array(unsigned int n = 0) {
        std::ostringstream output;

        output << "Rozmiar tablicy: " << arr_size << std::endl;
        output << "Liczba elementow: " << num_of_elements << std::endl;

        if (n > num_of_elements) n = num_of_elements;

        for (unsigned int i = 0; i < n; i++) {
            output << *&array[i] << std::endl;
        }

        return output.str();
    }
};

template <typename D>
class BinaryHeap {
public:
    void add(const D& data) {
        arr.add_element(data);
    }

    bool delete_max() {
        return 0;
    }

    void clear() {
        arr.delete_all();
    }

    std::string display(unsigned int n = 0) {
        return arr.display_array(n);
    }

private:
    DynamicArr<D> arr;
    
    void przekopcowanie_w_gore() {
        //todo
    }

    void przekopcowanie_w_dol() {
        //todo
    }
};

int main()
{
    BinaryHeap<int> test;
    test.add(2);
    test.add(90);
    test.add(3);
    test.add(65);
    test.add(211);
    test.add(212);
    test.add(30);
    test.add(11);
    test.add(1);

    std::cout << test.display(1000);
}
