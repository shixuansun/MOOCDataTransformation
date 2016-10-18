//
// Created by ssunah on 10/17/16.
//

#ifndef MOOCDATATRANSFORMATION_TABULARDATA_H
#define MOOCDATATRANSFORMATION_TABULARDATA_H

#include "ColumnData.h"
#include <vector>
#include <cstring>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class TabularData {
private:
    map<string, int> colNameToIdx;
    vector<void*> columns;
    vector<DataType> dataTypes;
    size_t curSize;

public:
    ~TabularData();

public:
    void AddColumn(string colName, DataType dataType, const size_t colLength);
    void SetData(const size_t colIdx, const int value);
    void SetData(const size_t colIdx, const char* value);
    void SetData(const size_t colIdx, const string& value);
    void NewRow();
};

#endif //MOOCDATATRANSFORMATION_TABULARDATA_H
