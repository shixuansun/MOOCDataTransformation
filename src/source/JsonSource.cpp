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
    colConfig.colLength = 24;
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
        exceedLengthColumnId.push_back(0);
    }
}

void JsonSource::ProcessFile(const string file)
{
    timeval start;
    gettimeofday(&start, NULL);

    ifstream inputStream(file, ifstream::binary);

    string str;
    int count = 0;
    int max = 1000000;
    while (std::getline(inputStream, str) && count < max)
    {
        Process(str, ++count);

        if (count % 2000 == 0) {
            cout << count << " rows have been processed." << endl;
        }
    }
    
    for (int i = 0; i < exceedLengthColumnId.size(); ++i) {
        cout << exceedLengthColumnId[i] << " " << endl;
    }

    cout << "The number of lines processed: " << count << endl;
    cout << "The number of lines can not be parsed: " << parsingErrorLines.size() << endl;
    cout << "The number of lines can not be saved: " << saveErrorLines.size() << endl;
    cout << "The number of lines exceed width: " << exceedLengthLines.size() << endl;
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
        parsingErrorLines.push_back(line);
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
                    string value = root.get(eventColumnsConfig[i].colName, "").toStyledString();
                    eventsTabular.SetData(i, value);
                    if (value.size() + 1 > eventColumnsConfig[i].colLength) {
                        exceedLengthLines.push_back(line);
                        exceedLengthColumnId[i] = 1;
                    }
                    break;
                }
            }
        }

        eventsTabular.NewRow();
    }
    catch (exception e) {
        saveErrorLines.push_back(line);
    }
}

void JsonSource::CreateNewRow() {
    for (int i = 0; i < 100000; ++i) {
        eventsTabular.NewRow();
        if (i % 10000 == 0)
            cout << "Hello" << endl;
    }
}

void JsonSource::GetMaximumLengthOfEachColumn(const string file) {
    timeval start;
    gettimeofday(&start, NULL);

    vector<int> maxLengthOfEachColumn;
    for (int i = 0; i < eventColumnsConfig.size(); ++i) {
        maxLengthOfEachColumn.push_back(0);
    }

    ifstream inputStream(file, ifstream::binary);
    string str;
    int count = 0;
    while (std::getline(inputStream, str))
    {
        Process(str, ++count);
        GetFieldLength(str, ++count, maxLengthOfEachColumn);
        if (count % 2000 == 0) {
            cout << count << " rows have been processed." << endl;
        }
    }

    timeval end;
    gettimeofday(&end, NULL);
    cout << "The number of lines processed: " << count << endl;
    cout << "The number of lines can not be parsed: " << parsingErrorLines.size() << endl;
    cout << "The number of lines can not be saved: " << saveErrorLines.size() << endl;

    cout << "Maximum length of each column:" << endl;
    for (int i = 0; i < maxLengthOfEachColumn.size(); ++i) {
        cout << "Column " << i << " : " << maxLengthOfEachColumn[i] << endl;
    }

    cout << "The elapsed time of reading log file: " << end.tv_sec-start.tv_sec << " seconds." << endl;
}

void JsonSource::GetFieldLength(const string& jsonObject, const int line, vector<int>& maxLengthOfEachColumn) {
    Json::Reader reader;
    Json::Value root;

    bool parsingSuccessful = reader.parse(jsonObject, root, false );
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        cerr << "Failed to parse configuration line " << line << endl;
        cerr << reader.getFormattedErrorMessages() << endl;
        parsingErrorLines.push_back(line);
        return;
    }

    try {
        for (int i = 0; i < eventColumnsConfig.size(); ++i) {
            switch (eventColumnsConfig[i].dataType)
            {
                case DataType::Integer: {
                    break;
                }
                case DataType::String: {
                    string value = root.get(eventColumnsConfig[i].colName, "").toStyledString();

                    if (value.size() > maxLengthOfEachColumn[i]) {
                        maxLengthOfEachColumn[i] = value.size();
                    }
                    break;
                }
            }
        }
    }
    catch (exception e) {
        saveErrorLines.push_back(line);
    }
}