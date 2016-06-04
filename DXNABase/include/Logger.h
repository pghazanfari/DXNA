#include <fstream>
#include <string>
#include <string.h>
#pragma once

using namespace std;

class Logger
{
	static string outputFile;
	static ofstream file;

	private:
		inline Logger() {}
		inline Logger(const Logger& logger) {}

	public:
		static inline void Initialize()
		{
			file.open(outputFile);
		}

		static inline void SetLogFile(string filename)
		{
			outputFile = filename;
			file.close();
			file.open(filename);
		}

		static inline void Log(string txt)
		{
			file << txt.c_str();
		}

		static inline void LogLine(string txt)
		{
			file << txt.c_str() << "\n";
		}

		static inline void LogLine()
		{
			file << "\n";
		}

		static inline void Flush()
		{
			file.flush();
		}

		static inline void Close()
		{
			file.flush();
			file.close();
		}
};