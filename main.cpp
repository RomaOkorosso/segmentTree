#include <iostream>
#include "tree.cpp"
#include <ctime>

int min(int a, int b){
    return std::min(a, b);
}

int main() {
    using namespace std;
    srand(time(NULL));

    int n = 16;
    int data[n];
    for (int i = 0; i < n; i++) {
        data[i] = rand() % 10;
        }

    SegmentTree<int> tree = SegmentTree<int> (data, n, min);
    tree.print();


    return 0;
}
