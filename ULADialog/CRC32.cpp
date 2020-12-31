// CRC32.cpp: implementation of the CCRC32 class.
//
//////////////////////////////////////////////////////////////////////

#include "..\stdafx.h"
#include "CRC32.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCRC32::CCRC32()
{

}

CCRC32::~CCRC32()
{

}

void CCRC32::initCRC32()
{
	unsigned int i, j, value;

	for(i = 0; i < 256; i++){
		value = i;
		for(j = 0; j < 8; j++){
			value = (value & 1) ? ((value >> 1) ^ 0xEDB88320) : (value >> 1 );
		}
		crc32tbl[i] = value;
	}
	crc32 = 0xFFFFFFFF;

}

unsigned int CCRC32::getCRC32(unsigned char pieceOfData)
{
	crc32 = crc32tbl[(unsigned char)crc32 ^ pieceOfData] ^ (crc32 >> 8);

	return (crc32);
}

void CCRC32::setCRC32(unsigned int aCRC32)
{
	crc32 = aCRC32;
}

unsigned int CCRC32::getCRC32()
{
	return crc32;
}