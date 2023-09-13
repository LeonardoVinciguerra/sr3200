//---------------------------------------------------------------------------
//
// Name:        SerialCom.cpp
// Author:      Gabriel Ferri
// Created:     07/05/2008
// Description: SerialCom functions implementation
//
//---------------------------------------------------------------------------
#include "SerialCom.h"
#include <wx/wx.h>


#define RETRYTIMES		10

//------------------------------------------------------------------------
// Table of ModBus CRC value for high-order byte
//------------------------------------------------------------------------
const unsigned char auchCRCHi[] = {
	0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,
	0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,
	0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,
	0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,
	0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,
	0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,
	0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,
	0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,
	0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,
	0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,
	0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,
	0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
	0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,
	0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x01,0xc0,
	0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,
	0xc0,0x80,0x41,0x00,0xc1,0x81,0x40,0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,
	0x00,0xc1,0x81,0x40,0x01,0xc0,0x80,0x41,0x01,0xc0,0x80,0x41,0x00,0xc1,0x81,
	0x40
};

//------------------------------------------------------------------------
// Table of ModBus CRC value for low-order byte
//------------------------------------------------------------------------
const unsigned char auchCRCLo[] = {
	0x00,0xc0,0xc1,0x01,0xc3,0x03,0x02,0xc2,0xc6,0x06,0x07,0xc7,0x05,0xc5,0xc4,
	0x04,0xcc,0x0c,0x0d,0xcd,0x0f,0xcf,0xce,0x0e,0x0a,0xca,0xcb,0x0b,0xc9,0x09,
	0x08,0xc8,0xd8,0x18,0x19,0xd9,0x1b,0xdb,0xda,0x1a,0x1e,0xde,0xdf,0x1f,0xdd,
	0x1d,0x1c,0xdc,0x14,0xd4,0xd5,0x15,0xd7,0x17,0x16,0xd6,0xd2,0x12,0x13,0xd3,
	0x11,0xd1,0xd0,0x10,0xf0,0x30,0x31,0xf1,0x33,0xf3,0xf2,0x32,0x36,0xf6,0xf7,
	0x37,0xf5,0x35,0x34,0xf4,0x3c,0xfc,0xfd,0x3d,0xff,0x3f,0x3e,0xfe,0xfa,0x3a,
	0x3b,0xfb,0x39,0xf9,0xf8,0x38,0x28,0xe8,0xe9,0x29,0xeb,0x2b,0x2a,0xea,0xee,
	0x2e,0x2f,0xef,0x2d,0xed,0xec,0x2c,0xe4,0x24,0x25,0xe5,0x27,0xe7,0xe6,0x26,
	0x22,0xe2,0xe3,0x23,0xe1,0x21,0x20,0xe0,0xa0,0x60,0x61,0xa1,0x63,0xa3,0xa2,
	0x62,0x66,0xa6,0xa7,0x67,0xa5,0x65,0x64,0xa4,0x6c,0xac,0xad,0x6d,0xaf,0x6f,
	0x6e,0xae,0xaa,0x6a,0x6b,0xab,0x69,0xa9,0xa8,0x68,0x78,0xb8,0xb9,0x79,0xbb,
	0x7b,0x7a,0xba,0xbe,0x7e,0x7f,0xbf,0x7d,0xbd,0xbc,0x7c,0xb4,0x74,0x75,0xb5,
	0x77,0xb7,0xb6,0x76,0x72,0xb2,0xb3,0x73,0xb1,0x71,0x70,0xb0,0x50,0x90,0x91,
	0x51,0x93,0x53,0x52,0x92,0x96,0x56,0x57,0x97,0x55,0x95,0x94,0x54,0x9c,0x5c,
	0x5d,0x9d,0x5f,0x9f,0x9e,0x5e,0x5a,0x9a,0x9b,0x5b,0x99,0x59,0x58,0x98,0x88,
	0x48,0x49,0x89,0x4b,0x8b,0x8a,0x4a,0x4e,0x8e,0x8f,0x4f,0x8d,0x4d,0x4c,0x8c,
	0x44,0x84,0x85,0x45,0x87,0x47,0x46,0x86,0x82,0x42,0x43,0x83,0x41,0x81,0x80,
	0x40
};

//-----------------------------------------------------------------------------
// Name: CRC_ModBus()
// Desc: Calcola il CRC sui dati
//-----------------------------------------------------------------------------
unsigned short CRC_ModBus( unsigned char* buffer, unsigned short buffer_len )
{
    unsigned char uchCRCHi = 0xff;
    unsigned char uchCRCLo = 0xff;

    unsigned char uindex;

	for (int i = 0; i < buffer_len; i++)
    {
        uindex = uchCRCHi ^ buffer[i];
        uchCRCHi = uchCRCLo ^ auchCRCHi[uindex];
        uchCRCLo = auchCRCLo[uindex];
    }
    return (uchCRCHi << 8 | uchCRCLo);
}

int TWSBus1_Send( wxCommInterface* commInt, unsigned char NSlave, unsigned char Cmd, unsigned char* TxBuf, unsigned short TxLen )
{
	return TWSBus1_Send( commInt, NSlave, Cmd, TxBuf, TxLen, NULL, NULL );
}

//-----------------------------------------------------------------------------
// Name: TWSBus1_Send()
// Desc: Invia dati su BUS TWS 1.0
//-----------------------------------------------------------------------------
#define OUT_BUF_DIM		128
#define IN_BUF_DIM		128

int TWSBus1_Send( wxCommInterface* commInt, unsigned char NSlave, unsigned char Cmd, unsigned char* TxBuf, unsigned short TxLen, unsigned char* RxBuf,  unsigned short* RxLen )
{
	unsigned char tx_buffer[OUT_BUF_DIM];
	unsigned char rx_buffer[IN_BUF_DIM];
	unsigned short rx_buffer_len = 0;
	unsigned short crc;
	short retry = 0;
	
	if( TxLen > OUT_BUF_DIM - 6 )
		return 1; // error - too much data to send
	
	// create message
	tx_buffer[0] = NSlave;				// slave address
	tx_buffer[1] = Cmd;					// commamd code
	tx_buffer[2] = TxLen >> 8;			// number of byte (H)
	tx_buffer[3] = TxLen;				// number of byte (L)
	
	for( int i = 0; i < TxLen; i++ )	// TxData
		tx_buffer[i+4] = TxBuf[i];
	
	crc = CRC_ModBus( tx_buffer, TxLen+4 );
	tx_buffer[4+TxLen] = crc >> 8;		// crc (H)
	tx_buffer[5+TxLen] = crc;			// crc (L)
	
	// init request cycle
	while( retry < RETRYTIMES )
	{
		int slot = commInt->Send( tx_buffer, TxLen+6 );
		if( slot == -1 )
			return 1; // error - commInt buffer full

		int ret_val = FIFO_STATE_RTS;
		while( ret_val == FIFO_STATE_RTS )
		{
			wxMilliSleep( 1 );
			ret_val = commInt->Receive( slot, rx_buffer, rx_buffer_len );
		}
		if( ret_val == FIFO_STATE_ERROR )
		{
			// try to send msg again
			retry++;
			continue;
		}

		// check message ( address, command and CRC )
		if( rx_buffer[0] == NSlave && rx_buffer[1] == Cmd )
		{
			crc = 256 * rx_buffer[rx_buffer_len - 2] + rx_buffer[rx_buffer_len - 1];
			if( crc == CRC_ModBus(rx_buffer, rx_buffer_len - 2) )
			{
				// copy message data
				if( (rx_buffer_len - 6 > 0) && (RxBuf != NULL) && (RxLen != NULL) )
				{
					memcpy( RxBuf, rx_buffer + 4, rx_buffer_len - 6 );
					*RxLen = rx_buffer_len - 6;
				}
				break;
			}
			else
			{
				// try to send msg again
				retry++;
				continue;
			}
		}
		else
		{
			// try to send msg again
			retry++;
			continue;
		}
	}
	
	if( retry == RETRYTIMES )
		return 1; // error
	
	return 0;
}

//-----------------------------------------------------------------------------
// Name: TWSBus1_Send_Command()
// Desc: 
//-----------------------------------------------------------------------------
int TWSBus1_Send_Command( wxCommInterface* commInt, unsigned char NSlave, unsigned char Cmd, unsigned char* RxData, bool activated )
{
	unsigned short rx_len = 0;
	
	if( !activated )
		return 0;

	return TWSBus1_Send( commInt, NSlave, Cmd, NULL, 0, RxData, &rx_len );
}

int TWSBus1_Send_Command( wxCommInterface* commInt, unsigned char NSlave, unsigned char Cmd, unsigned short TxData, unsigned char* RxData, bool activated )
{
	unsigned char tx_buffer[2];
	tx_buffer[0] = TxData >> 8;			// TxData (H)
	tx_buffer[1] = TxData;				// TxData (L)
	unsigned short rx_len = 0;
	
	if( !activated )
		return 0;

	return TWSBus1_Send( commInt, NSlave, Cmd, tx_buffer, 2, RxData, &rx_len );
}
