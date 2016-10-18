//
// Created by ssunah on 10/17/16.
//

#include "TabularData.h"

void TabularData::AddColumn(string colName, DataType dataType, const size_t colLength) {
    void* newColumn = NULL;

    switch (dataType) {
        case DataType::Integer:
            newColumn = (void*) new ColumnData<int>();
            break;
        case DataType::String:
            newColumn = (void*) new ColumnData<char>(colLength);
            break;
        default:
            break;
    }

    colNameToIdx[colName] = colNameToIdx.size();
    columns.push_back(newColumn);
    dataTypes.push_back(dataType);
}

void TabularData::NewRow() {
    for (int i = 0; i < columns.size(); ++i) {
        DataType dataType = dataTypes[i];
        switch (dataType) {
            case DataType::Integer: {
                ColumnData<int>* columnInteger = (ColumnData<int> *) columns[i];
                columnInteger->NewRow();
                break;
            }
            case DataType::String: {
                ColumnData<char>* columnString = (ColumnData<char>*) columns[i];
                columnString->NewRow();
                break;
            }
            default:
                break;
        }
    }

    curSize += 1;
}

void TabularData::SetData(const size_t colIdx, const char *value) {
    ColumnData<char>* columnString = (ColumnData<char>*) columns[colIdx];
    strcpy(columnString->GetCurrentCursor(), value);
}

void TabularData::SetData(const size_t colIdx, const string& value) {
    ColumnData<char>* columnString = (ColumnData<char>*) columns[colIdx];
    copy(value.begin(), value.end(), columnString->GetCurrentCursor());
}

void TabularData::SetData(const size_t colIdx, const int value) {
    ColumnData<int>* columnInteger = (ColumnData<int>*) columns[colIdx];
    *(columnInteger->GetCurrentCursor()) = value;
}

TabularData::~TabularData() {
    for (int i = 0; i < columns.size(); ++i) {
        DataType dataType = dataTypes[i];
        switch (dataType) {
            case DataType::Integer: {
                ColumnData<int>* columnInteger = (ColumnData<int> *) columns[i];
                delete columnInteger;
                break;
            }
            case DataType::String: {
                ColumnData<char>* columnString = (ColumnData<char>*) columns[i];
                delete columnString;
                break;
            }
            default:
                break;
        }
    }

    colNameToIdx.clear();
    columns.clear();
    dataTypes.clear();
}