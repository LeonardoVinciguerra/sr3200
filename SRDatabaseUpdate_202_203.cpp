/*
 * SRDatabaseUpdate_202_203.cpp
 *
 *  Created on: Jul 1, 2022
 *      Author: sr3200
 */

/*
 * SRDatabaseUpdate_202_203.cpp
 *
 *  Created on: Jun 27, 2022
 *      Author: Lenardo Vinciguerra
 */

#include "SRDatabase.h"
#include <wx/wxsqlite3.h>
#include <wx/msgdlg.h>


//----------------------------------------------------------------------------------
// From_202_to_203
//
//----------------------------------------------------------------------------------

int SRDatabase::From_202_to_203()
{
	wxSQLite3ResultSet q;
	wxSQLite3StatementBuffer stmtBuffer;

	//AntiReflects
	try{
		q = _SR3200.ExecuteQuery( wxT("ALTER TABLE WorkingModes ADD AntiReflectsEn INT; " ));
	}catch( wxSQLite3Exception& exc){
		wxMessageBox( exc.GetMessage(), "DB Update (AntiReflectsEn)", wxOK );
		cout<<" DB Update (Create table 202->203) FAILED: "<< exc.GetMessage() <<endl;
		return SR_ERROR;
	}

	try
	{
		q = _SR3200.ExecuteQuery( wxT("UPDATE MachineParams set Version = 2.03"));
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (Set Version)", wxOK );
		cout<<" DB Update (ActualProduction) ERROR!: "<< exc.GetMessage() <<endl;
		return 1;
	}
	return 0;
}
