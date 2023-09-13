//---------------------------------------------------------------------------
//
// Name:        wxMySerialPort.cpp
// Author:      Gabriel Ferri
// Created:     19/12/2008
// Description: wxMySerialPort class implementation
//
//---------------------------------------------------------------------------
#include "wxMySerialPort.h"

#include <wx/datetime.h>


wxMySerialPort::wxMySerialPort()
: wxSerialPort()
{
	timeout_ms = 100;
	timeout_flag = false;
	is_half_duplex = false;
}

wxMySerialPort::~wxMySerialPort()
{
}

int wxMySerialPort::MyOpen( wxString portName, wxBaud portBaud, bool halfDuplex )
{
	// try to open
	if( Open( portName.ToAscii() ) == -1 )
		return wxSERIAL_ERROR;

	// set the baudrate
	if( SetBaudRate( portBaud ) == -1 )
		return wxSERIAL_ERROR;

	// set params
	is_half_duplex = halfDuplex;

	return wxSERIAL_OK;
}

int wxMySerialPort::MyRead( unsigned char *buf, unsigned int len )
{
	char* p_buf = (char *)buf;
	unsigned int bytes_to_read = len;
	int num = 0;

	// start timeout-ctrl
	timeout_flag = false;
	wxDateTime start = wxDateTime::UNow();

	// start reading
	while( !timeout_flag && ( bytes_to_read > 0 ) )
	{
		if( (num = Read( p_buf, bytes_to_read )) == -1 )
			break;

		bytes_to_read -= num;
		p_buf += num;

		wxTimeSpan time_diff = wxDateTime::UNow() - start;
		timeout_flag = time_diff.GetMilliseconds() > timeout_ms ? true : false;
	}

	return bytes_to_read == 0 ? wxSERIAL_OK : wxSERIAL_ERROR;
}

int wxMySerialPort::MyWrite( unsigned char *buf, unsigned int len )
{
	char* p_buf = (char *)buf;
	unsigned int bytes_to_write = len;
	int num = 0;

	// start timeout-timer
	timeout_flag = false;
	wxDateTime start = wxDateTime::UNow();

	// start writing
	while( !timeout_flag && ( bytes_to_write > 0 ) )
	{
		if( (num = Write( p_buf, bytes_to_write )) == -1 )
			break;

		bytes_to_write -= num;
		p_buf += num;
		
		wxTimeSpan time_diff = wxDateTime::UNow() - start;
		timeout_flag = time_diff.GetMilliseconds() > timeout_ms ? true : false;
	}

	if( bytes_to_write != 0 )
		return wxSERIAL_ERROR;

	if( is_half_duplex )
	{
		unsigned char read_buf[BUFFER_MAX_LEN];
		p_buf = (char *)read_buf;
		unsigned int bytes_to_read = len;
		num = 0;

		// start timeout-ctrl
		timeout_flag = false;
		start = wxDateTime::UNow();

		// start reading
		while( !timeout_flag && ( bytes_to_read > 0 ) )
		{
			if( (num = Read( p_buf, bytes_to_read )) == -1 )
				break;

			bytes_to_read -= num;
			p_buf += num;

			wxTimeSpan time_diff = wxDateTime::UNow() - start;
			timeout_flag = time_diff.GetMilliseconds() > timeout_ms ? true : false;
		}

		if( bytes_to_read != 0 )
			return wxSERIAL_ERROR;
	}

	return wxSERIAL_OK;
}

void wxMySerialPort::DiscardBuffer()
{
	char inByte;
	while( Read( &inByte, 1 ) == 1 );
}
