//  SPDX-FileCopyrightText: 2023 Victor Shilin <chrono.monochrome@gmail.com>
//  SPDX-License-Identifier: MIT

#pragma once

#include <filesystem>
#include "helpers.hpp"

namespace rgssad {

using namespace std;

class File {
public:
	File(string rgssadFileName, string fileName, uint32_t iSize, uint32_t iOffset, uint32_t iKey);
	~File();
	void extract(string targetDir);
	void decrypt();
private:
	vector <uint8_t> mBuffer;
	string mRgssadFileName;
	string mFileName;
	ifstream mIfs;
	uint32_t mSize;
	uint32_t mOffset;
	uint32_t mKey;
};

}