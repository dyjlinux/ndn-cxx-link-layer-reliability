/**
 * Copyright (C) 2013 Regents of the University of California.
 * See COPYING for copyright and distribution information.
 */

#include <boost/test/unit_test.hpp>

#include "util/time.hpp"

namespace ndn {

BOOST_AUTO_TEST_SUITE(TestTime)

BOOST_AUTO_TEST_CASE (Simple)
{
  MillisecondsSince1970 value = getNowMilliseconds();
  BOOST_CHECK_GT(value, 1390966967032);

  BOOST_CHECK_EQUAL(toIsoString(1390966967032), "20140129T034247.032000");
  BOOST_CHECK_EQUAL(fromIsoString("20140129T034247.032000"), 1390966967032);

  BOOST_CHECK_EQUAL(fromIsoString("20140129T034247.032000Z"), 1390966967032);
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace ndn