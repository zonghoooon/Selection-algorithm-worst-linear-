#include <iostream>
#include <random>
#include <ctime>

using namespace std;
#define NUM 100000
int list[NUM];

class Select {
private:
    int sorted[NUM + 1];
    int Selection_partition(int arr[], int first, int last, int pivot, bool linear) {
        int low, high;
        low = first;
        high = last + 1;
        if (!linear) pivot = arr[first];
        else {
            for (int i = first; i <= last; i++) {
                if (arr[i] == pivot) {
                    swap(arr[first], arr[i]);
                    break;
                }
            }
        }//locate pivot front

        do {
            do {
                low++;
            } while (low <= last && arr[low] < pivot);
            do {
                high--;
            } while (high >= first && arr[high] > pivot);
            if (low < high) swap(arr[low], arr[high]);
        } while (low < high);
        swap(arr[first], arr[high]);
        return high;
    }
    int Selection_AVG(int arr[], int first, int last, int order) {
        if (first == last) return arr[first];
        int q = Selection_partition(arr, first, last, 0, false);
        int k = q - first + 1;
        if (order < k) return Selection_AVG(arr, first, q - 1, order);
        else if (order == k) return arr[q];
        else return Selection_AVG(arr, q + 1, last, order - k);
    }// Average llinear seletion
    int Selection_pivot(int arr[], int first, int last) {
        int num = (last - first) / 5;
        int fin;
        for (int i = 0; i < num; i++) {
            sorted[i] = Selection_Linear(arr, first + i * 5, first + i * 5 + 4, 3);
            fin = first + i * 5 + 5;
        }
        sorted[num] = Selection_Linear(arr, fin, last, ((last - fin) / 2) + 1);

        int med = Selection_Linear(sorted, 0, num, (num / 2) + 1);
        return med;
    }//worst linear selection

    int Selection_Linear(int arr[], int first, int last, int order) {
        if (last - first < 5) return Selection_AVG(arr, first, last, order);//if the elements smaller than 5, use Selection_AVG

        int num = (last - first) / 5;
        int med = Selection_pivot(arr, first, last);
        int q = Selection_partition(arr, first, last, med, true);
        int k = q - first + 1;

        if (order < k) return Selection_Linear(arr, first, q - 1, order);
        else if (order == k) return arr[q];
        else return Selection_Linear(arr, q + 1, last, order - k);

    }

public:
    int Selection() {
        return Selection_Linear(list, 0, NUM - 1, (NUM - 1) / 2 + 1);
    }
    bool Selection_checker(int num) {
        int cnt = 0;
        for (int i = 0; i < NUM - 1; i++) {
            if (list[i] < num) cnt++;
        }
        if (cnt == (NUM - 1) / 2) return true;
        else return false;
    }
};

class Array {
private:
    void Shuffle(int list[]) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(0, NUM - 1);
        int ran;
        for (int i = 0; i < NUM; i++) {
            ran = dis(gen);
            swap(list[i], list[ran]);
        }
    } 
public:
    void Make() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(1, 10);
        int temp = 0;
        for (int i = 0; i < NUM; i++) {
            temp += dis(gen);
            list[i] += temp;
        }
        Shuffle(list);
    }
};

int main()
{

    int med;
    Select sort = Select();
    Array array = Array();
    array.Make();

    clock_t t = clock();

    med = sort.Selection();
    t = clock() - t;
    cout << t << "ms." << endl;

    int temp;
    cout << "Median: " << med << endl;
    cout << "Enter '0' to verify that the median is right" << endl;
    cin >> temp;
    if (temp == 0) {
        if (sort.Selection_checker(med)) cout << "correct." << endl;
        else cout << "incorrect." << endl;
    }


}
/* result
        (first test running time, second test running time, third test running time)
        Linear selection 중간값 탐색: (5ms, 6ms, 5ms)소요
 */



