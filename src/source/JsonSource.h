//
// Created by ssunah on 10/17/16.
//

#ifndef MOOCDATATRANSFORMATION_JSONSOURCE_H
#define MOOCDATATRANSFORMATION_JSONSOURCE_H

#include "../DataConfig.h"
#include "../TabularData.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <json/json.h>

using namespace std;

class JsonSource {
private:
    vector<ColumnConfig> eventColumnsConfig;
    TabularData eventsTabular;
    vector<int> parsingErrorLines;
    vector<int> saveErrorLines;
    vector<int> exceedLengthLines;
    vector<int> exceedLengthColumnId;


private:
    // Currently, the schema is hard coded in this function for simplicity. In future, the schema should be input by
    // caller.
    void GenerateTabularSchema();
    void CreateSchema();

    // For test purpose

    void GetFieldLength(const string& jsonObject, const int line, vector<int>& maxLengthOfEachColumn);
public:
    JsonSource();
    void GetMaximumLengthOfEachColumn(const string file);
    void ProcessFile(const string file);
    void Process(const string& jsonObject, const int line);
    void CreateNewRow();
};


#endif //MOOCDATATRANSFORMATION_JSONSOURCE_H
