//---------------------------------------------------------------------------
//
// Name:        wxMySerialPort.h
// Author:      Gabriel Ferri
// Created:     19/12/2008
// Description: wxMySerialPort class declaration
//
//---------------------------------------------------------------------------
#ifndef __WXMYSERIALPORT_H
#define __WXMYSERIALPORT_H

#include <wx/ctb-0.13/serport.h>
#include <wx/string.h>

#define wxSERIAL_ERROR		-1
#define wxSERIAL_OK			0

#define BUFFER_MAX_LEN		512

class wxMySerialPort : public wxSerialPort
{
public:
	wxMySerialPort();
	~wxMySerialPort();

	// member functions
	int MyOpen( wxString portName = wxCOM1 , wxBaud portBaud = wxBAUD_9600, bool halfDuplex = false );
	int MyClose() { return Close() == -1 ? wxSERIAL_ERROR : wxSERIAL_OK; };

	int MyRead( unsigned char *buf, unsigned int len );
	int MyWrite( unsigned char *buf, unsigned int len );
	void SetTimeout( unsigned int time ) { timeout_ms = time; };
	void DiscardBuffer();

private:
	unsigned int timeout_ms;
	bool timeout_flag;
	bool is_half_duplex;
};

#endif
