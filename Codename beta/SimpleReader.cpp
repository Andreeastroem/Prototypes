//SimpleReader.cpp

#include "stdafx.h"

#include "SimpleReader.h"

//Essential functions

void SimpleReader::Initialise(const std::string &directory)
{
	m_Directory = directory;

	m_bInitialised = true;
}

bool SimpleReader::ReadFile(const std::string &label)
{
	if (m_bInitialised)
	{
		//Stream that reads through the file
		std::ifstream stream;

		//Open the stream
		stream.open(m_Directory + label);

		//Validation if the stream was able to open the file
		if (!stream.is_open())
		{
			Debug::LogError("File does not exists. Filename: " + m_Directory + label);
			return false;
		}

		//A dynamic array to store all the lines in the file
		std::vector<std::string>FileLines;

		//Segment the files content into seperate lines
		if (stream.is_open())
		{
			while (!stream.eof())
			{
				std::string Line;
				std::getline(stream, Line, '\n');
				FileLines.push_back(Line);
			}
			//If there were no lines, then just skip
			if (FileLines.size() < 1)
			{
				Debug::LogError("File was empty, found no lines. Filename: " + m_Directory + label);
				return false;
			}

			//Clear the vector of any empty lines
			DeleteEmptyLines(FileLines);

			m_Lines = FileLines;
		}

		return true;
	}
	else
	{
		Debug::LogError("The simple reader has not been initialised yet. \nSet the directory before you read a file.");
		return false;
	}
}

//Access functions

void SimpleReader::SetDirectory(const std::string &directory)
{
	m_Directory = directory;

	m_bInitialised = true;
}


//Member functions

void SimpleReader::DeleteEmptyLines(std::vector<std::string> &lines)
{
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		if (lines[i].length() == 0)
		{
			lines.erase(lines.begin() + i);
		}
	}
}

inline void SimpleReader::DeleteSpaces(std::string &line)
{
	line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
}

inline void SimpleReader::DeleteComment(std::string &line)
{
	//look for commentsign
	std::size_t commentsign = line.find('#');
	line.erase(commentsign);
}

std::string SimpleReader::CheckPreviousLine(int i)
{
	std::size_t positionInString;

	//Validation check if it is a legitimate line (0 being the first possible line)
	if (i >= 0)
	{
		if (m_Lines[i].length() == 0)
		{
			//If the line is empty we continue looking backwards
			std::string a = CheckPreviousLine(i - 1);
			
			return a;
		}
		else
		{
			//Look for the closing body sign
			positionInString = m_Lines[i].find(']');

			//If the position has reached the end of the string the closing body sign was not found
			//and we can use the entirety of the line as name (without spaces)
			if (positionInString == m_Lines[i].npos)
			{
				return m_Lines[i];
			}
			else
			{
				return m_Lines[i].substr(positionInString);
			}
		}
	}
	else
	{
		Debug::LogError("End of file.");
		return "";
	}
}

void SimpleReader::ProcessFile()
{
	bool BodyFound = false;
	bool VariableStatementFound = false;

	std::size_t positionInString;

	for (int i = 0; i < m_Lines.size(); i++)
	{
		//A temporary variable
		std::string temporaryString;
		std::string temporaryNameString;

		//Clear the line from any comment
		DeleteComment(m_Lines[i]);

		//Find body
		if (!BodyFound)
		{
			DeleteSpaces(m_Lines[i]);
			//Find the body opener
			positionInString = m_Lines[i].find('[');
			
			//Body name is the sequence of characters before '[' sign
			if (positionInString != std::string::npos)
			{
				BodyFound = true;

				//If the positionstring is at a position greater than zero, 
				//the characters before it will be interpreted as the name
				if (positionInString > 0)
				{
					temporaryNameString = m_Lines[i].substr(0, positionInString);
				}
				//Otherwise it will check the line before it
				else if (i > 0)
				{
					temporaryNameString = CheckPreviousLine(i - 1);
					DeleteSpaces(temporaryNameString);
				}
			}
			else
			{

			}

		}
		if (BodyFound)
		{
			m_Lines[i].find(']');
		}
	}
}