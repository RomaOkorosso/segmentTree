//
// Created by Roma on 02.04.2021.
//
#include <iostream>

template<typename T>

class SegmentTree {
private:
    T *_data;
    int _len;

    T (*_aggregate)(T, T);

    static int parent(int n) {
        return n / 2;
    }

    static int leftChild(int n) {
        return 2 * n;
    }

    static int rightChild(int n) {
        return 2 * n + 1;
    }

    T build(int n) {
        if (_len <= n)
            return _data[n];
        _data[n] = _aggregate(build(leftChild(n)), build(rightChild(n)));
        return _data[n];
    }

public:

    T get(int lBorder, int rBorder) {
        T result = _aggregate(_data[lBorder], _data[rBorder]);
        while (rBorder - lBorder > 2) {
            lBorder = lBorder / 2 + lBorder % 2;
            rBorder = rBorder / 2 - rBorder % 2; // here can be mistake
            result = _aggregate(result, _data[lBorder]);
            result = _aggregate(result, _data[lBorder]);
        }
        return result;
    }

    void update(int index, T value) {
        int node_index = index + _len;
        _data[node_index] = value;

        while (node_index > 1) {
            node_index = parent(node_index);
            _data[node_index] = _aggregate(leftChild(node_index), rightChild(node_index));
        }
    }

    void print() {
        int l = _len;
        while (l) {
            for (int i = l; i < 2 * l; i++)
                std::cout << _data[i] << ' ';
            std::cout << '\n';
            l /= 2;
        }
    }

    SegmentTree(T *src, int len, T (*func)(T, T)) {
        _aggregate = func;
        _len = 1;
        while (_len < len)
            _len <<= 1;
        _data = new T[2 * _len];
        for (int i = _len; i < _len + len; i++)
            _data[i] = src[i - _len];
        build(1);
        // print();
    }
};