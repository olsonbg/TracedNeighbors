#include <vector>
#include <algorithm>

#include "SimpleMath.cpp"
#include "gtest/gtest.h"

TEST(distance, Zero01)
{
	double x1 = 0.0;
	double y1 = 0.0;
	double z1 = 0.0;

	double x2 = 0.0;
	double y2 = 0.0;
	double z2 = 0.0;

	double eq = 0.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::distance(x1,y1,z1,x2,y2,z2));
}

TEST(distance, Zero02)
{
	double x1 = 3.0;
	double y1 = 5.0;
	double z1 = 30.0;

	double x2 = 3.0;
	double y2 = 5.0;
	double z2 = 30.0;

	double eq = 0.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::distance(x1,y1,z1,x2,y2,z2));
}

TEST(distance, Zero03)
{
	double x1 = -3.0;
	double y1 = -5.0;
	double z1 = -30.0;

	double x2 = -3.0;
	double y2 = -5.0;
	double z2 = -30.0;

	double eq = 0.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::distance(x1,y1,z1,x2,y2,z2));
}


TEST(distance, OnXaxis)
{
	double x1 = 0.0;
	double y1 = 0.0;
	double z1 = 0.0;

	double x2 = 1.0;
	double y2 = 0.0;
	double z2 = 0.0;

	double eq = 1.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::distance(x1,y1,z1,x2,y2,z2));
}

TEST(distance, OnYaxis)
{
	double x1 = 0.0;
	double y1 = 0.0;
	double z1 = 0.0;

	double x2 = 1.0;
	double y2 = 0.0;
	double z2 = 0.0;

	double eq = 1.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::distance(x1,y1,z1,x2,y2,z2));
}

TEST(distance, OnZaxis)
{
	double x1 = 0.0;
	double y1 = 0.0;
	double z1 = 0.0;

	double x2 = 1.0;
	double y2 = 0.0;
	double z2 = 0.0;

	double eq = 1.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::distance(x1,y1,z1,x2,y2,z2));
}

TEST(distance, RightTriangle01)
{
	double x1 = 0.0;
	double y1 = 0.0;
	double z1 = 0.0;

	double x2 = 3.0;
	double y2 = 4.0;
	double z2 = 0.0;

	double eq = 5.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::distance(x1,y1,z1,x2,y2,z2));
}

TEST(distance, RightTriangle02)
{
	double x1 = -1.0;
	double y1 = -1.0;
	double z1 =  0.0;

	double x2 = 2.0;
	double y2 = 3.0;
	double z2 = 0.0;

	double eq = 5.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::distance(x1,y1,z1,x2,y2,z2));
}

TEST(distance, RightTriangle03)
{
	double x1 = 0.0;
	double y1 = 0.0;
	double z1 = 0.0;

	double x2 = 0.0;
	double y2 = 3.0;
	double z2 = 4.0;

	double eq = 5.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::distance(x1,y1,z1,x2,y2,z2));
}

TEST(distance, RightTriangle04)
{
	double x1 =  0.0;
	double y1 = -1.0;
	double z1 = -1.0;

	double x2 = 0.0;
	double y2 = 2.0;
	double z2 = 3.0;

	double eq = 5.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::distance(x1,y1,z1,x2,y2,z2));
}

TEST(distance, RightTriangle05)
{
	double x1 =  0.0;
	double y1 =  0.0;
	double z1 =  0.0;

	double x2 = 1.0;
	double y2 = sqrt(3.0);
	double z2 = 0.0;

	double eq = 2.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::distance(x1,y1,z1,x2,y2,z2));
}

TEST(average, t01)
{
	std::vector<double>v;

	v.push_back(0.0);
	v.push_back(1.0);
	double eq = 0.5;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::average(v));
}

TEST(average, t02)
{
	double a[] = { 0.0, 1.0 };
	std::vector<double>v (a, a+sizeof(a)/sizeof(double));

	double eq = 0.5;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::average(v));
}

TEST(average, t03)
{
	double a[] = { 0.0, 1.0, 2.0 };
	std::vector<double>v (a, a+sizeof(a)/sizeof(double));

	double eq = 1.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::average(v));
}

TEST(average, t04)
{
	double a[] = { 0.0, 1.0, -1.0 };
	std::vector<double>v (a, a+sizeof(a)/sizeof(double));

	double eq = 0.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::average(v));
}

TEST(sum, t01)
{
	double a[] = { 0.0, 1.0, 2.0 };
	std::vector<double>v (a, a+sizeof(a)/sizeof(double));
	double eq = 3.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::Sum(v));
}

TEST(sum, t02)
{
	double a[] = { 0.0, 1.0, 2.0, -1.0, 3.0, 6.0 };
	std::vector<double>v (a, a+sizeof(a)/sizeof(double));
	double eq = 11.0;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::Sum(v));
}

TEST(SSQ,t01)
{
	double a[] = { 0.0, 2.0, 3.0, 4.0, 5.0 };
	std::vector<double>v (a, a+sizeof(a)/sizeof(double));
	double avg = 2.8;
	double eq = 14.8;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::SumSquaredDifferences(v));
	EXPECT_DOUBLE_EQ(eq, SimpleMath::SumSquaredDifferences(v, avg));
}

TEST(StandardDeviation,t01)
{
	double a[] = { 0.0, 2.0, 3.0, 4.0, 5.0 };
	std::vector<double>v (a, a+sizeof(a)/sizeof(double));
	double avg = 2.8;
	double eq = 1.9235384061671346;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::stddev(v));
	EXPECT_DOUBLE_EQ(eq, SimpleMath::stddev(v, avg));
}

TEST(StandardDeviation,t02)
{
	double a[] = { -1.0, -2.3, 3.4, 34.2, 40.0, -23.3, 0.009 };
	std::vector<double>v (a, a+sizeof(a)/sizeof(double));
	double avg = 7.287;
	double eq = 22.206145913537839;

	EXPECT_DOUBLE_EQ(eq, SimpleMath::stddev(v));
	EXPECT_DOUBLE_EQ(eq, SimpleMath::stddev(v, avg));
}
