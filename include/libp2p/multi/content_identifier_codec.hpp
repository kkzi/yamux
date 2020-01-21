/**
 * Copyright Soramitsu Co., Ltd. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LIBP2P_CONTENT_IDENTIFIER_CODEC_HPP
#define LIBP2P_CONTENT_IDENTIFIER_CODEC_HPP

#include <libp2p/multi/content_identifier.hpp>
#include <libp2p/multi/multibase_codec/codecs/base58.hpp>

namespace libp2p::multi {

  /**
   * Serializes and deserializes CID to byte representation.
   * To serialize it to a multibase encoded string, use MultibaseCodec
   * @see MultibaseCodec
   */
  class ContentIdentifierCodec {
   public:
    enum class EncodeError {
      INVALID_CONTENT_TYPE = 1,
      INVALID_HASH_TYPE,
      INVALID_HASH_LENGTH,
      VERSION_UNSUPPORTED
    };

    enum class DecodeError {
      EMPTY_VERSION = 1,
      EMPTY_MULTICODEC,
      MALFORMED_VERSION,
      RESERVED_VERSION
    };

    static outcome::result<std::vector<uint8_t>> encode(
        const ContentIdentifier &cid);

    /// Encodes arbitrary byte buffer into CID v.0 wire format
    static std::vector<uint8_t> encodeCIDV0(
        const void* byte_buffer, size_t sz);

    static outcome::result<ContentIdentifier> decode(
        gsl::span<const uint8_t> bytes);

    /**
     * @brief Encode CID v0 to string representation
     * @param cid - input CID for encode
     * @param encoding - type of the encoding, ignored for CID v0 (always
     * Base58)
     * @todo Sergey Kaprovich: FIL-133 add support for CID v1
     * @return CID string
     */
    static outcome::result<std::string> toString(
        const ContentIdentifier &cid,
        MultibaseCodec::Encoding encoding = MultibaseCodec::Encoding::BASE58);
  };

}  // namespace libp2p::multi

OUTCOME_HPP_DECLARE_ERROR(libp2p::multi, ContentIdentifierCodec::EncodeError);
OUTCOME_HPP_DECLARE_ERROR(libp2p::multi, ContentIdentifierCodec::DecodeError);

#endif  // LIBP2P_CONTENT_IDENTIFIER_CODEC_HPP
