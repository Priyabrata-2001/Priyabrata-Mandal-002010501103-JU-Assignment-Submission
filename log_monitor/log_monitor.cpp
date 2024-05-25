#include <bits/stdc++.h>

using namespace std;

struct LogEntry
{
    uint64_t timestamp;
    string logType;
    double severity;
};

vector<LogEntry> logs;
map<string, vector<double>> logTypeMap;

void addLogEntry(uint64_t timestamp, const string &logType, double severity)
{
    LogEntry entry = {timestamp, logType, severity};
    logs.push_back(entry);
    logTypeMap[logType].push_back(severity);
}

void computeStats(const vector<double> &severities, ofstream &outputFile)
{
    if (severities.empty())
    {
        outputFile << "Min: 0.0, Max: 0.0, Mean: 0.0\n";
        return;
    }

    double minSeverity = numeric_limits<double>::max();
    double maxSeverity = numeric_limits<double>::lowest();
    double sumSeverity = 0.0;

    for (double severity : severities)
    {
        if (severity < minSeverity)
            minSeverity = severity;
        if (severity > maxSeverity)
            maxSeverity = severity;
        sumSeverity += severity;
    }

    double meanSeverity = sumSeverity / severities.size();
    outputFile << "Min: " << fixed << setprecision(6) << minSeverity
               << ", Max: " << fixed << setprecision(6) << maxSeverity
               << ", Mean: " << fixed << setprecision(6) << meanSeverity << '\n';
}

void computeLogTypeStats(const string &logType, ofstream &outputFile)
{
    if (logTypeMap.find(logType) != logTypeMap.end())
    {
        computeStats(logTypeMap[logType], outputFile);
    }
    else
    {
        outputFile << "Min: 0.0, Max: 0.0, Mean: 0.0\n";
    }
}

void computeTimestampStats(uint64_t timestamp, bool isBefore, ofstream &outputFile)
{
    vector<double> severities;

    for (const LogEntry &entry : logs)
    {
        if ((isBefore && entry.timestamp < timestamp) || (!isBefore && entry.timestamp > timestamp))
        {
            severities.push_back(entry.severity);
        }
    }

    computeStats(severities, outputFile);
}

void computeTimestampLogTypeStats(uint64_t timestamp, const string &logType, bool isBefore, ofstream &outputFile)
{
    vector<double> severities;

    for (const LogEntry &entry : logs)
    {
        if (entry.logType == logType &&
            ((isBefore && entry.timestamp < timestamp) || (!isBefore && entry.timestamp > timestamp)))
        {
            severities.push_back(entry.severity);
        }
    }

    computeStats(severities, outputFile);
}

int main()
{
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open())
    {
        cerr << "Error opening input file" << endl;
        return 1;
    }
    if (!outputFile.is_open())
    {
        cerr << "Error opening output file" << endl;
        return 1;
    }

    string command;
    while (getline(inputFile, command))
    {
        if (command[0] == '1')
        {
            // Parse "1 timestamp; log_type; severity"
            size_t pos1 = command.find(';', 2);
            size_t pos2 = command.find(';', pos1 + 1);

            uint64_t timestamp = stoull(command.substr(2, pos1 - 2));
            string logType = command.substr(pos1 + 2, pos2 - pos1 - 2);
            double severity = stod(command.substr(pos2 + 2));

            addLogEntry(timestamp, logType, severity);
        }
        else if (command[0] == '2')
        {
            // Parse "2 log_type"
            string logType = command.substr(2);
            computeLogTypeStats(logType, outputFile);
        }
        else if (command[0] == '3')
        {
            // Parse "3 BEFORE/AFTER timestamp"
            bool isBefore = command[2] == 'B';
            uint64_t timestamp = stoull(command.substr(isBefore ? 10 : 9));
            computeTimestampStats(timestamp, isBefore, outputFile);
        }
        else if (command[0] == '4')
        {
            // Parse "4 BEFORE/AFTER log_type timestamp"
            bool isBefore = command[2] == 'B';
            size_t firstSpace = command.find(' ', 2);
            size_t lastSpace = command.find_last_of(' ');

            string logType = command.substr(firstSpace + 1, lastSpace - firstSpace - 1);
            uint64_t timestamp = stoull(command.substr(lastSpace + 1));

            computeTimestampLogTypeStats(timestamp, logType, isBefore, outputFile);
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
