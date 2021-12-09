#include <iostream>
#include <string>
#include <sstream>
#include <time.h>

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

    unsigned int size() {
        return num_of_elements;
    }

    T& operator[](unsigned int index) {
        return array[index];
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

    void remove(unsigned int index) {
        /*if (index <= num_of_elements - 1) {
            T* tmparr = new T[arr_size];
            std::copy(array, array + index, tmparr);
            std::copy(array + index + 1, array + arr_size, tmparr + index);
            delete[] array;
            array = tmparr;
            num_of_elements--;
        }*/

        if (index < num_of_elements && index >= 0) {
            for (int i = index; i < num_of_elements; i++) {
                array[i] = array[i + 1];
            }
            num_of_elements--;
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
        przekopcowanie_w_gore(arr.size() - 1);
    }

    D delete_max() {
        if (arr.size() == 0) {
            abort();
        }
        else {
            D max = arr[0];
            if (arr.size() == 1) {           
                clear();
            }
            else {
                std::swap(arr[0], arr[arr.size() - 1]);
                arr.remove(arr.size() - 1);
                przekopcowanie_w_dol(0);
            }
            return max;
        }
        
    }

    void clear() {
        arr.delete_all();
    }

    std::string display(unsigned int n = 0) {
        return arr.display_array(n);
    }

private:
    DynamicArr<D> arr;
    
    void przekopcowanie_w_gore(unsigned int i) {
        if (i != 0) {
            if (arr[i] > arr[(i - 1) / 2]) {
                std::swap(arr[i], arr[(i - 1) / 2]);
                przekopcowanie_w_gore((i - 1) / 2);
            }
        }
        else {
            return;
        }
    }

    void przekopcowanie_w_dol(unsigned int i) {
      
        if ((2 * i + 1 < arr.size() && arr[2 * i + 1] > arr[i]) || (2 * i + 2 < arr.size() && arr[2 * i + 2] > arr[i])) {
            if (arr[2 * i + 1] > arr[2 * i + 2]) {
                std::swap(arr[i], arr[2 * i + 1]);
                przekopcowanie_w_dol(2 * i + 1);
            }
            else {
                std::swap(arr[i], arr[2 * i + 2]);
                przekopcowanie_w_dol(2 * i + 2);
            }    
        }
        return;
    }
};

int main()
{
    /*{
        srand(time(NULL));
        BinaryHeap<int> bh;
        for (int i = 0; i < 10; i++) {
            bh.add(rand() % 32000);
        }

        std::cout << bh.display(100) << std::endl;
        std::cout << "===============================================" << std::endl;
        for (int i = 0; i < 10; i++) {
            bh.delete_max();
            std::cout << bh.display(100) << std::endl;
            std::cout << "-----------------------------------------------" << std::endl;

        }

        return 0;
    }*/
    BinaryHeap<int> bh;
    
    const int MAX_ORDER = 7;
    srand(time(NULL));
    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o);
        std::cout << "===============================================" << std::endl;
        std::cout << "                    TEST" << o << std::endl;
        std::cout << "===============================================" << std::endl;


        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            bh.add(rand() % 32000);
        }
        clock_t t2 = clock();
        
        std::cout << bh.display(8);
        std::cout << "-----------------------------------------------" << std::endl;
        double time = (t2 - t1) / (double)CLOCKS_PER_SEC;
        std::cout << "Calkowity czas dodawania: " << time << std::endl;
        std::cout << "Sredni czas dodawania: " << time / n << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;

        t1 = clock();
        for (int i = 0; i < n; i++) {
            int polled = bh.delete_max();
        }
        t2 = clock();
        std::cout << bh.display();
        std::cout << "-----------------------------------------------" << std::endl;

        time = (t2 - t1) / (double)CLOCKS_PER_SEC;
        std::cout << "Calkowity czas usuwana: " << time << std::endl;
        std::cout << "Sredni czas usuwania: " << time / n << std::endl;
        std::cout << "-----------------------------------------------" << std::endl;

        bh.clear();
    }
    system("pause");
}
