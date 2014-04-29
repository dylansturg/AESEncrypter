#include "stdafx.h"
#include "AESParser.h"

#include <fstream>

AESParser::AESParser()
{

}

pair<Key, vector<DataMatrix>> AESParser::ParseInFile(string filename)
{
	vector<DataMatrix> messages;

	ifstream file(filename, ios::in);

	if (!file.is_open())
	{
		fprintf(stderr, "Unable to open file: %s\n", filename.c_str());
		throw invalid_argument("Unable to open file: " + filename);
	}

	string keyLine;
	getline(file, keyLine);

	vector<unsigned char> keyValue = ParseBinString(keyLine);

	Key resultKey(keyValue);

	while (!file.eof())
	{
		string messageLine;
		getline(file, messageLine);

		messages.push_back(DataMatrix(ParseBinString(messageLine)));
	}

	file.close();

	return pair<Key, vector<DataMatrix>>(resultKey, messages);
}

vector<unsigned char> AESParser::ParseBinString(string binary)
{
	vector<unsigned char> parsed;
	for (int i = 0; i < binary.length(); i += 8)
	{
		parsed.push_back(ParseByte(binary.substr(i, 8)));
	}
	return parsed;
}

unsigned char AESParser::ParseByte(string byteBinary)
{
	unsigned char result = 0;
	for (int i = byteBinary.length() - 1; i >= 0; i--)
	{
		char digit[2];
		digit[0] = byteBinary.c_str()[i];
		digit[1] = 0;
		result += atoi(digit) * pow(2, 7 - i);
	}
	return result;
	
}