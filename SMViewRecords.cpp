/*
 * SMViewRecords.cpp
 *
 *  Created on: Jul 18, 2017
 *      Author: dpelitti
 */
#include "SMBase.h"
#include "wxInspectionBoardPanel.h"
#include "wxInspectionVerifyPanel.h"


int SMBase::SMViewRecordsFinalize(){

	mainVideo->DisconnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );

	return SR_OK;
}

int SMBase::SMViewRecordsInitialize(){

	camera->SetAuxMode( AUX_BLANK );

	wxInspectionVerifyPanel *panel = (wxInspectionVerifyPanel*)currentPanel;}

int SMBase::SMViewRecordsNext( int data ){
	int ID_Site=-1;
	int counter=0;
	int prev=-1;
	for (int i=0; i<SR->DB->SavedResult; i++){
		if( SR->DB->AUTOInspectionPointRecord[i].ID_Site != prev){
			counter++;
			prev=SR->DB->AUTOInspectionPointRecord[i].ID_Site;
			if (counter == SR->DB->SelectedSite+1){
				ID_Site = SR->DB->AUTOInspectionPointRecord[i].ID_Site;
				break;
			}
		}

	}


	if (data == wxInspectionBoardPanel::ID_EVENTRECORDS ){ //board has been selected, need to refresh image

	wxString ProductionName = SR->DB->LoadProductionName(SR->DB->SelectedIDprod);

	wxString fullpath;
	fullpath.Append( wxString::Format( FILE_PRODUCTION_FOLDER, ProductionName.ToAscii()) );
	fullpath.Append( wxString::Format("Post_Printing_%d, ", SR->DB->SelectedBoardNumber ));
	fullpath.Append( wxString::Format( FILE_SITE, ProductionName.ToAscii(), ID_Site) );
	cv::Mat RecordedPicture = cv::imread( fullpath.ToAscii() );



	camera->SetVideoMainImage(  wxImage( RecordedPicture.cols, RecordedPicture.rows, (unsigned char*)RecordedPicture.data, true)   );}

	else if (data == wxInspectionVerifyPanel::EVT_GRID_SELECTED_RECORDS ){ //need to draw a circle

		wxString ProductionName = SR->DB->LoadProductionName(SR->DB->SelectedIDprod);
		wxString fullpath;
		fullpath.Append( wxString::Format( FILE_PRODUCTION_FOLDER, ProductionName.ToAscii()) );
		fullpath.Append( wxString::Format("Post_Printing_%d, ", SR->DB->SelectedBoardNumber ));
		fullpath.Append( wxString::Format( FILE_SITE, ProductionName.ToAscii(), ID_Site) );
		cv::Mat RecordedPicture = cv::imread( fullpath.ToAscii() );



		int AddedResults=0;
		for (int i=0; i<SR->DB->SavedResult; i++){
			if (SR->DB->AUTOInspectionPointRecord[i].SpotNum != SR->DB->SelectedSite ){
				AddedResults++;
			}
			else
				break;
		}

		//cv::circle(RecordedPicture, SR->DB->AUTOInspectionPointRecord[ SR->DB->Selected_row + AddedResults].Centroids_PCB, 5, cv::Scalar(0,0,255),  1, CV_AA);
		cv::line(RecordedPicture, cv::Point(SR->DB->AUTOInspectionPointRecord[ SR->DB->Selected_row + AddedResults].Centroids_PCB.x - 5,SR->DB->AUTOInspectionPointRecord[ SR->DB->Selected_row + AddedResults].Centroids_PCB.y -5), cv::Point(SR->DB->AUTOInspectionPointRecord[ SR->DB->Selected_row + AddedResults].Centroids_PCB.x + 5,SR->DB->AUTOInspectionPointRecord[ SR->DB->Selected_row + AddedResults].Centroids_PCB.y +5), cv::Scalar(0,0,255), 1, CV_AA);
		cv::line(RecordedPicture, cv::Point(SR->DB->AUTOInspectionPointRecord[ SR->DB->Selected_row + AddedResults].Centroids_PCB.x - 5,SR->DB->AUTOInspectionPointRecord[ SR->DB->Selected_row + AddedResults].Centroids_PCB.y +5), cv::Point(SR->DB->AUTOInspectionPointRecord[ SR->DB->Selected_row + AddedResults].Centroids_PCB.x + 5,SR->DB->AUTOInspectionPointRecord[ SR->DB->Selected_row + AddedResults].Centroids_PCB.y -5), cv::Scalar(0,0,255), 1, CV_AA);

		camera->SetVideoMainImage(  wxImage( RecordedPicture.cols, RecordedPicture.rows, (unsigned char*)RecordedPicture.data, true)   );
	}
	else if(data == wxInspectionVerifyPanel::ID_CHANGEPICTURE ){

		wxString ProductionName = SR->DB->LoadProductionName(SR->DB->SelectedIDprod);
		wxString fullpath;
		fullpath.Append( wxString::Format( FILE_PRODUCTION_FOLDER, ProductionName.ToAscii()) );
		fullpath.Append( wxString::Format("Post_Printing_%d, ", SR->DB->SelectedBoardNumber ));
		fullpath.Append( wxString::Format( FILE_SITE, ProductionName.ToAscii(), ID_Site) );
		cv::Mat RecordedPicture = cv::imread( fullpath.ToAscii() );
		camera->SetVideoMainImage(  wxImage( RecordedPicture.cols, RecordedPicture.rows, (unsigned char*)RecordedPicture.data, true)   );}
	else if(data == wxInspectionVerifyPanel::EVT_IDENTIFY_ALL_WARNING){


		wxString ProductionName = SR->DB->LoadProductionName(SR->DB->SelectedIDprod);
		wxString fullpath;
		fullpath.Append( wxString::Format( FILE_PRODUCTION_FOLDER, ProductionName.ToAscii()) );
		fullpath.Append( wxString::Format("Post_Printing_%d, ", SR->DB->SelectedBoardNumber ));
		fullpath.Append( wxString::Format( FILE_SITE, ProductionName.ToAscii(), ID_Site) );
		cv::Mat RecordedPicture = cv::imread( fullpath.ToAscii() );

		if(SR->DB->AllWarningStatus==0){
			for (int i=0; i<SR->DB->SavedResult; i++){
				if (SR->DB->AUTOInspectionPointRecord[i].Percentage_covered > 100 - SR->DB->AUTOInspectionPointRecord[i].Warning && SR->DB->AUTOInspectionPointRecord[i].SpotNum == SR->DB->SelectedSite){
					cv::circle(RecordedPicture, SR->DB->AUTOInspectionPointRecord[ i].Centroids_PCB, 5, SR->DB->WARNING_COLOR,  1, CV_AA);
				}

			}
			SR->DB->AllWarningStatus=1;
			SR->DB->AllFaultyStatus=0;
		}
		else{
			SR->DB->AllWarningStatus=0;
		}
		camera->SetVideoMainImage(  wxImage( RecordedPicture.cols, RecordedPicture.rows, (unsigned char*)RecordedPicture.data, true)   );
	}
	else if(data == wxInspectionVerifyPanel::EVT_IDENTIFY_ALL_FAULTY){
		wxString ProductionName = SR->DB->LoadProductionName(SR->DB->SelectedIDprod);
		wxString fullpath;
		fullpath.Append( wxString::Format( FILE_PRODUCTION_FOLDER, ProductionName.ToAscii()) );
		fullpath.Append( wxString::Format("Post_Printing_%d, ", SR->DB->SelectedBoardNumber ));
		fullpath.Append( wxString::Format( FILE_SITE, ProductionName.ToAscii(), ID_Site) );
		cv::Mat RecordedPicture = cv::imread( fullpath.ToAscii() );

		if(SR->DB->AllFaultyStatus==0){
			for (int i=0; i<SR->DB->SavedResult; i++){
				if (SR->DB->AUTOInspectionPointRecord[i].Percentage_covered > 100 - SR->DB->AUTOInspectionPointRecord[i].Alarm && SR->DB->AUTOInspectionPointRecord[i].SpotNum == SR->DB->SelectedSite){
					cv::circle(RecordedPicture, SR->DB->AUTOInspectionPointRecord[i].Centroids_PCB, 5, SR->DB->ALARM_COLOR,  1, CV_AA);
				}
				if (SR->DB->AUTOInspectionPointRecord[i].ConnectedWith && SR->DB->AUTOInspectionPointRecord[i].SpotNum == SR->DB->SelectedSite){
					cv::circle(RecordedPicture, SR->DB->AUTOInspectionPointRecord[i].Centroids_PCB, 5, SR->DB->SHORT_COLOR,  1, CV_AA);
				}

			}
			SR->DB->AllFaultyStatus=1;
			SR->DB->AllWarningStatus=0;
		}
		else{
			SR->DB->AllFaultyStatus=0;
		}
		camera->SetVideoMainImage(  wxImage( RecordedPicture.cols, RecordedPicture.rows, (unsigned char*)RecordedPicture.data, true)   );
	}

}


