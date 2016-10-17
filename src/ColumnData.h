//
// Created by ssunah on 10/17/16.
//

#ifndef MOOCDATATRANSFORMATION_COLUMNDATA_H
#define MOOCDATATRANSFORMATION_COLUMNDATA_H

#include "BlockData.h"
#include <vector>
using namespace std;

template<typename T> class ColumnData {
private:
    vector<BlockData<T>*> blocks;
    size_t curSize;
    size_t colLength;
    BlockData<T>* curBlock;

public:
    ColumnData(const size_t length = 1) {
        curSize = 0;
        colLength = length;
        curBlock = new BlockData<T>(colLength);
        blocks.push_back(curBlock);
    }

    ~ColumnData() {
        for (int i = 0; i < blocks.size(); ++i) {
            delete blocks[i];
        }

        blocks.clear();
    }

    T* GetCurrentCursor() {
        return &(curBlock->values[curBlock->curSize * colLength]);
    }

    void NewRow() {
        curSize += 1;
        if (curBlock->curSize < BLOCK_SIZE) {
            curBlock->curSize += 1;
        }
        else
        {
            curBlock = new BlockData<T>(colLength);
            blocks.push_back(curBlock);
        }
    }

    size_t  GetColumnLength() {
        return colLength;
    }
};

#endif //MOOCDATATRANSFORMATION_COLUMNDATA_H
