#pragma once

#include "stdafx.h"

#include "Key.h"
#include "DataMatrix.h"

class AESParser{
public:
	AESParser();

	pair<Key, vector<DataMatrix>> ParseInFile(string filename);

	vector<unsigned char> ParseBinString(string);
	vector<unsigned char> ParseHexString(string);

private:


	unsigned char ParseByte(string);

};