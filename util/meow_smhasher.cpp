/* ========================================================================

   meow_smhasher.cpp - smhasher-compatible calls for the Meow hash
   (C) Copyright 2018-2019 by Molly Rocket, Inc. (https://mollyrocket.com)
   
   See https://mollyrocket.com/meowhash for license and details.
   
   ======================================================================== */

#include "meow_hash_x64_aesni.h"

//
// NOTE(casey): 128-bit wide implementation (Meow1)
//

// TODO(casey): At some point we really need SMHasher to have a spec that
// says different hashes take different size seeds.  This duplicate
// seed is here just to make sure we have 128-bytes to seed, since SMHasher
// gives us at most 4.
static meow_u8 MeowSMHasherSeed[128] =
{
    0x32, 0x43, 0xF6, 0xA8, 0x88, 0x5A, 0x30, 0x8D,
	0x31, 0x31, 0x98, 0xA2, 0xE0, 0x37, 0x07, 0x34,
	0x4A, 0x40, 0x93, 0x82, 0x22, 0x99, 0xF3, 0x1D,
	0x00, 0x82, 0xEF, 0xA9, 0x8E, 0xC4, 0xE6, 0xC8,
	0x94, 0x52, 0x82, 0x1E, 0x63, 0x8D, 0x01, 0x37,
	0x7B, 0xE5, 0x46, 0x6C, 0xF3, 0x4E, 0x90, 0xC6,
	0xCC, 0x0A, 0xC2, 0x9B, 0x7C, 0x97, 0xC5, 0x0D,
	0xD3, 0xF8, 0x4D, 0x5B, 0x5B, 0x54, 0x70, 0x91,
	0x79, 0x21, 0x6D, 0x5D, 0x98, 0x97, 0x9F, 0xB1,
	0xBD, 0x13, 0x10, 0xBA, 0x69, 0x8D, 0xFB, 0x5A,
	0xC2, 0xFF, 0xD7, 0x2D, 0xBD, 0x01, 0xAD, 0xFB,
	0x7B, 0x8E, 0x1A, 0xFE, 0xD6, 0xA2, 0x67, 0xE9,
	0x6B, 0xA7, 0xC9, 0x04, 0x5F, 0x12, 0xC7, 0xF9,
	0x92, 0x4A, 0x19, 0x94, 0x7B, 0x39, 0x16, 0xCF,
	0x70, 0x80, 0x1F, 0x2E, 0x28, 0x58, 0xEF, 0xC1,
	0x66, 0x36, 0x92, 0x0D, 0x87, 0x15, 0x74, 0xE6
};

void
Meow_32_SMHasher(const void * key, int len, int unsigned seed, void * out)
{
    *(int unsigned *)MeowSMHasherSeed = seed;
    meow_u128 Result = MeowHash(MeowSMHasherSeed, len, (void *)key);
    *(meow_u32 *)out = MeowU32From(Result, 0);
}

void
Meow_64_SMHasher(const void * key, int len, int unsigned seed, void * out)
{
    *(int unsigned *)MeowSMHasherSeed = seed;
    meow_u128 Result = MeowHash(MeowSMHasherSeed, len, (void *)key);
    ((meow_u64 *)out)[0] = MeowU64From(Result, 0);
}

void
Meow_128_SMHasher(const void * key, int len, int unsigned seed, void * out)
{
    *(int unsigned *)MeowSMHasherSeed = seed;
    meow_u128 Result = MeowHash(MeowSMHasherSeed, len, (void *)key);
    ((meow_u64 *)out)[0] = MeowU64From(Result, 0);
    ((meow_u64 *)out)[1] = MeowU64From(Result, 1);
}
