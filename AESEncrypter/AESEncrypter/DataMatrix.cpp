#include "stdafx.h"

#include "DataMatrix.h"

#include "SBox.h"

DataMatrix::DataMatrix(vector<unsigned char> values)
{
	this->matrix.insert(this->matrix.begin(), values.begin(), values.end());
}

void DataMatrix::AddRoundKey(vector<unsigned char> roundKey)
{
#ifdef DEBUG_LOGGING
	Logger::LogEntry("Iniated ARK", BinaryDump());
#endif
	for (int i = 0; i < 16; i++)
	{
		this->matrix[i] ^= roundKey[i];
	}
#ifdef DEBUG_LOGGING
	Logger::LogEntry("Finished ARK", BinaryDump());
#endif
}

void DataMatrix::ByteSubTransform()
{
#ifdef DEBUG_LOGGING
	Logger::LogEntry("Iniating BS", BinaryDump());
#endif

	SBox converter;

	for (int i = 0; i < this->matrix.size(); i++)
	{
		this->matrix[i] = converter.ConvertByte(this->matrix[i]);
	}
#ifdef DEBUG_LOGGING
	Logger::LogEntry("Finished BS", BinaryDump());
#endif
}

void DataMatrix::ShiftRowTransform()
{
#ifdef DEBUG_LOGGING
	Logger::LogEntry("Iniating SR", BinaryDump());
#endif

	// Opted to just hard code the swaps, because it would be faster than an elegant solution

	// Row 1 : 4 through 7
	vector<unsigned char> row;
	row.insert(row.begin(), &(this->matrix[4]), &(this->matrix[7]));

	this->matrix[4] = row[1];
	this->matrix[5] = row[2];
	this->matrix[6] = row[3];
	this->matrix[7] = row[0];

	// Row 2 : 8 through 11
	row.clear();
	row.insert(row.begin(), &(this->matrix[8]), &(this->matrix[11]));

	this->matrix[8] = row[2];
	this->matrix[9] = row[3];
	this->matrix[10] = row[0];
	this->matrix[11] = row[1];

	// Row 3 : 12 through 15
	row.clear();
	row.insert(row.begin(), &(this->matrix[12]), &(this->matrix[15]));

	this->matrix[12] = row[3];
	this->matrix[13] = row[0];
	this->matrix[14] = row[1];
	this->matrix[15] = row[2];

#ifdef DEBUG_LOGGING
	Logger::LogEntry("Finished SR", BinaryDump());
#endif
}

unsigned char Multiply2(unsigned char value)
{
	return value << 1;
}

unsigned char Multiply3(unsigned char value)
{
	return (value << 1) ^ value;
}

void DataMatrix::MixColumnTransform()
{
#ifdef DEBUG_LOGGING
	Logger::LogEntry("Iniating MC", BinaryDump());
#endif

	this->matrix[0] = Multiply2(this->matrix[0]);
	this->matrix[1] = Multiply3(this->matrix[1]);

	this->matrix[5] = Multiply2(this->matrix[5]);
	this->matrix[6] = Multiply3(this->matrix[6]);

	this->matrix[10] = Multiply2(this->matrix[10]);
	this->matrix[11] = Multiply3(this->matrix[11]);

	this->matrix[12] = Multiply3(this->matrix[12]);
	this->matrix[15] = Multiply2(this->matrix[15]);

#ifdef DEBUG_LOGGING
	Logger::LogEntry("Finished MC", BinaryDump());
#endif
}

string ByteToBinary(unsigned char byte)
{
	string binary("");
	for (int i = 0; i < 8; i++)
	{
		if ((byte>>i)&0x01){
			binary.append("1");
		}
		else {
			binary.append("0");
		}
	}
	return binary;
}

string DataMatrix::BinaryDump()
{
	string binary("");

	for (int i = 0; i < this->matrix.size(); i++)
	{
		binary.append(ByteToBinary(this->matrix[i]));
	}
	return binary;
}

