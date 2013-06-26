/* 
 * File:   test-no-boost.cpp
 * Author: jefft0
 *
 * Created on June 10, 2013, 4:21 PM
 */

#include <cstdlib>
#include <sstream>
#include <iostream>
#include "ndn-cpp/interest.h"
#include "ndn-cpp/encoding/ccnb.h"

using namespace std;
using namespace ndn;

/*
 * 
 */
int main(int argc, char** argv) {
  ndn::ptr_lib::shared_ptr<Interest> interest(new Interest());
  interest->setName(Name("/test"));
  interest->setMinSuffixComponents(2);
  interest->setMaxSuffixComponents(2);
  interest->setInterestLifetime(boost::posix_time::seconds(10));
  interest->setScope(Interest::SCOPE_LOCAL_CCND);
  interest->setAnswerOriginKind(Interest::AOK_STALE);
  interest->setChildSelector(Interest::CHILD_RIGHT);
  // i.setPublisherPublicKeyDigest(?);
  ostringstream binary;
  wire::Ccnb::appendInterest(binary, *interest);
  cout << binary.str().size() << "\n";
  
  return 0;
}