#include "mapstack.hpp"
#include <iostream>
#include <limits>
#include <set>
#include <tuple>

#include <boost/test/unit_test.hpp>

using namespace std;


struct MapstackFixture {
    Mapstack<string, int> mapstack;
    int value;
};

BOOST_FIXTURE_TEST_SUITE(mapstack_tests, MapstackFixture)

BOOST_AUTO_TEST_CASE( single_entry_1 )
{
    mapstack.Set("a", 1);
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 1);

    mapstack.Set("a", 2);
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 2);

    mapstack.Pop();
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == false, "mapstack.Get : shouldn't get value!");

    mapstack.Set("a", 1);
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 1);
    mapstack.Push();

    mapstack.Set("a", 2);
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 2);

    mapstack.Pop();
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 1);

    mapstack.Pop();
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == false, "mapstack.Get : shouldn't get value!");
}

BOOST_AUTO_TEST_CASE( single_entry_2 )
{
    mapstack.Set("a", 1);
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 1);

    mapstack.Push();
    mapstack.Pop();

    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 1);
    mapstack.Set("a", 2);
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 2);

    mapstack.Push();
    mapstack.Pop();

    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 2);
}

BOOST_AUTO_TEST_CASE( multiple_entry_1 )
{
    mapstack.Set("a", 1);
    mapstack.Set("b", 1);
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 1);
    BOOST_CHECK_MESSAGE(mapstack.Get("b", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 1);

    mapstack.Set("b", 2);
    BOOST_CHECK_MESSAGE(mapstack.Get("b", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 2);

    mapstack.Pop();
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == false, "mapstack.Get : shouldn't get value!");
    BOOST_CHECK_MESSAGE(mapstack.Get("b", value) == false, "mapstack.Get : shouldn't get value!");

    mapstack.Clear();
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == false, "mapstack.Get : shouldn't get value!");
    BOOST_CHECK_MESSAGE(mapstack.Get("b", value) == false, "mapstack.Get : shouldn't get value!");
    BOOST_CHECK_MESSAGE(mapstack.Get("c", value) == false, "mapstack.Get : shouldn't get value!");
    BOOST_CHECK_MESSAGE(mapstack.Get("d", value) == false, "mapstack.Get : shouldn't get value!");
}

BOOST_AUTO_TEST_CASE( multiple_entry_2 )
{
    mapstack.Set("a", 1);
    mapstack.Set("b", 2);
    mapstack.Push();
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 1);
    BOOST_CHECK_MESSAGE(mapstack.Get("b", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 2);

    mapstack.Set("c", 3);
    mapstack.Set("d", 4);
    BOOST_CHECK_MESSAGE(mapstack.Get("c", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 3);
    BOOST_CHECK_MESSAGE(mapstack.Get("d", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 4);

    mapstack.Pop();
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 1);
    BOOST_CHECK_MESSAGE(mapstack.Get("b", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 2);
    BOOST_CHECK_MESSAGE(mapstack.Get("c", value) == false, "mapstack.Get : shouldn't get value!");
    BOOST_CHECK_MESSAGE(mapstack.Get("d", value) == false, "mapstack.Get : shouldn't get value!");

    mapstack.Clear();
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == false, "mapstack.Get : shouldn't get value!");
    BOOST_CHECK_MESSAGE(mapstack.Get("b", value) == false, "mapstack.Get : shouldn't get value!");
    BOOST_CHECK_MESSAGE(mapstack.Get("c", value) == false, "mapstack.Get : shouldn't get value!");
    BOOST_CHECK_MESSAGE(mapstack.Get("d", value) == false, "mapstack.Get : shouldn't get value!");

}

BOOST_AUTO_TEST_CASE( multiple_entry_3 )
{
    mapstack.Set("a", 1);
    mapstack.Set("b", 2);
    mapstack.Push();
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 1);
    BOOST_CHECK_MESSAGE(mapstack.Get("b", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 2);


    mapstack.Set("a", 11);
    mapstack.Set("b", 12);
    mapstack.Set("c", 3);
    mapstack.Set("d", 4);
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 11);
    BOOST_CHECK_MESSAGE(mapstack.Get("b", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 12);
    BOOST_CHECK_MESSAGE(mapstack.Get("c", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 3);
    BOOST_CHECK_MESSAGE(mapstack.Get("d", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 4);

    mapstack.Pop();
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 1);
    BOOST_CHECK_MESSAGE(mapstack.Get("b", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 2);
}

BOOST_AUTO_TEST_CASE( multiple_entry_4 )
{
	// Initialy there is no element in the current list
    for(Mapstack<string, int>::current_const_iterator it = mapstack.CurrentBegin();
            it != mapstack.CurrentEnd();
            ++it) {
        BOOST_CHECK_MESSAGE(false, "Current list shouldn't have any element here!");
    }
	
    mapstack.Set("a", 1);
    mapstack.Set("b", 2);
    mapstack.Push();
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 1);
    BOOST_CHECK_MESSAGE(mapstack.Get("b", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 2);

    mapstack.Set("a", 11);
    mapstack.Set("b", 12);
    mapstack.Set("c", 3);
    mapstack.Set("d", 4);
    BOOST_CHECK_MESSAGE(mapstack.Get("a", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 11);
    BOOST_CHECK_MESSAGE(mapstack.Get("b", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 12);
    BOOST_CHECK_MESSAGE(mapstack.Get("c", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 3);
    BOOST_CHECK_MESSAGE(mapstack.Get("d", value) == true, "mapstack.Get : can't get value!");
    BOOST_CHECK_EQUAL(value, 4);

	// Mapstack current keys are {"a", "b", "c", "d"}
    string result[4] = {"a", "b", "c", "d"};
    int i = 0;
    for(auto it = mapstack.CurrentBegin();
            i < 4;
            ++it, ++i) {
        BOOST_CHECK_EQUAL(*it, result[i]);
    }

	// After pop mapstack current keys are {"a", "b"}
    mapstack.Pop();
    i = 0;
	auto it = mapstack.CurrentBegin();
    for(;
            i < 2;
            ++it, ++i) {
        BOOST_CHECK_EQUAL(*it, result[i]);
    }
	for(;
            it != mapstack.CurrentEnd();
            ++it) {
		std::cout << *it << std::endl;
		BOOST_CHECK_MESSAGE(false, "Current list shouldn't have any element here!");
    }

	// After pop mapstack keys are empty again
    mapstack.Pop();
    for(Mapstack<string, int>::current_const_iterator it = mapstack.CurrentBegin();
            it != mapstack.CurrentEnd();
            ++it) {
        BOOST_CHECK_MESSAGE(false, "Current list shouldn't have any element here!");
    }
}

BOOST_AUTO_TEST_CASE( const_iteration )
{
    std::vector<std::tuple<const std::string, int>> input
                    { std::make_tuple("a", 1)
                    , std::make_tuple("b", 2)
                    , std::make_tuple("c", 3)
                    , std::make_tuple("d", 4) };
					
	// initializing the mapstack with input
	for(auto elm : input) {
        mapstack.Set(std::get<0>(elm), std::get<1>(elm));
	}
		
	// check for equality of the two containers using std::set
    std::set<std::tuple<const std::string, int>> set1(mapstack.begin(), mapstack.end());
    std::set<std::tuple<const std::string, int>> set2(input.begin(),input.end());
	BOOST_CHECK_MESSAGE(set1 == set2, "mapstack and input should be equal here!");
	
	mapstack.Push();
	
	// Pushing new values
    std::vector<std::tuple<const std::string, int>> push  =
    {  std::make_tuple("a", 11)
     , std::make_tuple("b", 12)};
	for(auto elm : push) {
        mapstack.Set(std::get<0>(elm), std::get<1>(elm));
	}
	
	// mapstack content should now be equal to :
    std::set<std::tuple<const std::string, int>> set3
                    { std::make_tuple("a", 11)
                    , std::make_tuple("b", 12)
                    , std::make_tuple("c", 3)
                    , std::make_tuple("d", 4) };
	set1.clear();
	set1.insert(mapstack.begin(), mapstack.end());
	BOOST_CHECK_MESSAGE(set1 == set3, "mapstack and input should be equal here!");
	
	// After pop, mapstack should retrieve it's previous values
	mapstack.Pop();
	set1.clear();
	set1.insert(mapstack.begin(), mapstack.end());
	BOOST_CHECK_MESSAGE(set1 == set2, "mapstack and input should be equal here!");
	
	
}

BOOST_AUTO_TEST_CASE( iteration )
{
    std::vector<std::tuple<const std::string, int>> input
                    { std::make_tuple("a", 1)
                    , std::make_tuple("b", 2)
                    , std::make_tuple("c", 3)
                    , std::make_tuple("d", 4) };

    // initializing the mapstack with input
    for(auto elm : input) {
        mapstack.Set(std::get<0>(elm), std::get<1>(elm));
    }

    // check for equality of the two containers using std::set
    std::set<std::tuple<const std::string, int>> set1(mapstack.begin(), mapstack.end());
    std::set<std::tuple<const std::string, int>> set2(input.begin(),input.end());
    BOOST_CHECK_MESSAGE(set1 == set2, "mapstack and input should be equal here!");

    // mutate the mapstack from an iterator
    for(auto elem : mapstack) {
        std::get<1>(elem) -= 1;
    }

    // mapstack content should now be equal to :
    std::vector<std::tuple<const std::string, int>> output
                    { std::make_tuple("a", 0)
                    , std::make_tuple("b", 1)
                    , std::make_tuple("c", 2)
                    , std::make_tuple("d", 3) };

    set1.insert(mapstack.begin(), mapstack.end());
    set2.insert(output.begin(),output.end());
    BOOST_CHECK_MESSAGE(set1 == set2, "mapstack and output should be equal here!");

}

BOOST_AUTO_TEST_SUITE_END()
