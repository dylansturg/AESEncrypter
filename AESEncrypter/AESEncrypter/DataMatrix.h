#pragma once

#include "stdafx.h"

class DataMatrix{
public:
	vector<unsigned char> matrix;

	DataMatrix(vector<unsigned char>);

	void AddRoundKey(vector<unsigned char>);
	void ByteSubTransform();
	void ShiftRowTransform();
	void MixColumnTransform();

	string BinaryDump();

private:


	
};