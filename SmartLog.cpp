//---------------------------------------------------------------------------
//
// Name:        SmartLog.cpp
// Author:      Gabriel Ferri
// Created:     15/04/2008
// Description: SmartLog class implementation
//
//---------------------------------------------------------------------------

#include "SmartLog.h"
#include "GlobalDefs.h"
#include "GlobalUtils.h"
#include "Messages.h"
#include <stdio.h>
#include <wx/datetime.h>
#include <wx/colour.h>
#include <wx/gdicmn.h>
#include <wx/textfile.h>
#include <wx/msgdlg.h>

//----------------------------------------------------------------------------------
// SmartLog
// 
//----------------------------------------------------------------------------------
SmartLog::SmartLog( wxRichTextCtrl* textBoxRef, SRDatabase*DBref)
{
	textBox = textBoxRef;
	DB = DBref;
	enableFlag		= true;
	logToFileFlag	= false;
	dateFlag		= true;
	timeFlag		= true;
	lineFlag		= true;
	functionFlag	= true;
	requestedBuzzerStop = true;

	textBox->Connect(textBoxRef->GetId(),wxEVT_LEFT_DOWN,(wxObjectEventFunction)&SmartLog::OnTextClicked, NULL, this);





}

//----------------------------------------------------------------------------------
// ~SmartLog
// 
//----------------------------------------------------------------------------------
SmartLog::~SmartLog()
{
}

//----------------------------------------------------------------------------------
// LogToFileEnable
// 
//----------------------------------------------------------------------------------
void SmartLog::LogToFileEnable( bool state )
{
	logToFileFlag = state;

	if( logToFileFlag )
	{
		MACHINE_CONFIG( SHARED_LOG )
			// check/create "logs" directory

			if( !CheckDirectory( DIR_SHARED_LOGS ) )
			{
				if( mkdir( DIR_SHARED_LOGS, DIR_CREATION_FLAG ) )
				{
					wxMessageBox( MSG_ERRORDIRLOGS, MACHINE_NAME, wxOK | wxICON_ERROR, 0 );
					return;
				}
			}
		MACHINE_CONFIG_END

		if( !CheckDirectory( DIR_LOGS ) )
		{
			if( mkdir( DIR_LOGS, DIR_CREATION_FLAG ) )
			{
				wxMessageBox( MSG_ERRORDIRLOGS, MACHINE_NAME, wxOK | wxICON_ERROR, 0 );
				return;
			}
		}
		wxDateTime dateTime = wxDateTime::Now();

		MACHINE_CONFIG( SHARED_LOG )
			filename_shared = wxT("//mnt//qserver//logs//SR3200log_") + dateTime.FormatISODate() + wxT(".txt");
			wxTextFile logFile_shared( filename_shared );
			if( !logFile_shared.Exists() )
			{
				logFile_shared.Create();
				logFile_shared.Close();
			}
		MACHINE_CONFIG_END

		filename = wxT(".//logs//log_") + dateTime.FormatISODate() + wxT(".txt");
		wxTextFile logFile( filename );
		if( !logFile.Exists() )
		{
			logFile.Create();
			logFile.Close();
		}
	}
}

//----------------------------------------------------------------------------------
// Write
// 
//----------------------------------------------------------------------------------
void SmartLog::Write( const wxString &msg, MsgTypeEnum msgType )
{
	wxString temp;
	wxDateTime dateTime = wxDateTime::Now();

	switch( msgType )
	{
		case MSG_MSG:
			textBox->BeginTextColour( wxColour( wxT("BLACK") ) );
			break;

		case MSG_ERROR:
			textBox->BeginTextColour( wxColour( wxT("RED") ) );
			break;

		case MSG_SUCCESS:
			textBox->BeginTextColour( wxColour( 0, 170, 0 ) ); // GREEN
			break;
	}

	// write message to file
	if( logToFileFlag )
	{
		wxString IdProd;
		IdProd << DB->ProductionDataS.ProductionName;
		wxString Counter;
		Counter << DB->ProductionDataS.Counter;

		MACHINE_CONFIG( SHARED_LOG )
			//Shared
			wxTextFile logFile_shared( filename_shared );
			logFile_shared.Open();
			logFile_shared.AddLine(  IdProd + wxT("\t") + wxT("Counter: ") + Counter + wxT("\t") + dateTime.FormatTime() + wxT("\t") + msg );
			logFile_shared.Write();
			logFile_shared.Close();
		MACHINE_CONFIG_END
		//Local
		wxTextFile logFile( filename );
		logFile.Open();
		logFile.AddLine(  IdProd + wxT("\t") + wxT("Counter: ") + Counter + wxT("\t") + dateTime.FormatTime() + wxT("\t") + msg );
		logFile.Write();
		logFile.Close();
	}

	// write formatted text: date(opt) - time(opt) - message
	if( dateFlag )
	{	
		temp = temp + dateTime.FormatDate() + wxT("\t");
	}
	if( timeFlag )
	{
		temp = temp + dateTime.FormatTime() + wxT("\t\t");
	}
	textBox->AppendText( temp + msg + wxT("\n") );

	textBox->ShowPosition( textBox->GetValue().Len() + 1 );
	textBox->GetCaret()->Hide();
}


//----------------------------------------------------------------------------------
// MoveToEnd
//
//----------------------------------------------------------------------------------
void SmartLog::MoveToEnd()
{
	textBox->ShowPosition( textBox->GetValue().Len() + 1 );
	textBox->GetCaret()->Hide();
}

void SmartLog::OnTextClicked(wxCommandEvent& event){

	this->requestedBuzzerStop = true;
	std::cout<< " requestedBuzzerStop set value: "<<requestedBuzzerStop <<std::endl;
}
