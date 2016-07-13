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

#ifndef NDN_LINK_PB_ACK_HPP
#define NDN_Link_PB_ACK_HPP

#include "common.hpp"
#include "util/time.hpp"
#include "management/nfd-local-control-header.hpp"
#include "tag-host.hpp"
#include "data.hpp"
#include "interest.hpp"
#include "ack-group.hpp"
//#include "repeat-group.hpp"
 
namespace ndn {

class Data;
class Interest;
class LinkPbAck;
class AckGroup;

/** @brief represents an LinkPbAck packet
 */
class LinkPbAck : public TagHost, public enable_shared_from_this<LinkPbAck>
{
public:
  class Error : public tlv::Error
  {
  public:
    explicit
    Error(const std::string& what)
      : tlv::Error(what)
    {
    }
  };

  /** @brief Create a new LinkPbAck with an empty name (`ndn:/`)
   *  @warning In certain contexts that use LinkPbAck::shared_from_this(), LinkPbAck must be created
   *           using `make_shared`. Otherwise, .shared_from_this() will throw an exception.
   */
  LinkPbAck();


  LinkPbAck(std::list<uint32_t> ackGroup);

  
  LinkPbAck(const Data &data);


  LinkPbAck(const Interest &interest);


  LinkPbAck(AckGroup ackGroup, Data &data);


  LinkPbAck(AckGroup ackGroup, Interest &interest);


  /** @brief Create from wire encoding
   *  @warning In certain contexts that use LinkPbAck::shared_from_this(), LinkPbAck must be created
   *           using `make_shared`. Otherwise, .shared_from_this() will throw an exception.
   */
  explicit
  LinkPbAck(const Block& wire);

  /**
   * @brief Fast encoding or block size estimation
   */
  template<encoding::Tag TAG>
  size_t
  wireEncode(EncodingImpl<TAG>& block) const;

  /**
   * @brief Encode to a wire format
   */
  const Block&
  wireEncode() const;

  /**
   * @brief Decode from the wire format
   */
  void
  wireDecode(const Block& wire);


  std::list<uint32_t>
  getAckList() const;

  void
  setAckList(std::list<uint32_t> ackList);
  
  void
  addAckNumber(uint32_t ackNumber);

  /*
  std::list<uint32_t>
  getRepeatList() const;

  void
  setRepeatList(std::list<uint32_t> repeatList);
  
  void
  addRepeatNumber(uint32_t repeatNumber);
  */
  
  /**
   * @brief Check if already has wire
   */
  bool
  hasWire() const
  {
    return m_wire.hasWire();
  }

  bool
  containData() const;

  bool
  containInterest() const;

  Data
  getData() const;

  Interest
  getInterest() const;

  void
  setData(const Data& data);

  void
  setInterest(const Interest& interest);

  /**
   * @brief Encode the name according to the NDN URI Scheme
   *
   * If there are LinkPbAck selectors, this method will append "?" and add the selectors as
   * a query string.  For example, "/test/name?ndn.ChildSelector=1"
   */
  std::string
  toUri() const;

public: // local control header
  nfd::LocalControlHeader&
  getLocalControlHeader()
  {
    return m_localControlHeader;
  }

  const nfd::LocalControlHeader&
  getLocalControlHeader() const
  {
    return m_localControlHeader;
  }

  uint64_t
  getIncomingFaceId() const
  {
    return getLocalControlHeader().getIncomingFaceId();
  }

  LinkPbAck&
  setIncomingFaceId(uint64_t incomingFaceId)
  {
    getLocalControlHeader().setIncomingFaceId(incomingFaceId);
    // ! do not reset LinkPbAck's wire !
    return *this;
  }

  uint64_t
  getNextHopFaceId() const
  {
    return getLocalControlHeader().getNextHopFaceId();
  }

  LinkPbAck&
  setNextHopFaceId(uint64_t nextHopFaceId)
  {
    getLocalControlHeader().setNextHopFaceId(nextHopFaceId);
    // ! do not reset LinkPbAck's wire !
    return *this;
  }

public: // EqualityComparable concept
  bool
  operator==(const LinkPbAck& other) const
  {
    return wireEncode() == other.wireEncode();
  }

  bool
  operator!=(const LinkPbAck& other) const
  {
    return !(*this == other);
  }

private:
  mutable Block m_wire;
  
  Data m_data;
  Interest m_interest;
  
  bool m_hasData;
  bool m_hasInterest;

  AckGroup m_ackGroup;
  //RepeatGroup m_repeatGroup;

  nfd::LocalControlHeader m_localControlHeader;
  friend class nfd::LocalControlHeader;
};

std::ostream&
operator<<(std::ostream& os, const LinkPbAck& LinkPbAck);

inline std::string
LinkPbAck::toUri() const
{
  std::ostringstream os;
  os << *this;
  return os.str();
}

} // namespace ndn

#endif
