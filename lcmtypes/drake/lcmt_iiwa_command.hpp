/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#include <lcm/lcm_coretypes.h>

#ifndef __drake_lcmt_iiwa_command_hpp__
#define __drake_lcmt_iiwa_command_hpp__

#include <vector>

namespace drake
{

/// Commands a single set of joint states for the arm.
class lcmt_iiwa_command
{
    public:
        int64_t    utime;

        int32_t    num_joints;

        std::vector< double > joint_position;

        std::vector< double > joint_torque;

        double     wrench[6];

    public:
        /**
         * Encode a message into binary form.
         *
         * @param buf The output buffer.
         * @param offset Encoding starts at thie byte offset into @p buf.
         * @param maxlen Maximum number of bytes to write.  This should generally be
         *  equal to getEncodedSize().
         * @return The number of bytes encoded, or <0 on error.
         */
        inline int encode(void *buf, int offset, int maxlen) const;

        /**
         * Check how many bytes are required to encode this message.
         */
        inline int getEncodedSize() const;

        /**
         * Decode a message from binary form into this instance.
         *
         * @param buf The buffer containing the encoded message.
         * @param offset The byte offset into @p buf where the encoded message starts.
         * @param maxlen The maximum number of bytes to reqad while decoding.
         * @return The number of bytes decoded, or <0 if an error occured.
         */
        inline int decode(const void *buf, int offset, int maxlen);

        /**
         * Retrieve the 64-bit fingerprint identifying the structure of the message.
         * Note that the fingerprint is the same for all instances of the same
         * message type, and is a fingerprint on the message type definition, not on
         * the message contents.
         */
        inline static int64_t getHash();

        /**
         * Returns "lcmt_iiwa_command"
         */
        inline static const char* getTypeName();

        // LCM support functions. Users should not call these
        inline int _encodeNoHash(void *buf, int offset, int maxlen) const;
        inline int _getEncodedSizeNoHash() const;
        inline int _decodeNoHash(const void *buf, int offset, int maxlen);
        inline static uint64_t _computeHash(const __lcm_hash_ptr *p);
};

int lcmt_iiwa_command::encode(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;
    int64_t hash = (int64_t)getHash();

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->_encodeNoHash(buf, offset + pos, maxlen - pos);
    if (tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int lcmt_iiwa_command::decode(const void *buf, int offset, int maxlen)
{
    int pos = 0, thislen;

    int64_t msg_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &msg_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (msg_hash != getHash()) return -1;

    thislen = this->_decodeNoHash(buf, offset + pos, maxlen - pos);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int lcmt_iiwa_command::getEncodedSize() const
{
    return 8 + _getEncodedSizeNoHash();
}

int64_t lcmt_iiwa_command::getHash()
{
    static int64_t hash = _computeHash(NULL);
    return hash;
}

const char* lcmt_iiwa_command::getTypeName()
{
    return "lcmt_iiwa_command";
}

int lcmt_iiwa_command::_encodeNoHash(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &this->utime, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_encode_array(buf, offset + pos, maxlen - pos, &this->num_joints, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    if(this->num_joints > 0) {
        tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->joint_position[0], this->num_joints);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    if(this->num_joints > 0) {
        tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->joint_torque[0], this->num_joints);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __double_encode_array(buf, offset + pos, maxlen - pos, &this->wrench[0], 6);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int lcmt_iiwa_command::_decodeNoHash(const void *buf, int offset, int maxlen)
{
    int pos = 0, tlen;

    tlen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &this->utime, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __int32_t_decode_array(buf, offset + pos, maxlen - pos, &this->num_joints, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    if(this->num_joints) {
        this->joint_position.resize(this->num_joints);
        tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->joint_position[0], this->num_joints);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    if(this->num_joints) {
        this->joint_torque.resize(this->num_joints);
        tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->joint_torque[0], this->num_joints);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __double_decode_array(buf, offset + pos, maxlen - pos, &this->wrench[0], 6);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int lcmt_iiwa_command::_getEncodedSizeNoHash() const
{
    int enc_size = 0;
    enc_size += __int64_t_encoded_array_size(NULL, 1);
    enc_size += __int32_t_encoded_array_size(NULL, 1);
    enc_size += __double_encoded_array_size(NULL, this->num_joints);
    enc_size += __double_encoded_array_size(NULL, this->num_joints);
    enc_size += __double_encoded_array_size(NULL, 6);
    return enc_size;
}

uint64_t lcmt_iiwa_command::_computeHash(const __lcm_hash_ptr *)
{
    uint64_t hash = 0x824cf99dc1a2d574LL;
    return (hash<<1) + ((hash>>63)&1);
}

}

#endif
