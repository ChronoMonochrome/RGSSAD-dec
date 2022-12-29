//  SPDX-FileCopyrightText: 2023 Victor Shilin <chrono.monochrome@gmail.com>
//  SPDX-License-Identifier: MIT

#pragma once

#include "helpers.hpp"

namespace rgssad {

using namespace std;

inline uint32_t DecryptIntV1(uint32_t value, uint32_t iKey);
void ReadRGSSADV1(string rgssadFilePath, string targetDir, uint32_t *iKey, int maxCount);
uint32_t nextIKey(uint32_t iKey);

}