// Copyright 2016 Chris Drake
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#include <gtest/gtest.h>

#include "core/Solver.h"
#include "glucosaminetest.h"


class VecTest : public GlucosamineTest {};


using namespace Glucose;


TEST_F(VecTest, Basic)
{
    vec<int> v;

    EXPECT_EQ(v.size(), 0);

    for (int i = 0; i < 1024; ++i) {
        v.push(i);
    }

    EXPECT_EQ(v.size(), 1024);

    for (int i = 0; i < 1024; ++i) {
        v.pop();
    }

    EXPECT_EQ(v.size(), 0);
}
