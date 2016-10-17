//
// Created by ssunah on 10/17/16.
//

#include <iostream>
#include <fstream>
#include <json/json.h>
#include "source/JsonSource.h"

using namespace std;

int main() {
//    ifstream inputStream("../input.json", ifstream::binary);
//    Json::Value root;
//    Json::Reader reader;
//    bool parsingSuccessful = reader.parse( inputStream, root, false );
//    if ( !parsingSuccessful )
//    {
//        // report to the user the failure and their locations in the document.
//        std::cout  << "Failed to parse configuration\n"
//        << reader.getFormattedErrorMessages();
//        return -1;
//    }
//
//    Json::Value page = root["page"];
//    cout << page.size() << endl;
//    if (page.isNull())
//        cout << "Is Null" << endl;
//
//    cout << root["agent"] << endl;
//
//    Json::Value event;
//    reader.parse(root["event"].asString(), event, false);
//    cout << event << endl;
//    if (event.isObject())
//        cout << "Is Object" << endl;
//    else
//        cout << "Is not object" << endl;
//    cout << root << endl;
    string file = "../input.json";
    JsonSource jsonSrc;
    jsonSrc.ProcessFile(file);
    return 0;
}
