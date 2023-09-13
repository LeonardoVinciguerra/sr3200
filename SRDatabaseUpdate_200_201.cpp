#include "SRDatabase.h"
#include <wx/wxsqlite3.h>
#include <wx/msgdlg.h>


//----------------------------------------------------------------------------------
// From_200_to_201
//
//----------------------------------------------------------------------------------

int SRDatabase::From_200_to_201()
{
	wxSQLite3ResultSet q;
	wxSQLite3StatementBuffer stmtBuffer;
	try
	{
		// ActualProduction
		q = _SR3200.ExecuteQuery( wxT("ALTER TABLE WorkingModes ADD PistonLoadingDeltaX double; ") );
		q = _SR3200.ExecuteQuery( wxT("ALTER TABLE WorkingModes ADD PistonLoadingDeltaY double; ") );
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (Add fields)", wxOK );
		cout<<" DB Update (ActualProduction) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}

	try{
		q = _SR3200.ExecuteQuery( wxT("UPDATE MachineParams set Version = 2.01"));
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (Set Version)", wxOK );
		cout<<" DB Update (ActualProduction) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}
	return 0;
}
