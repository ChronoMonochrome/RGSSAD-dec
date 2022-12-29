#include <BinaryReader.hpp>

namespace rgssad {
	
using namespace std;

BinaryReader::BinaryReader(string fileName)
{
	mIfs.open(fileName, ifstream::binary);
	if (mIfs.is_open())
	{
		mIfs.seekg(0, ios_base::end);
		mFileSize = mIfs.tellg();
		mIfs.seekg(0, ios_base::beg);
	}
	//cout << "file" << fileName << " is ok: " << mFileSize << " bytes" << endl;
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

char *BinaryReader::read(size_t length)
{
	mBuffer.reserve(length);
	mIfs.read(&mBuffer[0], length);
	return mBuffer.data();
}

void BinaryReader::seek(streamoff off)
{
	mIfs.seekg(off, ios_base::beg);
}

streamoff BinaryReader::tell()
{
	return mIfs.tellg();
}

}