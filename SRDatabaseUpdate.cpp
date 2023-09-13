//---------------------------------------------------------------------------
//
// Name:        SRDatabase.cpp
// Author:      Gabriel Ferri
// Created:     11/04/2008
// Description: SRDatabase class implementation
//
//---------------------------------------------------------------------------

#include "SRDatabase.h"
#include <wx/filename.h>
#include "GlobalUtils.h"

bool SRDatabase::CheckVersion( const wxString ver )
{
	std::string stlstring = std::string(MachineParamsS.Version.mb_str());
	std::string UpdatedVersion = std::string(ver.mb_str());
	return stlstring.compare(UpdatedVersion)== 0 ? true : false;
	//return MachineParamsS.Version.Cmp( ver ) == 0 ? true : false;
}
//----------------------------------------------------------------------------------
// Update
// Aggiorna il DB
//----------------------------------------------------------------------------------
int SRDatabase::Update()
{
	cout << "Updating";
	wxString dbFileOrig = DIR_DBUPDATE;
	dbFileOrig += wxFileName::GetPathSeparator();
	dbFileOrig += dbFile;
	dbFileOrig += wxT(".");
	dbFileOrig += MachineParamsS.Version;

	wxString dbEmpty = DIR_DBUPDATE;
	dbEmpty += wxFileName::GetPathSeparator();
	dbEmpty += FILE_DBEMPTY;


	if( MachineParamsS.Version.Cmp( wxT("1.00") ) == 0 )
	{
		/*
		// copy the original db file
		if( CopyFile( dbFile.ToAscii(), dbFileOrig.ToAscii() ) != 0 )
			return SR_ERROR;

		// copy the empty db file
		dbEmpty += wxT(".1.01");
		if( CopyFile( dbEmpty.ToAscii(), dbFile.ToAscii() ) )
			return SR_ERROR;*/
		dbEmpty += ".2.00";
		cout<<"  dbEmpity: "<<dbEmpty<< endl;

		if( From_100_to_200( dbEmpty )){
			return SR_ERROR;
		}
		MachineParamsS.Version = "2.00";

		//now the data is copied, we should change database
		wxString newName =DIR_DBUPDATE;
		newName += wxFileName::GetPathSeparator();
		newName += MACHINE_DB;
		wxRenameFile(dbEmpty, newName);

		//delete the old DB
		_SR3200.Close();
		if(!wxRemoveFile(MACHINE_DB)){
			cout<<"Rimozione Principale fallita! "<<endl;
		}

		//move the new DB in the main Folder
		if(!wxCopyFile ( newName, MACHINE_DB, true)){
			cout<<"Copia fallita! "<<endl;
		}
		_SR3200.Open(MACHINE_DB);
		//delete the temp db
		if(!wxRemoveFile(newName)){
			cout<<"Rimozione TMP fallita! "<<endl;
		}

	}
	else if( MachineParamsS.Version.Cmp( wxT("2.00") ) == 0 )
	{
		if( From_200_to_201()){
			return SR_ERROR;
		}
		MachineParamsS.Version = "2.01";

	}
	else if( MachineParamsS.Version.Cmp( wxT("2.01") ) == 0 )
	{
		if( From_201_to_202()){
			return SR_ERROR;
		}
		MachineParamsS.Version = "2.02";
	}
	else if( MachineParamsS.Version.Cmp( wxT("2.02") ) == 0 ) //for the future!
	{
		if( From_202_to_203())
		{
			return SR_ERROR;
		}
		MachineParamsS.Version = "2.03";
	}
	else
		return SR_ERROR;



	if( MachineParamsS.Version.Cmp( wxT("2.00") ) == 0 ){
		_DBspiAUTO.Close();

		wxString dbEmpty = DIR_DBUPDATE;
		dbEmpty += wxFileName::GetPathSeparator();
		dbEmpty += FILE_DBEMPTY_SPI;
		dbEmpty += ".1.00";

		wxString newName =DIR_DBUPDATE;
		newName += wxFileName::GetPathSeparator();
		newName += AUTOspi_DB;

		wxRenameFile(dbEmpty, newName);

		if(!wxRemoveFile(AUTOspi_DB)){
			cout<<"Rimozione AUTOspi_DB fallita! "<<endl;
		}

		//move the new DB in the main Folder
		if(!wxCopyFile ( newName, AUTOspi_DB, true)){
			cout<<"Copia AUTOspi_DB fallita! "<<endl;
		}
		_DBspiAUTO.Open(AUTOspi_DB);
	}




	return SR_OK;
}
