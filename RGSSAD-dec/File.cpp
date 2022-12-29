//  SPDX-FileCopyrightText: 2023 Victor Shilin <chrono.monochrome@gmail.com>
//  SPDX-License-Identifier: MIT

#include <File.hpp>
#include <decryptor.hpp>

namespace rgssad {

using namespace std;

namespace fs = std::filesystem;

File::File(string rgssadFileName, string fileName, uint32_t iSize, uint32_t iOffset, uint32_t iKey) :
	mRgssadFileName(rgssadFileName),
	mFileName(fileName),
	mSize(iSize),
	mOffset(iOffset),
	mKey(iKey)
{
	mIfs.open(rgssadFileName, ifstream::binary);
	if (!mIfs.is_open())
		panic("failed to open file {}", rgssadFileName);
}

File::~File()
{
	mIfs.close();
}

void File::extract(string targetDir)
{
	if (targetDir == "") {
		std::replace(mRgssadFileName.begin(), mRgssadFileName.end(), '\\', '/');
		targetDir = fs::path(mRgssadFileName).remove_filename().string();
	}

	std::replace(targetDir.begin(), targetDir.end(), '\\', '/');

	fs::path fullpath(targetDir);
	fullpath /= mFileName;

	string tmpPath(fullpath.string());
	std::replace(tmpPath.begin(), tmpPath.end(), '\\', '/');
	fullpath = tmpPath;

	fs::path targetDirPath(fullpath);
	targetDirPath.remove_filename();
	fs::create_directories(targetDirPath);

#ifdef DEBUG
	println("{}: mSize = ", fullpath.c_str(), mSize);
#endif

	fstream file;
	decrypt();
	file.open(fullpath.c_str(), ios::out | ios::binary | ios::trunc);

	file.write(reinterpret_cast<const char*>(mBuffer.data()), mSize);
	file.close();
}

void File::decrypt()
{
	mBuffer.reserve(mSize);
#ifdef VERBOSE_DEBUG
	println("reading {} bytes from offset {}", mSize, mOffset);
#endif
	mIfs.seekg(mOffset, ios_base::beg);
	mIfs.read(reinterpret_cast<char*>(&mBuffer[0]), mSize);

	int j = 0;
	int i = 0;
	

	for (; i < mSize; i++, j++)
	{
		if (j == 4) {
			j = 0;
			mKey = nextIKey(mKey);
		}
#ifdef VERBOSE_DEBUG
		println("{} ^ {} = {}", int(mBuffer[i]), (mKey >> (j * 8)) & 0xff, mBuffer[i] ^ ((mKey >> (j * 8)) & 0xff) & 0xff);
#endif
		mBuffer[i] = mBuffer[i] ^ ((mKey >> (j * 8)) & 0xff) & 0xff;
	}
}

}