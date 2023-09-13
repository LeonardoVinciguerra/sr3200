
#include "SMBase.h"

#include <wx/msgdlg.h>
#include "GlobalUtils.h"
#include "Messages.h"
#include "VisionFunctions.h"

#define PANEL_DISABLE		PANEL_MOVE_DISABLE, PANEL_OUTPUT_NONE


//----------------------------------------------------------------------------------
// Init
// Inizializza il controllo
//----------------------------------------------------------------------------------
int SMBase::Init( SRMachine* SRRef, SmartLog* smartLoggerRef, wxDatasette* datasetteRef, wxControlPanel* controlPanelRef, wxMainVideo* mainVideoRef, wxPanel *toolBoxRef, wxBitmapButton* menuBtnRef, wxCameraControl *cameraRef, AutoSPICheck *AutoSPIcheckRef, AutoSPIProc *AutoSPIprocRef, wxWindow* parentRef )
{
	SR				= SRRef;
	smartLogger		= smartLoggerRef;
	datasette		= datasetteRef;
	controlPanel	= controlPanelRef;
	mainVideo		= mainVideoRef;
	toolBox			= toolBoxRef;
	menuBtn			= menuBtnRef;
	camera			= cameraRef;
	parent			= parentRef;

	AutoSPIproc		= AutoSPIprocRef;
	AutoSPIcheck    = AutoSPIcheckRef;

	currentSM = SM_NONE;

	isMainVideoClickEnable = false;
	isAuxVideoClickEnable = false;

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SelectSM
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SelectSM( SMEnum sm, wxPanel *panelRef )
{
	switch( currentSM )
	{
		case SM_NONE:
			break;

		case SM_ALIGNMENT:
			SMAlignmentFinalize();
			break;

		case SM_PRINTING:
			SMPrintingFinalize();
			break;

		case SM_VERIFY:
			SMVerifyFinalize();
			break;

		case SM_PINS:
			SMPinsFinalize();
			break;

		case SM_PASTE:
			SMPasteConditioningFinalize();
			break;

		case SM_PLATEMOVEMENT:
			SMPlateMovementFinalize();
			break;

		case SM_CAMERAFOCUS:
			SMCameraFocusFinalize();
			break;

		case SM_CAMERASCALE:
			SMCameraScaleFinalize();
			break;

		case SM_CAMERAOFFSET:
			SMCameraOffsetFinalize();
			break;

		case SM_HARDWARETEST:
			SMHardwareTestFinalize();
			break;

		case SM_VISION:
			SMVisionFinalize();
			break;

		case SM_DEMOMODE:
			SMDemomodeFinalize();
			break;

		case SM_CONVEDGE:
			SMConveyorEdgeFinalize();
			break;

		case SM_INSPECTION:
			SMInspectionFinalize();
			break;
		//aggiuto this is the view record mchine
		case SM_VIEWRECORDS:
			SMViewRecordsFinalize();
		case SM_CAMERAZERO:
			SMCameraZeroFinalize();
	}

	currentSM		= sm;
	currentPanel	= panelRef;

	// sets controls state
	datasette->StartEnable( currentSM == SM_NONE ? false : true );
	datasette->StopEnable( false );
	datasette->NextEnable( false );
	datasette->PrevEnable( false );
	controlPanel->SetState( PANEL_DISABLE );

	camera->SetMainMode( MAIN_BLANK );
	camera->SetAuxMode( AUX_BLANK );

	isMainVideoClickEnable = false;
	isAuxVideoClickEnable = false;

	switch( currentSM )
	{
		case SM_NONE:
			return SR_OK;

		case SM_ALIGNMENT:
			datasette->SetFuncLabel( _("Alignment") );
			return SMAlignmentInitialize();

		case SM_PRINTING:
			datasette->SetFuncLabel( _("Printing") );
			return SMPrintingInitialize();

		case SM_VERIFY:
			datasette->SetFuncLabel( _("Verify") );
			return SMVerifyInitialize();

		case SM_PINS:
			datasette->SetFuncLabel( _("Pins") );
			return SMPinsInitialize();

		case SM_PASTE:
			datasette->SetFuncLabel( _("Paste") );
			return SMPasteConditioningInitialize();
			break;

		case SM_PLATEMOVEMENT:
			datasette->SetFuncLabel( _("Plate Height") );
			return SMPlateMovementInitialize();

		case SM_CAMERAFOCUS:
			datasette->SetFuncLabel( _("Camera Focus") );
			return SMCameraFocusInitialize();

		case SM_CAMERASCALE:
			datasette->SetFuncLabel( _("Camera Scale") );
			return SMCameraScaleInitialize();

		case SM_CAMERAOFFSET:
			datasette->SetFuncLabel( _("Camera Offset") );
			return SMCameraOffsetInitialize();

		case SM_CAMERAZERO:
			datasette->SetFuncLabel( _("Camera Zero") );
			return SMCameraZeroInitialize();

		case SM_HARDWARETEST:
			return SMHardwareTestInitialize();

		case SM_VISION:
			datasette->SetFuncLabel( _("Vision") );
			return SMVisionInitialize();

		case SM_DEMOMODE:
			datasette->SetFuncLabel( _("Demo") );
			return SMDemomodeInitialize();

		case SM_CONVEDGE:
			datasette->SetFuncLabel( _("Conveyor Edge") );
			return SMConveyorEdgeInitialize();

		case SM_INSPECTION:
			datasette->SetFuncLabel( _("Inspection") );
			return SMInspectionInitialize();
			//agginto
		case SM_VIEWRECORDS:
			return SMViewRecordsInitialize();
	}

	return SR_ERROR;
}

//----------------------------------------------------------------------------------
// SMReset
// Resetta la macchina a stati selezionata
//----------------------------------------------------------------------------------
void SMBase::SMReset()
{
	isMainVideoClickEnable = false;
	isAuxVideoClickEnable = false;

	datasette->StopEnable( false );
	datasette->NextEnable( false );
	datasette->PrevEnable( false );
	datasette->PauseEnable( false );
	controlPanel->SetState( PANEL_DISABLE );

	camera->StopCapture();
	camera->SetMainMode( MAIN_BLANK );
	camera->SetAuxMode( AUX_BLANK );

	switch( currentSM )
	{
		case SM_NONE:
			break;

		case SM_ALIGNMENT:
			SMAlignmentReset();
			break;

		case SM_PRINTING:
			SMPrintingReset();
			break;

		case SM_VERIFY:
			SMVerifyReset();
			break;

		case SM_PINS:
			SMPinsReset();
			break;

		case SM_PASTE:
			SMPasteConditioningReset();
			break;

		case SM_PLATEMOVEMENT:
			SMPlateMovementReset();
			break;

		case SM_CAMERAFOCUS:
			SMCameraFocusReset();
			break;

		case SM_CAMERASCALE:
			SMCameraScaleReset();
			break;

		case SM_CAMERAOFFSET:
			SMCameraOffsetReset();
			break;

		case SM_CAMERAZERO:
			SMCameraZeroReset();
			break;

		case SM_VISION:
			SMVisionReset();
			break;

		case SM_DEMOMODE:
			SMDemomodeReset();
			break;

		case SM_CONVEDGE:
			SMConveyorEdgeReset();
			break;

		case SM_INSPECTION:
			SMInspectionReset();
			break;

		default:
			break;
	}

	datasette->StartEnable( currentSM == SM_NONE ? false : true );

	toolBox->Enable( true );
	menuBtn->Enable( true );
}

//----------------------------------------------------------------------------------
// SMAuxVideoLeftClick
// 
//----------------------------------------------------------------------------------
void SMBase::SMAuxVideoLeftClick( wxMouseEvent& e )
{
	if( !isAuxVideoClickEnable || camera->GetAuxMode() != AUX_CAMPOSITION || camera->GetMainMode() == MAIN_BLANK )
		return;

	isAuxVideoClickEnable = false;
	
	// Cursor position
	int cursorX = e.GetPosition().x + mainVideo->GetAuxVideoDisplacement();
	int cursorY = e.GetPosition().y + mainVideo->GetAuxVideoDisplacement();

	// Workplace position
	int posX = (cursorX - WORKPLACE_IMG_DELTA)*(WORKPLACE_DIM_X/float(WORKPLACE_IMG_W - 1)) + WORKPLACE_X;
	int posY = -cursorY*(WORKPLACE_DIM_Y/float(WORKPLACE_IMG_H - 1)) + WORKPLACE_Y;

	// Move camera to reaches the clicked point
	if( SR->MoveCameraAndWait( posX, posY, ABS_MOVE ) == SR_ERROR )
	{
		smartLogger->Write( MSG_CAMERAERROR, MSG_ERROR );
		SR->ErrorManagement();
		//return;
	}
	
	isAuxVideoClickEnable = true;
}

//----------------------------------------------------------------------------------
// SMAlignmentMainVideoKeyPress
// 
//----------------------------------------------------------------------------------
void SMBase::SMMainVideoKeyPress( wxKeyEvent& e )
{
	if( e.GetKeyCode() == WXK_RETURN )
	{
		wxMouseEvent mouseLeftClickEvent( wxEVT_LEFT_DOWN );

		switch( currentSM )
		{
			case SM_ALIGNMENT:
				SMAlignmentMainVideoLeftClick( mouseLeftClickEvent );
				break;

			case SM_PRINTING:
				SMPrintingMainVideoLeftClick( mouseLeftClickEvent );
				break;

			case SM_CAMERASCALE:
				SMCameraScaleMainVideoLeftClick( mouseLeftClickEvent );
				break;

			case SM_CAMERAOFFSET:
				SMCameraOffsetMainVideoLeftClick( mouseLeftClickEvent );
				break;

			default:
				break;
		}
	}
	e.Skip();
}

int SMBase::LoadBoardCameraCheck(){

	if( SR->isBoardLoaded )
		return SR_OK;

	// Camera piston to correct position to stop the board
	if( SR->MoveCameraAndWait( SR->DB->MachineParamsS.ConvEdgeX + SR->DB->ProductionDataS.PCBX/2 + SR->DB->MachineParamsS.CamPistonDeltaX + SR->DB->WorkingModesS.PistonLoadingDeltaX,
			SR->DB->MachineParamsS.ConvEdgeY + SR->DB->ProductionDataS.PCBY/2 + SR->DB->MachineParamsS.CamPistonDeltaY + SR->DB->WorkingModesS.PistonLoadingDeltaY, ABS_MOVE ) == SR_ERROR )
	return SR_ERROR;

	if( SR->SetCamera( CAMERA_DOWN )== SR_ERROR){
		smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
	}
	SR->SetCameraLight( LED_HIGH );
	myMilliSleep(FLICKERING_DELAY);
	camera->StartCapture();
	camera->GetColorFrames(MAX_FRAMES_FIDUCIAL);
	cv::Mat firstFrame = camera->GetWorkingColorFrame(0).clone();
	camera->GetColorFrames(MAX_FRAMES_FIDUCIAL);
	camera->StopCapture();
	cv::Mat secondFrame = camera->GetWorkingColorFrame(0).clone();
	cv::cvtColor(firstFrame, firstFrame, CV_BGR2GRAY);
	cv::cvtColor(secondFrame, secondFrame, CV_BGR2GRAY);
	cv::Mat frameDifference;
	//cv::imshow("Prima immagine", firstFrame);
	//cv::imshow("Seconda immagine", secondFrame);
	cv::subtract(firstFrame, secondFrame, frameDifference);
	//cv::imshow("Immagine sottratta", frameDifference);
	cv::Scalar mean, stddev;
	cv::meanStdDev(frameDifference, mean, stddev);
	int autoThreshold = 5*MAX(4,stddev(0));
	std::cout<<"Mean Std Dev found. StdValue: "<<stddev(0)<<" autoThreshold: "<<autoThreshold<<std::endl;

	if( SR->startBoardLoading() == SR_ERROR ){
		smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
		SR->SetCameraLight( LED_LOW );
		return SR_ERROR;
	}


	camera->StartCapture();
	camera->GetColorFrames(MAX_FRAMES_FIDUCIAL);
	camera->StopCapture();
	SR->SetCameraLight( LED_LOW );
	cv::Mat loadedPicture = camera->GetWorkingColorFrame(0).clone();
	cv::cvtColor(loadedPicture, loadedPicture, CV_BGR2GRAY);
	//cv::imshow("Immagine Post load", loadedPicture);
	cv::Mat resultFrame;
	cv::subtract(loadedPicture, firstFrame, resultFrame);
	//cv::imshow("Immagine differenza pre post", resultFrame);
	cv::threshold(resultFrame, resultFrame, autoThreshold, 255, CV_THRESH_BINARY);
	//cv::imshow("Risultato thresholding", resultFrame);
	int nonZeroPx = countNonZero(resultFrame);

	std::cout<<"nonZeroPx: "<<nonZeroPx<<std::endl;

	int retVal = MOTOR_OK;
	if(nonZeroPx < MIN_NON_ZERO_PIXELS && SR->DB->WorkingModesS.InputSensorEnabled){
		wxMessageBox( MSG_INPUTSECURITYSERROR, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
		retVal = SR_ERROR;
		if( SR->SetOutput( OUTPUT_CAMERA_PISTON, false ) == SR_ERROR ){
			smartLogger->Write( MSG_CAMPISTONERROR, MSG_ERROR );
			return SR_ERROR;
		}
	}else{
		if( SR->finishBoardLoading() == SR_ERROR ){
			smartLogger->Write( MSG_LOADERROR, MSG_ERROR );
			return SR_ERROR;
		}
	}



	if( SR->SetCamera( CAMERA_OFF )== SR_ERROR){
		smartLogger->Write( MSG_CAMERAVIEWERROR, MSG_ERROR );
	}

	return retVal;
}

//----------------------------------------------------------------------------------
// MoveSqueegeesSide
// 
//----------------------------------------------------------------------------------
void SMBase::MoveSqueegeesSide( bool operatorSide )
{
	// Check if origins are correctly setted
	if( !SR->CheckOrigin() )
	{
		SR->ErrorManagement();
		return;
	}
	// Check if immediate stop has been pressed
	if( SR->GetStop() )
	{
		smartLogger->Write( MSG_NOTIFYMOTORRESET );
		return;
	}
	
	if( ( SR->GetSqueegeesCycle() == true && SR->DB->ProductionDataS.SqueegeesMove <= 0 ) ||
		( SR->GetSqueegeesCycle() == false && SR->DB->ProductionDataS.SqueegeesMove > 0 ) )
	{
		// Sueeges are on the back side
		if( operatorSide )
		{
			// Deactivate squeegees
			if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, false ) == SR_ERROR )
			{
				SR->ErrorManagement();
				return;
			}
			if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, false ) == SR_ERROR )
			{
				SR->ErrorManagement();
				return;
			}

			// Move the squeegees
			if( SR->SqueegeesMotor.MoveAndWait( SR->DB->ProductionDataS.SqueegeesZeroMove + SR->DB->ProductionDataS.SqueegeesMove, ABS_MOVE ) == SR_ERROR )
			{
				SR->ErrorManagement();
				return;
			}
			SR->SetSqueegeesCycle( true );
		}
	}
	else
	{
		// Sueeges are on the operator side
		if( !operatorSide )
		{
			// Deactivate squeegees
			if( SR->SetOutput( OUTPUT_SQUEEGEESFRONT, false ) == SR_ERROR )
			{
				SR->ErrorManagement();
				return;
			}
			if( SR->SetOutput( OUTPUT_SQUEEGEESREAR, false ) == SR_ERROR )
			{
				SR->ErrorManagement();
				return;
			}

			// Move the squeegees
			if( SR->SqueegeesMotor.MoveAndWait( SR->DB->ProductionDataS.SqueegeesZeroMove, ABS_MOVE ) == SR_ERROR )
			{
				SR->ErrorManagement();
				return;
			}
			SR->SetSqueegeesCycle( false );
		}
	}
}

//----------------------------------------------------------------------------------
// SMInitCheck
// 
//----------------------------------------------------------------------------------
int SMBase::SMInitCheck( CheckStruct check )
{
	MACHINE_CONFIG( MACHINE_ENABLE )
	// Check cover
	if( check.cover )
	{
		if( SR->GetInput( INPUT_COVER ) == 0 )
		{
			if( wxMessageBox( MSG_COVEROPEN, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent ) != wxYES )
				return SR_ERROR;
		}
		else
			SR->CheckCover( true );
	}
	// Check for air pressure
	if( check.air )
	{
		input = SR->GetInput( INPUT_AIR );
		if( input == LOW || input == SR_ERROR )
		{
			smartLogger->Write( MSG_AIRPRESSUREERROR, MSG_ERROR );
			wxMessageBox( MSG_AIRPRESSUREERROR, MACHINE_NAME, wxOK | wxICON_ERROR, parent );
			return SR_ERROR;
		}
	}
	MACHINE_CONFIG_END

	// Check for PCB height
	if( check.pcb )
	{
		if( check.pcb_height == 0 )
		{
			if( wxMessageBox( MSG_PCBZEROHEIGHT, MACHINE_NAME, wxYES_NO | wxICON_WARNING, parent ) != wxYES )
				return SR_ERROR;
		}
	}

	// We assure the frame is correctly locked
	if( check.frame )
	{
		if( SR->SetOutput( OUTPUT_FRAMEUNLOCK, false ) == SR_ERROR )
		{
			smartLogger->Write( MSG_FRAMELOCKERROR, MSG_ERROR );
			return SR_ERROR;
		}
	}

	// Check for motors position
	if( check.motors_pos )
	{
		if( SR->CheckMotorsPos() == SR_ERROR )
			if( SR->ResetMotors( check.motor_state ) == SR_ERROR )
				return SR_ERROR;
	}

	return SR_OK;
}


int SMBase::MoveCameraToCompensateOffset(bool secondCycle){
	double differenceX = (SR->DB->cameraZeroFound.X - CAM_W / 2) * SR->DB->MachineParamsS.DnXPixMm;
	double differenceY = (SR->DB->cameraZeroFound.Y - CAM_H / 2) * SR->DB->MachineParamsS.DnYPixMm;

	smartLogger->Write( wxString::Format( MSG_CAMERAZEROFOUND, differenceX, differenceY ), MSG_MSG );


	if(fabs(differenceX) > CAMERA_ZERO_MAX_OFFSET || fabs(differenceY) > CAMERA_ZERO_MAX_OFFSET && !secondCycle){
		cout<< "Difference is too big! x: "<<differenceX<< "    y:"<<differenceY<< endl;
		return SR_WARNING;
	}
	//if( SR->MoveCameraAndWait(differenceX, differenceY, ABS_MOVE , LIMIT_OFF) == SR_ERROR ){
	if( SR->MoveCameraAndWait(differenceX, -differenceY, ABS_MOVE , LIMIT_OFF) == SR_ERROR ){
		return SR_ERROR;
	}
	//cout<<"Nuovo zero x: "<<differenceX << " y: "<<differenceY<<endl;
	bool isError = false;
	//wxString msgMartini = wxString::Format("Nuovo zero X: %f , Y: %f",differenceX, differenceY );
	//smartLogger->Write(msgMartini);

	if( SR->CamXMotor.motor->Home() == MOTOR_ERROR )
		isError = true;
	if( SR->CamYMotor.motor->Home() == MOTOR_ERROR )
		isError = true;

	SR->CamXMotor.ResetPosition();
	SR->CamYMotor.ResetPosition();

	if( isError == true )
	{
		smartLogger->Write( MSG_MOTORDRIVERERROR, MSG_ERROR );
		return SR_ERROR;
	}

	return SR_OK;
}
//----------------------------------------------------------------------------------
// CopyFiducial
// 
//----------------------------------------------------------------------------------
void SMBase::CopyFiducial( int dest, int source )
{
	/*
	FiducialParamsStruct temp = SR->DB->FiducialParamsS[dest];
	SR->DB->FiducialParamsS[dest] = SR->DB->FiducialParamsS[source];
	*/
	FiducialParamsStruct temp;
	memcpy( &temp, &SR->DB->FiducialParamsS[dest], sizeof(FiducialParamsStruct) );
	memcpy( &SR->DB->FiducialParamsS[dest], &SR->DB->FiducialParamsS[source], sizeof(FiducialParamsStruct) );
	// restore unique fields
	SR->DB->FiducialParamsS[dest].Id = temp.Id;
	SR->DB->FiducialParamsS[dest].Type = temp.Type;
}

//----------------------------------------------------------------------------------
// CopyFiducials
// 
//----------------------------------------------------------------------------------
void SMBase::CopyFiducials()
{
	CopyFiducial( FIDUCIAL_ROT1, FIDUCIAL_ROT1_A );
	CopyFiducial( FIDUCIAL_ROT2, FIDUCIAL_ROT2_A );
	CopyFiducial( FIDUCIAL_TRA, FIDUCIAL_TRA_A );
	CopyFiducial( FIDUCIAL_ROT1_FRAME, FIDUCIAL_ROT1_FRAME_A );
	CopyFiducial( FIDUCIAL_ROT2_FRAME, FIDUCIAL_ROT2_FRAME_A );
	CopyFiducial( FIDUCIAL_TRA_FRAME, FIDUCIAL_TRA_FRAME_A );
}

//----------------------------------------------------------------------------------
// CheckTemplateImage
// 
//----------------------------------------------------------------------------------
bool SMBase::CheckTemplateImage()
{
	for( int i = FIDUCIAL_ROT1; i <= FIDUCIAL_TRA; i++ )
	{
		if( !camera->CheckTemplateImage( wxString::Format( "%s_%d.jpeg", SR->DB->ProductionDataS.ProductionName.ToAscii(), i ) ) )
			return false;
	}
	
	if( SR->DB->WorkingModesS.FiducialOnFrame )
	{
		for( int i = FIDUCIAL_ROT1_FRAME; i <= FIDUCIAL_TRA_FRAME; i++ )
		{
			if( !camera->CheckTemplateImage( wxString::Format( "%s_%d.jpeg", SR->DB->ProductionDataS.ProductionName.ToAscii(), i ) ) )
				return false;
		}
	}

	return true;
}

//----------------------------------------------------------------------------------
// ISite_CreateArray
//----------------------------------------------------------------------------------
void SMBase::ISite_CreateArray()
{
	for( int i = 0; i < SR->DB->SiteCount(); i++ )
	{
		iSitesEnabled[i] = false;

		if( SR->DB->AUTOInspectionSiteStruct[i].Enable )
		{
			if( SR->DB->WorkingModesS.InspectionType == INSPECTION_SPI )
			{
				//if( spiCheck->CheckImages( SR->DB->AUTOInspectionSiteStruct[i].IdSite ) )
					iSitesEnabled[i] = true;
			}
			else
				iSitesEnabled[i] = true;
		}
	}
}

//----------------------------------------------------------------------------------
// ISite_SelectFirst
//----------------------------------------------------------------------------------
bool SMBase::ISite_SelectFirst()
{
	for( int i = 0; i < SR->DB->SiteCount(); i++ )
	{
		if( iSitesEnabled[i] )
		{
			SR->DB->SiteSelect( i );
			return true;
		}
	}

	return false;
}

//----------------------------------------------------------------------------------
// ISite_SelectNext
//----------------------------------------------------------------------------------
bool SMBase::ISite_SelectNext()
{
	if( SR->DB->SiteCount() == 0 )
		return false;

	for( int i = SR->DB->SiteGetSelected() + 1; i < SR->DB->SiteCount(); i++ )
	{
		if( iSitesEnabled[i] )
		{
			SR->DB->SiteSelect( i );
			return true;
		}
	}

	return false;
}

//----------------------------------------------------------------------------------
// ISite_SelectPrev
//----------------------------------------------------------------------------------
bool SMBase::ISite_SelectPrev()
{
	if( SR->DB->SiteCount() == 0 )
		return false;

	if( ISite_IsFirst() )
		return false;

	for( int i = SR->DB->SiteGetSelected() - 1; i >= 0; i-- )
	{
		if( iSitesEnabled[i] )
		{
			SR->DB->SiteSelect( i );
			return true;
		}
	}

	return false;
}

//----------------------------------------------------------------------------------
// ISite_IsFirst
//----------------------------------------------------------------------------------
bool SMBase::ISite_IsFirst()
{
	// si suppone che il sito corrente sia "enable"
	for( int i = SR->DB->SiteGetSelected() - 1; i >= 0; i-- )
	{
		if( iSitesEnabled[i] )
			return false;
	}

	return true;
}

//----------------------------------------------------------------------------------
// ISite_Count
//----------------------------------------------------------------------------------
int SMBase::ISite_Count()
{
	int counter = 0;

	for( int i = 0; i < SR->DB->SiteCount(); i++ )
	{
		if( iSitesEnabled[i] )
			counter++;
	}

	return counter;
}

//----------------------------------------------------------------------------------
// ISite_GetSelected
//----------------------------------------------------------------------------------
int SMBase::ISite_GetSelected()
{
	int index = 0;

	// si suppone che il sito corrente sia "enable"
	for( int i = SR->DB->SiteGetSelected() - 1; i >= 0; i-- )
	{
		if( iSitesEnabled[i] )
			index++;
	}

	return index;
}

//----------------------------------------------------------------------------------
// findTemplate
//----------------------------------------------------------------------------------
//TEMP - da rivedere
bool SMBase::findTemplate( void* pImage_8, const wxString& filename, PointF& position, float& score )
{
	IplImage* pImage = (IplImage*)pImage_8;

	wxString fullpath( DIR_VISION );
	fullpath.Append( filename );

	FindTemplate( pImage, fullpath.ToAscii(), position, score );

	bool retVal = false;

	// draw template position
	IplImage* pTemplateImage = cvLoadImage( fullpath.ToAscii(), CV_LOAD_IMAGE_GRAYSCALE );

	IplImage* rgb = cvCreateImage( cvSize(pImage->width, pImage->height), IPL_DEPTH_8U, 3 );
	cvCvtColor( pImage, rgb, CV_GRAY2BGR );

	wxBitmap bmp = wxImage( pImage->width, pImage->height, (unsigned char*)rgb->imageData, true );
	wxMemoryDC dc;

	dc.SelectObject( bmp );
	dc.SetBrush( *wxTRANSPARENT_BRUSH );

	if( score >= (SR->DB->pCurrentFiducial->TemplateThr / 100.f) )
	{
		dc.SetPen( PEN_SHAPE_FOUNDED );
		dc.DrawRectangle( int(position.X), int(position.Y), pTemplateImage->width, pTemplateImage->height );
		retVal = true;
	}

	dc.SelectObject( wxNullBitmap );

	// Clean
	cvReleaseImage( &pTemplateImage );
	cvReleaseImage( &rgb );

	//TEMP
	camera->SetVideoMainImage( bmp );

	return retVal;
}

void SMBase::OnStart()
{
	// The function could be called also from a timer
	if( !datasette->IsStartEnable() )
		return;
	
	// Check if origins are correctly setted
	if( !SR->CheckOrigin() )
	{
		SR->ErrorManagement();
		return;
	}
	// Check if immediate stop has been pressed
	if( SR->GetStop() )
	{
		if( wxMessageBox( wxString::Format( "%s\n%s", MSG_NOTIFYMOTORRESET, MSG_ASKMOTORRESET ), MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent ) != wxYES )
		{
			return;
		}
		else
		{
			datasette->StartEnable( false );
			controlPanel->SetState( PANEL_DISABLE );

			toolBox->Enable( false );
			menuBtn->Enable( false );

			// Reset squeegees and squeegees cycle...
			SR->SetOutput( OUTPUT_SQUEEGEESFRONT, false );
			SR->SetOutput( OUTPUT_SQUEEGEESREAR, false );
			// ...reset motors
			if( SR->ResetMotors( MODE_START_POSITION ) == SR_ERROR )
			{
				SR->ErrorManagement();
				SMReset();
				return;
			}

			smartLogger->Write( MSG_MOTORSTARTPOS );
		}
	}

	// SRMachine errors reset
	SR->ResetErrors();

	datasette->StartEnable( false );
	controlPanel->SetState( PANEL_DISABLE );

	toolBox->Enable( false );
	menuBtn->Enable( false );

	int ret_value = SR_OK;
	switch( currentSM )
	{
		case SM_ALIGNMENT:
			ret_value = SMAlignment( ALIGNMENT_STATE_INIT0 );
			break;

		case SM_VERIFY:
			ret_value = SMVerify( VERIFY_STATE_INIT );
			break;

		case SM_PINS:
			ret_value = SMPins( PINS_STATE_INIT );
			break;

		case SM_PASTE:
			ret_value = SMPasteConditioning( PASTE_STATE_INIT1 );
			break;

		case SM_PRINTING:
			ret_value = SMPrinting( PRINTING_STATE_INIT1 );
			break;

		case SM_PLATEMOVEMENT:
			ret_value = SMPlateMovement( PLATEMOVEMENT_STATE_INIT );
			break;

		case SM_CAMERAFOCUS:
			ret_value = SMCameraFocus( CAMERAFOCUS_STATE_INIT );
			break;

		case SM_CAMERASCALE:
			ret_value = SMCameraScale( CAMERASCALE_STATE_INIT );
			break;

		case SM_CAMERAOFFSET:
			ret_value = SMCameraOffset( CAMERAOFFSET_STATE_INIT );
			break;

		case SM_CAMERAZERO:
			ret_value = SMCameraZero( CAMERAZERO_STATE_INIT0 );
			break;

		case SM_VISION:
			ret_value = SMVision( VISION_STATE_INIT );
			break;

		case SM_DEMOMODE:
			ret_value = SMDemomode( DEMOMODE_STATE_INIT );
			break;

		case SM_CONVEDGE:
			ret_value = SMConveyorEdge( CONVEDGE_STATE_INIT );
			break;

		case SM_INSPECTION:
			SMInspectionNext(-1);
			break;

		default:
			break;
	}

	if( ret_value == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

void SMBase::OnPrev( int data )
{
	isMainVideoClickEnable = false;
	isAuxVideoClickEnable = false;

	switch( currentSM )
	{
		case SM_ALIGNMENT:
			SMAlignmentPrev();
			break;

		case SM_PRINTING:
			SMPrintingPrev();
			break;

		case SM_VERIFY:
			SMVerifyPrev();
			break;

		case SM_PINS:
			SMPinsPrev();
			break;

		case SM_PASTE:
			break;

		case SM_PLATEMOVEMENT:
			break;

		case SM_CAMERAFOCUS:
			break;

		case SM_CAMERASCALE:
			SMCameraScalePrev();
			break;

		case SM_CAMERAOFFSET:
			SMCameraOffsetPrev();
			break;

		case SM_CAMERAZERO:
			SMCameraZeroPrev();
			break;

		case SM_VISION:
			SMVisionPrev();
			break;

		case SM_CONVEDGE:
			break;

		case SM_INSPECTION:
			SMInspectionPrev( data );
			break;

		default:
			break;
	}
}

void SMBase::OnNext( int data )
{
	isMainVideoClickEnable = false;
	isAuxVideoClickEnable = false;

	switch( currentSM )
	{
		case SM_ALIGNMENT:
			SMAlignmentNext();
			break;

		case SM_PRINTING:
			//SMPrintingNext();
			//AGGIUNTO
			SMPrintingNext(data);
			break;

		case SM_VERIFY:
			SMVerifyNext();
			break;

		case SM_PINS:
			SMPinsNext();
			break;

		case SM_PASTE:
			break;

		case SM_PLATEMOVEMENT:
			SMPlateMovementNext();
			break;

		case SM_CAMERAFOCUS:
			SMCameraFocusNext();
			break;

		case SM_CAMERASCALE:
			SMCameraScaleNext();
			break;

		case SM_CAMERAOFFSET:
			SMCameraOffsetNext();
			break;

		case SM_CAMERAZERO:
			SMCameraZeroNext();
			break;

		case SM_VISION:
			SMVisionNext();
			break;

		case SM_CONVEDGE:
			SMConveyorEdgeNext();
			break;

		case SM_INSPECTION:
			SMInspectionNext( data );
			//aggiunto
			//SMPrinting( PRINTING_STATE_INIT1 );
			//fine
			break;
		case SM_VIEWRECORDS:
			SMViewRecordsNext( data );
			break;


		default:
			break;
	}
}

void SMBase::OnStop()
{
	if( wxMessageBox( MSG_ASKABORT, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, parent ) != wxYES )
		return;

	int ret_value = SR_OK;
	switch( currentSM )
	{
		case SM_ALIGNMENT:
			smartLogger->Write( MSG_ALIGNABORTED, MSG_ERROR );
			ret_value = SMAlignment( ALIGNMENT_STATE_RESET );
			break;

		case SM_PRINTING:
			smartLogger->Write( MSG_PRINTINGABORTED, MSG_ERROR );
			ret_value = SMPrinting( PRINTING_STATE_RESET );
			break;

		case SM_VERIFY:
			smartLogger->Write( MSG_VERIFYABORTED, MSG_ERROR );
			ret_value = SMVerify( VERIFY_STATE_RESET );
			break;

		case SM_PINS:
			smartLogger->Write( MSG_PINSABORTED, MSG_ERROR );
			ret_value = SMPins( PINS_STATE_RESET );
			break;

		case SM_PASTE:
			smartLogger->Write( MSG_PASTEABORTED, MSG_ERROR );
			ret_value = SMPasteConditioning( PASTE_STATE_RESET );
			break;

		case SM_PLATEMOVEMENT:
			smartLogger->Write( MSG_PLATEMOVEABORTED, MSG_ERROR );
			ret_value = SMPlateMovement( PLATEMOVEMENT_STATE_RESET );
			break;

		case SM_CAMERAFOCUS:
			smartLogger->Write( MSG_CAMERAFOCUSABORTED, MSG_ERROR );
			ret_value = SMCameraFocus( CAMERAFOCUS_STATE_RESET );
			break;

		case SM_CAMERASCALE:
			smartLogger->Write( MSG_CAMERASCALEABORTED, MSG_ERROR );
			ret_value = SMCameraScale( CAMERASCALE_STATE_RESET );
			break;

		case SM_CAMERAZERO:
			smartLogger->Write( MSG_CAMERAZEROABORTED, MSG_ERROR );
			ret_value = SMCameraZero( CAMERAZERO_STATE_RESET );
			break;

		case SM_CAMERAOFFSET:
			smartLogger->Write( MSG_CAMERAOFFSETABORTED, MSG_ERROR );
			ret_value = SMCameraOffset( CAMERAOFFSET_STATE_RESET );
			break;

		case SM_VISION:
			ret_value = SMVision( VISION_STATE_RESET );
			break;

		case SM_DEMOMODE:
			ret_value = SMDemomode( DEMOMODE_STATE_RESET );
			break;

		case SM_CONVEDGE:
			smartLogger->Write( MSG_CONVEDGEABORTED, MSG_ERROR );
			ret_value = SMConveyorEdge( CONVEDGE_STATE_RESET );
			break;

		case SM_INSPECTION:
			smartLogger->Write( MSG_INSPECTIONABORTED, MSG_ERROR );
			ret_value = SMInspection( INSPECTION_STATE_RESET );
			break;

		default:
			break;
	}

	if( ret_value == SR_ERROR )
	{
		SR->ErrorManagement();
		SMReset();
	}
}

void SMBase::OnPause()
{
	switch( currentSM )
	{
		case SM_PRINTING:
			if( SR->DB->MachineParamsS.LoaderInstalled && SR->DB->WorkingModesS.LoaderEn )
			{
				SR->SetLoaderStop( true );
				datasette->PauseEnable( false );
			}
			break;

		default:
			break;
	}
}

int SMBase::antiReflects( int fiducialType){
	if ( !SR->DB->WorkingModesS.AntiReflectsEn )
		return SR_OK;
	//Scendo per evitare riflesso della lamina
	if (!IsFiducialOnPCB( currentFiducial ))
	{
		if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus -10, ABS_MOVE , ABS_MOVE ) == SR_ERROR )
		{
			smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
			return SR_ERROR;
		}
	}
	else
	{
		if( SR->PlateMotor.MoveAndWait( SR->DB->MachineParamsS.CameraFocus, ABS_MOVE ) == SR_ERROR )
		{
			smartLogger->Write( MSG_PLATEERROR, MSG_ERROR );
			return SR_ERROR;
		}
	}
}

