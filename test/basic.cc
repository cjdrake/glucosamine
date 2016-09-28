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


class BasicTest : public GlucosamineTest {};


using Glucose::Lit;
using Glucose::Solver;
using Glucose::lbool;  // l_False, l_True
using Glucose::mkLit;
using Glucose::vec;


TEST_F(BasicTest, Majority)
{
    Solver solver;

    // x0, x1, x2
    for (size_t i = 0; i < 3; ++i)
        solver.newVar();

    vec<Lit> clause [3];

    // x0 + x1
    clause[0].push_back(mkLit(0));
    clause[0].push_back(mkLit(1));

    // x0 + x2
    clause[1].push_back(mkLit(0));
    clause[1].push_back(mkLit(2));

    // x1 + x2
    clause[2].push_back(mkLit(1));
    clause[2].push_back(mkLit(2));

    for (size_t i = 0; i < 3; ++i)
        solver.addClause(clause[i]);

    auto sat = solver.solve();

    int sum = 0;
    for (size_t i = 0; i < 3; ++i)
        sum += (solver.modelValue(i) == l_True);

    EXPECT_TRUE(sat) << "majority(x0, x1, x2) is SAT";
    EXPECT_GE(sum, 2) << "majority(x0, x1, x2) has >= 2 solutions";
}
