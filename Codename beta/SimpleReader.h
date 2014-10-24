//SimpleReader.h

/*
Simple reader is file reader that translates the text to in game info
for example create arrays and fill them with values

Author: André Åström [Kjof]
*/

#pragma once

class SimpleReader
{
public:
	//Essential functions
	void Initialise(const std::string &directory);
	bool ReadFile(const std::string &label);

	//Access functions
	void SetDirectory(const std::string &directory);

	//Check if Intialise() have been called or not
	bool m_bInitialised = false;

private:
	//Member functions
	void DeleteEmptyLines(std::vector<std::string> &lines);
	inline void DeleteSpaces(std::string &line);
	inline void DeleteComment(std::string &line);
	
	std::string CheckPreviousLine(int i);

	void ProcessFile();

	//A temporary deposit for files, which are read through and passed in as indepent lines
	std::vector<std::string> m_Lines;

	//A map of all the bodies that have been read through
	//Name of the body as key, then its own lines
	std::map<std::string, std::map<std::string, std::string>> m_Bodies;

	//The directory that files are read from
	std::string m_Directory;
};