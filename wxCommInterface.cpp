//---------------------------------------------------------------------------
//
// Name:        wxCommInterface.cpp
// Author:      Gabriel Ferri
// Created:     19/12/2008
// Description: wxCommInterface class implementation
//
//---------------------------------------------------------------------------
#include "wxCommInterface.h"

#define SENDTIME				5

wxCommInterface::wxCommInterface( wxMySerialPort *com_port, int serialProtocol )
: wxThread()
{
	cs.Enter();
	fifo_buf_i = fifo_buf_ii = 0;
	for( int i = 0; i < FIFO_BUF_DIM; i++ )
	{
		fifo_buf[i].state = FIFO_STATE_EMPTY;
	}
	
	com = com_port;
	protocol = serialProtocol;
	cs.Leave();
	
	Create();
}

void* wxCommInterface::Entry()
{
	char state;
	
	for(;;)
	{
		for( int i = 0; i < FIFO_BUF_DIM; i++ )
		{
			cs.Enter();
			state = fifo_buf[ fifo_buf_ii ].state;
			cs.Leave();
			
			if( state == FIFO_STATE_RTS )
				break;
			
			fifo_buf_ii++;
			if( fifo_buf_ii == FIFO_BUF_DIM )
				fifo_buf_ii = 0;
		}
		
		if( state == FIFO_STATE_RTS )
		{
			cs.Enter();
			
			com->DiscardBuffer();
			
			// send message
			if( com->MyWrite( fifo_buf[ fifo_buf_ii ].io_buf, fifo_buf[ fifo_buf_ii ].io_bytes ) == wxSERIAL_OK )
			{
				// if addr is zero exit
				// is the same in both protocol (TWS and EVER)
				if( fifo_buf[ fifo_buf_ii ].io_buf[0] == 0 )
					fifo_buf[ fifo_buf_ii ].state = FIFO_STATE_DONE;
				// else wait for the response
				// read HEADER (4 bytes)
				else
				{
					if( protocol == PROTOCOL_TWS )
					{
						if( com->MyRead( fifo_buf[ fifo_buf_ii ].io_buf, 4 ) == wxSERIAL_OK )
						{
							short len = 256 * fifo_buf[ fifo_buf_ii ].io_buf[2] + fifo_buf[ fifo_buf_ii ].io_buf[3];
							if( len >= 0 || len <= IO_BUF_DIM - 6 )
							{
								// read DATA and CRC (2 bytes)
								if( com->MyRead( fifo_buf[ fifo_buf_ii ].io_buf + 4, len + 2 ) == wxSERIAL_OK )
								{
									fifo_buf[ fifo_buf_ii ].io_bytes = len + 6;
									fifo_buf[ fifo_buf_ii ].state = FIFO_STATE_DONE;
								}
							}
						}
					}
					else if( protocol == PROTOCOL_EVER )
					{
						if( com->MyRead( fifo_buf[ fifo_buf_ii ].io_buf, fifo_buf[ fifo_buf_ii ].expected_in_bytes ) == wxSERIAL_OK )
						{
							fifo_buf[ fifo_buf_ii ].io_bytes = fifo_buf[ fifo_buf_ii ].expected_in_bytes;
							fifo_buf[ fifo_buf_ii ].state = FIFO_STATE_DONE;
						}
					}
				}
			}
			
			if( fifo_buf[ fifo_buf_ii ].state != FIFO_STATE_DONE )
				fifo_buf[ fifo_buf_ii ].state = FIFO_STATE_ERROR;
			
			cs.Leave();
		}
		
		if( TestDestroy() )
			return NULL;

		Sleep( SENDTIME );
	}
	
	return NULL;
}

int wxCommInterface::Send( const unsigned char *sx_buf, unsigned short sx_bytes, unsigned short expected_bytes )
{
	int ret_val;
	bool isFull = true;
	
	cs.Enter();
	
	for( int i = 0; i < FIFO_BUF_DIM; i++ )
	{
		if( fifo_buf[ fifo_buf_i ].state == FIFO_STATE_EMPTY )
		{
			isFull = false;
			break;
		}
		
		fifo_buf_i++;
		if( fifo_buf_i == FIFO_BUF_DIM )
			fifo_buf_i = 0;
	}
	if( isFull )
	{
		cs.Leave();
		return -1;
	}
	
	memcpy( fifo_buf[ fifo_buf_i ].io_buf, sx_buf, sx_bytes );
	fifo_buf[ fifo_buf_i ].io_bytes = sx_bytes;
	fifo_buf[ fifo_buf_i ].expected_in_bytes = expected_bytes;
	fifo_buf[ fifo_buf_i ].state = FIFO_STATE_RTS;
	
	ret_val = fifo_buf_i;
	
	fifo_buf_i++;
	if( fifo_buf_i == FIFO_BUF_DIM )
		fifo_buf_i = 0;
	
	cs.Leave();
	
	return ret_val;
}

int wxCommInterface::Receive( int slot, unsigned char *rx_buf, unsigned short &rx_bytes )
{
	int ret_val;
	
	cs.Enter();
	ret_val = fifo_buf[ slot ].state;
	
	if( ret_val == FIFO_STATE_DONE || ret_val == FIFO_STATE_ERROR )
	{
		memcpy( rx_buf, fifo_buf[ slot ].io_buf, fifo_buf[ slot ].io_bytes );
		rx_bytes = fifo_buf[ slot ].io_bytes;
		fifo_buf[ slot ].state = FIFO_STATE_EMPTY;
	}
	cs.Leave();
	
	return ret_val;
}
