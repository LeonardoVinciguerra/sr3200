//---------------------------------------------------------------------------
//
// Name:        SRMachineUpdateDriver.cpp
// Author:      Daniele Belloni, Gabriel Ferri
// Created:     21/05/2008
// Description: SRMachine class implementation
//
//---------------------------------------------------------------------------
#include "SRMachine.h"
#include "Messages.h"
#include "GlobalUtils.h"


#define RETRYTIMES              3
#define MAX_FAKE_CHARS          5
#define TX_OK                   0x11
#define ERROR_Crc               0x22
#define ERROR_Line              0x33
#define ERROR_Signature         0x44
#define ERROR_OverFlow          0x55
#define ERROR_TopModule         0x66


//----------------------------------------------------------------------------------
// Hex2Val
// Converte un carattere esadecimale in numero intero
//----------------------------------------------------------------------------------
unsigned char Hex2Val( unsigned char hex )
{
	// number
	if( hex >= '0' && hex <= '9' )
		return hex - '0';

	// upper alpha
	if( hex >= 'A' && hex <= 'F' )
		return hex - 'A' + 10;

	// lower alpha
	if( hex >= 'a' && hex <= 'f' )
		return hex - 'a' + 10;

	return 0;
}

//----------------------------------------------------------------------------------
// UpdateDriver
// Carica il firmware nel driver
//----------------------------------------------------------------------------------
int SRMachine::UpdateDriver( int driverId, wxFile *inFile )
{
	MACHINE_CONFIG( MACHINE_ENABLE )
	unsigned char inByte, outByte;
	int retry = 0;
	wxFileOffset byteIndex = 0;

	int i, txSize, bufferSize = 0;
	unsigned char buffer[0x20000];

	wxProgressDialog progressDialog( MACHINE_NAME, wxT("                                                                                ") );

	// set 1msec timeout
	serialPortStepper->SetTimeout( 100 );

	wxMySerialPort* serialPortDriver;
	MotorModule* IODriver;
	if( DB->MotorParamsS[driverId].Driver == DRIVER_STEPPER_ID )
	{
		IODriver = new StepperModule( commIntStepper, 0 );
		serialPortDriver = serialPortStepper;
	}
	else
	{
		IODriver = new BrushlessModule( commIntBrushless, 0 );
		serialPortDriver = serialPortBrushless;
	}

	// Suspend the other drivers
	progressDialog.Update( 0, MSG_DRIVERSUSPENDALL );
	for( i = 0; i < NUM_MOTORSBOARDS; i++ )
	{
		if( (i != driverId) && (DB->MotorParamsS[i].Driver == DB->MotorParamsS[driverId].Driver) )
		{
			IODriver->ChangeAddress( DB->MotorParamsS[i].Address );

			smartLogger->Write( wxString::Format( MSG_DRIVERSUSPEND, DB->MotorParamsS[i].Address ) );

			if( IODriver->SuspendDrive() == MOTOR_ERROR )
			{
				smartLogger->Write( wxString::Format( MSG_DRIVERSUSPENDERROR, DB->MotorParamsS[i].Address ), MSG_ERROR );
				return SR_ERROR;
			}
		}
	}

	// Reset target driver
	progressDialog.Update( 0, MSG_DRIVERRESET );
	IODriver->ChangeAddress( DB->MotorParamsS[driverId].Address );
	if( IODriver->ResetDrive() == MOTOR_ERROR )
	{
		smartLogger->Write( MSG_DRIVERRESETERROR, MSG_ERROR );
		return SR_ERROR;
	}

	for( i = 0; i < MAX_FAKE_CHARS; i++ )
	{
		// set 10sec timeout
		serialPortDriver->SetTimeout( 10000 );

		if( serialPortDriver->MyRead( &inByte, 1 ) == wxSERIAL_ERROR )
		{
			smartLogger->Write( MSG_DRIVERNOTFOUND, MSG_ERROR );
			return SR_ERROR;
		}

		if( inByte == 'a' )
		{
			inByte = 'b';

			if( serialPortDriver->MyWrite( &inByte, 1 ) == wxSERIAL_ERROR )
			{
				smartLogger->Write( wxString( MSG_DRIVERCOMMERROR ) + wxT(" - Timeout 1 !"), MSG_ERROR );
        		return SR_ERROR;
			}

			// esce dal ciclo
			break;
		}
	}

	if( i == MAX_FAKE_CHARS )
	{
		smartLogger->Write( wxString( MSG_DRIVERCOMMERROR ) + wxT(" - MAX_FAKE_CHARS reached !"), MSG_ERROR );
		return SR_ERROR;
	}
	
    // looking for 'b' character
	if( serialPortDriver->MyRead( &inByte, 1 ) == wxSERIAL_ERROR )
	{
		smartLogger->Write( wxString( MSG_DRIVERCOMMERROR ) + wxT(" - Timeout 3 !"), MSG_ERROR );
		return SR_ERROR;
	}

	if( inByte != 'b' )
	{
		smartLogger->Write( wxString( MSG_DRIVERCOMMERROR ) + wxT(" - Unexpected character !"), MSG_ERROR );
		return SR_ERROR;
	}

	progressDialog.Update( 0, MSG_TRANSFERDATA );

	// ignore any received bytes (flush input buffer)
	serialPortDriver->DiscardBuffer();

	inFile->Seek( 0, wxFromStart );
	wxFileOffset fileLen = inFile->Length()-4; //non si considerano gli ultimi byte (carattere terminatore + spazi + CR + LF)

	// start char
	inFile->Read( &outByte, 1 );
	byteIndex++;
	buffer[0] = outByte;

	if( serialPortDriver->MyWrite( &buffer[0], 1 ) == wxSERIAL_ERROR )
	{
		smartLogger->Write( wxString( MSG_DRIVERCOMMERROR ) + wxT(" - Timeout 4 !"), MSG_ERROR );
		return SR_ERROR;
	}

	// looking for target response
	if( serialPortDriver->MyRead( &inByte, 1 ) == wxSERIAL_ERROR )
	{
		smartLogger->Write( wxString( MSG_DRIVERCOMMERROR ) + wxT(" - Timeout 5 !"), MSG_ERROR );
		return SR_ERROR;
	}
	if( outByte != inByte )
	{
		smartLogger->Write( wxString( MSG_DRIVERCOMMERROR ) + wxT(" - Error receiving echo !"), MSG_ERROR );
		return SR_ERROR;
	}

	while( !inFile->Eof() && (byteIndex<=fileLen) )
	{
		inFile->Read( &outByte, 1 );
		byteIndex++;
		if( (outByte == 32) || (outByte == 13) || (outByte == 10) )
			continue;
		buffer[0] = Hex2Val( outByte ) * 16;

		inFile->Read( &outByte, 1 );
		byteIndex++;
		if( (outByte == 32) || (outByte == 13) || (outByte == 10) )
			continue;
		buffer[0] += Hex2Val( outByte );

		// update progress bar
		progressDialog.Update( 100 * byteIndex / fileLen );

		if( serialPortDriver->MyWrite( &buffer[0], 1 ) == wxSERIAL_ERROR )
		{
			smartLogger->Write( wxString( MSG_DRIVERCOMMERROR ) + wxT(" - Timeout 6 !"), MSG_ERROR );
			return SR_ERROR;
		}

		// looking for target response
		if( serialPortDriver->MyRead( &inByte, 1 ) == wxSERIAL_ERROR )
		{
			smartLogger->Write( wxString( MSG_DRIVERCOMMERROR ) + wxT(" - Timeout 7 !"), MSG_ERROR );
			return SR_ERROR;
		}
		if( buffer[0] != inByte )
		{
			smartLogger->Write( wxString( MSG_DRIVERCOMMERROR ) + wxT(" - Error receiving echo !"), MSG_ERROR );
			return SR_ERROR;
		}
	}

	// restore com timeout
	serialPortDriver->SetTimeout( COMTIMEOUT );

	progressDialog.Update( 100 );
	smartLogger->Write( MSG_TRANSFERDATAENDED, MSG_SUCCESS );

	MACHINE_CONFIG_END
	return 0;
}
