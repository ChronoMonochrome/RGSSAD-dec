//  SPDX-FileCopyrightText: 2023 Victor Shilin <chrono.monochrome@gmail.com>
//  SPDX-License-Identifier: MIT

#include <iostream>
#include <BinaryReader.hpp>
#include <decryptor.hpp>

using namespace std;

int main(int argc, char *argv[])
{
	uint32_t iKey = 0xdeadcafe;

	if (argc < 2)
		panic("Usage: RGSSAD-dec file.rgssad [targetDirectory]");

	rgssad::ReadRGSSADV1(argv[1], argc == 3 ? argv[2] : "", &iKey, -1);
	return 0;
}