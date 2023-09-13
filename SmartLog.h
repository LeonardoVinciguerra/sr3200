//---------------------------------------------------------------------------
//
// Name:        SmartLog.h
// Author:      Gabriel Ferri
// Created:     15/04/2008
// Description: SmartLog class declaration
//
//---------------------------------------------------------------------------
#ifndef __SMARTLOG_H
#define __SMARTLOG_H

#include <wx/richtext/richtextctrl.h>
#include "SRDatabase.h"

enum MsgTypeEnum { MSG_MSG, MSG_ERROR, MSG_SUCCESS };

class SmartLog : public wxEvtHandler
{
public:
	SmartLog( wxRichTextCtrl* textBoxRef , SRDatabase* DBref);
	~SmartLog();

	void LogToFileEnable( bool state );
	
	bool enableFlag;				// when set to false, no logs are made
	bool logToFileFlag;				// when true, write the log message to file

	bool dateFlag;					// when true, logs the date
	bool timeFlag;					// when true, logs the time
	bool lineFlag;					// when true, logs the line number from where the logging is made
	bool functionFlag;				// when true, logs the function name
	bool requestedBuzzerStop;

	void Write( const wxString &msg, MsgTypeEnum msgType = MSG_MSG );
	void MoveToEnd();

	void OnTextClicked(wxCommandEvent& event);
	SRDatabase* DB;
	wxString filename;
	wxString filename_shared;

protected:
	wxRichTextCtrl* textBox;

};

#endif
