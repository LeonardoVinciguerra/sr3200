#include "SRDatabase.h"
#include <wx/wxsqlite3.h>
#include <wx/msgdlg.h>


//----------------------------------------------------------------------------------
// From_200_to_201
//
//----------------------------------------------------------------------------------

int SRDatabase::From_201_to_202()
{
	wxSQLite3ResultSet q;
	wxSQLite3StatementBuffer stmtBuffer;
	try
	{
		// ActualProduction
		q = _SR3200.ExecuteQuery( wxT("CREATE TABLE GLOBAL_OFFSET ( "
									"GLOBAL_OFFSET_DELTA_X REAL, "
									"GLOBAL_OFFSET_DELTA_Y REAL "
									");" ));
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (Create table 201->202)", wxOK );
		cout<<" DB Update (Create table 201->202) FAILED: "<< exc.GetMessage() <<endl;
		return SR_ERROR;
	}

	try{
		q = _SR3200.ExecuteQuery( wxT("INSERT INTO GLOBAL_OFFSET ("
									"GLOBAL_OFFSET_DELTA_X, "
									"GLOBAL_OFFSET_DELTA_Y) "
									"VALUES (0, 0);" ));
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (Insert Globals)", wxOK );
		cout<<" DB Update (Create table 201->202) FAILED: "<< exc.GetMessage() <<endl;
		return SR_ERROR;
	}

	//Motor
	try{
		q = _SR3200.ExecuteQuery( wxT("ALTER TABLE motorparams "
									  " ADD EncoderType INT " ));
	}catch( wxSQLite3Exception& exc){
		wxMessageBox( exc.GetMessage(), "DB Update (EncoderType)", wxOK );
		cout<<" DB Update (Create table 201->202) FAILED: "<< exc.GetMessage() <<endl;
		return SR_ERROR;
	}
	try{
		q = _SR3200.ExecuteQuery( wxT("ALTER TABLE motorparams "
									  " ADD EncoderMode INT " ));
	}catch( wxSQLite3Exception& exc){
		wxMessageBox( exc.GetMessage(), "DB Update (EncoderMode)", wxOK );
		cout<<" DB Update (Create table 201->202) FAILED: "<< exc.GetMessage() <<endl;
		return SR_ERROR;
	}
	//Ejector
	try{
		q = _SR3200.ExecuteQuery( stmtBuffer.Format("INSERT INTO motorparams (Id, Address, MinCurrent, MaxCurrent, Microstepping, Pulley, Reduction, AccCurrent, Current, HomeFast, HomeSlow)"
									  " VALUES (%d, %d, %d, %d, %d,  %f, %f, %d, %d, %d, %d) ",13, 13, 1400, 1400, 8, 12.74, 1, 1400, 1400, 3000, 500 ));
	}catch( wxSQLite3Exception& exc){
		wxMessageBox( exc.GetMessage(), "DB Update (ejectorMotor)", wxOK );
		cout<<" DB Update (Create table 201->202) FAILED: "<< exc.GetMessage() <<endl;
		return SR_ERROR;
	}
	try{
		q = _SR3200.ExecuteQuery( stmtBuffer.Format("INSERT INTO speedTable (Id, LowSpeed, LowAcc, LowDec, NormalSpeed, NormalAcc, NormalDec, HighSpeed, HighAcc, HighDec)"
									  " VALUES (%d, %d, %d, %d, %d, %d, %d, %d, %d, %d) ",9, 1000, 1000, 1000, 1000, 3000, 5000,  2000, 5000, 10000 ));
	}catch( wxSQLite3Exception& exc){
		wxMessageBox( exc.GetMessage(), "DB Update (ejectorSpeed)", wxOK );
		cout<<" DB Update (Create table 201->202) FAILED: "<< exc.GetMessage() <<endl;
		return SR_ERROR;
	}

	//Add inpust
	try{
		q = _SR3200.ExecuteQuery( stmtBuffer.Format("INSERT INTO ioparams (Id, Type, DriverId, DriverPort)"
									  " VALUES (%d, %d, %d, %d) ", INPUT_LCONVPZERO, 0, 9, 1));
	}catch( wxSQLite3Exception& exc){
		wxMessageBox( exc.GetMessage(), "DB Update (INPUT_LCONVPZERO)", wxOK );
		cout<<" DB Update (Create table 201->202) FAILED: "<< exc.GetMessage() <<endl;
		return SR_ERROR;
	}
	try{
		q = _SR3200.ExecuteQuery( stmtBuffer.Format("INSERT INTO ioparams (Id, Type, DriverId, DriverPort)"
									  " VALUES (%d, %d, %d, %d) ", INPUT_SENSOR_INT, 0, 11, 2));
	}catch( wxSQLite3Exception& exc){
		wxMessageBox( exc.GetMessage(), "DB Update (INPUT_SENSOR_INT)", wxOK );
		cout<<" DB Update (Create table 201->202) FAILED: "<< exc.GetMessage() <<endl;
		return SR_ERROR;
	}


	//Finalize
	try{
		q = _SR3200.ExecuteQuery( wxT("UPDATE MachineParams set Version = 2.02"));
	}
	catch( wxSQLite3Exception& exc)
	{
		wxMessageBox( exc.GetMessage(), "DB Update (Set Version)", wxOK );
		cout<<" DB Update (MachineParams 202) ERROR!: "<< exc.GetMessage() <<endl;
		return SR_ERROR;
	}
	return 0;
}
