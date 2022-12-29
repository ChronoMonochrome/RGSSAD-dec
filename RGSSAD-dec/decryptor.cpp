//  SPDX-FileCopyrightText: 2023 Victor Shilin <chrono.monochrome@gmail.com>
//  SPDX-License-Identifier: MIT

#include <decryptor.hpp>
#include <BinaryReader.hpp>
#include <File.hpp>

namespace rgssad {

static uint32_t iKeyIterCurrent = 0;

inline uint32_t getIKey(uint32_t iterCurr, uint32_t iterMax, uint32_t iKey)
{
	if (iterCurr == iterMax)
		return iKey;

	iKeyIterCurrent++;
	return getIKey(iterCurr + 1, iterMax, (iKey * 7 + 3) & 0xffffffff);
}

uint32_t nextIKey(uint32_t iKey) {
	return getIKey(iKeyIterCurrent, iKeyIterCurrent + 1, iKey);
}

inline uint32_t DecryptIntV1(uint32_t value, uint32_t iKey)
{
	return value ^ iKey;
}

void DecryptNameV1(vector<char> &dest, vector<char> &nameEncoded, size_t length, uint32_t *iKey)
{
	dest.resize(length);
	int i = 0;
	for (; i < length; i++)
	{
		dest[i] = nameEncoded[i] ^ *iKey;
#ifdef VERBOSE_DEBUG
		println("{}, iKey={:08x}", dest[i], *iKey);
#endif
		*iKey = nextIKey(*iKey);
	}
	dest[i] = 0;
}

void ReadRGSSADV1(string rgssadFilePath, string targetDir, uint32_t *iKey, int maxCount)
{
	if (maxCount < 0)
		maxCount = 10000000;

	int numFiles = 0;
	uint32_t length = 0;
	vector<char> fileNameEncBuffer;
	vector<char> fileNameDecBuffer;

	BinaryReader br(rgssadFilePath);
	br.seek(8, ios_base::beg);

	while (numFiles <= maxCount)
	{
		uint32_t tmp = br.readUint32();
		if (br.eof())
			return;

		length = DecryptIntV1(tmp, *iKey);
		*iKey = nextIKey(*iKey);
		if (length > 256)
			panic("{}: {}: filename is too long: {} bytes, ikey={:08x}, tmp={:08x}", __func__, rgssadFilePath, length, *iKey, tmp);

		br.read(fileNameEncBuffer, length);
		DecryptNameV1(fileNameDecBuffer, fileNameEncBuffer, length, iKey);

		length = DecryptIntV1(br.readUint32(), *iKey);
		*iKey = nextIKey(*iKey);

#ifdef VERBOSE_DEBUG
		println("filename {}: file size {} bytes, iKey {:08x}", fileNameDecBuffer.data(), length, *iKey);
#endif

		File myFile(rgssadFilePath, fileNameDecBuffer.data(), length, br.tell(), *iKey);
		myFile.extract(targetDir);

		br.seek(length, ios_base::cur);
		numFiles++;
		if (numFiles % 100 == 0)
			println("{} / ?", numFiles);
	}
}

}