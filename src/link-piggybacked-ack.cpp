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

#include "link-piggybacked-ack.hpp"
#include "util/random.hpp"
#include "util/crypto.hpp"
#include "util/concepts.hpp"
#include "encoding/block-helpers.hpp"

namespace ndn {

BOOST_CONCEPT_ASSERT((boost::EqualityComparable<LinkPbAck>));
BOOST_CONCEPT_ASSERT((WireEncodable<LinkPbAck>));
BOOST_CONCEPT_ASSERT((WireDecodable<LinkPbAck>));
static_assert(std::is_base_of<tlv::Error, LinkPbAck::Error>::value,
              "LinkPbAck::Error must inherit from tlv::Error");

LinkPbAck::LinkPbAck()
{
  m_hasInterest = false;
  m_hasData = false;
}

LinkPbAck::LinkPbAck(std::list<uint32_t> ackGroup)
: m_ackGroup( ackGroup )
{
  m_hasInterest = false;
  m_hasData = false;
}

LinkPbAck::LinkPbAck(const Data & data)
: m_data (data)
{
  m_hasInterest = false;
  m_hasData = true;
}

LinkPbAck::LinkPbAck(const Interest &interest)
: m_interest (interest)
{
  m_hasInterest = true;
  m_hasData = false;
}

LinkPbAck::LinkPbAck(AckGroup ackGroup, Data &data)
: m_data (data)
, m_ackGroup( ackGroup )
{
  m_hasInterest = false;
  m_hasData = true;
}

LinkPbAck::LinkPbAck(AckGroup ackGroup, Interest &interest)
: m_interest ( interest )
, m_ackGroup( ackGroup )
{
  m_hasInterest = true;
  m_hasData = false;
}

LinkPbAck::LinkPbAck(const Block& wire)
{
  wireDecode(wire);
}

template<encoding::Tag TAG>
size_t
LinkPbAck::wireEncode(EncodingImpl<TAG>& block) const
{
  size_t totalLength = 0;

  // LinkPbAck ::= LinkPbAck-TYPE TLV-LENGTH
  //                AckGroup?
  //                RepeatGroup?
  //                (Data / Ack)?
 
  // (reverse encoding)
  
  //if (! m_repeatGroup.empty())
  //  totalLength += m_repeatGroup.wireEncode(block);  
  
  if (! m_ackGroup.empty())
    totalLength += m_ackGroup.wireEncode(block);  
  
  if (m_hasData && m_hasInterest)
    throw Error("link-piggybacked-ack can't have both Interest and Data at the same time");

  if (m_hasData)
    totalLength += m_data.wireEncode(block);  
  else if (m_hasInterest)
    totalLength += m_interest.wireEncode(block);  
  
  totalLength += block.prependVarNumber(totalLength);
  totalLength += block.prependVarNumber(tlv::LinkPbAck);
  return totalLength;
}

template size_t
LinkPbAck::wireEncode<encoding::EncoderTag>(EncodingImpl<encoding::EncoderTag>& block) const;

template size_t
LinkPbAck::wireEncode<encoding::EstimatorTag>(EncodingImpl<encoding::EstimatorTag>& block) const;

const Block&
LinkPbAck::wireEncode() const
{
  if (m_wire.hasWire())
    return m_wire;

  EncodingEstimator estimator;
  size_t estimatedSize = wireEncode(estimator);

  EncodingBuffer buffer(estimatedSize, 0);
  wireEncode(buffer);


  const_cast<LinkPbAck*>(this)->wireDecode(buffer.block());

  return m_wire;
}

void
LinkPbAck::wireDecode(const Block& wire)
{
  //std::cout << "5_1" << std::endl;
  m_wire = wire;
  m_wire.parse();

  // LinkPbAck ::= LinkPbAck-TYPE TLV-LENGTH
  //               AckGroup?
  //               RepeatGroup?      
  //              (Data / Ack)?

  if (m_wire.type() != tlv::LinkPbAck)
    throw Error("Unexpected TLV number when decoding LinkPbAck");

  // Acknowledgment number
  // m_name.wireDecode(m_wire.get(tlv::Name));

  m_ackGroup.setAckList(std::list<uint32_t>());
  Block::element_const_iterator val = m_wire.find(tlv::AckGroup);
  if (val != m_wire.elements_end())
  {
    m_ackGroup.wireDecode(*val);
  }

/*  m_repeatGroup.setRepeatList(std::list<uint32_t>());
  val = m_wire.find(tlv::RepeatGroup);
  if (val != m_wire.elements_end())
  {
    m_repeatGroup.wireDecode(*val);
  }
*/
  // Interest / Data
  val = m_wire.find(tlv::Interest);
  if (val != m_wire.elements_end())
  {
      m_interest.wireDecode(*val);
      m_hasInterest = true;
      m_hasData = false;
  }
  
  val = m_wire.find(tlv::Data);
  if (val != m_wire.elements_end())
  {
      m_data.wireDecode(*val);
      m_hasData = true;
      m_hasInterest = false;
  }
  //std::cout << "5_2" << std::endl;
}


std::list<uint32_t>
LinkPbAck::getAckList() const
{
  return m_ackGroup.getAckList();
}

void
LinkPbAck::setAckList(std::list<uint32_t> ackList)
{
  m_ackGroup.setAckList(ackList);
}


void 
LinkPbAck::addAckNumber(uint32_t ackNumber)
{
  m_ackGroup.addAckNumber(ackNumber);
}

/*
std::list<uint32_t>
LinkPbAck::getRepeatList() const
{
  return m_repeatGroup.getRepeatList();
}

void
LinkPbAck::setRepeatList(std::list<uint32_t> repeatList)
{
  m_repeatGroup.setRepeatList(repeatList);
}

void 
LinkPbAck::addRepeatNumber(uint32_t repeatNumber)
{
  m_repeatGroup.addRepeatNumber(repeatNumber);
}
*/

Data
LinkPbAck::getData() const
{
  if (m_hasData)
    return m_data;
  else
    throw Error("The LinkPbAck doesn't contain data");
}

void
LinkPbAck::setData(const Data &data)
{
  m_data = data;
  m_hasData = true;
  m_hasInterest = false;
}

Interest
LinkPbAck::getInterest() const
{
  if (m_hasInterest)
    return m_interest;
  else
    throw Error("The LinkPbAck doesn't contain interest");
}

void
LinkPbAck::setInterest(const Interest &interest)
{
  m_interest = interest;
  m_hasInterest = true;
  m_hasData = false;
}

bool 
LinkPbAck::containInterest() const
{
  return m_hasInterest;
}

bool
LinkPbAck::containData() const
{
  return  m_hasData;
}

std::ostream&
operator<<(std::ostream& os, const LinkPbAck& linkPbAck)
{
  os << "N/A";
  return os;
}

} // namespace ndn
