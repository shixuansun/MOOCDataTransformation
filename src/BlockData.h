//
// Created by ssunah on 10/17/16.
//

#ifndef MOOCDATATRANSFORMATION_BLOCKDATA_H
#define MOOCDATATRANSFORMATION_BLOCKDATA_H

#include "DataConfig.h"

template<typename T> class BlockData {
public:
    T* values;
    size_t curSize;

public:
    BlockData(const size_t length = 1);
    ~BlockData();
};

template<typename T> BlockData<T>::BlockData(const size_t length) {
    values = new T[BLOCK_SIZE * length];
    curSize = 0;
}

template<typename T> BlockData<T>::~BlockData() {
    delete[] values;
    curSize = 0;
}

#endif //MOOCDATATRANSFORMATION_BLOCKDATA_H
