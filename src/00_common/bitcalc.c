 /* bitcalc.c:  utilities to deal with bits and masks

   Copyright (c) 2012-2016, Joerg Hoppe
   j_hoppe@t-online.de, www.retrocmp.com

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
   JOERG HOPPE BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


   14-Feb-2012  JH      created
*/


#define BITCALC_C_

#include <math.h>
#include <assert.h>

#include "bitcalc.h"

// get a bit mask of a given len (0..8)
unsigned char BitmaskFromLen8[9] =
{ 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff };


uint32_t BitmaskFromLen32[33] = {
		 0x00000000, //
			0x00000001, 0x00000003, 0x00000007, 0x0000000f, //
			0x0000001f, 0x0000003f, 0x0000007f, 0x000000ff, //
			0x000001ff, 0x000003ff, 0x000007ff, 0x00000fff, //
			0x00001fff, 0x00003fff, 0x00007fff, 0x0000ffff, //
			0x0001ffff, 0x0003ffff, 0x0007ffff, 0x000fffff, //
			0x001fffff, 0x003fffff, 0x007fffff, 0x00ffffff, //
			0x01ffffff, 0x03ffffff, 0x07ffffff, 0x0fffffff, //
			0x1fffffff, 0x3fffffff, 0x7fffffff, 0xffffffff //
};


uint64_t BitmaskFromLen64[65] =
{ 0x0000000000000000ULL, //
		0x0000000000000001ULL, 0x0000000000000003ULL, 0x0000000000000007ULL, 0x000000000000000fULL, //
		0x000000000000001fULL, 0x000000000000003fULL, 0x000000000000007fULL, 0x00000000000000ffULL, //
		0x00000000000001ffULL, 0x00000000000003ffULL, 0x00000000000007ffULL, 0x0000000000000fffULL, //
		0x0000000000001fffULL, 0x0000000000003fffULL, 0x0000000000007fffULL, 0x000000000000ffffULL, //
		0x000000000001ffffULL, 0x000000000003ffffULL, 0x000000000007ffffULL, 0x00000000000fffffULL, //
		0x00000000001fffffULL, 0x00000000003fffffULL, 0x00000000007fffffULL, 0x0000000000ffffffULL, //
		0x0000000001ffffffULL, 0x0000000003ffffffULL, 0x0000000007ffffffULL, 0x000000000fffffffULL, //
		0x000000001fffffffULL, 0x000000003fffffffULL, 0x000000007fffffffULL, 0x00000000ffffffffULL, //
		0x00000001ffffffffULL, 0x00000003ffffffffULL, 0x00000007ffffffffULL, 0x0000000fffffffffULL, //
		0x0000001fffffffffULL, 0x0000003fffffffffULL, 0x0000007fffffffffULL, 0x000000ffffffffffULL, //
		0x000001ffffffffffULL, 0x000003ffffffffffULL, 0x000007ffffffffffULL, 0x00000fffffffffffULL, //
		0x00001fffffffffffULL, 0x00003fffffffffffULL, 0x00007fffffffffffULL, 0x0000ffffffffffffULL, //
		0x0001ffffffffffffULL, 0x0003ffffffffffffULL, 0x0007ffffffffffffULL, 0x000fffffffffffffULL, //
		0x001fffffffffffffULL, 0x003fffffffffffffULL, 0x007fffffffffffffULL, 0x00ffffffffffffffULL, //
		0x01ffffffffffffffULL, 0x03ffffffffffffffULL, 0x07ffffffffffffffULL, 0x0fffffffffffffffULL, //
		0x1fffffffffffffffULL, 0x3fffffffffffffffULL, 0x7fffffffffffffffULL, 0xffffffffffffffffULL //
		};

// get the bit-reversed of a byte
// (swap lsb and msbs)
unsigned char BitmaskReversed[256] =
{ 0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, //
		0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0, //
		0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8, //
		0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8, //
		0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4, //
		0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4, //
		0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec, //
		0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc, //
		0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2, //
		0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2, //
		0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea, //
		0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa, //
		0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6, //
		0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6, //
		0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee, //
		0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe, //
		0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1, //
		0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1, //
		0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9, //
		0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9, //
		0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5, //
		0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5, //
		0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed, //
		0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd, //
		0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3, //
		0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3, //
		0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb, //
		0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb, //
		0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7, //
		0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7, //
		0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, //
		0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff //
		};

/*
 * BitsMirrored:
 * bit[0] -> bit[bitlen-1], bit[1] -> bit[bitlen-2]
 * Optimized with byte table
 */
unsigned char BitsMirrored[256] =
{ 0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0,
		0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78,
		0xF8, 0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4,
		0x74, 0xF4, 0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C,
		0xBC, 0x7C, 0xFC, 0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2,
		0x32, 0xB2, 0x72, 0xF2, 0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A,
		0xDA, 0x3A, 0xBA, 0x7A, 0xFA, 0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96,
		0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6, 0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E,
		0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE, 0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1,
		0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1, 0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69,
		0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9, 0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5,
		0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5, 0x0D, 0x8D, 0x4D, 0xCD, 0x2D,
		0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD, 0x03, 0x83, 0x43, 0xC3,
		0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3, 0x0B, 0x8B, 0x4B,
		0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB, 0x07, 0x87,
		0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7, 0x0F,
		0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF };


/* calc the bit reverse table
 #include <stdlib.h>
 #include <stdio.h>

 main()
 {
 int i, j, tmp;

 for (i = 0; i <= 255; i++)
 {
 // calc the 8 bit  bit-reversed of i

 tmp = 0;
 for (j = 0; j < 8; j++)
 {
 tmp <<= 1;
 if ((i >> j) & 1)
 tmp |= 1;
 }
 printf("0x%02x, ", tmp);
 if (i % 8 == 7)
 printf("\n");
 }
 printf("\n");
 }
*/

// how many digits has the decimal representation of 2^n?
// example: n= 10, 2^10 = 1024 -> 4 digits
int DecimalDigitLenFromLen64[65] = {
 1 ,  1 ,  1 ,  1 ,  2 ,  2 ,  2 ,  3 ,  3 ,  3 ,  4 ,  4 ,  4 ,  4 ,  5 ,  5 , //
 5 ,  6 ,  6 ,  6 ,  7 ,  7 ,  7 ,  7 ,  8 ,  8 ,  8 ,  9 ,  9 ,  9 , 10 , 10 , //
10 , 10 , 11 , 11 , 11 , 12 , 12 , 12 , 13 , 13 , 13 , 13 , 14 , 14 , 14 , 15 , //
15 , 15 , 16 , 16 , 16 , 16 , 17 , 17 , 17 , 18 , 18 , 18 , 19 , 19 , 19 , 19 , //
20 } ;

/* calc the bit DecimalDigitLenFromLen64 table
 *  compile with
 *  	cc bitcalc.c -lm ; ./a.out >
 *

 #include <stdlib.h>
 #include <stdio.h>

 main()
 {
 // len is trunc(lg(2^n))+1  and lg(x) = log(x)/log(10)
	int i ;
	double tmp ;
	double twoexp = 1;

	printf ("int DecimalDigitLenFromLen64[65] = {\n") ;

	for (i = 0; i <= 64; i++)
	{
		tmp = floor((log(twoexp) / log(10))) + 1;
		twoexp *= 2;
printf("%2.0f", tmp);
if (i < 64) printf(", ") ;
 if (i % 16 == 15)
 printf("\n");
 }
 printf("} ; \n");

 }
*/

uint64_t mirror_bits(uint64_t value, unsigned bitlen)
{
    uint64_t result;
    unsigned i;
    unsigned byte_count; // value uses this much bytes ...
    unsigned extra_bits; // and so much msb bits are unused then
//  u_int8_t    b ;
    uint8_t b[8]; // temp byte array. No unions, be independent of endianess!

    byte_count = (bitlen + 7) >> 3; // 1..8 -> 1, 9..16 -> 2, ...
    extra_bits = (byte_count << 3) - bitlen;

    // separate value into bytes, and calc byte mirror
    switch (byte_count) {
    case 8:
        b[7] = (value >> 56) & 0xff; // no break: fall through!
    case 7:
        b[6] = (value >> 48) & 0xff;
    case 6:
        b[5] = (value >> 40) & 0xff;
    case 5:
        b[4] = (value >> 32) & 0xff;
    case 4:
        b[3] = (value >> 24) & 0xff;
    case 3:
        b[2] = (value >> 16) & 0xff;
    case 2:
        b[1] = (value >> 8) & 0xff;
    case 1:
        b[0] = (value >> 0) & 0xff;
    }

    // mount result_ byte[0] -> byte[7],
    result = 0;
    for (i = 0; i < byte_count; i++)
        result = (result << 8) | BitsMirrored[b[i]];

    // extra msbs are now extra lsbs
    return result >> extra_bits;
}


/*
 * find index of lowest set or or reset bit ('bitval')
 * -1, if not found
 */
int find_lowest_bit64(uint64_t value, int bitval)
{
	int i;
	for (i = 0; i < 64; i++)
	{
		if ((value & 1) == bitval)
			return i;
		value >>= 1;
	}
	return -1;
}

/*
 * find index of highest bit set.
 * result: index ( 0 for 0x0001, 1 for 0x0002, 2 for 0x0004, ... )
 * -1, value == 0
 */
int get_msb_index64(uint64_t value)
{
	int i;
	for (i = 0; i < 64; i++)
	{
		if (value == 0)
			return (i - 1);
		value >>= 1;
	}
	return 63;
}

// bitmask is a left shifted bit field, wich is moutned into buffer so, that
// bitmask.bit[0] -> buffer.bit[buffer_bitoffset]
uint64_t mount_bits_to_mask64(uint64_t buffer, uint64_t bitmask, int bitmask_leftshift,
		int buffer_bitoffset)
{
	uint64_t tmp;
	tmp = (bitmask >> bitmask_leftshift) << buffer_bitoffset;
	return buffer | tmp;
}

// write the bytes, which form a 64 bit integer, to the byte array "buffer"
// lsb first, only the "bytecount" lowest bytes
// Example: value= 0x123456789a, bytecount = 6
// buffer[0] = 9a, buffer[1] = 78, 56, 34, 12, buffer[5]  = 00
void encode_uint64_to_bytes(unsigned char *buffer, uint64_t value, unsigned bytecount)
{
	assert(bytecount < 9);
	// loop unrolled
	if (bytecount > 0)
		buffer[0] = value & 0xff;
	if (bytecount > 1)
		buffer[1] = (value >> 8) & 0xff;
	if (bytecount > 2)
		buffer[2] = (value >> 16) & 0xff;
	if (bytecount > 3)
		buffer[3] = (value >> 24) & 0xff;
	if (bytecount > 4)
		buffer[4] = (value >> 32) & 0xff;
	if (bytecount > 5)
		buffer[5] = (value >> 36) & 0xff;
	if (bytecount > 6)
		buffer[6] = (value >> 40) & 0xff;
	if (bytecount > 7)
		buffer[7] = (value >> 44) & 0xff;
}

// build a 64 bit integer from the  byte array "buffer"
// lsb first, only the "bytecount" lowest bytes
// Example buffer[0] = 9a, buffer[1] = 78, 56, 34, Buffer[4] = 12, buffer[5]  = 00, bytecount = 4
// => result =  0x3456789a
uint64_t decode_uint64_from_bytes(unsigned char *buffer, unsigned bytecount)
{
	uint64_t value = 0;
	assert(bytecount < 9);
	// loop unrolled
	if (bytecount > 0)
		value |= (uint64_t) buffer[0];
	if (bytecount > 1)
		value |= (uint64_t) buffer[1] << 8;
	if (bytecount > 2)
		value |= (uint64_t) buffer[2] << 16;
	if (bytecount > 3)
		value |= (uint64_t) buffer[3] << 24;
	if (bytecount > 4)
		value |= (uint64_t) buffer[4] << 32;
	if (bytecount > 5)
		value |= (uint64_t) buffer[5] << 36;
	if (bytecount > 6)
		value |= (uint64_t) buffer[6] << 40;
	if (bytecount > 7)
		value |= (uint64_t) buffer[7] << 44;
	return value;
}

// how long is decimal/octal/hex representation?

int digitcount_from_bitlen(int radix, int bitlen)
{
	assert(bitlen <= 64);
	assert(radix ==10 || radix==8 || radix==16);

	if (radix == 10)
		return DecimalDigitLenFromLen64[bitlen];
	else if (radix == 8)
		return (bitlen + 2) / 3; // count of octal digits
	else if (radix == 16)
		return (bitlen + 3) / 4; // count of hex digits
	return 0 ; // not reached, assert()
}

