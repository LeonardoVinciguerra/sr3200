//---------------------------------------------------------------------------
//
// Name:        wxCommInterface.h
// Author:      Gabriel Ferri
// Created:     19/12/2008
// Description: wxCommInterface class declaration
//
//---------------------------------------------------------------------------
#ifndef _WXCOMMINTERFACE_H_
#define _WXCOMMINTERFACE_H_

#include <wx/thread.h>
#include "wxMySerialPort.h"

#define FIFO_BUF_DIM		128
#define IO_BUF_DIM			BUFFER_MAX_LEN

#define FIFO_STATE_ERROR	-1
#define FIFO_STATE_EMPTY	0
#define FIFO_STATE_RTS		1
#define FIFO_STATE_DONE		2

enum SerialProtocolEnum
{
	PROTOCOL_TWS,
	PROTOCOL_EVER
};


class wxCommInterface : public wxThread
{
	public:
		wxCommInterface( wxMySerialPort *com_port, int serialProtocol );
		virtual void* Entry();

		int Send( const unsigned char *buf, unsigned short sx_bytes, unsigned short expected_bytes = 0 );
		int Receive( int slot, unsigned char *rx_buf, unsigned short &rx_bytes );

	private:
		struct wxCommUnit
		{
			unsigned char io_buf[IO_BUF_DIM];
			short io_bytes;
			short expected_in_bytes;
			char state;
		};
		wxCommUnit fifo_buf[FIFO_BUF_DIM];
		int fifo_buf_i, fifo_buf_ii;
		
		wxCriticalSection cs;
		
		wxMySerialPort *com;
		int protocol;
};

#endif // _WXCOMMINTERFACE_H_
