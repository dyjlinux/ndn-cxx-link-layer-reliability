/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2013-2015 Regents of the University of California.
 *
 * This file is part of ndn-cxx library (NDN C++ library with eXperimental eXtensions).
 *
 * ndn-cxx library is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * ndn-cxx library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 *
 * You should have received copies of the GNU General Public License and GNU Lesser
 * General Public License along with ndn-cxx, e.g., in COPYING.md file.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * See AUTHORS.md for complete list of ndn-cxx authors and contributors.
 */

#include "ack-group.hpp"
#include "util/random.hpp"
#include "util/crypto.hpp"
#include "util/concepts.hpp"
#include "encoding/block-helpers.hpp"

namespace ndn {

BOOST_CONCEPT_ASSERT((boost::EqualityComparable<AckGroup>));
BOOST_CONCEPT_ASSERT((WireEncodable<AckGroup>));
BOOST_CONCEPT_ASSERT((WireDecodable<AckGroup>));
static_assert(std::is_base_of<tlv::Error, AckGroup::Error>::value,
              "AckGroup::Error must inherit from tlv::Error");

AckGroup::AckGroup()
{
}

AckGroup::AckGroup(std::list<uint32_t> ackGroup)
: m_ackGroup (ackGroup)
{

}

AckGroup::AckGroup(const Block& wire)
{
  wireDecode(wire);
}

template<encoding::Tag TAG>
size_t
AckGroup::wireEncode(EncodingImpl<TAG>& block) const
{
  size_t totalLength = 0;

  // AckGroup ::= AckGroup-TYPE TLV-LENGTH
  //                AckNumber*
 
  //std::cout << "3_1" << std::endl;
  
  // (reverse encoding)
  std::list<uint32_t>::const_iterator it;
  for (it = m_ackGroup.begin(); it != m_ackGroup.end(); it++)
      totalLength += prependNonNegativeIntegerBlock(block, tlv::AckNumber, *it);

  totalLength += block.prependVarNumber(totalLength);
  totalLength += block.prependVarNumber(tlv::AckGroup);
  //std::cout << "3_2" << std::endl;
  return totalLength;
}

template size_t
AckGroup::wireEncode<encoding::EncoderTag>(EncodingImpl<encoding::EncoderTag>& block) const;

template size_t
AckGroup::wireEncode<encoding::EstimatorTag>(EncodingImpl<encoding::EstimatorTag>& block) const;

const Block&
AckGroup::wireEncode() const
{
  if (m_wire.hasWire())
    return m_wire;
  EncodingEstimator estimator;
  size_t estimatedSize = wireEncode(estimator);

  EncodingBuffer buffer(estimatedSize, 0);
  wireEncode(buffer);

  const_cast<AckGroup*>(this)->wireDecode(buffer.block());

  return m_wire;
}

void
AckGroup::wireDecode(const Block& wire)
{
  //std::cout << "2_1" << std::endl;
      
  m_wire = wire;
  m_wire.parse();

  // AckGroup ::= AckGroup-TYPE TLV-LENGTH
  //                AckNumber*      

  if (m_wire.type() != tlv::AckGroup)
    throw Error("Unexpected TLV number when decoding AckGroup");


  // Acknowledgment number
  Block::element_const_iterator val = m_wire.find(tlv::AckNumber);
  m_ackGroup.clear();
  while (val != m_wire.elements_end())
  {
     //std::cout << "xxx" << std::endl;
      m_ackGroup.push_back(readNonNegativeInteger(*val));
      val++;
  }
  //std::cout << "2_2" << std::endl;
      
}

std::list<uint32_t>
AckGroup::getAckList() const
{
  return m_ackGroup;
}

void 
AckGroup::setAckList(std::list<uint32_t> ackGroup)
{
  m_ackGroup = ackGroup;
}

void
AckGroup::addAckNumber(uint32_t ackNumber)
{
  m_ackGroup.push_back(ackNumber);
}

bool
AckGroup::empty() const
{
  return m_ackGroup.empty();
}

std::ostream&
operator<<(std::ostream& os, const AckGroup& ackGroup)
{
  os << "(";
  // std::list<uint32_t>::iterator it;
  // for (it = ackGroupbegin(); it != ackGroup.end(); it++)
  //   os << *it << ",";
  os << ")";
  return os;
}

} // namespace ndn
