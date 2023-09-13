//---------------------------------------------------------------------------
//
// Name:        dbSPI.cpp
// Author:      Gabriel Ferri
// Created:     18/05/2011
// Description: dbSPI class implementation
//
//---------------------------------------------------------------------------

#include "SRDatabase.h"
#include <wx/wxsqlite3.h>
#include <wx/msgdlg.h>
#include <wx/tokenzr.h>
#include "GlobalUtils.h"
#include "GlobalEnum.h"
#include <string>
#include <wx/dir.h>

//aggiunto
#include "AutoSPI.h"
//#include "ctime"
#include <sys/time.h>


#define SPI_POS					0.0f
#define SPI_BIN_THR				230
#define SPI_ENABLE				1
#define SPI_CAMERA_BRIGHTNESS	0.5f
#define SPI_CAMERA_CONTRAST		0.5f
#define SPI_TYPE				0
#define SPI_UNDEFINED			-1
#define SPI_UNDEFINED_FLOAT		-1.0
#define SPI_BGA_BALL_DIAMETER	40	// mm/100

#define SPI_AREA_SEARCHAREA_DEF	10
#define SPI_ALARM		80
#define SPI_WARNING		85


//aggiunto
extern wxSQLite3Database _DBspiAUTO;

extern wxSQLite3Database _SR3200;



//----------------------------------------------------------------------------------
// LoadInspectionSites
//----------------------------------------------------------------------------------
int SRDatabase::LoadInspectionSites()
{
	sitesNum = 0;
	Spots2Save=0;


	try
		{
		//cout<< _DBspiAUTO.IsOpen()<< endl;
		wxSQLite3ResultSet q = _DBspiAUTO.ExecuteQuery( wxString::Format("SELECT * FROM SITES WHERE SITES_IdProd = %d;", ProductionDataS.IdProd) );

			while( q.NextRow() ){

				AUTOInspectionSiteStruct[sitesNum].IdSite = q.GetInt( wxT("SITES_ID") );
				AUTOInspectionSiteStruct[sitesNum].IdProd = ProductionDataS.IdProd;
				AUTOInspectionSiteStruct[sitesNum].Name = q.GetString( wxT("SITES_Name") );
				AUTOInspectionSiteStruct[sitesNum].X = q.GetDouble( wxT("SITES_X") );
				AUTOInspectionSiteStruct[sitesNum].Y = q.GetDouble( wxT("SITES_Y") );
				AUTOInspectionSiteStruct[sitesNum].Orientation = q.GetDouble( wxT("SITES_Orientation") );
				AUTOInspectionSiteStruct[sitesNum].BinarizationThr = q.GetInt( wxT("SITES_Binarization_threshold") );
				AUTOInspectionSiteStruct[sitesNum].Enable = q.GetInt( wxT("SITES_Enable") );
				AUTOInspectionSiteStruct[sitesNum].CameraBrightness = q.GetDouble( wxT("SITES_Brightness") );;
				AUTOInspectionSiteStruct[sitesNum].CameraContrast = q.GetDouble( wxT("SITES_Contrast") );
				AUTOInspectionSiteStruct[sitesNum].PointsNum =q.GetInt( wxT("SITES_PointsNum") );
				AUTOInspectionSiteStruct[sitesNum].Alarm =q.GetInt( wxT("SITES_Alarm") );
				AUTOInspectionSiteStruct[sitesNum].Warning =q.GetInt( wxT("SITES_Warning") );
				AUTOInspectionSiteStruct[sitesNum].ImgScaleFactor=q.GetInt( wxT("SITES_ScaleFactor") );

				AUTOInspectionSiteStruct[sitesNum].BestChannel	=	q.GetInt(wxT("SITES_BestChannel"));
				AUTOInspectionSiteStruct[sitesNum].BestHue	=	q.GetDouble(wxT("SITES_BestHue"));
				AUTOInspectionSiteStruct[sitesNum].PadThreshold = q.GetInt(wxT("SITES_PadThr"));

				AUTOInspectionSiteStruct[sitesNum].PasteCentralHUE = q.GetInt("SITES_PasteCentralHUE");
				AUTOInspectionSiteStruct[sitesNum].PasteHUEWidth = q.GetInt("SITES_PasteHUEWidth");

				AUTOInspectionSiteStruct[sitesNum].BestChannelPads = q.GetInt("SITES_BestChannelPads");
				AUTOInspectionSiteStruct[sitesNum].CentralPadsColor = q.GetInt("SITES_CentralPadsColor");
				AUTOInspectionSiteStruct[sitesNum].PadsColorWidth = q.GetInt("SITES_PadsColorWidth");
				//load pcb spots
				try
						{
							wxSQLite3ResultSet s = _DBspiAUTO.ExecuteQuery( wxString::Format("SELECT * FROM SPOTS WHERE SITES_ID = %d AND SPOTS_Type = 'PCB';", AUTOInspectionSiteStruct[sitesNum].IdSite) );

							//Clear structs
							AUTOInspectionSiteStruct[sitesNum].Area.clear();
							AUTOInspectionSiteStruct[sitesNum].Centroids.clear();
							AUTOInspectionSiteStruct[sitesNum].SpotEnable.clear();
							AUTOInspectionSiteStruct[sitesNum].Uncovered_Area.clear();
							AUTOInspectionSiteStruct[sitesNum].Contours.clear();
							AUTOInspectionSiteStruct[sitesNum].Area_Mask.clear();
							AUTOInspectionSiteStruct[sitesNum].Centroids_Mask.clear();
							AUTOInspectionSiteStruct[sitesNum].Contours_Mask.clear();
							AUTOInspectionSiteStruct[sitesNum].Coupled_spots.Mask.clear();
							AUTOInspectionSiteStruct[sitesNum].Coupled_spots.PCB.clear();

							while( s.NextRow() ){
								int spotID=s.GetInt( wxT("SPOTS_ID") );
								AUTOInspectionSiteStruct[sitesNum].Area.push_back( s.GetDouble( wxT("SPOTS_Area") ) );
								cv::Point2f P;
								P.x = s.GetDouble( wxT("SPOTS_X_Centroid") );
								P.y = s.GetDouble( wxT("SPOTS_Y_Centroid") );
								AUTOInspectionSiteStruct[sitesNum].Centroids.push_back(P);
								AUTOInspectionSiteStruct[sitesNum].SpotEnable.push_back( s.GetBool( wxT("SPOTS_Enable") ) );
								AUTOInspectionSiteStruct[sitesNum].Uncovered_Area.push_back(s.GetDouble( wxT("SPOTS_UncoveredArea")) );
								wxString Name= s.GetString( wxT("SPOTS_Contours") );
								string String_contour =Name.ToAscii();


								//split points
								std::string delimiter = ";";
								size_t pos = 0;
								vector<string> String_Points;
								cv::Point pippo;
								int counter_points=0;
								vector<cv::Point> single_contour;

								while ( (pos = String_contour.find(delimiter)) != std::string::npos) {
									String_Points.push_back( String_contour.substr(0, pos) );
									String_contour.erase(0, pos + delimiter.length());

									pos = String_Points[counter_points].find(","); //dont know if the coord has 1,2,or 3 digits
									pippo.x= std::atoi( String_Points[counter_points].substr(0, pos).c_str() );
									pippo.y= std::atoi( String_Points[counter_points++].substr(++pos).c_str()  );
									single_contour.push_back(pippo);

									}






								AUTOInspectionSiteStruct[sitesNum].Contours.push_back(single_contour);
								//cout<<String_contour<<endl;

							}
						}
				catch( wxSQLite3Exception& exc )
						{
							wxMessageBox( exc.GetMessage(), "wxSQLite_AREA_PCB", wxOK | wxICON_ERROR );
							return SR_ERROR;
						}

				//load Mask spots
				try
					{
							wxSQLite3ResultSet s = _DBspiAUTO.ExecuteQuery( wxString::Format("SELECT * FROM SPOTS WHERE SITES_ID = %d AND SPOTS_Type = 'Mask';", AUTOInspectionSiteStruct[sitesNum].IdSite) );

							while( s.NextRow() ){
								int spotID=s.GetInt( wxT("SPOTS_ID") );
								AUTOInspectionSiteStruct[sitesNum].Area_Mask.push_back( s.GetDouble( wxT("SPOTS_Area") ) );
								cv::Point2f P;
								P.x = s.GetDouble( wxT("SPOTS_X_Centroid") );
								P.y = s.GetDouble( wxT("SPOTS_Y_Centroid") );
								AUTOInspectionSiteStruct[sitesNum].Centroids_Mask.push_back(P);
								//AUTOInspectionSiteStruct[sitesNum].SpotEnable.push_back( s.GetBool( wxT("SPOTS_Enable") ) );

								wxString Name= s.GetString( wxT("SPOTS_Contours") );
								string String_contour =Name.ToAscii();


								//split points
								std::string delimiter = ";";
								size_t pos = 0;
								vector<string> String_Points;
								cv::Point pippo;
								int counter_points=0;
								vector<cv::Point> single_contour;

								while ( (pos = String_contour.find(delimiter)) != std::string::npos) {
										String_Points.push_back( String_contour.substr(0, pos) );
										String_contour.erase(0, pos + delimiter.length());

										pos = String_Points[counter_points].find(","); //dont know if the coord has 1,2,or 3 digits
										pippo.x= std::atoi( String_Points[counter_points].substr(0, pos).c_str() );
										pippo.y= std::atoi( String_Points[counter_points++].substr(++pos).c_str()  );
										single_contour.push_back(pippo);

										}






										AUTOInspectionSiteStruct[sitesNum].Contours_Mask.push_back(single_contour);
										//cout<<String_contour<<endl;

								}
						}
				catch( wxSQLite3Exception& exc )
						{
							wxMessageBox( exc.GetMessage(), "wxSQLite_AREA_Mask", wxOK | wxICON_ERROR );
							return SR_ERROR;
						}



						sitesNum++;


			}
		}
	catch( wxSQLite3Exception& exc )
		{
			wxMessageBox( exc.GetMessage(), "wxSQLite_SITE", wxOK | wxICON_ERROR );
			return SR_ERROR;
		}


	// load first site
	pAUTOInspectionCurrentSiteStruct = AUTOInspectionSiteStruct;
	savedSite = savedArea = 0;



	//get the last ID of spots
	wxSQLite3ResultSet last = _DBspiAUTO.ExecuteQuery( wxString::Format("SELECT SPOTS_ID FROM SPOTS") );
	//int final_id_spots=0;
	while(last.NextRow()){
		final_id_spots=last.GetInt("SPOTS_ID");}

	last = _DBspiAUTO.ExecuteQuery( wxString::Format("SELECT RESULTS_ID FROM RESULTS") );
		//int final_id_spots=0;
		while(last.NextRow()){
			final_id_results=last.GetInt("RESULTS_ID");}

	SavedResult=0;
	///////////////////////////////////////////////////////////////////////////////
	//converto tutti i png to jpeg
	/////////////////////////////////////////////////////////////////////////////////
	/*wxString path( "/home/dpelitti12/Projects/wxsr3200/vision/B23B-TOP");
	wxString filename;
	wxDir *dir = new wxDir(path);
	bool cont = dir->GetFirst(&filename);
	while(cont)
	{
		filename= path + "/" + filename; //complete path
		cv::Mat img_tmp = cv::imread(filename.ToAscii());
		wxRemoveFile(filename);

		wxString newfile = filename.SubString( 0, filename.Length() -5);
		cout<<newfile<<endl;
		newfile.append(".jpeg");
		cv::imwrite(newfile.ToAscii(), img_tmp);
		cont = dir->GetNext(&filename);
		//cont= false;
	}*/


	return SR_OK;
}

//----------------------------------------------------------------------------------
// SaveInspectionSite
//----------------------------------------------------------------------------------
int SRDatabase::SaveInspectionSite( int siteNum )
{
	//cout<< "salvo sito "<<siteNum << "pointsNum: "<< AUTOInspectionSiteStruct[siteNum].PointsNum<<endl;
	//cout<< "aggiorno diteID: "<< AUTOInspectionSiteStruct[siteNum].IdSite<<endl;
	try
	{

		wxSQLite3StatementBuffer stmtBuffer;
		_DBspiAUTO.ExecuteQuery( stmtBuffer.Format("UPDATE SITES SET "
				"SITES_Name = '%s', "
				"SITES_X = %f, "
				"SITES_Y = %f, "
				"SITES_Orientation = %f, "
				"SITES_Binarization_threshold = %d, "
				"SITES_Enable = %d, "
				"SITES_Brightness = %f, "
				"SITES_Contrast = %f, "
				"SITES_PointsNum = %d, "
				"SITES_Alarm = %d, "
				"SITES_Warning = %d, "
				"SITES_ScaleFactor = %d, "
				"SITES_BestChannel = %d, "
				"SITES_BestHue = %f, "
				"SITES_PadThr = %d, "
				"SITES_PasteCentralHUE = %d, "
				"SITES_PasteHUEWidth = %d, "
				"SITES_BestChannelPads = %d, "
				"SITES_CentralPadsColor = %d, "
				"SITES_PadsColorWidth = %d "
				"WHERE SITES_ID = %d ;",
				AUTOInspectionSiteStruct[siteNum].Name.ToAscii(),
				AUTOInspectionSiteStruct[siteNum].X,
				AUTOInspectionSiteStruct[siteNum].Y,
				AUTOInspectionSiteStruct[siteNum].Orientation,
				AUTOInspectionSiteStruct[siteNum].BinarizationThr,
				AUTOInspectionSiteStruct[siteNum].Enable,
				AUTOInspectionSiteStruct[siteNum].CameraBrightness,
				AUTOInspectionSiteStruct[siteNum].CameraContrast,
				AUTOInspectionSiteStruct[siteNum].PointsNum,
				AUTOInspectionSiteStruct[siteNum].Alarm,
				AUTOInspectionSiteStruct[siteNum].Warning,
				AUTOInspectionSiteStruct[siteNum].ImgScaleFactor,
				AUTOInspectionSiteStruct[siteNum].BestChannel,
				AUTOInspectionSiteStruct[siteNum].BestHue,
				AUTOInspectionSiteStruct[siteNum].PadThreshold,
				AUTOInspectionSiteStruct[siteNum].PasteCentralHUE,
				AUTOInspectionSiteStruct[siteNum].PasteHUEWidth,
				AUTOInspectionSiteStruct[siteNum].BestChannelPads,
				AUTOInspectionSiteStruct[siteNum].CentralPadsColor,
				AUTOInspectionSiteStruct[siteNum].PadsColorWidth,
				AUTOInspectionSiteStruct[siteNum].IdSite

		) );
		//cout<< "provo il buffer "<<stmtBuffer<<endl;


	}
	catch( wxSQLite3Exception& exc )
			{
				wxMessageBox( exc.GetMessage(), "wxSQLite_update_sites", wxOK | wxICON_ERROR );
				return SR_ERROR;
			}

	//site updated, now we must update spots
	try
		{

		//load the old spots
			wxSQLite3ResultSet s = _DBspiAUTO.ExecuteQuery( wxString::Format("SELECT * FROM SPOTS WHERE SITES_ID = %d; AND SPOTS_Type= 'PCB';", AUTOInspectionSiteStruct[siteNum].IdSite) );

			//delete the old spots and all the associated contours
			while ( s.NextRow() ){
				_DBspiAUTO.ExecuteQuery( wxString::Format("DELETE FROM SPOTS WHERE SPOTS_ID = %d AND SPOTS_Type= 'PCB';", s.GetInt( wxT("SPOTS_ID"))  ) );

			}

			wxSQLite3StatementBuffer stmtBuffer;




			//insert new spots
			cv::vector<cv::Point> ciccio;
			for(int i=0; i<AUTOInspectionSiteStruct[siteNum].PointsNum; i++){

				//Prepare contours as string to be stored
				std::string stringa;
				ciccio=AUTOInspectionSiteStruct[siteNum].Contours[i];
				for (int j=0; j<AUTOInspectionSiteStruct[siteNum].Contours[i].size(); j++){


				stringa.append( wxString::Format( wxT("%i"), ciccio[j].x ).ToAscii());
				stringa.append(",");
				stringa.append( wxString::Format( wxT("%i"), ciccio[j].y ).ToAscii());
				stringa.append(";");

				}

			wxString pippo(stringa); //string directly in DB causes problems
			//(SPOTS_Area,SPOTS_X_Centroid,SPOTS_Y_Centroid,SPOTS_Enable,SITE_ID)
			_DBspiAUTO.ExecuteUpdate( stmtBuffer.Format("INSERT INTO SPOTS VALUES (%d, %f, %f, %f, %d, '%s','%s', %d, %f);",
			++final_id_spots,
			AUTOInspectionSiteStruct[siteNum].Area[i],
			AUTOInspectionSiteStruct[siteNum].Centroids[i].x,
			AUTOInspectionSiteStruct[siteNum].Centroids[i].y,
			(int)AUTOInspectionSiteStruct[siteNum].SpotEnable[i],
			pippo.ToAscii(),
			wxT("PCB"),
			AUTOInspectionSiteStruct[siteNum].IdSite,
			AUTOInspectionSiteStruct[siteNum].Uncovered_Area[i] ) );
				}

		}
	catch( wxSQLite3Exception& exc )
			{
				wxMessageBox( exc.GetMessage(), "wxSQLite_update_spots", wxOK | wxICON_ERROR );
				return SR_ERROR;
			}

	return SR_OK;
}

int SRDatabase::SaveInspectionSiteMask( )
{
	try
			{

			//load the old spots
			wxSQLite3ResultSet s = _DBspiAUTO.ExecuteQuery( wxString::Format("SELECT * FROM SPOTS WHERE SITES_ID = %d AND SPOTS_Type = 'Mask';", pAUTOInspectionCurrentSiteStruct->IdSite) );

				//delete the old spots and all the associated contours
				while ( s.NextRow() ){
					_DBspiAUTO.ExecuteQuery( wxString::Format("DELETE FROM SPOTS WHERE SPOTS_ID = %d AND SPOTS_Type = 'Mask';", s.GetInt( wxT("SPOTS_ID"))  ) );

				}


				wxSQLite3StatementBuffer stmtBuffer;

				//insert new spots
				cv::vector<cv::Point> ciccio;
				for(int i=0; i<pAUTOInspectionCurrentSiteStruct->Centroids_Mask.size(); i++)
				{
					//Prepare contours as string to be stored
					std::string stringa;
					ciccio=pAUTOInspectionCurrentSiteStruct->Contours_Mask[i];

					for (int j=0; j<pAUTOInspectionCurrentSiteStruct->Contours_Mask[i].size(); j++)
					{
						stringa.append( wxString::Format( wxT("%i"), ciccio[j].x ).ToAscii());
						stringa.append(",");
						stringa.append( wxString::Format( wxT("%i"), ciccio[j].y ).ToAscii());
						stringa.append(";");
					}

				wxString pippo(stringa); //string directly in DB causes problems

				//(SPOTS_Area,SPOTS_X_Centroid,SPOTS_Y_Centroid,SPOTS_Enable,SITE_ID)
				_DBspiAUTO.ExecuteUpdate( stmtBuffer.Format("INSERT INTO SPOTS VALUES (%d, %f, %f, %f, %d, '%s','%s', %d, %f);",
				++final_id_spots,
				pAUTOInspectionCurrentSiteStruct->Area_Mask[i],
				pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i].x,
				pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i].y,
				1,
				pippo.ToAscii(),
				wxT("Mask"),
				pAUTOInspectionCurrentSiteStruct->IdSite,
				SPI_UNDEFINED_FLOAT) ); //this one is the uncoveredArea, saved in the PCB records
					}


			}
		catch( wxSQLite3Exception& exc )
				{
					wxMessageBox( exc.GetMessage(), "wxSQLite_update_spots_mask", wxOK | wxICON_ERROR );
					return SR_ERROR;
				}

		return SR_OK;
	}

int SRDatabase::UpdateName( int siteNum ){
	try
	{
		_DBspiAUTO.ExecuteQuery( wxString::Format("UPDATE SITES SET SITES_Name= '%s' WHERE SITES_ID = %d ", AUTOInspectionSiteStruct[siteNum].Name.ToAscii(),  AUTOInspectionSiteStruct[siteNum].IdSite ) );

	}
	catch( wxSQLite3Exception& exc )
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_update_Name", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}
}

//----------------------------------------------------------------------------------
// InsertInspectionSite
// Inserisce nel DB (e nella struct in memoria) un nuovo sito di ispezione
// Ritorna l'IdSite inserito se ok, SR_ERROR altrimenti
//----------------------------------------------------------------------------------
int SRDatabase::InsertInspectionSite()
{
	//cout<<"inserisco nuovo sito"<<endl;
	wxString empty_str( wxT("") );

	if( sitesNum >= NUM_INSPECTION_SITES )
		return SR_ERROR;

	//aggiunto
	wxSQLite3ResultSet last = _DBspiAUTO.ExecuteQuery( wxString::Format("SELECT SITES_ID FROM SITES ORDER BY SITES_ID DESC") );
	int final_id=0;
	/*while(last.NextRow()){
		final_id=last.GetInt("SITES_ID");}*/
	final_id=last.GetInt("SITES_ID");

	try{
		wxSQLite3StatementBuffer stmtBuffer;
		_DBspiAUTO.ExecuteUpdate( stmtBuffer.Format("INSERT INTO SITES VALUES ( %d, '%s', %f, %f, %f, %d, %d, %f, %f, %d, %d, %d, %d, %d, %d, %f, %d, %d, %d, %d,%d, %d )",
			++final_id,
			empty_str.ToAscii(),
			SPI_POS,
			SPI_POS,
			SPI_POS,
			SPI_BIN_THR,
			SPI_ENABLE,
			SPI_CAMERA_BRIGHTNESS,
			SPI_CAMERA_CONTRAST,
			0, //pointsnum
			SPI_ALARM ,
			SPI_WARNING,
			ProductionDataS.IdProd,
			0,				//0 is the ImgScaleFactor
			SPI_UNDEFINED, 	//bestChannel
			SPI_UNDEFINED_FLOAT,		//bestHue
			SPI_UNDEFINED,		//pasteThr
			SPI_UNDEFINED,
			SPI_UNDEFINED,	//padCenter
			SPI_UNDEFINED,	//BestChannelPads
			200,	//CentralPadsColor
			15) ); 	//PadsColorWidth
	}
	catch( wxSQLite3Exception& exc )
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_new_insert", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}

	AUTOInspectionSiteStruct[sitesNum].IdSite = final_id;
	AUTOInspectionSiteStruct[sitesNum].IdProd = ProductionDataS.IdProd;
	AUTOInspectionSiteStruct[sitesNum].Name = wxT("");
	AUTOInspectionSiteStruct[sitesNum].X = SPI_POS;
	AUTOInspectionSiteStruct[sitesNum].Y = SPI_POS;;
	AUTOInspectionSiteStruct[sitesNum].BinarizationThr = SPI_BIN_THR;
	AUTOInspectionSiteStruct[sitesNum].Enable = SPI_ENABLE;
	AUTOInspectionSiteStruct[sitesNum].CameraBrightness = SPI_CAMERA_BRIGHTNESS;
	AUTOInspectionSiteStruct[sitesNum].CameraContrast = SPI_CAMERA_CONTRAST;
	AUTOInspectionSiteStruct[sitesNum].PointsNum =0;
	AUTOInspectionSiteStruct[sitesNum].Area = *new vector<double>;
	AUTOInspectionSiteStruct[sitesNum].Contours = *new vector< vector<cv::Point> >;
	AUTOInspectionSiteStruct[sitesNum].Centroids= *new vector<cv::Point2f>;;
	AUTOInspectionSiteStruct[sitesNum].Alarm =SPI_ALARM ;
	AUTOInspectionSiteStruct[sitesNum].Warning =SPI_WARNING ;
	AUTOInspectionSiteStruct[sitesNum].ImgScaleFactor = 0;

	AUTOInspectionSiteStruct[sitesNum].BestHue = SPI_UNDEFINED;
	AUTOInspectionSiteStruct[sitesNum].BestChannel = SPI_UNDEFINED;
	AUTOInspectionSiteStruct[sitesNum].PadThreshold =SPI_UNDEFINED;
	AUTOInspectionSiteStruct[sitesNum].PasteHUEWidth = SPI_UNDEFINED;
	AUTOInspectionSiteStruct[sitesNum].PasteCentralHUE = SPI_UNDEFINED;
	AUTOInspectionSiteStruct[sitesNum].BestChannelPads = SPI_UNDEFINED;
	AUTOInspectionSiteStruct[sitesNum].CentralPadsColor = 200;
	AUTOInspectionSiteStruct[sitesNum].PadsColorWidth = 15;
	//cout<< "inserito sito "<<sitesNum<<endl;
	sitesNum++;


	return 1;
}

//----------------------------------------------------------------------------------
// DeleteInspectionSite
// Elimina dal DB il sito di ispezione selezionato
//----------------------------------------------------------------------------------
int SRDatabase::DeleteInspectionSite( int siteNum )
{

	//we not delete it, we just change the foreign key of production
	//cout<< "deleting site: "<<siteNum<<endl;
	try
		{
			wxSQLite3StatementBuffer stmtBuffer;
			//delete the site (actually the site is hidden)
			_DBspiAUTO.ExecuteQuery( stmtBuffer.Format("UPDATE SITES SET SITES_IdProd = %d WHERE SITES_ID = %d",-1, AUTOInspectionSiteStruct[siteNum].IdSite ) );
			//delete the children
			_DBspiAUTO.ExecuteUpdate( stmtBuffer.Format("DELETE FROM SPOTS WHERE SITES_ID = %d", AUTOInspectionSiteStruct[siteNum].IdSite ) );
		}
		catch( wxSQLite3Exception& exc )
		{
			wxMessageBox( exc.GetMessage(), "wxSQLite_DELETE_entire_site", wxOK | wxICON_ERROR );
			return SR_ERROR;
		}




	//aggiunto
	for( AUTOInspectionSitesStruct* p = pAUTOInspectionCurrentSiteStruct + 1; p < &AUTOInspectionSiteStruct[sitesNum]; p++ )
		{
			*(p-1) = *p;
		}


	sitesNum--;

	// 
	if( sitesNum )
	{

		pAUTOInspectionCurrentSiteStruct=MIN( pAUTOInspectionCurrentSiteStruct, &AUTOInspectionSiteStruct[sitesNum-1] );;
	}
	else
	{
		siteAreasNum = 0;
	}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// DeleteInspectionSiteAll
// Elimina dal DB tutti i siti di ispezione della produzione corrente
//----------------------------------------------------------------------------------
int SRDatabase::DeleteInspectionSiteAll( int idProd, bool keepResults )
{
	sitesNum = 0;
	siteAreasNum = 0;


	try
		{
			wxSQLite3ResultSet s = _DBspiAUTO.ExecuteQuery( wxString::Format("SELECT SITES_ID FROM SITES WHERE SITES_IdProd = %d", idProd ) );
			try{
				wxSQLite3StatementBuffer stmtBuffer;
				while(s.NextRow()){
					_DBspiAUTO.ExecuteUpdate( stmtBuffer.Format("DELETE FROM SPOTS WHERE SITES_ID = %d", s.GetInt("SITES_ID") ) );
				}
			}
			catch (wxSQLite3Exception& exc) {
				wxMessageBox( exc.GetMessage(), "wxSQLite_DELETE_ALL_SPOTS", wxOK | wxICON_ERROR );
			}

			wxSQLite3StatementBuffer stmtBuffer;
			_DBspiAUTO.ExecuteQuery( stmtBuffer.Format("DELETE FROM SITES WHERE SITES_IdProd = %d", idProd ) );

			if(!keepResults){
				wxString path( wxString::Format(FILE_PRODUCTION_FOLDER,ProductionDataS.ProductionName.ToAscii()));
				wxString filename;
				wxDir *dir = new wxDir(path);
				bool cont = dir->GetFirst(&filename);
				while(cont)
				{
					filename= path + "/" + filename; //complete path
					wxRemoveFile(filename);
					cont = dir->GetNext(&filename);
				}
				wxRmdir( path );
				_DBspiAUTO.ExecuteUpdate( stmtBuffer.Format("DELETE FROM RESULTS WHERE SITES_IdProd = %d", idProd ) );
			}
			else{
				_DBspiAUTO.ExecuteQuery(stmtBuffer.Format("INSERT INTO DELETED_PRODUCTIONS VALUES(%d, '%s')", idProd, ProductionDataS.ProductionName.ToAscii()));
			}

		}
		catch( wxSQLite3Exception& exc )
		{
			wxMessageBox( exc.GetMessage(), "wxSQLite_DELETE_ALL_idProd", wxOK | wxICON_ERROR );
			return SR_ERROR;
		}

	return SR_OK;
}

//----------------------------------------------------------------------------------
// ClearInspectionSite
// Resetta il sito di ispezione selezionato
//----------------------------------------------------------------------------------
int SRDatabase::ClearInspectionSite( int siteNum )
{

	// clear vector values
	AUTOInspectionSiteStruct[siteNum].Enable = 0;
	AUTOInspectionSiteStruct[siteNum].PointsNum = 0;
	AUTOInspectionSiteStruct[siteNum].Contours.clear();
	AUTOInspectionSiteStruct[siteNum].Area.clear();
	AUTOInspectionSiteStruct[siteNum].Centroids.clear();

	AUTOInspectionSiteStruct[siteNum].Centroids_Mask.clear();
	AUTOInspectionSiteStruct[siteNum].Contours_Mask.clear();
	AUTOInspectionSiteStruct[siteNum].Coupled_spots.Mask.clear();
	AUTOInspectionSiteStruct[siteNum].Coupled_spots.PCB.clear();
	AUTOInspectionSiteStruct[siteNum].Area_Mask.clear();

	return SR_OK;
}

//---------------------------------------------------------------------------------
//SaveResults
//---------------------------------------------------------------------------------
int SRDatabase::SaveResults () {
	//results are saved in progressive order!

	for (int i=0; i < Spots2Save; i++){
		long int rigth_now = (long int) time(NULL);

		try{
				wxSQLite3StatementBuffer stmtBuffer;
				_DBspiAUTO.ExecuteUpdate( stmtBuffer.Format("INSERT INTO RESULTS VALUES ( %d, %d, %f, %f, %f, %d, %d, %d, %d, %f, %f , %d)",
				++final_id_results,
				AUTOInspectionResults[i].White_pixels,
				AUTOInspectionResults[i].SiteX,
				AUTOInspectionResults[i].SiteY,
				AUTOInspectionResults[i].Percentage_covered,
				ProductionDataS.Counter,
				pAUTOInspectionCurrentSiteStruct->IdSite,
				rigth_now,
				AUTOInspectionResults[i].Connected, //0 not connected, 1 connected!
				AUTOInspectionResults[i].WhiteX,
				AUTOInspectionResults[i].WhiteY,
				ProductionDataS.IdProd) );
			}
		catch( wxSQLite3Exception& exc )
		{
			wxMessageBox( exc.GetMessage(), "wxSQLite_Save_result", wxOK | wxICON_ERROR );
			return SR_ERROR;
		}
	}



	return 1;

}
//----------------------------------------------------------------------------------
// SiteFirst
//----------------------------------------------------------------------------------
bool SRDatabase::SiteFirst()
{
	if( SiteCount() )
	{
		//SaveInspectionSite( SiteGetSelected() );

		//aggiunto
		pAUTOInspectionCurrentSiteStruct = AUTOInspectionSiteStruct;
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------
// SiteLast
//----------------------------------------------------------------------------------
bool SRDatabase::SiteLast()
{
	if( SiteCount() )
	{
		//aggiunto
		pAUTOInspectionCurrentSiteStruct = &AUTOInspectionSiteStruct[sitesNum-1];
		return true;
	}
	return false;
}

//----------------------------------------------------------------------------------
// SiteNext
//----------------------------------------------------------------------------------
bool SRDatabase::SiteNext()
{
	if( SiteIsLast() || SiteCount() == 0 )
		return false;


	pAUTOInspectionCurrentSiteStruct++;

	return true;
}

//----------------------------------------------------------------------------------
// SitePrev
//----------------------------------------------------------------------------------
bool SRDatabase::SitePrev()
{
	if( SiteIsFirst() || SiteCount() == 0 )
		return false;

	pAUTOInspectionCurrentSiteStruct--;

	return true;
}

//----------------------------------------------------------------------------------
// SiteGetSelected
// return -1 on error
//----------------------------------------------------------------------------------
int SRDatabase::SiteGetSelected()
{


	int pos = pAUTOInspectionCurrentSiteStruct - AUTOInspectionSiteStruct;


	return ( pos < 0 || pos >= NUM_INSPECTION_SITES ) ? -1 : pos;
}

//----------------------------------------------------------------------------------
// SiteSelect
//----------------------------------------------------------------------------------
bool SRDatabase::SiteSelect( int pos )
{
	if( SiteCount() )
	{
		UpdateName( SiteGetSelected() );


		//aggiunto
		pAUTOInspectionCurrentSiteStruct = MID (AUTOInspectionSiteStruct, AUTOInspectionSiteStruct +pos, &AUTOInspectionSiteStruct[sitesNum-1] );

		int newpos = pAUTOInspectionCurrentSiteStruct - AUTOInspectionSiteStruct;

		return newpos != pos ? false : true;
	}
	return false;
}







//----------------------------------------------------------------------------------
// SiteSavePosition
//----------------------------------------------------------------------------------
void SRDatabase::SiteSavePosition()
{
	savedSite = SiteGetSelected();
}

//----------------------------------------------------------------------------------
// SiteRestorePosition
//----------------------------------------------------------------------------------
void SRDatabase::SiteRestorePosition()
{
	SiteSelect( savedSite );
}

bool SRDatabase::ClearResultStruct()
{
	for(int i=0; i<NUM_INSPECTION_POINTS; i++)
	{
		AUTOInspectionResults[i].SpotNum = 0;
		AUTOInspectionResults[i].White_pixels = 0;
		AUTOInspectionResults[i].WhiteX = 0.0;
		AUTOInspectionResults[i].WhiteY = 0.0;
		AUTOInspectionResults[i].Percentage_covered = 0.0;
		AUTOInspectionResults[i].SiteX = 0.0;
		AUTOInspectionResults[i].SiteY = 0.0;
	}
	//SavedResult=0;
}



//////////////////////////////////////////////////////////////////////////
//			added for records
/////////////////////////////////////////////////////////////////////////

int SRDatabase::LoadBoards(wxString Name){

	recordNum=-1;
	//load the last board
	int lastBoard=0;
	//clear the struct
	ClearBoardStruct();

	//1704
	//struct timeval tp;
	//gettimeofday(&tp, NULL);
	//long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;



	try
		{
		wxSQLite3ResultSet q;

		if(Name=="All"){
		 q = _DBspiAUTO.ExecuteQuery( wxT("SELECT * FROM RESULTS ORDER BY RESULTS_N_Scheda DESC") );
		}
		else{
			wxSQLite3ResultSet ID_finder = _SR3200.ExecuteQuery( wxString::Format( "SELECT idProd, ProductionName  FROM productiondata WHERE ProductionName = '%s' ;", Name.ToAscii()) );
			int ID= ID_finder.GetInt( 0 ); //it doesn't like  wxT("idProd"). IDProd is the frst column
			if(ID==0){
				wxSQLite3ResultSet ID_finder = _DBspiAUTO.ExecuteQuery( wxString::Format( "SELECT ID_PROD FROM DELETED_PRODUCTIONS WHERE PRODUCTION_NAME = '%s' ;", Name.ToAscii()) );
				ID= ID_finder.GetInt( 0 );
			}
			q = _DBspiAUTO.ExecuteQuery( wxString::Format( "SELECT * FROM RESULTS WHERE SITES_IdProd=%d ORDER BY RESULTS_N_Scheda DESC",ID ) ) ;
		}

		//1704
		//struct timeval tp2;
		//gettimeofday(&tp2, NULL);
		//long int ms2 = tp2.tv_sec * 1000 + tp2.tv_usec / 1000;

		int boardNumIndex = q.FindColumnIndex(wxT("RESULTS_N_Scheda"));
		int siteIDProd = q.FindColumnIndex(wxT("SITES_IdProd"));
		int dateIndex = q.FindColumnIndex( wxT("RESULTS_Date"));
		int percentageIndex = q.FindColumnIndex( wxT("RESULTS_Percentage_Covered"));
		int connectedIndex = q.FindColumnIndex( wxT("SPOTS_ID_Connected"));

		int previous_board = -1;
		int previous_site = -1;
		int whiteCounter=0;
		int connectedSpots=0;
		int Alarm=0;

		while( q.NextRow() ){

			int actual_board = q.GetInt(boardNumIndex);
			int actual_site = q.GetInt(wxT("SITES_ID"));


			if (actual_board != previous_board){

				recordNum++;
				if(recordNum==NUM_INSPECTION_POINTS){
					break;
				}
				RecordedBoardstruct[recordNum].WhiteAreas=0; //first i clean these values
				RecordedBoardstruct[recordNum].ConnectedSpots=0; //first i clean these values

				RecordedBoardstruct[recordNum].BoardNumber = q.GetInt(boardNumIndex);//q.GetInt(wxT("RESULTS_N_Scheda"));
				RecordedBoardstruct[recordNum].ID_production = q.GetInt(siteIDProd);//q.GetInt(wxT("SITES_IdProd"));
				//RecordedBoardstruct[recordNum].ID_Site = q.GetInt(wxT("SITES_ID"));
				RecordedBoardstruct[recordNum].Time = q.GetInt(dateIndex);;//q.GetInt( wxT("RESULTS_Date"));

				if (Name != "All"){
					RecordedBoardstruct[recordNum].ProductionName = Name;
				}
				else{
					wxSQLite3ResultSet NameProd =  _SR3200.ExecuteQuery(  wxString::Format("SELECT ProductionName FROM ProductionData WHERE IdProd= %d", RecordedBoardstruct[recordNum].ID_production) );
					RecordedBoardstruct[recordNum].ProductionName = NameProd.GetString(wxT("ProductionName"));
				}
				previous_board= actual_board;

			}

			if(actual_site != previous_site){
				wxSQLite3ResultSet Alarm_q =  _DBspiAUTO.ExecuteQuery(  wxString::Format("SELECT SITES_Alarm FROM SITES WHERE SITES_ID= %d", q.GetInt(wxT("SITES_ID")) ) );
				//Alarm_q.NextRow();
				Alarm = Alarm_q.GetInt("SITES_Alarm");
				previous_site = actual_site;
			}
			/*
			//cout<<q.GetInt(wxT("SITES_ID"))<<endl;
			wxSQLite3ResultSet Alarm_q =  _DBspiAUTO.ExecuteQuery(  wxString::Format("SELECT SITES_Alarm FROM SITES WHERE SITES_ID= %d", q.GetInt(wxT("SITES_ID")) ) );
			//Alarm_q.NextRow();
			Alarm = Alarm_q.GetInt("SITES_Alarm");
			previous_board= actual_board; */



			if ( q.GetDouble(percentageIndex) > 100-Alarm  ){
				RecordedBoardstruct[recordNum].WhiteAreas++;
			}
			if (q.GetInt(connectedIndex) >0 ){
				RecordedBoardstruct[recordNum].ConnectedSpots++;
			}



		}

		//1704
		//struct timeval tp3;
		//gettimeofday(&tp3, NULL);
		//long int ms3 = tp3.tv_sec * 1000 + tp3.tv_usec / 1000;
		//std::cout << "finished computation at " <<ms3 -ms2 << " risultati estratti dal db in: "<<ms2 -ms<< endl;;

		return recordNum;

}


	catch( wxSQLite3Exception& exc )
		{
			wxMessageBox( exc.GetMessage(), "wxSQLite_LoadBoards", wxOK | wxICON_ERROR );
			return false;
		}

	return 1;
};


int SRDatabase::BoardsNum( ){
	return recordNum;
}

int SRDatabase::LoadResultsSites( int BoardNumber, int IDprod, int siteNum){

	int CurrentSiteID;
	int PrevSiteID;
	int counter=0;

	ClearPointsStruct();

	SavedResult=0;
	try{
		wxSQLite3ResultSet q = _DBspiAUTO.ExecuteQuery( wxString::Format("SELECT * FROM RESULTS WHERE SITES_IdProd = %d AND RESULTS_N_Scheda=%d ORDER BY RESULTS_DATE ASC", IDprod, BoardNumber ) );
		//if( !q.NextRow() ){
			//return 0;	//there are not spots
		//}


		int counter=-1;
		int prev_site_id=-1;

		bool first_time=true;
		int Alarm;
		int Warning;
		wxString Name;



		while( q.NextRow() ){

			int Current_site_id = q.GetInt("SITES_ID");
			if(Current_site_id!=prev_site_id){
				counter++;
				first_time=true; //every time i change site, i need to refresh alarm thr and name
			}
			prev_site_id = Current_site_id;



			//if ( siteNum == counter ) {
				AUTOInspectionPointRecord[SavedResult].Percentage_covered = q.GetDouble("RESULTS_Percentage_Covered");
				AUTOInspectionPointRecord[SavedResult].ConnectedWith = q.GetInt("SPOTS_ID_Connected");
				AUTOInspectionPointRecord[SavedResult].SiteNum = counter;




				if(first_time){
					//wxSQLite3ResultSet Alarm_q =  _DBspiAUTO.ExecuteQuery(  wxString::Format("SELECT SITES_Alarm, SITES_Name FROM SITES WHERE SITES_IdProd= %d", RecordedBoardstruct[siteNum].ID_production) );
					wxSQLite3ResultSet Alarm_q =  _DBspiAUTO.ExecuteQuery(  wxString::Format("SELECT SITES_Alarm, SITES_Name, SITES_Warning FROM SITES WHERE SITES_ID= %d", Current_site_id ) );
					/*
					for (int i=0; i<counter+1; i++){
						Alarm_q.NextRow();
						//cout<<Alarm_q.GetString("SITES_Name").ToAscii()<<endl;
					}*/

					Alarm = Alarm_q.GetInt("SITES_Alarm");
					Warning = Alarm_q.GetInt("SITES_Warning");
					//cout<<Warning<<endl;
					first_time =false;

					Name=  Alarm_q.GetString("SITES_Name");
					//cout<<Name.ToAscii()<<"  "<<Alarm<<endl;
				}
				AUTOInspectionPointRecord[SavedResult].Alarm = Alarm;
				strncpy(AUTOInspectionPointRecord[SavedResult].SiteName, (const char*)Name.mb_str(wxConvUTF8), 49);
				//AUTOInspectionPointRecord[SavedResult].SiteName = Name.ToAscii() ;
				AUTOInspectionPointRecord[SavedResult].Warning = Warning ;
				//cout<< Name.ToAscii()<<endl;
				AUTOInspectionPointRecord[SavedResult].ID_Site = q.GetInt("SITES_ID");
				//cout<< "   id site "<< AUTOInspectionPointRecord[SavedResult].ID_Site<<endl;
				AUTOInspectionPointRecord[SavedResult].SpotNum =counter;
				//cout<< "   spotNum "<< AUTOInspectionPointRecord[SavedResult].SpotNum;
				//cout<<endl;

				AUTOInspectionPointRecord[SavedResult].Centroids_PCB.x = q.GetDouble("RESULTS_X_Centroid");
				AUTOInspectionPointRecord[SavedResult].Centroids_PCB.y = q.GetDouble("RESULTS_Y_Centroid");


				SavedResult++;

				if(SavedResult==NUM_INSPECTION_POINTS*2){
					cout<<"limit on Saved results reached!!!"<<endl;
					break;
				}



		}

	}
	catch( wxSQLite3Exception& exc ){
		wxMessageBox( exc.GetMessage(), "wxSQLite_LoadResultsSites", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}
	return SavedResult;
}

wxString SRDatabase::LoadProductionName ( int IDprod){


	wxSQLite3ResultSet q =  _SR3200.ExecuteQuery(  wxString::Format("SELECT ProductionName FROM ProductionData WHERE IdProd= %d", IDprod) );
	q.NextRow();
	wxString Name = q.GetString("ProductionName");
	if(Name==wxT("")){
		wxSQLite3ResultSet deleted =_DBspiAUTO.ExecuteQuery( wxString::Format("SELECT PRODUCTION_NAME FROM DELETED_PRODUCTIONS WHERE ID_PROD = %d", IDprod));
		Name=deleted.GetString("PRODUCTION_NAME");
	}
	return Name;
}

wxArrayString SRDatabase::LoadAllNames(){

	wxArrayString names;
	wxSQLite3ResultSet query =  _DBspiAUTO.ExecuteQuery(  wxString::Format("SELECT DISTINCT SITES_IdProd FROM RESULTS") );

	while (query.NextRow()){
		wxSQLite3ResultSet NameProdCursor =  _SR3200.ExecuteQuery(  wxString::Format("SELECT ProductionName FROM ProductionData WHERE IdProd= %d", query.GetInt("SITES_IdProd")) );
		wxString name = NameProdCursor.GetString("ProductionName");
		if (name == wxT("")){
			wxSQLite3ResultSet deleted =_DBspiAUTO.ExecuteQuery( wxString::Format("SELECT PRODUCTION_NAME FROM DELETED_PRODUCTIONS WHERE ID_PROD = %d", query.GetInt("SITES_IdProd")));
			names.Add(deleted.GetString("PRODUCTION_NAME"));
		}
		else{
			names.Add(name);
		}

	}
	return names;



}

bool SRDatabase::WriteSPIparams()
{
	wxSQLite3StatementBuffer stmtBuffer;
	try{
		_DBspiAUTO.ExecuteQuery( stmtBuffer.Format("UPDATE SITES SET "
				"SITES_PasteCentralHUE = %d, "
				"SITES_PasteHUEWidth = %d, "
				"SITES_PadThr= %d, "
				"SITES_BestHue = %f, "
				"SITES_BestChannel = %d, "
				"SITES_BestChannelPads = %d, "
				"SITES_CentralPadsColor = %d, "
				"SITES_PadsColorWidth = %d  "
				"WHERE SITES_ID = %d; ",
				pAUTOInspectionCurrentSiteStruct->PasteCentralHUE,
				pAUTOInspectionCurrentSiteStruct->PasteHUEWidth,
				pAUTOInspectionCurrentSiteStruct->PadThreshold,
				pAUTOInspectionCurrentSiteStruct->BestHue,
				pAUTOInspectionCurrentSiteStruct->BestChannel,
				pAUTOInspectionCurrentSiteStruct->BestChannelPads,
				pAUTOInspectionCurrentSiteStruct->CentralPadsColor,
				pAUTOInspectionCurrentSiteStruct->PadsColorWidth,
				pAUTOInspectionCurrentSiteStruct->IdSite ) );

	}
	catch(wxSQLite3Exception& exc){
		wxMessageBox( exc.GetMessage(), "wxSQLite_WriteSPIParams" , wxOK | wxICON_ERROR );
		cout<<pAUTOInspectionCurrentSiteStruct->PasteCentralHUE<<" "<<
				pAUTOInspectionCurrentSiteStruct->PasteHUEWidth<< " "<<
				pAUTOInspectionCurrentSiteStruct->PadThreshold<< " "<<
				pAUTOInspectionCurrentSiteStruct->BestHue<<" "<<
				pAUTOInspectionCurrentSiteStruct->BestChannel<<" "<<
				pAUTOInspectionCurrentSiteStruct->BestChannelPads<<" "<<
				pAUTOInspectionCurrentSiteStruct->CentralPadsColor<<" "<<
				pAUTOInspectionCurrentSiteStruct->PadsColorWidth<<" "<<
				pAUTOInspectionCurrentSiteStruct->IdSite<< "  \nStringa completa "<<stmtBuffer.Format("UPDATE SITES SET "
						"SITES_PasteCentralHUE = %d, "
						"SITES_PasteHUEWidth = %d, "
						"SITES_PadThr= %d, "
						"SITES_BestHue = %f, "
						"SITES_BestChannel = %d, "
						"SITES_BestChannelPads = %d, "
						"SITES_CentralPadsColor = %d, "
						"SITES_PadsColorWidth = %d  "
						"WHERE SITES_ID = %d; ",
						pAUTOInspectionCurrentSiteStruct->PasteCentralHUE,
						pAUTOInspectionCurrentSiteStruct->PasteHUEWidth,
						pAUTOInspectionCurrentSiteStruct->PadThreshold,
						pAUTOInspectionCurrentSiteStruct->BestHue,
						pAUTOInspectionCurrentSiteStruct->BestChannel,
						pAUTOInspectionCurrentSiteStruct->BestChannelPads,
						pAUTOInspectionCurrentSiteStruct->CentralPadsColor,
						pAUTOInspectionCurrentSiteStruct->PadsColorWidth,
						pAUTOInspectionCurrentSiteStruct->IdSite )<< endl;
		return false;

	};
	return true;


}

bool SRDatabase::RestoreSPIparams()
{
	try{
		wxSQLite3StatementBuffer stmtBuffer;
		wxSQLite3ResultSet cursor =_DBspiAUTO.ExecuteQuery( stmtBuffer.Format("SELECT SITES_PasteCentralHUE, SITES_PasteHUEWidth, SITES_PadThr, SITES_BestHue, SITES_BestChannel, SITES_BestChannelPads, SITES_CentralPadsColor, SITES_PadsColorWidth  FROM SITES WHERE SITES_IdProd = %d", pAUTOInspectionCurrentSiteStruct->IdSite));
		pAUTOInspectionCurrentSiteStruct->PadThreshold = cursor.GetInt("SITES_PadThr");
		pAUTOInspectionCurrentSiteStruct->BestChannel = cursor.GetInt("SITES_BestChannel");
		pAUTOInspectionCurrentSiteStruct->BestHue = cursor.GetInt("SITES_BestHue");
		pAUTOInspectionCurrentSiteStruct->PasteCentralHUE = cursor.GetInt("SITES_PasteCentralHUE");
		pAUTOInspectionCurrentSiteStruct->PasteHUEWidth = cursor.GetInt("SITES_PasteHUEWidth");
		pAUTOInspectionCurrentSiteStruct->BestChannelPads = cursor.GetInt("SITES_BestChannelPads");
		pAUTOInspectionCurrentSiteStruct->CentralPadsColor = cursor.GetInt("SITES_CentralPadsColor");
		pAUTOInspectionCurrentSiteStruct->PadsColorWidth = cursor.GetInt("SITES_PadsColorWidth");
		return true;

	}
	catch(wxSQLite3Exception& exc){
		wxMessageBox( exc.GetMessage(), "wxSQLite_RestoreSPIParams", wxOK | wxICON_ERROR );
		return false;
	}
};
bool SRDatabase::RestoreSPIparamsPhase2(){

	try{
		wxSQLite3StatementBuffer stmtBuffer;
		wxSQLite3ResultSet cursor =_DBspiAUTO.ExecuteQuery( stmtBuffer.Format("SELECT SITES_PasteCentralHUE, SITES_PasteHUEWidth, SITES_BestChannelPads, SITES_CentralPadsColor, SITES_PadsColorWidth FROM SITES WHERE SITES_IdProd = %d", pAUTOInspectionCurrentSiteStruct->IdSite));
		pAUTOInspectionCurrentSiteStruct->PasteCentralHUE = cursor.GetInt("SITES_PasteCentralHUE");
		pAUTOInspectionCurrentSiteStruct->PasteHUEWidth = cursor.GetInt("SITES_PasteHUEWidth");
		pAUTOInspectionCurrentSiteStruct->BestChannelPads = cursor.GetInt("SITES_BestChannelPads");
		pAUTOInspectionCurrentSiteStruct->CentralPadsColor = cursor.GetInt("SITES_CentralPadsColor");
		pAUTOInspectionCurrentSiteStruct->PadsColorWidth = cursor.GetInt("SITES_PadsColorWidth");

		return true;
	}
	catch(wxSQLite3Exception& exc){
		wxMessageBox( exc.GetMessage(), "wxSQLite_RestoreSPIParams2", wxOK | wxICON_ERROR );
		return false;
	}
}

bool SRDatabase::UpdateAlarmAndWarning(wxString Warning, wxString Alarm, int IDSite)
{
	int AlarmINT = wxAtoi(Alarm);
	int WarningINT = wxAtoi(Warning);
	if(IDSite<=0 || AlarmINT<=0 || WarningINT<=0)
			return false;

	try{
		wxSQLite3StatementBuffer stmtBuffer;
		_DBspiAUTO.ExecuteQuery( stmtBuffer.Format("UPDATE SITES SET SITES_Alarm = %d, SITES_Warning = %d  WHERE SITES_ID = %d",
				AlarmINT,
				WarningINT,
				IDSite ) );
	}
	catch(wxSQLite3Exception& exc){
		wxMessageBox( exc.GetMessage(), "wxSQLite_UpdateAlarm", wxOK | wxICON_ERROR );
		return false;

	};

	for(int i=0; i < SavedResult; i++){
		if(AUTOInspectionPointRecord[i].ID_Site == IDSite){
			AUTOInspectionPointRecord[i].Alarm = AlarmINT;
			AUTOInspectionPointRecord[i].Warning = WarningINT;
		}
	}

	return true;
}

bool SRDatabase::ClearPointsStruct(){
	for(int i=0; i<NUM_INSPECTION_POINTS; i++){
		AUTOInspectionPointRecord[i].Alarm=0;
		AUTOInspectionPointRecord[i].Centroids_PCB=cv::Point(-1,-1);
		AUTOInspectionPointRecord[i].ConnectedWith=0;
		AUTOInspectionPointRecord[i].ID_Site=0;
		AUTOInspectionPointRecord[i].Percentage_covered=0;
		//AUTOInspectionPointRecord[i].SiteName=wxT(""); //Questo stronzo non si resetta
		//AUTOInspectionPointRecord[i].SiteName.clear();
		AUTOInspectionPointRecord[i].SiteName[0] = '\0';
		AUTOInspectionPointRecord[i].SiteNum=0;
		AUTOInspectionPointRecord[i].SpotNum=0;
		AUTOInspectionPointRecord[i].Warning=0;
		AUTOInspectionPointRecord[i].White_pixels=0;
		AUTOInspectionPointRecord[i].x=0;
		AUTOInspectionPointRecord[i].y=0;
	}
	SavedResult=-1;
	return true;
}

bool SRDatabase::ClearBoardStruct(){
	for(int i=0; i<NUM_INSPECTION_POINTS; i++){
		RecordedBoardstruct[i].BoardNumber = -1;
		RecordedBoardstruct[i].ConnectedSpots = -1;
		RecordedBoardstruct[i].ID_production = -1;
		//RecordedBoardstruct[i].ProductionName = wxT("");
		RecordedBoardstruct[i].ProductionName.clear();
		RecordedBoardstruct[i].Time = -1;
		RecordedBoardstruct[i].WhiteAreas = -1;

	}
	recordNum=-1;
	return true;
}
bool SRDatabase::DeleteBoardResults(int IDprod, int BoardNum){
	try
	{
		wxSQLite3StatementBuffer stmtBuffer;
		_DBspiAUTO.ExecuteQuery( wxString::Format("DELETE FROM RESULTS WHERE SITES_IdProd = %d AND RESULTS_N_Scheda = %d;", IDprod, BoardNum  ) );


	}
	catch( wxSQLite3Exception& exc )
	{
		wxMessageBox( exc.GetMessage(), "wxSQLite_Delete_Board_Result", wxOK | wxICON_ERROR );
		return SR_ERROR;
	}
}










