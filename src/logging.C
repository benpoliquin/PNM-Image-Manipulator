 #include <cstring>
 #include "logging.h"

FILE* Logger::logger = fopen("logfile.txt", "w");

void Logger::LogEvent(const char *event)
{

	fwrite(event, sizeof(char), strlen(event), logger);
}

void Logger::Finalize()
{
	fclose(logger);
}

DataFlowException::DataFlowException(const char *type, const char *error)
{
	sprintf(msg, "Throwing exception: (%s), %s ", type, error);
	Logger::LogEvent(msg);	
}