#include "stdafx.h"

#include "Encrypter.h"

Encrypter::Encrypter(Key encryptKey, vector<DataMatrix> messages, int encryptCount)
{
	this->encryptionKey = encryptionKey;
	this->messages = messages;
	this->encryptCount = encryptCount;
}

DataMatrix Encrypter::EncryptMessage(int messageId)
{
	DataMatrix cipherText = this->messages[messageId];

	for (int i = 0; i < this->encryptCount; i++)
	{
		cipherText = PerformAES(cipherText);
	}

	return cipherText;
}

DataMatrix Encrypter::PerformAES(DataMatrix message)
{
	/*
		1. ARK with initial key
		2. Nine rounds of BS, SR, MC, ARK, using round keys 1 through 9
		3. Last round: BS, SR, ARK, using 10th round key
	*/
	message.AddRoundKey(this->encryptionKey.GetRoundKey(0));

	for (int i = 0; i <= 9; i++)
	{
		message.ByteSubTransform();
		message.ShiftRowTransform();
		message.MixColumnTransform();
		message.AddRoundKey(this->encryptionKey.GetRoundKey(i));
	}

	message.ByteSubTransform();
	message.ShiftRowTransform();
	message.AddRoundKey(this->encryptionKey.GetRoundKey(10));

	return message;
}