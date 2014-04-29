#pragma once

class Key{
public:
	Key();
	Key(vector<unsigned char>);

	vector<unsigned char> GetRoundKey(int);

	vector<unsigned char> matrix;

private:
	
	vector<unsigned char> extendedKey;

	void CalculateExtendedKey();

	vector<unsigned char> GetColumn(int);
	void SetColumn(vector<unsigned char>, int);

};