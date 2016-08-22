//
// Created by iskakoff on 22/07/16.
//

#include "gtest/gtest.h"

#include "SzSymmetry.h"


TEST(SzSymmetryTest, Combinatorics) {
  EDParams p;
  SzSymmetry sym(p);
  sym.init();

  ASSERT_EQ(sym.comb().c_n_k(3, 2), 3);
}


TEST(SzSymmetryTest, States) {
  EDParams p;
  SzSymmetry sym(p);
  sym.init();
}