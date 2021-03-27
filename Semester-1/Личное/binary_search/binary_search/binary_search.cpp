#include <iostream>
#include <iomanip>
int bynary_search(int* f, int length, int item);

int main()
{
    int* arr = new int[1024];
    for (int i = 0; i < 1024; i++) {
        arr[i] = i;
    }

    std::cout << bynary_search(arr, 1024, 26);
    return 0;
}

int bynary_search(int* f, int length, int item) {
    int mid, low = 0;
    int high = length - 1;
    int guess, position = -1;
    while (low <= high) {
        mid = (high + low) / 2;
        guess = f[mid];
        if (guess == item) {
            position = mid;
            break;
        }
        else if (guess > item) {
            high = mid - 1;
        }
        else if (guess < item) {
            low = mid + 1;
        }
    }
    return position;
}
