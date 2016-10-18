//
// Created by ssunah on 10/17/16.
//

#include "JsonSource.h"
#include<sys/time.h>

JsonSource::JsonSource() {
    GenerateTabularSchema();
    CreateSchema();
}

void JsonSource::GenerateTabularSchema() {
    ColumnConfig colConfig;
    colConfig.colName = "agent";
    colConfig.colLength = 256;
    colConfig.dataType = DataType::String;
    colConfig.srcName = "agent";
    eventColumnsConfig.push_back(colConfig);

    colConfig.colName = "event_source";
    colConfig.colLength = 32;
    colConfig.dataType = DataType::String;
    colConfig.srcName = "event_source";
    eventColumnsConfig.push_back(colConfig);

    colConfig.colName = "event_type";
    colConfig.colLength = 256;
    colConfig.dataType = DataType::String;
    colConfig.srcName = "event_type";
    eventColumnsConfig.push_back(colConfig);

    colConfig.colName = "ip";
    colConfig.colLength = 16;
    colConfig.dataType = DataType::String;
    colConfig.srcName = "ip";
    eventColumnsConfig.push_back(colConfig);

    colConfig.colName = "page";
    colConfig.colLength = 256;
    colConfig.dataType = DataType::String;
    colConfig.srcName = "page";
    eventColumnsConfig.push_back(colConfig);

    colConfig.colName = "time";
    colConfig.colLength = 48;
    colConfig.dataType = DataType::String;
    colConfig.srcName = "time";
    eventColumnsConfig.push_back(colConfig);

    colConfig.colName = "username";
    colConfig.colLength = 64;
    colConfig.dataType = DataType::String;
    colConfig.srcName = "username";
    eventColumnsConfig.push_back(colConfig);

    colConfig.colName = "course_id";
    colConfig.colLength = 128;
    colConfig.dataType = DataType::String;
    colConfig.srcName = "course_id";
    eventColumnsConfig.push_back(colConfig);

    colConfig.colName = "course_display_name";
    colConfig.colLength = 128;
    colConfig.dataType = DataType::String;
    colConfig.srcName = "course_display_name";
    eventColumnsConfig.push_back(colConfig);

    colConfig.colName = "event";
    colConfig.colLength = 512;
    colConfig.dataType = DataType::String;
    colConfig.srcName = "event";
    eventColumnsConfig.push_back(colConfig);

    colConfig.colName = "context";
    colConfig.colLength = 512;
    colConfig.dataType = DataType::String;
    colConfig.srcName = "context";
    eventColumnsConfig.push_back(colConfig);
}

void JsonSource::CreateSchema() {
    for (int i = 0; i < eventColumnsConfig.size(); ++i) {
        eventsTabular.AddColumn(eventColumnsConfig[i].colName, eventColumnsConfig[i].dataType,
                                eventColumnsConfig[i].colLength);
    }
}

void JsonSource::ProcessFile(const string file)
{
    timeval start;
    gettimeofday(&start, NULL);

    ifstream inputStream(file, ifstream::binary);

    string str;
    int count = 0;
    while (std::getline(inputStream, str))
    {
        if (count % 2000 == 0) {
            cout << count << " rows have been processed." << endl;
        }
        
        Process(str, ++count);
    }

    timeval end;
    gettimeofday(&end, NULL);
    cout << "The elapsed time of reading log file: " << end.tv_sec-start.tv_sec << " seconds." << endl;
}

void JsonSource::Process(const string& jsonObject, const int line) {
    Json::Reader reader;
    Json::Value root;

    bool parsingSuccessful = reader.parse(jsonObject, root, false );
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        cerr << "Failed to parse configuration line " << line << endl;
        cerr << reader.getFormattedErrorMessages() << endl;
        errorLines.push_back(line);
        return;
    }

    try {
        for (int i = 0; i < eventColumnsConfig.size(); ++i) {
            switch (eventColumnsConfig[i].dataType)
            {
                case DataType::Integer: {
                    int res = root.get(eventColumnsConfig[i].colName, 0).asInt();
                    eventsTabular.SetData(i, res);
                    break;
                }
                case DataType::String: {
                    eventsTabular.SetData(i, root.get(eventColumnsConfig[i].colName, "").toStyledString());
                    break;
                }
            }
        }

        eventsTabular.NewRow();
    }
    catch (exception e) {
        errorLines.push_back(line);
    }
}