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
using Glucose::lbool;
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
    clause[0].push(mkLit(0, true));
    clause[0].push(mkLit(1, true));

    // x0 + x2
    clause[1].push(mkLit(0, true));
    clause[1].push(mkLit(2, true));

    // x1 + x2
    clause[2].push(mkLit(1, true));
    clause[2].push(mkLit(2, true));

    for (size_t i = 0; i < 3; ++i)
        solver.addClause(clause[i]);

    auto sat = solver.solve();

    EXPECT_TRUE(sat);
}
