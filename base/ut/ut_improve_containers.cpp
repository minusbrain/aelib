#include <base/improve_containers.h>

#include "gtest/gtest.h"

TEST(EasierSorting, SortIntegerVector_ExpectEqual)
{
    std::vector<int> dut = {13, 5, 24, 1};
    std::vector<int> ref = {1, 5, 13, 24};

    base::sort(dut);

    EXPECT_EQ(ref, dut);
}

TEST(EasierSorting, SortIntegerVectorBackwards_ExpectEqual)
{
    std::vector<int> dut = {13, 5, 24, 1};
    std::vector<int> ref = {24, 13, 5, 1};

    base::sort(dut, [](int l, int r) { return l > r; });

    EXPECT_EQ(ref, dut);
}

TEST(EasierSorting, SortIntegerList_ExpectEqual)
{
    std::list<int> dut = {13, 5, 24, 1};
    std::list<int> ref = {1, 5, 13, 24};

    base::sort(dut);

    EXPECT_EQ(ref, dut);
}

TEST(EasierSorting, SortIntegerListBackwards_ExpectEqual)
{
    std::list<int> dut = {13, 5, 24, 1};
    std::list<int> ref = {24, 13, 5, 1};

    base::sort(dut, [](int l, int r) { return l > r; });

    EXPECT_EQ(ref, dut);
}

TEST(EasierSorting, SortIntegerCppArray_ExpectEqual)
{
    std::array<int, 4> dut = {13, 5, 24, 1};
    std::array<int, 4> ref = {1, 5, 13, 24};

    base::sort(dut);

    EXPECT_EQ(ref, dut);
}

TEST(EasierSorting, SortCppArrayBackwards_ExpectEqual)
{
    std::array<int, 4> dut = {13, 5, 24, 1};
    std::array<int, 4> ref = {24, 13, 5, 1};

    base::sort(dut, [](int l, int r) { return l > r; });

    EXPECT_EQ(ref, dut);
}

TEST(EasierSorting, SortIntegerPlainArray_ExpectEqual)
{
    int dut[] = {13, 5, 24, 1};
    int ref[] = {1, 5, 13, 24};

    base::sort<int, 4>(
        dut);  // Length of array is required to do a comparison of plain arrays

    EXPECT_EQ(0, memcmp(dut, ref, 4 * sizeof(int)));
}

TEST(EasierSorting, SortIntegerPlainArrayBackwards_ExpectEqual)
{
    int dut[] = {13, 5, 24, 1};
    int ref[] = {24, 13, 5, 1};

    base::sort<int, 4>(dut, [](int l, int r) { return l > r; });

    EXPECT_EQ(0, memcmp(dut, ref, 4 * sizeof(int)));
}

TEST(ContainerStreaming, StreamIntegerVector_ExpectCorrectString)
{
    std::vector<int> dut = {13, 5, 24, 1};
    std::string ref = "Vector {13, 5, 24, 1}";
    std::ostringstream os;
    os << dut;

    EXPECT_EQ(ref, os.str());
}

TEST(ContainerStreaming, StreamIntegerList_ExpectCorrectString)
{
    std::list<int> dut = {13, 5, 24, 1};
    std::string ref = "List {13, 5, 24, 1}";
    std::ostringstream os;
    os << dut;

    EXPECT_EQ(ref, os.str());
}

TEST(ContainerStreaming, StreamIntegerArray_ExpectCorrectString)
{
    std::array<int, 4> dut = {13, 5, 24, 1};
    std::string ref = "Array {13, 5, 24, 1}";
    std::ostringstream os;
    os << dut;

    EXPECT_EQ(ref, os.str());
}

TEST(ContainerStreaming, StreamIntegerToStringMap_ExpectCorrectString)
{
    std::map<int, std::string> dut = {{13, "Auto"}, {5, "Mofa"}, {24, "Bus"}};
    std::string ref = "Map {{5 -> Mofa}, {13 -> Auto}, {24 -> Bus}}";
    std::ostringstream os;
    os << dut;

    EXPECT_EQ(ref, os.str());
}

TEST(ContainerStreaming, StreamStringToVectorOfIntegerMap_ExpectCorrectString)
{
    std::map<std::string, std::vector<int>> dut = {{"Auto", {1, 2, 3, 4, 5}},
                                                   {"Mofa", {100, -3}}};
    std::string ref =
        "Map {{Auto -> Vector {1, 2, 3, 4, 5}}, {Mofa -> Vector {100, -3}}}";
    std::ostringstream os;
    os << dut;

    EXPECT_EQ(ref, os.str());
}

class MyType
{
   public:
    MyType(int x, std::string bla) : _x(x), _bla(bla) {}
    ~MyType() = default;

    int getX() const { return _x; }
    std::string getBla() const { return _bla; }

   private:
    int _x;
    std::string _bla;
};

std::ostream& operator<<(std::ostream& os, const MyType& mytype)
{
    os << "MyType {" << mytype.getX() << ", " << mytype.getBla() << "}";
    return os;
}

TEST(ContainerStreaming, StreamUserTypeVector_ExpectCorrectString)
{
    std::vector<MyType> dut = {{13, "Auto"}, {5, "Mofa"}, {24, "Bus"}};
    std::string ref = "Vector {MyType {13, Auto}, MyType {5, Mofa}, MyType {24, Bus}}";
    std::ostringstream os;
    os << dut;

    EXPECT_EQ(ref, os.str());
}