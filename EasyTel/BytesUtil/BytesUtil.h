#ifndef _BYTES_UTIL_H_
#define _BYTES_UTIL_H_
#ifdef __cplusplus
extern "C" {
#endif
/*
Naming Rule:
1. Categorize by the method of getting the result.
<data type> bytes2<data type><method>(const byte* bytes,xxx);
<data type>: int32, float, double, etc.
<method>: r: rvalue, assign the result to the variable by return value.
          p: pointer, assign the result to the variable by pass variable's pointer to parameter.

You can quickly search "@section" int IDE to see the different categories of methods

2. spuuort : at least c99,only using stbu_bool std lib.
*/

//Select the appropriate platform nefore writing other code,the default configuration is 32-bit machines
// #define _8_BIT_SYSTEM
// #define _16_BIT_SYSTEM
// #define _32_BIT_SYSTEM
// #define _64_BIT_SYSTEM
#define _32_BIT_SYSTEM

#ifdef _8_BIT_SYSTEM //TODO : the following definitions are for 8-bit maybe wrong
#define bu_uint8 unsigned char
#define bu_int8 char
#define bu_uint16 unsigned short
#define bu_int16 short
#define bu_uint32 unsigned long
#define bu_int32 long
#define bu_uint64 unsigned long long
#define bu_int64 long long
#define bu_float float
#define bu_double double
#define bu_long_double long double

#define bu_byte bu_uint8
#define bu_word bu_uint16
#define bu_dword bu_uint32
#define bu_qword bu_uint64

#define bu_size_t bu_uint32
#endif

#ifdef _16_BIT_SYSTEM
#define bu_uint8 unsigned char
#define bu_int8 char
#define bu_uint16 unsigned short
#define bu_int16 short
#define bu_uint32 unsigned long
#define bu_int32 long
#define bu_uint64 unsigned long long
#define bu_int64 long long
#define bu_float float
#define bu_double double
#define bu_long_double long double

#define bu_byte bu_uint8
#define bu_word bu_uint16
#define bu_dword bu_uint32
#define bu_qword bu_uint64

#define bu_size_t bu_uint32
#endif

#ifdef _32_BIT_SYSTEM
#define bu_uint8 unsigned char
#define bu_int8 char
#define bu_uint16 unsigned short
#define bu_int16 short
#define bu_uint32 unsigned int
#define bu_int32 int
#define bu_uint64 unsigned long long
#define bu_int64 long long
#define bu_float float
#define bu_double double
#define bu_long_double long double

#define bu_byte bu_uint8
#define bu_word bu_uint16
#define bu_dword bu_uint32
#define bu_qword bu_uint64

#define bu_size_t bu_uint32
#endif

#ifdef _64_BIT_SYSTEM
#define bu_uint8 unsigned char
#define bu_int8 char
#define bu_uint16 unsigned short
#define bu_int16 short
#define bu_uint32 unsigned int
#define bu_int32 int
#define bu_uint64 unsigned long long
#define bu_int64 long long
#define bu_float float
#define bu_double double
#define bu_long_double long double

#define bu_byte bu_uint8
#define bu_word bu_uint16
#define bu_dword bu_uint32
#define bu_qword bu_uint64

#define bu_size_t bu_uint32
#endif


#include <stdbool.h>
#define bu_bool bool
#define bu_true true
#define bu_false false

typedef enum {
    LITTLE_ENDIAN = 0,
    BIG_ENDIAN = 1
}Endian;

#define ENDIA_JUDGE_DATA 0x20220204

/**
 * @brief  get the endian of the system using the data ENDIA_JUDGE_DATA.
 *
 * @param data : ENDIA_JUDGE_DATA bytes come from other system.
 * @return Endian
 *
 */
Endian getEndian(const bu_byte * data);

/**
 * @brief get self endian.
 * 
 * @return Endian
 */
Endian getSelfEndian();

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
bu_float bytes2floatr(const bu_byte* bytes,bu_bool change_endian);

/**
 * @brief convert bytes[0-8] to a double.
 * 
 * @param bytes byes data
 * @param endian 
 * @return bu_float 
 * 
 * @note the bytes data must be at least  8 bytes.
 */
bu_double bytes2doubler(const bu_byte* bytes,bu_bool change_endian);

/**
 * @brief convert bytes[0-2] to a int16.
 * 
 * @param bytes byes data
 * @param endian 
 * @return bu_double 
 * 
 * @note the bytes data must be at least  2 bytes.
 */
bu_int16 bytes2int16r(const bu_byte* bytes,bu_bool change_endian);

/**
 * @brief convert bytes[0-4] to a int32.
 * 
 * @param bytes byes data
 * @param endian 
 * @return bu_int16 
 * 
 * @note the bytes data must be at least  be 4 bytes.
 */
bu_int32 bytes2int32r(const bu_byte* bytes,bu_bool change_endian);

/**
 * @brief convert bytes[0-8] to a int64.
 * 
 * @param bytes byes data
 * @param endian
 * @return bu_int64
 * 
 * @note the bytes data must be at least  be 8 bytes.
 */
bu_int64 bytes2int64r(const bu_byte* bytes,bu_bool change_endian);

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
void bytes2floatp(const bu_byte* bytes,bu_float *dst,bu_bool change_endian);

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
void bytes2doublep(const bu_byte* bytes,bu_double *dst,bu_bool change_endian);


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
void bytes2int16p(const bu_byte* bytes,bu_int16 *dst,bu_bool change_endian);


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
void bytes2int32p(const bu_byte* bytes,bu_int32 *dst,bu_bool change_endian);


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
void bytes2int64p(const bu_byte* bytes,bu_int64 *dst,bu_bool change_endian);


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
void reverse2bytes(const bu_byte* bytes,bu_byte* dst);


/**
 * @brief 4 bytes reverse.
 * 
 * @param bytes byes data
 * @param dst : the pointer to a byte * which will be assigned the reversed bytes.
 * @return void
 * 
 * @note the bytes data must be at least  4 bytes.
 */
void reverse4bytes(const bu_byte* bytes,bu_byte* dst);


/**
 * @brief 8 bytes reverse.
 * 
 * @param bytes byes data
 * @param dst : the pointer to a byte * which will be assigned the reversed bytes.
 * @return void
 * 
 * @note the bytes data must be at least 8 bytes.
 */
void reverse8bytes(const bu_byte* bytes,bu_byte* dst);


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
void reverseNbytes(const bu_byte* bytes,bu_byte* dst,bu_size_t n);


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
void float2bytes(bu_float f,bu_byte* dst,bu_bool change_endian);


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
void double2bytes(bu_double d,bu_byte* dst,bu_bool change_endian);


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
void int162bytes(bu_int16 i,bu_byte* dst,bu_bool change_endian);


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
void int322bytes(bu_int32 i,bu_byte* dst,bu_bool change_endian);


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
void int642bytes(bu_int64 i,bu_byte* dst,bu_bool change_endian);

/* @section 5: bit reverse */

/**
 * @brief reverse the bits of a byte.
 * 
 * @param data original byte
 * @return bit reversed byte 
 */
bu_byte bit_reverse8(bu_byte data);

/**
 * @brief reverse the bits of a uint16.
 * 
 * @param data original uint16 data
 * @return bit reversed uint16
 */
bu_uint16 bit_reverse16(bu_uint16 data);

/**
 * @brief reverse the bits of a uint32.
 * 
 * @param data original uint32 data
 * @return bit reversed uint32 
 */
bu_uint32 bit_reverse32(bu_uint32 data);


/**
 * @brief reverse the bits of a uint64.
 * 
 * @param data original uint64 data
 * @return bit reversed uint64
 */
bu_uint64 bit_reverse64(bu_uint64 data);

/* @section 6: unsigned int convert macro */
#define bytes2uint16r(bytes,change_endian) (bu_uint16)(bytes2int16r((bytes),(change_endian)))
#define bytes2uint32r(bytes,change_endian) (bu_uint32)(bytes2int32r((bytes),(change_endian)))
#define bytes2uint64r(bytes,change_endian) (bu_uint64)(bytes2int64r((bytes),(change_endian)))

#define bytes2uint16p(bytes,dst,change_endian) (bytes2int16p((bytes),(bu_int16*)(dst),(change_endian)))
#define bytes2uint32p(bytes,dst,change_endian) (bytes2int32p((bytes),(bu_int32*)(dst),(change_endian)))
#define bytes2uint64p(bytes,dst,change_endian) (bytes2int64p((bytes),(bu_int64*)(dst),(change_endian)))

/* @section end: Summarize all methods into comment */
/*
Endian getEndian(bu_uint32 data);
Endian getSelfEndian();

bu_float bytes2floatr(const bu_byte* bytes,bu_bool change_endian);
bu_double bytes2doubler(const bu_byte* bytes,bu_bool change_endian);
bu_int16 bytes2int16r(const bu_byte* bytes,bu_bool change_endian);
bu_int32 bytes2int32r(const bu_byte* bytes,bu_bool change_endian);
bu_int64 bytes2int64r(const bu_byte* bytes,bu_bool change_endian);

void bytes2floatp(const bu_byte* bytes,bu_float *dst,bu_bool change_endian);
void bytes2doublep(const bu_byte* bytes,bu_double *dst,bu_bool change_endian);
void bytes2int16p(const bu_byte* bytes,bu_int16 *dst,bu_bool change_endian);
void bytes2int32p(const bu_byte* bytes,bu_int32 *dst,bu_bool change_endian);
void bytes2int64p(const bu_byte* bytes,bu_int64 *dst,bu_bool change_endian);

void reverse2bytes(const bu_byte* bytes,bu_byte* dst);
void reverse4bytes(const bu_byte* bytes,bu_byte* dst);
void reverse8bytes(const bu_byte* bytes,bu_byte* dst);
void reverseNbytes(const bu_byte* bytes,bu_byte* dst,bu_size_t n);

void float2bytes(bu_float f,bu_byte* dst,bu_bool change_endian);
void double2bytes(bu_double d,bu_byte* dst,bu_bool change_endian);
void int162bytes(bu_int16 i,bu_byte* dst,bu_bool change_endian);
void int322bytes(bu_int32 i,bu_byte* dst,bu_bool change_endian);
void int642bytes(bu_int64 i,bu_byte* dst,bu_bool change_endian);

bu_byte bit_reverse8(bu_byte data);
bu_uint16 bit_reverse16(bu_uint16 data);
bu_uint32 bit_reverse32(bu_uint32 data);
bu_uint64 bit_reverse64(bu_uint64 data);
*/


#define REVERSE_2_BYTES_P(dst, src) \
    do { \
        dst[0] = src[1]; \
        dst[1] = src[0]; \
    } while(0)

#define REVERSE_4_BYTES_P(dst, src) \
    do { \
        dst[0] = src[3]; \
        dst[1] = src[2]; \
        dst[2] = src[1]; \
        dst[3] = src[0]; \
    } while(0)

#define REVERSE_8_BYTES_P(dst, src) \
    do{ \
        dst[0] = src[7]; \
        dst[1] = src[6]; \
        dst[2] = src[5]; \
        dst[3] = src[4]; \
        dst[4] = src[3]; \
        dst[5] = src[2]; \
        dst[6] = src[1]; \
        dst[7] = src[0]; \
    } while(0)

#define REVERSE_16_BYTES_P(dst, src) \
    do{ \
        dst[0] = src[15]; \
        dst[1] = src[14]; \
        dst[2] = src[13]; \
        dst[3] = src[12]; \
        dst[4] = src[11]; \
        dst[5] = src[10]; \
        dst[6] = src[9]; \
        dst[7] = src[8]; \
        dst[8] = src[7]; \
        dst[9] = src[6]; \
        dst[10] = src[5]; \
        dst[11] = src[4]; \
        dst[12] = src[3]; \
        dst[13] = src[2]; \
        dst[14] = src[1]; \
        dst[15] = src[0]; \
    } while(0)
    
#define REVERSE_2_BYTES_R(value) (((value) >> 8) | ((value) << 8))

#define REVERSE_4_BYTES_R(value) (((value) >> 24) | (((value) >> 8) & 0x0000FF00L) | (((value) << 8) & 0x00FF0000L) | ((value) << 24))

#define REVERSE_8_BYTES_R(value) (((value) >> 56) | (((value) >> 40) & 0x000000000000FF00LL) | (((value) >> 24) & 0x0000000000FF0000LL) | (((value) >> 8) & 0x00000000FF000000LL) | (((value) << 8) & 0x000000FF00000000LL) | (((value) << 24) & 0x0000FF0000000000LL) | (((value) << 40) & 0x00FF000000000000LL) | ((value) << 56))

#define CAST_2_CONST_BYTE_P(obj) ((const bu_byte *)(obj))

#ifdef __cplusplus
}
#endif

#endif // _BYTES_UTIL_H_