**Assumptions**

**Input Format:**

Timestamp will come in an ascending sorted order.
Log Type can be any UTF-8 supported string with a maximum length of 100.
Severity will be a positive non-zero floating-point number with no limit.
Precision: Severity results must be calculated with a precision of 10^-6.

Performance: The program should be fast enough to handle all functionalities efficiently.

#Explanation :
**Data Structures:**

struct LogEntry: Represents a log entry with timestamp, logType, and severity.
vector<LogEntry> logs: Stores all log entries.
map<string, vector<double>> logTypeMap: Maps each log type to a vector of severities.
Functions:

addLogEntry: Adds a new log entry to the data structures.
computeStats: Computes and outputs the min, max, and mean of a vector of severities.
computeLogTypeStats: Computes stats for a specified log type.
computeTimestampStats: Computes stats for all entries before or after a specified timestamp.
computeTimestampLogTypeStats: Computes stats for a specified log type before or after a specified timestamp.

**Main Function:**

Reads commands from input.txt.
Processes each command and performs the corresponding operation.
Writes results to output.txt.
Input and Output Files
input.txt: Contains the commands to be executed by the program.
output.txt: The program writes the results of the operations to this file.
