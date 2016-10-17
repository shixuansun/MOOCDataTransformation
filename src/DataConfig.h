//
// Created by ssunah on 10/17/16.
//

#ifndef MOOCDATATRANSFORMATION_DATACONFIG_H
#define MOOCDATATRANSFORMATION_DATACONFIG_H

#include <stddef.h>
#include <string>

#define BLOCK_SIZE 8192

enum DataType {
    Integer,
    String
};

class ColumnConfig {
public:
    DataType dataType;
    size_t colLength;
    std::string colName;
    std::string srcName;
};

#endif //MOOCDATATRANSFORMATION_DATACONFIG_H
