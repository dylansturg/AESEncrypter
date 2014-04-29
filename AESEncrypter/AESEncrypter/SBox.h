#pragma once

class SBox
{
public:
	SBox();

	unsigned char ConvertByte(unsigned char);

private:
	static vector<unsigned char> lookupTable;

	static void initializeBox();

};