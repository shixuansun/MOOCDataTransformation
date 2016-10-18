//
// Created by ssunah on 10/17/16.
//

#include <iostream>
#include <fstream>
#include <json/json.h>
#include "source/JsonSource.h"

using namespace std;

int main() {
    string file = "/home/shixuan_sun/data/mitx-24.00x-2013-sond/log_data/MITx-24.00x-2013_SOND___2014_08_17___tracking_log.json";
    // string file = "../data/input.json";
    JsonSource jsonSrc;
    // jsonSrc.ProcessFile(file);
    jsonSrc.GetMaximumLengthOfEachColumn(file);
    return 0;
}
