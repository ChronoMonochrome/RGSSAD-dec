//  SPDX-FileCopyrightText: 2023 Victor Shilin <chrono.monochrome@gmail.com>
//  SPDX-License-Identifier: MIT

#include <BinaryReader.hpp>

namespace rgssad {

using namespace std;

BinaryReader::BinaryReader(string fileName)
{
	mIfs.open(fileName, ifstream::binary);
	if (mIfs.is_open())
	{
		mIfs.seekg(0, ios_base::end);
		mBinSize = mIfs.tellg();
		mIfs.seekg(0, ios_base::beg);
	}
	cout << "file " << fileName << " opened ok: " << mBinSize << " bytes" << endl;
}

BinaryReader::~BinaryReader()
{
	mIfs.close();
}

uint32_t BinaryReader::readUint32()
{
	uint32_t buf;
	mIfs.read(reinterpret_cast<char *>(&buf), sizeof(uint32_t));

	return buf;
}

void BinaryReader::read(vector<char> &buffer, size_t length)
{
	buffer.reserve(length);
	mIfs.read(&buffer[0], length);
}

void BinaryReader::seek(streamoff off, ios_base::seekdir way)
{
	mIfs.seekg(off, way);
}

streamoff BinaryReader::tell()
{
	return mIfs.tellg();
}

int BinaryReader::eof()
{
	return mIfs.eof();
}

}