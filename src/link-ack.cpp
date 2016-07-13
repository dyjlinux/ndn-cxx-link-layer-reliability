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

#include "link-ack.hpp"
#include "util/random.hpp"
#include "util/crypto.hpp"
#include "util/concepts.hpp"
#include "encoding/block-helpers.hpp"

namespace ndn {

BOOST_CONCEPT_ASSERT((boost::EqualityComparable<LinkAck>));
BOOST_CONCEPT_ASSERT((WireEncodable<LinkAck>));
BOOST_CONCEPT_ASSERT((WireDecodable<LinkAck>));
static_assert(std::is_base_of<tlv::Error, LinkAck::Error>::value,
              "LinkAck::Error must inherit from tlv::Error");

LinkAck::LinkAck()
: m_ackNumber(0)
{
}

LinkAck::LinkAck(uint32_t ackNumber)
: m_ackNumber( ackNumber )
{
}


LinkAck::LinkAck(const Block& wire)
{
  wireDecode(wire);
}

template<encoding::Tag TAG>
size_t
LinkAck::wireEncode(EncodingImpl<TAG>& block) const
{
  size_t totalLength = 0;

  // LinkAck ::= LinkAck-TYPE TLV-LENGTH
  //                AckNumber
 
  // (reverse encoding)
  totalLength += prependNonNegativeIntegerBlock(block, tlv::AckNumber, getAckNumber());
  totalLength += block.prependVarNumber(totalLength);
  totalLength += block.prependVarNumber(tlv::LinkAck);
  return totalLength;
}

template size_t
LinkAck::wireEncode<encoding::EncoderTag>(EncodingImpl<encoding::EncoderTag>& block) const;

template size_t
LinkAck::wireEncode<encoding::EstimatorTag>(EncodingImpl<encoding::EstimatorTag>& block) const;

const Block&
LinkAck::wireEncode() const
{
  if (m_wire.hasWire())
    return m_wire;

  EncodingEstimator estimator;
  size_t estimatedSize = wireEncode(estimator);

  EncodingBuffer buffer(estimatedSize, 0);
  wireEncode(buffer);

  const_cast<LinkAck*>(this)->wireDecode(buffer.block());

  return m_wire;
}

void
LinkAck::wireDecode(const Block& wire)
{
  m_wire = wire;
  m_wire.parse();

  // LinkAck ::= LinkAck-TYPE TLV-LENGTH
  //                AckNumber      

  if (m_wire.type() != tlv::LinkAck)
    throw Error("Unexpected TLV number when decoding LinkAck");


  // Acknowledgment number
  Block::element_const_iterator val = m_wire.find(tlv::AckNumber);
  if (val != m_wire.elements_end())
    {
      m_ackNumber = readNonNegativeInteger(*val);
    }
  else
    m_ackNumber = 0;
}

uint32_t
LinkAck::getAckNumber() const
{
  return m_ackNumber;
}

void 
LinkAck::setAckNumber(uint32_t ackNumber)
{
  m_ackNumber = ackNumber;
}

std::ostream&
operator<<(std::ostream& os, const LinkAck& linkAck)
{
  os << linkAck.getAckNumber();
  return os;
}

} // namespace ndn
