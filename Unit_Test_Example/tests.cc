#include <gtest/gtest.h>
#include <vector>
#include "Quadratic.cc"

TEST(Quadratic, simpletest){
	std::vector<double>roots;
	roots = quadraticroot(1, 0, 0);
	ASSERT_EQ (0.0, roots[0]);
}

TEST(Quadratic, ManyTests){
	std::vector<double>roots;
	roots = quadraticroot(1, 1, -4);
	ASSERT_NEAR (1.56155281281, roots[0], 1e-10);
	ASSERT_NEAR (-2.56155281281, roots[1], 1e-10);
	roots = quadraticroot(1, -3, -4);
	ASSERT_EQ (4, roots[0]);
	ASSERT_EQ (-1, roots[1]);
	roots = quadraticroot(1, 0, -4);
	ASSERT_EQ (2, roots[0]);
	ASSERT_EQ (-2, roots[1]);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}