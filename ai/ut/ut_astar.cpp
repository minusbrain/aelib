#include <aelib/ai/astar.h>
#include "gtest/gtest.h"
#include <cmath>

//#define DEBUG_FLAG

typedef std::pair<uint32_t, uint32_t> TestNode;

class TestWorld: public ::testing::Test, public ae::IPathfindWorld<TestNode> {
public:
	static const uint32_t WORLDSIZE = 10;
	static const uint32_t SIMPLE_TRAVELCOST = 100;
	static const uint32_t DIAGONAL_TRAVELCOST = 141;
	

	template <size_t ROW, size_t COL>
	using Array2dBool = std::array<std::array<bool, COL>, ROW>;

	TestWorld(): _world{true} {}

	/* Empty world, all squares walkable
	O----------O
	|          |
	|          |
	|          |
	|          |
	|          |
	|          |
	|          |
	|          |
	|          |
	|          |
	O----------O
	*/
	void setWorldEmpty() {
		for(uint32_t r = 0;r < WORLDSIZE; ++r) {
			for(uint32_t c = 0;c < WORLDSIZE; ++c) {
				_world[r][c] = true;
			}
		}
	}

	/* vertical barrier in the middle
	O----------O
	|          |
	|     x    |
	|     x    |
	|     x    |
	|     x    |
	|     x    |
	|     x    |
	|     x    |
	|     x    |
	|          |
	O----------O
	*/
	void setWorldBarrier() {
		for(uint32_t r = 0;r < WORLDSIZE; ++r) {
			for(uint32_t c = 0;c < WORLDSIZE; ++c) {
				if(c == 5 && r != 0 && r != 9) {
					_world[r][c] = false;
				} 
				else {
					_world[r][c] = true;
				}
			}
		}
	}

	/* cross
	O----------O
	|          |
	|     x    |
	|     x    |
	|     x    |
	|     x    |
	| xxxxxxxx |
	|     x    |
	|     x    |
	|     x    |
	|          |
	O----------O
	*/
	void setWorldCross() {
		for(uint32_t r = 0;r < WORLDSIZE; ++r) {
			for(uint32_t c = 0;c < WORLDSIZE; ++c) {
				if((c == 5 && r != 0 && r != 9) || (r == 5 && c != 0 && c != 9)){
					_world[r][c] = false;
				} 
				else {
					_world[r][c] = true;
				}
			}
		}
	}

	virtual std::vector<std::pair<TestNode, uint32_t>> getDirectNeigboursAndCosts(TestNode node) {
		std::vector<std::pair<TestNode, uint32_t>> neigbourList{};

		for(int32_t row = (int32_t)node.first - 1; row <= (int32_t)node.first + 1; ++row) {
			for(int32_t col = (int32_t)node.second - 1; col <= (int32_t)node.second + 1; ++col) {
				if(row >= 0 && row < (int32_t)WORLDSIZE && col >= 0 && col < (int32_t)WORLDSIZE) {
					if(_world[row][col] == false)
						continue;
					uint32_t cost = SIMPLE_TRAVELCOST;
					if(row != (int32_t)node.first && col != (int32_t)node.second) {
						cost = DIAGONAL_TRAVELCOST;
					}
					neigbourList.push_back(std::pair<TestNode, uint32_t>{{row, col}, cost});
				}
			}
		}

		return neigbourList;
	}

	virtual uint32_t getEstimatedCost(TestNode node1, TestNode node2) {
		return std::round(std::sqrt(
			std::pow(static_cast<float>(node1.first) - node2.first, 2.0) + 
			std::pow(static_cast<float>(node1.second) - node2.second, 2.0)) * SIMPLE_TRAVELCOST);
	}


private:
	Array2dBool<WORLDSIZE, WORLDSIZE> _world;
};

TEST_F(TestWorld, Meta_EstimatedCostFunction_Diagonal){
	EXPECT_EQ(getEstimatedCost({1, 1}, {8,8}), 990); // sqrt((7*7)+(7*7)) * 100
}

TEST_F(TestWorld, Meta_EstimatedCostFunction_Straight){
	EXPECT_EQ(getEstimatedCost({1, 1}, {1,8}), 700); // sqrt((7*7)+(0)) * 100
}

	/* Scenario
	O----------O
	|          |
	| S        |
	|  \       |
	|   \      |
	|    \     |
	|     \    |
	|      \   |
	|       \  |
	|        D |
	|          |
	O----------O
	Horizontal or vertical cost is 100
	Diagonal cost is 141
	Expect Length to be 987 (7 * 141)
	*/
TEST_F(TestWorld, EmptyWorld_SimpleAtoBDiagonal_CorrectCost)
{
	setWorldEmpty();

	ae::Path<TestNode> path = ae::Pathfinder<TestNode>::findPath(this, {1, 1}, {8,8});

#ifdef DEBUG_FLAG
	auto it = path.cbegin();
	while(it != path.cend()) {
		if(it != path.cbegin()) {
			std::cout << " -> ";
		}
		std::cout << "(" << it->first << " | " << it->second << ")";
		++it;
	}
	std::cout << std::endl;
#endif

	EXPECT_EQ(path.getCost(), 987);
}

	/* Scenario
	O----------O
	|S--------D|
	|          |
	|          |
	|          |
	|          |
	|          |
	|          |
	|          |
	|          |
	|          |
	O----------O
	Horizontal or vertical cost is 100
	Diagonal cost is 141
	Expect Length to be 900 (9 * 100)
	*/
TEST_F(TestWorld, EmptyWorld_SimpleAtoBStraight_CorrectCost)
{
	setWorldEmpty();

	ae::Path<TestNode> path = ae::Pathfinder<TestNode>::findPath(this, {0, 0}, {0,9});

#ifdef DEBUG_FLAG
	auto it = path.cbegin();
	while(it != path.cend()) {
		if(it != path.cbegin()) {
			std::cout << " -> ";
		}
		std::cout << "(" << it->first << " | " << it->second << ")";
		++it;
	}
	std::cout << std::endl;
#endif

	EXPECT_EQ(path.getCost(), 900);
}

	/* Scenario
	O----------O
	|     ---\ |
	|    /x   D|
	|    |x    |
	|   / x    |
	|  /  x    |
	| /   x    |
	|S    x    |
	|     x    |
	|     x    |
	|          |
	O----------O
	Horizontal or vertical cost is 100
	Diagonal cost is 141
	Expect Length to be 1246 (6 * 141 + 100)
	*/
TEST_F(TestWorld, BarrierWorld_AtoB_CorrectCost)
{
	setWorldBarrier();

	ae::Path<TestNode> path = ae::Pathfinder<TestNode>::findPath(this, {6, 0}, {1, 9});

#ifdef DEBUG_FLAG
	auto it = path.cbegin();
	while(it != path.cend()) {
		if(it != path.cbegin()) {
			std::cout << " -> ";
		}
		std::cout << "(" << it->first << " | " << it->second << ")";
		++it;
	}
	std::cout << std::endl;
#endif

	EXPECT_EQ(path.getCost(), 1246);
}

	/* Scenario
	O----------O
	|     .    |
	|    |x\   |
	|    |x \  |
	|    |x  \ |
	|    Sx   ||
	| xxxxxxxx/|
	|     xD-- |
	|     x    |
	|     x    |
	|          |
	O----------O
	Horizontal or vertical cost is 100
	Diagonal cost is 141
	Expect Length to be 1446 (6 * 141 + 6 * 100)
	*/
TEST_F(TestWorld, CrossWorld_AtoB_CorrectCost)
{
	setWorldCross();
	ae::Path<TestNode> path = ae::Pathfinder<TestNode>::findPath(this, {4, 4}, {6, 6});

#ifdef DEBUG_FLAG
	auto it = path.cbegin();
	while(it != path.cend()) {
		if(it != path.cbegin()) {
			std::cout << " -> ";
		}
		std::cout << "(" << it->first << " | " << it->second << ")";
		++it;
	}
	std::cout << std::endl;
#endif

	EXPECT_EQ(path.getCost(), 1446);
}