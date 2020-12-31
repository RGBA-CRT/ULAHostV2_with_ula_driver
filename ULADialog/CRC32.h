// CRC32.h: interface for the CCRC32 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRC32_H__C2D91E39_FF95_49E4_9CCB_B4C60FA43940__INCLUDED_)
#define AFX_CRC32_H__C2D91E39_FF95_49E4_9CCB_B4C60FA43940__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCRC32  
{
public:
	CCRC32();
	virtual ~CCRC32();

	unsigned int getCRC32(unsigned char pieceOfData);
	void initCRC32();
	void setCRC32(unsigned int aCRC32);
	unsigned int getCRC32();

private:
	unsigned int crc32;
	unsigned int crc32tbl[256];


};

#endif // !defined(AFX_CRC32_H__C2D91E39_FF95_49E4_9CCB_B4C60FA43940__INCLUDED_)
