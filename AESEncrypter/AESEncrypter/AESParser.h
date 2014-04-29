#pragma once

#include "stdafx.h"

#include "Key.h"
#include "DataMatrix.h"

class AESParser{
public:
	AESParser();

	pair<Key, vector<DataMatrix>> ParseInFile(string filename);

private:

	vector<unsigned char> ParseBinString(string);
	unsigned char ParseByte(string);

};