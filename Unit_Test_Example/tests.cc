#include <gtest/gtest.h>
#include <vector>
#include "Quadratic.cc"

TEST(Quadratic, simpletest){
	std::vector<double>roots;
	roots = quadraticroot(1, 0, 0);
	ASSERT_EQ (roots[0], 0.0);
}

TEST(Quadratic, ManyTests){
	std::vector<double>roots;
	roots = quadraticroot(1, 1, -4);
	ASSERT_NEAR (roots[0],1.56155281281, 1e-10);
	ASSERT_NEAR (roots[1],-2.56155281281, 1e-10);
	roots = quadraticroot(1, -3, -4);
	ASSERT_EQ (roots[0],4);
	ASSERT_EQ (roots[1],-1);
	roots = quadraticroot(1, 0, -4);
	ASSERT_EQ (roots[0],2);
	ASSERT_EQ (roots[1],-2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}