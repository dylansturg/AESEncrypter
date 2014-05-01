#pragma once

#include "stdafx.h"

#include "Key.h"
#include "DataMatrix.h"

class Encrypter{
public:
	Encrypter(Key&, vector<DataMatrix> &, int);

	DataMatrix EncryptMessage(int);

private:
	int encryptCount;
	Key encryptionKey;
	vector<DataMatrix> messages;

	DataMatrix PerformAES(DataMatrix);
};