#include "BytesUtil.h"

/**
 * @brief  get the endian of the system using the data ENDIA_JUDGE_DATA.
 *
 * @param data : ENDIA_JUDGE_DATA bytes come from other system.
 * @return Endian
 *
 */
Endian getEndian(const bu_byte * data)
{
    if (data[0] == 0x04)
    {
        return LITTLE_ENDIAN;
    }
    else
    {
        return BIG_ENDIAN;
    }
}

/**
 * @brief get self endian.
 *
 * @return Endian
 */
Endian getSelfEndian()
{
    bu_uint32 data = ENDIA_JUDGE_DATA;
    bu_byte *p = (bu_byte *)&data;
    if (p[0] == 0x04)
    {
        return LITTLE_ENDIAN;
    }
    else
    {
        return BIG_ENDIAN;
    }
}

/* @section 1: rvalue method */
/**
 * @brief convert bytes[0-3] to a float.
 *
 * @param bytes byes data
 * @param endian
 * @return bu_float
 *
 * @note the bytes data must be at least  4 bytes.
 */
bu_float bytes2floatr(const bu_byte *bytes, bu_bool change_endian)
{
    union
    {
        bu_float f;
        bu_byte b[4];
    } u;
    if (change_endian)
    {
        REVERSE_4_BYTES_P(u.b, bytes);
    }
    else
    {
        *((bu_float*)&u) = *((bu_float*)bytes);
    }
    return u.f;
}

/**
 * @brief convert bytes[0-8] to a double.
 *
 * @param bytes byes data
 * @param endian
 * @return bu_float
 *
 * @note the bytes data must be at least  8 bytes.
 */
bu_double bytes2doubler(const bu_byte *bytes, bu_bool change_endian)
{
    union
    {
        bu_double d;
        bu_byte b[8];
    } u;
    if (change_endian)
    {
        REVERSE_2_BYTES_P(u.b, bytes);
    }
    else
    {
        *((bu_double*)&u) = *((bu_double*)bytes);
    }
    return u.d;
}

/**
 * @brief convert bytes[0-2] to a int16.
 *
 * @param bytes byes data
 * @param endian
 * @return bu_double
 *
 * @note the bytes data must be at least  2 bytes.
 */
bu_int16 bytes2int16r(const bu_byte *bytes, bu_bool change_endian)
{
    union
    {
        bu_int16 i;
        bu_byte b[2];
    } u;
    if (change_endian)
    {
        REVERSE_2_BYTES_P(u.b, bytes);
    }
    else
    {
        *((bu_int16*)&u) = *((bu_int16*)bytes);
    }
    return u.i;
}

/**
 * @brief convert bytes[0-4] to a int32.
 *
 * @param bytes byes data
 * @param endian
 * @return bu_int16
 *
 * @note the bytes data must be at least  be 4 bytes.
 */
bu_int32 bytes2int32r(const bu_byte *bytes, bu_bool change_endian)
{
    union
    {
        bu_int32 i;
        bu_byte b[4];
    } u;
    if (change_endian)
    {
        REVERSE_4_BYTES_P(u.b, bytes);
    }
    else
    {
        *((bu_int32*)&u) = *((bu_int32*)bytes);
    }
    return u.i;
}

/**
 * @brief convert bytes[0-8] to a int64.
 *
 * @param bytes byes data
 * @param endian
 * @return bu_int64
 *
 * @note the bytes data must be at least  be 8 bytes.
 */
bu_int64 bytes2int64r(const bu_byte *bytes, bu_bool change_endian)
{
    union
    {
        bu_int64 i;
        bu_byte b[8];
    } u;
    if (change_endian)
    {
        REVERSE_8_BYTES_P(u.b, bytes);
    }
    else
    {
        *((bu_int64*)&u) = *((bu_int64*)bytes);
    }
    return u.i;
}

/* @section 2: pointer method */
/**
 * @brief convert bytes[0-3] to a float.
 *
 * @param bytes byes data
 * @param dst : the pointer to the variable to be assigned.
 * @param endian
 * @return void
 *
 * @note the bytes data must be at least  4 bytes.
 */
void bytes2floatp(const bu_byte *bytes, bu_float *dst, bu_bool change_endian)
{
    if (change_endian)
    {
        REVERSE_4_BYTES_P(dst, bytes);
    }
    else
    {
        *((bu_float*)dst) = *((bu_float*)bytes);
    }
}

/**
 * @brief convert bytes[0-8] to a double.
 *
 * @param bytes byes data
 * @param dst : the pointer to the variable to be assigned.
 * @param endian
 * @return void
 *
 * @note the bytes data must be at least  8 bytes.
 */
void bytes2doublep(const bu_byte *bytes, bu_double *dst, bu_bool change_endian)
{
    if (change_endian)
    {
        REVERSE_8_BYTES_P(dst, bytes);
    }
    else
    {
        *((bu_double*)dst) = *((bu_double*)bytes);
    }
}

/**
 * @brief convert bytes[0-2] to a int16.
 *
 * @param bytes byes data
 * @param dst : the pointer to the variable to be assigned.
 * @param endian
 * @return void
 *
 * @note the bytes data must be at least  2 bytes.
 */
void bytes2int16p(const bu_byte *bytes, bu_int16 *dst, bu_bool change_endian)
{
    if (change_endian)
    {
        REVERSE_2_BYTES_P(dst, bytes);
    }
    else
    {
        *((bu_int16*)dst) = *((bu_int16*)bytes);
    }
}

/**
 * @brief convert bytes[0-4] to a int32.
 *
 * @param bytes byes data
 * @param dst : the pointer to the variable to be assigned.
 * @param endian
 * @return void
 *
 * @note the bytes data must be at least  be 4 bytes.
 */
void bytes2int32p(const bu_byte *bytes, bu_int32 *dst, bu_bool change_endian)
{
    if (change_endian)
    {
        REVERSE_4_BYTES_P(dst, bytes);
    }
    else
    {
        *((bu_int32*)dst) = *((bu_int32*)bytes);
    }
}

/**
 * @brief convert bytes[0-8] to a int64.
 *
 * @param bytes byes data
 * @param dst : the pointer to the variable to be assigned.
 * @param endian
 * @return void
 *
 * @note the bytes data must be at least  be 8 bytes.
 */
void bytes2int64p(const bu_byte *bytes, bu_int64 *dst, bu_bool change_endian)
{
    if (change_endian)
    {
        REVERSE_8_BYTES_P(dst, bytes);
    }
    else
    {
        *((bu_int64*)dst) = *((bu_int64*)bytes);
    }
}

/* @section 3: bytes reverse */
/**
 * @brief 2 bytes reverse.
 *
 * @param bytes byes data
 * @param dst : the pointer to a byte * which will be assigned the reversed bytes.
 * @return void
 *
 * @note the bytes data must be at least  2 bytes.
 */
void reverse2bytes(const bu_byte *bytes, bu_byte *dst)
{
    REVERSE_2_BYTES_P(dst, bytes);
}

/**
 * @brief 4 bytes reverse.
 *
 * @param bytes byes data
 * @param dst : the pointer to a byte * which will be assigned the reversed bytes.
 * @return void
 *
 * @note the bytes data must be at least  4 bytes.
 */
void reverse4bytes(const bu_byte *bytes, bu_byte *dst)
{
    REVERSE_4_BYTES_P(dst, bytes);
}

/**
 * @brief 8 bytes reverse.
 *
 * @param bytes byes data
 * @param dst : the pointer to a byte * which will be assigned the reversed bytes.
 * @return void
 *
 * @note the bytes data must be at least 8 bytes.
 */
void reverse8bytes(const bu_byte *bytes, bu_byte *dst)
{
    REVERSE_8_BYTES_P(dst, bytes);
}

/**
 * @brief n bytes reverse.
 *
 * @param bytes byes data
 * @param dst : the pointer to a byte * which will be assigned the reversed bytes.
 * @param n : the number of bytes to be reversed.
 * @return void
 *
 * @note the bytes data must be at least  n bytes.
 */
void reverseNbytes(const bu_byte *bytes, bu_byte *dst, bu_size_t n)
{
    bu_size_t i = 0;
    for (i = 0; i < n; i++)
    {
        dst[i] = bytes[n - i - 1];
    }
}

/* section 4: convert data to bytes */
/**
 * @brief convert a float to bytes.
 *
 * @param f : the float to be converted.
 * @param dst : the pointer to a byte * which will be assigned the converted bytes.
 * @param endian
 * @return void
 *
 * @note the bytes data will be at least 4 bytes space.
 */
void float2bytes(bu_float f, bu_byte *dst, bu_bool change_endian)
{
    bu_byte *p = (bu_byte *)&f;
    if (change_endian)
    {
        REVERSE_4_BYTES_P(dst, p);
    }
    else
    {
        *((bu_float*)dst) = f;
    }
}

/**
 * @brief convert a double to bytes.
 *
 * @param d : the double to be converted.
 * @param dst : the pointer to a byte * which will be assigned the converted bytes.
 * @param endian
 * @return void
 *
 * @note the bytes data will be at least 8 bytes space.
 */
void double2bytes(bu_double d, bu_byte *dst, bu_bool change_endian)
{
    bu_byte *p = (bu_byte *)&d;
    if (change_endian)
    {
        REVERSE_8_BYTES_P(dst, p);
    }
    else
    {
        *((bu_double*)dst) = d;
    }
}

/**
 * @brief convert a int16 to bytes.
 *
 * @param i : the int16 to be converted.
 * @param dst : the pointer to a byte * which will be assigned the converted bytes.
 * @param endian
 * @return void
 *
 * @note the bytes data will be at least 2 bytes space.
 */
void int162bytes(bu_int16 i, bu_byte *dst, bu_bool change_endian)
{
    bu_byte *p = (bu_byte *)&i;
    if (change_endian)
    {
        REVERSE_2_BYTES_P(dst, p);
    }
    else
    {
        *((bu_int16*)dst) = i;
    }
}

/**
 * @brief convert a int32 to bytes.
 *
 * @param i : the int32 to be converted.
 * @param dst : the pointer to a byte * which will be assigned the converted bytes.
 * @param endian
 * @return void
 *
 * @note the bytes data will be at least 4 bytes space.
 */
void int322bytes(bu_int32 i, bu_byte *dst, bu_bool change_endian)
{
    bu_byte *p = (bu_byte *)&i;
    if (change_endian)
    {
        REVERSE_4_BYTES_P(dst, p);
    }
    else
    {
        *((bu_int32*)dst) = i;
    }
}

/**
 * @brief convert a int64 to bytes.
 *
 * @param i : the int64 to be converted.
 * @param dst : the pointer to a byte * which will be assigned the converted bytes.
 * @param endian
 * @return void
 *
 * @note the bytes data will be at least 8 bytes space.
 */
void int642bytes(bu_int64 i, bu_byte *dst, bu_bool change_endian)
{
    bu_byte *p = (bu_byte *)&i;
    if (change_endian)
    {
        REVERSE_8_BYTES_P(dst, p);
    }
    else
    {
        *((bu_int64*)dst) = i;
    }
}

/* @section 5: bit reverse */
/*
0xA : B1010
0x5 : B0101
0xC : B1100
0x3 : B0011
0xF0 : B1111 0000
0x0F : B0000 1111
Iterate from long to short
eg. 8 bit reverse.
abcd efgh -> efgh abcd -> ghef cdab -> hgfe dcba
1.
abcd efgh -> efgh abcd
2.
ef00 ab00 -> 00ef 00ab
00gh 00cd -> gh00 cd00
3.
g0e0 c0a0 -> 0g0e 0c0a
0h0f 0d0b -> h0f0 d0b0

or iterate from short to long
eg. 8 bit reverse.
abcd efgh -> badc fehg -> dcba hgfe -> hgfe dcba
*/
/**
 * @brief reverse the bits of a byte.
 *
 * @param data original byte
 * @return bit reversed byte
 */
bu_byte bit_reverse8(bu_byte data)
{
    data=(data>>4)|(data<<4);
	data=((data&0xcc)>>2)|((data&0x33)<<2);
	data=((data&0xaa)>>1)|((data&0x55)<<1);
    return data;
}


/**
 * @brief reverse the bits of a uint16.
 *
 * @param data original uint16 data
 * @return bit reversed uint16
 */
bu_uint16 bit_reverse16(bu_uint16 data)
{
    data=(data>>8)|(data<<8);
    data=((data&0xf0f0)>>4)|((data&0x0f0f)<<4);
    data=((data&0xcccc)>>2)|((data&0x3333)<<2);
    data=((data&0xaaaa)>>1)|((data&0x5555)<<1);
    return data;
}

/**
 * @brief reverse the bits of a uint32.
 *
 * @param data original uint32 data
 * @return bit reversed uint32
 */
bu_uint32 bit_reverse32(bu_uint32 data)
{
    data = (((data & 0xaaaaaaaaL) >> 1) | ((data & 0x55555555L) << 1));
    data = (((data & 0xccccccccL) >> 2) | ((data & 0x33333333L) << 2));
    data = (((data & 0xf0f0f0f0L) >> 4) | ((data & 0x0f0f0f0fL) << 4));
    data = (((data & 0xff00ff00L) >> 8) | ((data & 0x00ff00ffL) << 8));
    return ((data >> 16) | (data << 16));
}

/**
 * @brief reverse the bits of a uint64.
 *
 * @param data original uint64 data
 * @return bit reversed uint64
 */
bu_uint64 bit_reverse64(bu_uint64 data)
{
    data = (((data & 0xaaaaaaaaaaaaaaaaLL) >> 1) | ((data & 0x5555555555555555LL) << 1));
    data = (((data & 0xccccccccccccccccLL) >> 2) | ((data & 0x3333333333333333LL) << 2));
    data = (((data & 0xf0f0f0f0f0f0f0f0LL) >> 4) | ((data & 0x0f0f0f0f0f0f0f0fLL) << 4));
    data = (((data & 0xff00ff00ff00ff00LL) >> 8) | ((data & 0x00ff00ff00ff00ffLL) << 8));
    data = (((data & 0xffff0000ffff0000LL) >> 16)| ((data & 0x0000ffff0000ffffLL) << 16));
    return ((data >> 32) | (data << 32));
}
