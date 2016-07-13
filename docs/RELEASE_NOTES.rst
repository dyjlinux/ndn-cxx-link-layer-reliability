.. _Release Notes:

ndn-cxx Release Notes
---------------------

ndn-cxx v0.3.1 (changes since version 0.3.0)
++++++++++++++++++++++++++++++++++++++++++++

Release date: March 3, 2015

New features:
^^^^^^^^^^^^^

- **Management**

  - Add isConnected() in :ndn-cxx:`signal::Connection` and :ndn-cxx:`signal::ScopedConnection`
    (:issue:`2308`)

  - Extend :ndn-cxx:`DummyClientFace` to process :ndn-cxx:`LocalControlHeader` (:issue:`2510`)

  - Add CachingPolicy to :ndn-cxx:`LocalControlHeader` (:issue:`2183`)

Updates and bug fixes:
^^^^^^^^^^^^^^^^^^^^^^

- **Wire encoding**

  - Refactoring of :ndn-cxx:`EncodingImpl` class template (``EncodingBuffer`` and
    ``EncodingEstimator``) (:issue:`2494`, :issue:`2490`)

  - Change :ndn-cxx:`Block::fromBuffer` return type (:issue:`2553`)

- **Miscellaneous tools**

  - Mark ``Digest<Hash>::operator==`` as unsuitable in a security sensitive context
    (:issue:`2395`)

  - Restrict destruction of Signal from handler (:issue:`2313`)

- **Documentation**

  - Correct function names in security library tutorial (:issue:`2474`)

  - Remind users to reinstall ports after OSX upgrade (:issue:`2284`)

- **Tests**

  - Fix global buffer overflow in ``ImplicitSha256Digest`` test case (:issue:`2307`)

  - Change naming conventions for unit test files and test suite names (:issue:`2497`)

- **Build**

  - Explicitly define ``_GLIBCXX_USE_NANOSLEEP``, necessary for gcc < 4.8 in some environments
    (:issue:`2499`)

Removed:
^^^^^^^^

- Delete deprecated ``Block(std::istream&)`` constructor (:issue:`2241`)

- Delete deprecated ``ndn::ptr_lib``, ``ndn::func_lib`` (:issue:`2110`)

- Delete deprecated ``MetaInfo::TYPE_*`` (:issue:`2170`)

****************************************************************************

ndn-cxx v0.3.0 (changes since version 0.2.0)
++++++++++++++++++++++++++++++++++++++++++++

Release date: February 2, 2015

New features:
^^^^^^^^^^^^^

- **Build**

  + The code now requires C++11.  The minimum supported gcc version is 4.6, as earlier versions
    do not have proper support for C++11 features.

- **Base**

  + Enable detailed version information when built from shallow clone or tarball
    (:issue:`1915`)

  + Make default transport configurable (:issue:`2189`)

  + Add ability to do partial Name comparison (:issue:`2090`)

- **Security**

  + Add support for KeyDigest key locator (:issue:`1426`)

  + Add a method to get KeyDigest from a PublicKey instance (:issue:`1964`)

  + Add support for KeyChain to sign Interest using SHA256 digest (:issue:`2218`)

  + Add ``ndnsec-dsk-gen`` tool to generate a pair of Data-Signing-Key (DSK) for the specified
    identity  (:issue:`2246`)

  + Pair-up PIB and TPM in KeyChain: PIB remembers the last used TPM type/location, which is
    used during KeyChain construction (unless overriden) (:issue:`2242`)

- **Wire encoding**

  + Add support for application-defined meta information blocks (:issue:`2021`)

  + Introduce new ``name::Component::is*`` methods to allow checking if the name component
    follows the specific naming convention without relying on the exception handling
    (:issue:`2088`)

  + Add definition of producer-generated NACK (:issue:`2111`)

  + Add ``std::hash<Name>`` specialization to support ``unordered_map`` container
    (:issue:`2147`)

  + Add support for ImplicitSha256DigestComponent (:issue:`1640`)

  + Allow tagging Interest and Data packets with arbitrary information (:issue:`2336`)

- **Management**

  + Support NFD face query operation (:issue:`2085`)

- **Miscellaneous tools**

  + Add a new helper to calculate digests over dynamic inputs (:issue:`1934`)

  + Add DNS resolver helper (:issue:`1918`)

  + Import and re-license Ethernet and FaceUri classes from NFD codebase, add FaceUri
    canonization support for ``udp``, ``tcp``, and ``ether`` schemas (:issue:`1994`)

  + Add per-application in-memory storage with LRU, LFU, and FIFO replacement policies
    (:issue:`1940`)

  + Add ability to specialize system and steady clocks (e.g., for unit tests and simulation
    purposes) (:issue:`2158`)

  + Expose DummyClientFace as public API

  + New IndentedStream helper class to simplify writing to streams with the specified indents
    or prefixes (:issue:`2238`)

  + New Signal class template as an enhanced version of the deprecated EventEmitter
    (:issue:`2279`)

  + New scheduler::ScopedEventId helper to automatically cancel scheduled events upon
    destruction (:issue:`2442`)

  + New NetworkMonitor helper to detect network state changes (:issue:`2443`)

Updates and bug fixes:
^^^^^^^^^^^^^^^^^^^^^^

- **Base**

  + Prevent flags being set for rib/unregister command (:issue:`1945`)

  + Fix segfault caused by Face::unregisterPrefix when registeredPrefixId does not exist

  + Add explicit internal KeyChain to Face class.  KeyChain previously existed in the Face as
    part of NFD controller class.  (:issue:`2039`)

  + Properly disable assertions in release builds (:issue:`2135`)

  + Connect to Transport during construction of Face instance (:issue:`2318`)

- **Wire encoding**

  + Fix segfault when decoding empty Exclude element (:issue:`1970`)

  + Provide EqualityComparable concept for Exclude element

  + Correct Marker in Name::appendVersion() (:issue:`2086`)

  + Ensure that wire-encoding errors are inherited from ``tlv::Error`` (:issue:`1983`)

- **Management**

  + Replace FaceFlags with individual fields in face management data structures (:issue:`1992`)

  + ``ndn::nfd::Controller`` extended to allow generating ControlCommand for remote prefix
    registration (:issue:`2039`)

  + Change ``ForwarderStatus.NfdVersion`` to string (:issue:`2003`)

- **Security**

  + Fix ``ndnsec-cert-gen`` to correctly infer prefix before KEY component (:issue:`2052`)

  + Help message corrections in ``ndnsec-cert-dump``, ``ndnsec-cert-gen``, and
    ``ndnsec-key-gen`` (:issue:`2052`)

  + Accept ``--sign-id`` and ``--cert-prefix`` in ``ndnsec-cert-revoke`` (:issue:`2058`)

  + Changes output format of ``ndnsec-cert-revoke`` to base64 encoding (:issue:`2059`)

  + Add a new (safer) option to ``ndnsec-cert-gen`` allowing inclusion of additional
    information blocks into the certificate.  The new ``--signed-info`` parameter makes minimum
    assumptions, treating text before first space as OID and the rest as the associated string
    with this OID.

  + Make Face optional in Validator class (:issue:`2124`)

  + Display signature information when printing a certificate (:issue:`2196`)

  + Handle certificate decoding error in validation process (:issue:`2212`)

  + Fix segmentation fault in ``ndnsec-sign-req`` (:issue:`2211`)

  + Allow verbose option in ``ndnsec-list`` (:issue:`2197`)

  + Allow generation of DSK using ``ndnsec-key-gen`` (:issue:`2247`)

  + Allow ``ndnsec-key-gen`` to generate ECDSA keys (:issue:`2248`)

  + Fix memory leak in SecPublicInfoSqlite3 (:issue:`2253`)

  + Properly report status of ``ndnsec-delete`` execution (:issue:`2275`)

- **Miscellaneous tools**

  + Fix incorrect tag map in ``tlvdump`` tool

  + Change to default resolver behavior in util::dns::Resolver (:issue:`2415`)

- **Documentation**

  + Update of tutorials and installation instructions

  + Rename manpage of ``client.conf`` to ``ndn-client.conf`` (:issue:`1967`)

  + Updated and extended ndn-cxx code style:

    - add rules for some C++11 constructs
    - prefer ``BOOST_ASSERT`` and ``static_assert``

  + Improve example applications (:issue:`1976`)

- **Tests**

  + Improve security unit test cases (:issue:`1683`)

  + Embedding CI build and test running scripts into the repository

  + Partial unit test coverage for Face class (previously covered only by integration tests)
    (:issue:`1947`)

  + Improve stability of unit tests by using UnitTestTime (wall clock independent time)
    (:issue:`2152`)

- **Build**

  + Redesign the way default compiler flags are determined (:issue:`2209`)

  + Support tools and examples with multiple translation units (:issue:`2344`)

  + Disable installation of internal headers and headers of the disabled components
    (:issue:`2266`, and :issue:`2269`)

  + Enable conditional compilation based on presence of ``getpass()`` function

- Other minor fixes and corrections

Deprecated:
^^^^^^^^^^^

- ``ndn::ptr_lib`` and ``ndn::func_lib`` namespace aliases

- The following ``nfd::Controller`` methods:

  + ``Controller::start`` overloads, except the overload taking ``CommandOptions``
  + ``Controller::Sign`` typedef
  + ``Controller::getDefaultCommandTimeout``
  + ``ControlCommand::getPrefix``
  + ``ControlCommand::getRequestName(ControlParameters)``
  + ``Controller::Controller(Face&)``

- ``MetaInfo::TYPE_*`` constants

- ``EventEmitter`` is deprecated in favor of ``Signal``

Removed:
^^^^^^^^

- FaceFlags APIs (:issue:`1992`)

- ``ControlCommand::makeCommandInterest`` (:issue:`2008`)

- namespace ``ndn::Tlv`` (:issue:`2079`)

- ``shared_ptr<io_service>`` constructor and getter in Face class

- ``tlv::ConentType`` (typo in the name)

- ``Selectors::Selectors(int, int, Exclude, int, bool)`` constructor

- ``Interest::Interest(Name, int, int, Exclude, int, bool, int, time::milliseconds, uint32_t)``
  constructor

- ``signature-sha256.hpp`` file

- unused ``encryption-manager.hpp`` file

- unused ``openssl`` dependency

****************************************************************************

ndn-cxx v0.2.0 (changes since version 0.1.0)
++++++++++++++++++++++++++++++++++++++++++++

Release date: August 25, 2014

New features:
^^^^^^^^^^^^^

- **Base**

  + The license under which the library is released is changed to **Lesser GNU Public
    License version 3.0**.

  + New ways to use incoming Interest dispatching:

    * New :ndn-cxx:`InterestFilter` abstraction that supports filtering based on name
      prefixes and regular expressions.

    * Separated :ndn-cxx:`Face::registerPrefix()` and :ndn-cxx:`Face::setInterestFilter()`
      methods allow distinct operations of registering with the local NDN forwarder and setting
      up application-specific ``OnInterest`` call dispatch using InterestFilters.

  + Add support for new `NDN naming conventions
    <http://named-data.net/doc/tech-memos/naming-conventions.pdf>`_ (:issue:`1761`)

- **Security**

  + Add ``type dir`` :ref:`trust-anchor in ValidatorConfig <validator-conf-trust-anchors>`
    to add all certificates under the specified directory as trust anchors.
    The new option also allow periodic reloading trust anchors, allowing dynamic trust
    models.

  + Added support for multiple signature types to :ndn-cxx:`PublicKey`,
    :ndn-cxx:`SecPublicInfo` abstractions

  + New :ndn-cxx:`SignatureSha256WithEcdsa` signature type

  + Updates in :ndn-cxx:`Signature` data structure to reflect changes in `NDN-TLV spec
    0.1.1 <http://named-data.net/doc/NDN-TLV/0.1.1/>`_

- **Wire encoding**

  + :ndn-cxx:`Data::getFullName() <getFullName()>` method to get :ndn-cxx:`Data` packet
    name with implicit digest

  + New :ndn-cxx:`Name::getSuccessor()` method to get name successor (:issue:`1677`)

  + New in-wire refreshing of Interest's nonce (:issue:`1758`)

- **Management**

  + Support for :ndn-cxx:`ChannelStatus`, :ndn-cxx:`StrategyChoice` datasets

  + Defining new common Route Origins for NFD RIB management protocol (:issue:`1719`)

  + New RibEntry and Route data structures for RIB management protocol (:issue:`1764`)

  + Add support for RIB flags for setInterestFilter and registerPrefix (:issue:`1842`)

- **Miscellaneous tools**

  + Introduce :ndn-cxx:`Scheduler::cancelAllEvents` to cancel all previously scheduled events
    (:issue:`1757`)

  + Introduce :ndn-cxx:`util::EventEmitter`, :ndn-cxx:`util::NotificationSubscriber`,
    :ndn-cxx:`util::NotificationStream`, and :ndn-cxx:`nfd::FaceMonitor` utility classes

  + Introduce :ndn-cxx:`util::SegmentFetcher` helper class to fetch multi-segmented data
    (:issue:`1879`)

- **Build**

  + enabled support of precompiled headers for clang and gcc compilers to speed up compilation

Updates and bug fixes:
^^^^^^^^^^^^^^^^^^^^^^

- **Base**

  + Serialization of socket write operations (:issue:`1707`)

  + Enforcing limit on Interest and Data packet size in :ndn-cxx:`Face::expressInterest` and
    :ndn-cxx:`Face::put` methods (:issue:`1774`)

  + Cleaning up transport state on communication failure, so Face can try to reconnect
    in the future.

  + Fix bug with Face::removePendingInterest (:issue:`1917`)

- **Wire encoding**

  + Nonce field is now encoded as 4-byte uint8_t value, as defined by NDN-TLV spec.

  + Optimized Data packet signing

    :ndn-cxx:`KeyChain::sign` method now pre-allocates :ndn-cxx:`EncodingBuffer`, requests
    unsigned portion of :ndn-cxx:`Data` using ``Data::wireEncode(EncodingBuffer, true)``,
    and then appends the resulting signature and prepends :ndn-cxx:`Data` packet header.
    This way there is no extra memory allocation after :ndn-cxx:`Data` packet is signed.

  + Optimized implicit digest calculation in :ndn-cxx:`Interest::matchesData` method
    (:issue:`1769`)

- **Management**

  + Add link-layer byte counts in FaceStatus data structure (:issue:`1765`)

- **Security**

  + Allow user to explicitly specify the cert name prefix before 'KEY' component in
    ``ndnsec-certgen``

  + ``SignatureSha256`` has been renamed to :ndn-cxx:`DigestSha256` to conform with
    `NDN-TLV specification <http://named-data.net/doc/ndn-tlv/>`_.

  + Add checking of ``Timestamp`` and ``Nonce`` fields in signed Interest within
    :ndn-cxx:`ValidatorConfig`

  + Allow validator customization using hooks:

    Sub-classes of :ndn-cxx:`Validator` class can use the following hooks to fine-tune the
    validation process:

      * :ndn-cxx:`Validator::preCertificateValidation <preCertificateValidation>` to
        process received certificate before validation.
      * :ndn-cxx:`Validator::onTimeout <onTimeout>` to process interest timeout
      * :ndn-cxx:`Validator::afterCheckPolicy <afterCheckPolicy>` to process validation requests.

  + Fix memory issues in :ndn-cxx:`SecPublicInfoSqlite3`

- **Miscellaneous tools**

  + Redefine method for random number generation: ``random::generateWord*`` and
    ``random::generateSecureWord*`` to generate cryptographically non-secure (fast) and
    secure (slow) random numbers.

- Other minor fixes and corrections

Deprecated:
^^^^^^^^^^^

- ``SignatureSha256`` class, use :ndn-cxx:`DigestSha256` instead.

- All :ndn-cxx:`Face` constructors that accept ``shared_ptr<io_service>``.

  Use versions that accept reference to ``io_service`` object.

- ``Face::ioService`` method, use :ndn-cxx:`Face::getIoService` instead.

- :ndn-cxx:`Interest` constructor that accepts name, individual selectors, and individual
  guiders as constructor parameters.

  Use ``Interest().setX(...).setY(...)`` or use the overload taking ``Selectors``

- ``name::Component::toEscapedString`` method, use :ndn-cxx:`name::Component::toUri` instead.

- ``SecPublicInfo::addPublicKey`` method, use :ndn-cxx:`SecPublicInfo::addKey` instead.

- ``Tlv::ConentType`` constant (typo), use ``Tlv::ContentType`` instead.

- ``CommandInterestGenerator`` and ``CommandInterestValidator`` utility classes.
  :ndn-cxx:`ValidatorConfig` should be used instead.

Removed:
^^^^^^^^

- support of ndnd-tlv (only NFD management protocol is supported now)

- ``SecPublicInfoMemory`` and ``SecTpmMemory`` classes that were no longer used

- Removing concept of periodic event from :ndn-cxx:`Scheduler`.

  In applications, periodic events should be just re-scheduled within the callback for
  single-shot events.

****************************************************************************

ndn-cxx v0.1.0
++++++++++++++

Release date: May 7, 2014

Version 0.1.0 is the initial release of ndn-cxx, an NDN C++ library with eXperimental
eXtensions.

Originally based on `ndn-cpp library <https://github.com/named-data/ndn-cpp>`_ the ndn-cxx
library adopts a slightly different design philosophy (including an extensive use of Boost
libraries to facilitate development, as well as the use of Crypto++ library to support
cryptographic operations), and includes a number of extensions that aim to simplify NDN
application development.

The current features include:

- **Base**

  + Fully asynchronous, event-driven communication model, which is implemented using `Boost.Asio
    <http://www.boost.org/doc/libs/1_48_0/doc/html/boost_asio.html>`_
  + Single-threaded, but thread-safe Face operations

      A single Face object can be safely used in multiple threads to express Interests and
      publish Data packets

  + Explicit time management for NDN operations using `Boost.Chrono
    <http://www.boost.org/doc/libs/1_48_0/doc/html/chrono.html>`_
  + Simplified and extended `NDN API <doxygen/annotated.html>`_
  + Extensive set of unit-tests based on `Boost.Test framework
    <http://www.boost.org/doc/libs/1_48_0/libs/test/doc/html/index.html>`_

    - Continuous integration using an in-house installation of Jenkins build bots and the
      hosted `Travis CI <https://travis-ci.org/named-data/ndn-cxx>`_ continuous
      integration service compile and verify correctness of the library for each commit

- **Wire format**

  + Full support of `NDN-TLV packet format v0.1 <http://named-data.net/doc/NDN-TLV/0.1/>`_
  + Pure C++ implementation of wire encoding/decoding with simple access to wire format
    of all NDN packet abstractions via ``wireEncode`` and ``wireDecode`` methods

      In many cases, NDN packet abstractions are just "indices" to the wire format

- **Communication with the forwarder**

  + Enable connecting to local forwarder via UNIX and TCP transports and to remote
    forwarders using TCP transport
  + Full support for communication with `Named Data Networking Forwarding Daemon (NFD)
    <https://github.com/named-data/NFD>`_

    - Full support for `NFD management protocols
      <http://redmine.named-data.net/projects/nfd/wiki/Management>`_ to NFD status
      information, create and manage NFD Faces, receive NFD Face status change
      notifications, update StrategyChoice for namespaces, and manage routes in RIB
    - Support for `LocalControlHeader
      <http://redmine.named-data.net/projects/nfd/wiki/LocalControlHeader>`_ to implement
      special NDN applications that need low-level control of NDN packet forwarding

- **Security support**

  + A set of security primitives to allowing implementation of secure NDN applications in
    a simplified manner

    - **KeyChain**: provides simple interfaces of packet signing, and key and certificate
      management
    - **ValidatorConfig**: validator that implements trust model defined in a configuration
      file
    - **CommandInterestGenerator** and **CommandInterestValidator**: convenient helpers to produce
      and validate command interests, while preventing potential replay attacks

  + Several implementations of trusted platform modules to securely manage private keys

    - **SecTpmOsx**: TPM based on OSX KeyChain (OSX-specific)
    - **SecTpmFile**: TPM that uses file-based access control to protect keys (cross-platform)

  + Extensive set of security command-line tools to manage security identities and certificates

    - Generating private/public keys
    - Issuing certificates
    - Exporting/importing identities
    - Managing default security settings

- **Miscellaneous tools**

  + Scheduler to support delayed time operations
  + NDN regular expressions
  + Simple config file to alter various aspects of the library
  + **tlvdump**: a simple tool to visualize TLV-encoded blocks
