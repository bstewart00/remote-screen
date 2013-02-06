#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test1 )
{
    BOOST_CHECK( 2 == 1 );
}

BOOST_AUTO_TEST_CASE( test2 )
{
    int i = 0;

    BOOST_CHECK_EQUAL( i, 2 );
    BOOST_CHECK_EQUAL( i, 0 );
}