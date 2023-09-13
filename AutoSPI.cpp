//---------------------------------------------------------------------------
//
// Name:        AutoSPI.cpp
// Author:      Daniele Pelitti
// Created:     05/06/2017
// Description: SPI (Solder Paste Inspection) functions implementation
//
//---------------------------------------------------------------------------

#include "AutoSPI.h"
#include "FileFunctions.h"
#include "wxThresholdDialog.h"
#include "SmartLog.h"
#include "wxCameraControl.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 		SPIproc
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AutoSPIProc::AutoSPIProc( SRMachine* SRRef, SmartLog* smartLoggerRef, wxCameraControl *cameraRef, wxWindow* parentRef )
{
	SR				= SRRef;
	smartLogger		= smartLoggerRef;
	camera			= cameraRef;
	parent			= parentRef;


	spiImg_8 = 0;
	spiImg_8_lowThr = 0;
	spiImg_24 = 0;
	spiImg_Drag_24 = 0;
	spiStorageFind = 0;
	spiStorageDraw = 0;
	Border_distance_inspection_rectangle=30;

}

AutoSPIProc::~AutoSPIProc()
{

}

void AutoSPIProc::spiDraw(cv::Mat *image ){

	//create 3 channels image
	cv::Mat temp= image->clone();

	if(temp.channels()==1)
		cv::cvtColor(temp, temp, CV_GRAY2RGB);

	vector<vector<cv::Point> > Contours;
	Contours=SR->DB->pAUTOInspectionCurrentSiteStruct->Contours;

	if (SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.PCB.size()==0)
		SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots = MatchRegions(false);

	//check if there are regions in the PCB without association with mask
	for (int i=0; i<SR->DB->pAUTOInspectionCurrentSiteStruct->PointsNum; i++){
		bool find=false;
		for(int j=0; j < SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask.size(); j++){
			if (SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.PCB[j]==i){
				//PBC has a match!
				find=true;
				break;
			}
		}

		if(!find){
			SR->DB->pAUTOInspectionCurrentSiteStruct->SpotEnable[i]=false;
		}
	}//if not, the spot is disabled!


	for (int sitePointsNum = 0; sitePointsNum < SR->DB->pAUTOInspectionCurrentSiteStruct->PointsNum; sitePointsNum++)
	{

		//cv::putText(temp,'OpenCV',origin, cv::FONT_HERSHEY_COMPLEX, 4,(255,255,255),2);

		//cv::drawContours(temp, Contours[sitePointsNum], sitePointsNum , cv::Scalar(255), CV_FILLED);
		if (SR->DB->pAUTOInspectionCurrentSiteStruct->SpotEnable[sitePointsNum])
		cv::drawContours(temp, Contours, sitePointsNum, CV_RGB(255,0,0) );
		else
		cv::drawContours(temp, Contours, sitePointsNum, CV_RGB(0,153,255) );

	}



	//it draws contours from mask
	for(int pointNum=0; pointNum< SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.PCB.size(); pointNum++){

		cv::drawContours(temp, SR->DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask, SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask[pointNum] , CV_RGB(0,255,0) );

	}
	for(int pointNum=0; pointNum<SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask.size(); pointNum++){
			cv::line(temp, SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[ SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask[pointNum]  ],  SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids[ SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.PCB[pointNum] ], CV_RGB(0,0,0) );
	}
	cv::Point a(Border_distance_inspection_rectangle, Border_distance_inspection_rectangle);
	cv::Point b(temp.cols - Border_distance_inspection_rectangle, temp.rows -Border_distance_inspection_rectangle);
	cv::rectangle(temp,a,b, cv::Scalar(255,0,0) );


	//picture must be 24 bit depth,
	camera->SetVideoMainImage( wxImage( image->cols, image->rows, temp.data, true) );


}

int AutoSPIProc::LoadDraw(cv::Mat* image, int type){

	cv::Mat pippo;
	IplImage* pImage = cvCreateImage( cvSize(CAM_W, CAM_H), IPL_DEPTH_8U, 3 );
	if( !ffCheckFile( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ), wxString::Format( FILE_SITEREF, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii() ) )
					return SR_ERROR;
	if( !ffCheckFile( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ), wxString::Format( FILE_SITE, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii() ) )
					return SR_ERROR;
	if (type==simple){
		//ffLoad_IplImage_8( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ), wxString::Format( FILE_SITE, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii(), pImage );
		ffLoad_Mat_24( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ), wxString::Format( FILE_SITE, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii(), &pippo);
		//we must copy the working picture to Frame_to_Mat in SMInspecion, to be used in spiDraw
		pippo.copyTo(*image);
	}
	else{
		//ffLoad_IplImage_8( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ), wxString::Format( FILE_SITEREF, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii(), pImage );
		ffLoad_Mat_24( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ), wxString::Format( FILE_SITEREF, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii(), &pippo);

		//pippo=cv::cvarrToMat(pImage);
		cv::Mat Img_Aux = pippo.clone();
		//cv::cvtColor(pippo, Img_Aux, CV_GRAY2BGR);
		resize(Img_Aux, Img_Aux, cv::Size(480,360), 0, 0, cv::INTER_LINEAR );
		Img_Aux.copyTo(camera->Mask_frame);
	}

				cvReleaseImage(&pImage);
				return true;


}


int AutoSPIProc::FindRegions(cv::Mat* image, int type, bool newFind)
{
	/* IMPORTANT!
	 * use registered images, or the function could include regions on the border!
	 */
	cv::Mat pippo;

	if( !newFind )
	{

		if (type==adaptive){
			if( !ffCheckFile( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ), wxString::Format( FILE_SITEREF, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii() ) )
				return SR_ERROR;
		}
		if (type==simple){
			if( !ffCheckFile( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ), wxString::Format( FILE_SITE, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii() ) )
				return SR_ERROR;
		}

		if (type==simple){
		ffLoad_Mat_24( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ), wxString::Format( FILE_SITE, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii(), &pippo);
		//we must copy the working picture to Frame_to_Mat in SMInspecion, to be used in spiDraw
		pippo.copyTo(*image);
		}
		else{
			ffLoad_Mat_24( wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() ), wxString::Format( FILE_SITEREF, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii(), &pippo);
			cv::Mat Img_Aux = pippo.clone();
			//cv::cvtColor(pippo, Img_Aux, CV_GRAY2BGR);
			resize(Img_Aux, Img_Aux, cv::Size(480,360), 0, 0, cv::INTER_LINEAR );
			Img_Aux.copyTo(camera->Mask_frame);
		}

	}
	else{
		image->copyTo(pippo);
	}

	//fot the analysis, we use the grayscale
	if (pippo.channels()==3)
	{
		cvtColor(pippo,pippo,CV_BGR2GRAY);
	}




	cv::Mat temp;
	int thresh;
	int cols;
	int rows;


	if (type==adaptive){

		cv::Mat dest;

		//color filtering
		cv::bilateralFilter(pippo,dest, 9, 10, 80 );

		// b/w filtering
		cv::adaptiveThreshold(dest , temp, 255 , cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY_INV, 171,  0 );
		cv::erode(temp, temp,  cv::Mat(), cv::Point(-1, -1), 2); //ridotto di due pixel!!!

		cv::Mat img_to_camera;
		cv::cvtColor(temp, img_to_camera, CV_GRAY2BGR);
		resize(img_to_camera, img_to_camera, cv::Size(480,360), 0, 0, cv::INTER_LINEAR );
		img_to_camera.copyTo(camera->Mask_frame);


		double X =1- SR->DB->MachineParamsS.UpXPixMm/SR->DB->MachineParamsS.DnXPixMm;
		double Y =1- SR->DB->MachineParamsS.UpYPixMm/SR->DB->MachineParamsS.DnYPixMm;
		cols = round(X*temp.cols);
		rows = round( Y*temp.rows);
		cols = 0;
		rows = 0;
		//cv::resize(temp,temp, cv::Size(temp.cols - cols, temp.rows - rows));

		if(SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor != 0){
			//double proportion = (temp.rows/(float)temp.cols);
			double proportion = CAM_H/(float)CAM_W;
			//cv::resize(temp,temp, cv::Size(temp.cols+SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor, temp.rows+SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor));
			cv::resize(temp,temp, cv::Size(temp.cols+SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor, temp.rows+ round(SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor*proportion) ));
		}
		//cout<< "scale factor: "<<SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor<<endl;

	}
	else{
		thresh=SR->DB->pAUTOInspectionCurrentSiteStruct->BinarizationThr;
		cv::threshold(pippo, temp, thresh, 255, cv::THRESH_BINARY);
	}

	//pippo has 3 channels now
	cvtColor(pippo,pippo,CV_GRAY2BGR);


	//minimum spot length
	double minContourArea = 40;
	// Find contours
	vector<vector<cv::Point> > contours_all;
	//cv::imshow("famigerata temp", temp);
	//cv::waitKey(100);
	cv::findContours(temp, contours_all, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);


	 vector<cv::Moments> mu( contours_all.size() );

	 //vector<cv::Point2f> centroids_all( contours_all.size() );
	 int counter=0;
	 double area_region;

	 //these 3 are the result
	 vector<vector<cv::Point> > Contours;
	 vector<cv::Point2f> Centroids;
	 vector<double> Areas;

	 bool exit_cycle;
	 //clear current site
	 if(type==simple){

		 SR->DB->pAUTOInspectionCurrentSiteStruct->Area.clear();
	 	 SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids.clear();
	 	 SR->DB->pAUTOInspectionCurrentSiteStruct->Contours.clear();
	 	 SR->DB->pAUTOInspectionCurrentSiteStruct->SpotEnable.clear();
	 }
	 else{
	 	  SR->DB->pAUTOInspectionCurrentSiteStruct->Area_Mask.clear();
	 	  SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.clear();
	 	  SR->DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask.clear();
	 }
	 SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask.clear();
	 SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.PCB.clear();

	for (int i = 0; i < contours_all.size(); ++i)
	    {
	        // Check area
		exit_cycle=false;
				area_region=cv::contourArea(contours_all[i]);
				if ( area_region < minContourArea) continue;

					//discard every region close to borders
			        for (int j = 0; j < contours_all[i].size(); j++)
				        {
				        	if(contours_all[i][j].x<Border_distance_inspection_rectangle||contours_all[i][j].x>temp.cols-Border_distance_inspection_rectangle)
				        	{
				        		exit_cycle=true;
				        		break;
				        	};
				        	if(contours_all[i][j].y<Border_distance_inspection_rectangle||contours_all[i][j].y>temp.rows-Border_distance_inspection_rectangle)
				        	{
				        		exit_cycle=true;
				        		break;
				        	};
				        }
			if(exit_cycle)continue;

	        Areas.push_back( area_region );
	        mu[counter] = moments( contours_all[i], false ); //moments
	        Centroids.push_back( cv::Point2f( mu[counter].m10/mu[counter].m00 , mu[counter].m01/mu[counter].m00 ) ); //mass center
	        Contours.push_back( contours_all[i]);

	        cv::drawContours(pippo, contours_all, i, CV_RGB(255,0,0) );

	        if(type==simple){

	        SR->DB->pAUTOInspectionCurrentSiteStruct->Area.push_back(Areas[counter]);
	        SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids.push_back(Centroids[counter]);
	        SR->DB->pAUTOInspectionCurrentSiteStruct->Contours.push_back(Contours[counter]);
	        SR->DB->pAUTOInspectionCurrentSiteStruct->SpotEnable.push_back(true);}
	        else{
	        	Centroids[counter].x += cols/2 -SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor/2;
	        	Centroids[counter].y += rows/2 -SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor/2;

	        	for(int i=0; i<Contours[counter].size(); i++){
	        		Contours[counter][i].x += round(cols/2-SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor/2) ;
	        		Contours[counter][i].y += round(rows/2-SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor/2);
	        	}


	        	SR->DB->pAUTOInspectionCurrentSiteStruct->Area_Mask.push_back(Areas[counter]);
	        	SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.push_back(Centroids[counter]);
	        	SR->DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask.push_back(Contours[counter]);

	        }
	        counter++;

	    }
	//cv::imshow("finale", pippo);
	//areas are PCB areas!

	if(type==simple)
	SR->DB->pAUTOInspectionCurrentSiteStruct->PointsNum=Areas.size();

	if(Areas.size()!=0)
	{
	return Areas.size();
	}
	else
		return SR_ERROR;


}

int AutoSPIProc::CorrectTraslation( ){

	if(SR->DB->pAUTOInspectionCurrentSiteStruct->Area.size()==0 || SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask.size()==0){
		return SR_ERROR;
	}
	cv::Point a; //centroid in mask
	cv::Point b;  //centroid in PCB
	float X=0;
	float Y=0;
	int counter=0;

	/*cv::Mat matrice = cv::Mat().zeros(cv::Size(640,480), CV_8UC1);
	cv::drawContours(matrice, SR->DB->pAUTOInspectionCurrentSiteStruct->Contours, -1, cv::Scalar(128));
	cv::drawContours(matrice, SR->DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask, -1, cv::Scalar(255));
	cv::imshow("contorni disegnati", matrice);
	cv::waitKey(0);*/

	for (int i=0; i<SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask.size(); i++){
		a=SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[ SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask[i] ];
		b=SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids[ SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.PCB[i] ];
		if(norm2(a,b)< 30){
			X += (a.x - b.x);
			Y += (a.y - b.y);
			counter++;
		}
	}
	X=X/counter;
	Y=Y/counter;

	for (int i=0; i < SR->DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask.size(); i++ ){
		SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i].x -= X;
		SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i].y -= Y;

				for(int j=0; j<SR->DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i].size(); j++){
					SR->DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i][j].x -= X;
					SR->DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i][j].y -= Y;

					}
		}
	return 1;

}

int AutoSPIProc::AdaptScale(cv::Mat* currentPicture){

	cv::Mat deformed;
	vector<double>cost;

	//try to enlarge the original picture
	bool reduce = false;

	//cv::Mat img_copy = currentPicture->clone();
	cost.push_back( ScaleCost(  false ) );
	int original_value=SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor;
	//cout<<"initial enlarging cost: "<<cost[0]<<endl;

	for (int i=1; i<MAX_SCALE_ADAPTING; i++){

		SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor++;

		cost.push_back(ScaleCost( false ) );
		//cout<<"enlarging image, cost "<<cost[i] <<endl;



			if (cost[i]>=cost[i-1]){

				if(i<=2){ //we accept 2 iterations (the first one can be devious)
					reduce=true;
					//cout<< "devo ridurre l'immagne"<<endl;
					SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor = original_value;
					break;
					}

				SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor--;
				ScaleCost( true );
				break;


		}
	}

	//cout<<"devo restringere, non allargare"<<endl;

	if(reduce){


		cost.clear();
		cost.push_back( ScaleCost(  false ) );
		//cout<<"initial reducing cost: "<<cost[0]<<endl;

		for(int i=1; i <MAX_SCALE_ADAPTING; i++){

			SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor--;
			cost.push_back( ScaleCost( false ) );
			//cout<<"reducing image, cost "<<cost[i] <<endl;

			//if distance rises again, we finished
			if (cost[i] > cost[i-1]){

				//try next 2 values
				double fistIterationOut;
				double secondIterationOut;
				SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor--;
				fistIterationOut = ScaleCost( false );
				SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor--;
				secondIterationOut = ScaleCost( false );
				SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor += 2;

				if(fistIterationOut < cost[i-1]){
					cost[i] = fistIterationOut;
					//cout<<"first iteration out, cost "<<cost[i] <<endl;

				}
				if(secondIterationOut < cost[i-1]){
					cost[i] = secondIterationOut;
					//cout<<"second iteration out, cost "<<cost[i] <<endl;
				}
				else{
					SR->DB->pAUTOInspectionCurrentSiteStruct->ImgScaleFactor++;
					ScaleCost( true );
					return 0;
				}

			}

		}
	}



}

double AutoSPIProc::ScaleCost( bool overwrite, int pixel_cut){


	/*Here we search the centroids of the new picture

	 SR->DB->pAUTOInspectionCurrentSiteStruct->Contours;


	vector<vector<cv::Point> > Contours = SR->DB->pAUTOInspectionCurrentSiteStruct->Contours;
	vector<cv::Point2f> Centroids = SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids;
	vector<double> Areas = SR->DB->pAUTOInspectionCurrentSiteStruct->Area;*/



	//qui ci sono tutti i contorni
	//cv::Mat tmpsdp= PCB_Image->clone();
	//cv::drawContours(tmpsdp, Contours, -1, 0);
	//cout<<"contorni num"<<  Contours.size()<<endl;
	//cv::imshow("immagine con contorni, tutti!", tmpsdp);
	//cv::waitKey(1000);
	//END search


	//Contours_and_proprieties Region_PCB;
	//Contours_and_proprieties Region_Mask;
	wxString fullpath = wxString::Format(FILE_PRODUCTION_FOLDER, SR->DB->ProductionDataS.ProductionName.ToAscii() );
	fullpath.Append( wxString::Format( FILE_SITEREF, SR->DB->ProductionDataS.ProductionName.ToAscii(), SR->DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii() );
	cv::Mat Mask= cv::imread(fullpath.ToAscii());

	FindRegions(&Mask, adaptive, true);


	SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots = MatchRegions(true);

	CorrectTraslation();
	//cv::drawContours(Mask, SR->DB->pAUTOInspectionCurrentSiteStruct->Contours, -1, 0 );
	//cv::drawContours(Mask, SR->DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask, -1, 0 );
	//cv::imshow("Mask", Mask);
	//cv::waitKey(10000);



	//and after all we estimate the total cost
	int counter=0;
	cv::Point a;
	cv::Point b;
	double cost=0;
	for (int i=0; i<SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask.size(); i++){
			a=SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[ SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask[i] ];
			b=SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids[ SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.PCB[i] ];
			cv::line(Mask, a,b, 0);
			if(norm2(a,b)< MAX_DISTANCE_SCALE_COST){
				//cost += pow(norm2(a,b),2);
				cost += pow(norm2(a,b),1);
				counter++;
		}
	}
	//cv::imshow("Mask", Mask);
	//cv::waitKey(10000);

	/*cv::drawContours(*PCB_Image, Region_Mask.contours, -1, cv::Scalar(0,0,0) );
	cv::drawContours(*PCB_Image, Region_PCB.contours, -1, cv::Scalar(0,0,0) );
	for(int pointNum=0; pointNum<coupled_regions.Mask.size(); pointNum++){
			cv::line(*PCB_Image,Region_Mask.centroids[ coupled_regions.Mask[pointNum] ],  Region_PCB.centroids[ coupled_regions.PCB[pointNum] ], CV_RGB(0,0,0) );
			//cv::line(temp, SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[ SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask[pointNum]  ],  SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids[ SR->DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.PCB[pointNum] ], CV_RGB(0,0,0) );

	}*/


	//cv::imshow("imm scale cost", *PCB_Image);
	//cv::waitKey(10000);



	return cost/counter;







}

cv::Mat AutoSPIProc::Resize (cv::Mat* image, double i, int direction){
	cv::Mat result;
	if(direction==HORIZONTAL){
		if(i>0)
		{
			result= image->colRange(0,image->cols-i);
			return result;
		}
		if(i<0)
		{
			result= image->colRange(abs(i),image->cols);
			return result;
		}


	}
	else
	{
		if(i>0)
			{
				result= image->rowRange(0,image->rows-i);
				return result;
			}
			if(i<0)
			{
				result= image->rowRange(abs(i),image->rows);
				return result;
			}
	}


	//if i was 0, no shift
	return  *image;
}


bool AutoSPIProc::spiSelectThresholdMat( cv::Mat* Image, PointI p1, PointI p2 )
{
	bool retVal = false;
	cv::Mat grayscale_Img;
	cv::cvtColor(*Image, grayscale_Img, CV_BGR2GRAY);

	// get scan line from image using Bresenham algo
	int pix = 0;
	int dy = p2.Y - p1.Y;
	int dx = p2.X - p1.X;
	int stepx, stepy;

	if( dy < 0 ) { dy = -dy; stepy = -1; } else { stepy = 1; }
	if( dx < 0 ) { dx = -dx; stepx = -1; } else { stepx = 1; }

	// create scan line
	char* imgRow = new char[ MAX( dx, dy ) + 1 ];
	int imgRowLen = 0;

	// add starting point
	int rowStep= (int)*grayscale_Img.step.p;

	imgRow[imgRowLen++] = *(grayscale_Img.data + p1.Y * rowStep + p1.X);

	dy <<= 1; // dy is now 2*dy
	dx <<= 1; // dx is now 2*dx

	//cv::Mat img(pImage_8, true);

	if( dx > dy )
	{
		int fraction = dy - (dx >> 1); // same as 2*dy - dx
		while( p1.X != p2.X )
		{
			if( fraction >= 0 )
			{
				p1.Y += stepy;
				fraction -= dx; // same as fraction -= 2*dx
			}
			p1.X += stepx;
			fraction += dy; // same as fraction -= 2*dy

			// add point
			imgRow[imgRowLen++] = *(grayscale_Img.data + p1.Y * rowStep + p1.X);
		}
	}
	else
	{
		int fraction = dx - (dy >> 1);
		while( p1.Y != p2.Y )
		{
			if( fraction >= 0 )
			{
				p1.X += stepx;
				fraction -= dy;
			}
			p1.Y += stepy;
			fraction += dx;

			// add point
			imgRow[imgRowLen++] = *(grayscale_Img.data + p1.Y * rowStep + p1.X);
		}
	}

	// show dialog
	wxThresholdDialog* thrDialog = new wxThresholdDialog( parent );
	thrDialog->SetScanLine( (unsigned char*)imgRow, imgRowLen );
	if( thrDialog->ShowModal() == wxOK )
	{
		SR->DB->pAUTOInspectionCurrentSiteStruct->BinarizationThr = thrDialog->GetThreshold();
		retVal = true;
	}

	// clean
	delete thrDialog;
	delete [] imgRow;

	return retVal;
}

int AutoSPIProc::TogglePointAt( PointI position){

	int min_index=-1;
	float min_distance=PTRDIFF_MAX;//max value

	float Xc, Yc;
	float distance;

	for (int i=0; i<SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids.size(); i++){
		Xc=SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids[i].x;
		Yc=SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids[i].y;
		distance = sqrt( pow((Xc-position.X),2) + pow((Yc-position.Y),2) );

		if( distance <min_distance )
		{
			min_distance=distance;
			min_index=i;
		}

	}

	if (min_distance < MAX_DISTANCE_TOGGLE){

		if(SR->DB->pAUTOInspectionCurrentSiteStruct->SpotEnable[min_index]==false){
			SR->DB->pAUTOInspectionCurrentSiteStruct->SpotEnable[min_index]=true;
			return 1;}
		else{
			SR->DB->pAUTOInspectionCurrentSiteStruct->SpotEnable[min_index]=false;
			return 1;}
	}
	return -1;





}

int AutoSPIProc::spiSetPointsInsideRect( PointI p1, PointI p2, bool check ){

	if( p1.X > p2.X )
		{
			// swap
			int x = p1.X;
			p1.X = p2.X;
			p2.X = x;
		}

		if( p1.Y > p2.Y )
		{
			// swap
			int y = p1.Y;
			p1.Y = p2.Y;
			p2.Y = y;
		}

	for (int i=0; i< SR->DB->pAUTOInspectionCurrentSiteStruct->Area.size(); i++ ){


		bool c1=SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids[i].x>p1.X;
		bool c2=SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids[i].x<p2.X;

		bool c3=SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids[i].y>p1.Y;
		bool c4=SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids[i].y<p2.Y;

		if (check && c1 && c2 && c3 && c4){
			SR->DB->pAUTOInspectionCurrentSiteStruct->SpotEnable[i]=false;
		}
		if (!check && c1 && c2 && c3 && c4){
				SR->DB->pAUTOInspectionCurrentSiteStruct->SpotEnable[i]=true;
			}
	}

	return 0;

}

void AutoSPIProc::spiDrawMouseDrag( const PointI& p1, const PointI& p2 , cv::Mat* Image)
{
	cv::Mat pippo = Image->clone();

	vector<vector<cv::Point> > Contours;
	Contours=SR->DB->pAUTOInspectionCurrentSiteStruct->Contours;

		for (int sitePointsNum = 0; sitePointsNum < SR->DB->pAUTOInspectionCurrentSiteStruct->PointsNum; sitePointsNum++)
		{

			//cv::putText(temp,'OpenCV',origin, cv::FONT_HERSHEY_COMPLEX, 4,(255,255,255),2);

			//cv::drawContours(temp, Contours[sitePointsNum], sitePointsNum , cv::Scalar(255), CV_FILLED);
			if (SR->DB->pAUTOInspectionCurrentSiteStruct->SpotEnable[sitePointsNum])
			cv::drawContours(pippo, Contours, sitePointsNum, CV_RGB(255,0,0) );
			else
			cv::drawContours(pippo, Contours, sitePointsNum, CV_RGB(0,153,255) );

		}


	cv::rectangle(pippo, cv::Point(p1.X, p1.Y), cv::Point(p2.X, p2.Y), CV_RGB(192,192,192));

	// show on main
	camera->SetVideoMainImage(   wxImage(CAM_W, CAM_H, (unsigned char*)pippo.data, true)   );
}

float AutoSPIProc::norm2 (cv::Point2f v1, cv::Point2f v2){
	float ret=sqrt( pow((v1.x-v2.x),2) + pow((v1.y-v2.y),2) );
	return ret;
}


bool AutoSPIProc::ComputeSupposedUncoveredArea (){
	cv::Mat ContoursPCBImage= cv::Mat().zeros(CAM_H,CAM_W, CV_8UC1);
	cv::Mat ContoursMaskImage = cv::Mat().zeros(CAM_H,CAM_W, CV_8UC1);

	for (int i=0 ; i<SR->DB->pAUTOInspectionCurrentSiteStruct->Contours.size(); i++)
	{
		SR->DB->pAUTOInspectionCurrentSiteStruct->Uncovered_Area.push_back(0); //initialize the vector with 0s
		if(!SR->DB->pAUTOInspectionCurrentSiteStruct->SpotEnable[i]) continue;
		vector<cv::Point> tmp = SR->DB->pAUTOInspectionCurrentSiteStruct->Contours.at(i);
		const cv::Point* elementPoint[1] ={&tmp[0]};
		int n_points = (int)tmp.size();
		cv::fillPoly(ContoursPCBImage, elementPoint, &n_points, 1 , cv::Scalar(255),8);
	}

	for (int i=0 ; i<SR->DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask.size(); i++){
			vector<cv::Point> tmp = SR->DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask.at(i);
			const cv::Point* elementPoint[1] ={&tmp[0]};
			int n_points = (int)tmp.size();
			cv::fillPoly(ContoursMaskImage, elementPoint, &n_points, 1 , cv::Scalar(255),8);
		}

	//cv::imshow("contours PCB", ContoursPCBImage);
	//cv::imshow("contours Mask", ContoursMaskImage);


	cv::bitwise_and(ContoursPCBImage, ContoursMaskImage, ContoursPCBImage);
	//cv::imshow("intersection", ContoursPCBImage);

	vector< vector <cv::Point> > IntersectionContours;
	cv::findContours(ContoursPCBImage, IntersectionContours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	vector< cv::Moments> mu;
	vector< cv::Point2f > IntersectionCenter;
	for (int i=0 ; i<IntersectionContours.size(); i++){
		mu.push_back( cv::moments( IntersectionContours[i], false ) ); //moments
		IntersectionCenter.push_back( cv::Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 ) );
	}


	for(int j=0; j<SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids.size(); j++ )
	{
		if(!SR->DB->pAUTOInspectionCurrentSiteStruct->SpotEnable[j]) continue;
		int index=-1;
		float MinDistance = 9999999;
		for (int i=0 ; i<IntersectionContours.size(); i++)
		{
			float distance= norm2(IntersectionCenter[i], SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids[j]);
			if(distance < MinDistance){
				MinDistance = distance;
				index= i;
			}
		}
		if(IntersectionContours.size() == 0 )continue;
		SR->DB->pAUTOInspectionCurrentSiteStruct->Uncovered_Area[j] = SR->DB->pAUTOInspectionCurrentSiteStruct->Area[j] - cv::contourArea(IntersectionContours[index]);
	}




}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 		SPICheck
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



AutoSPICheck::AutoSPICheck( SRDatabase *DBRef, SRMachine *SRRef, wxCameraControl *cameraRef )
{
	DB = DBRef;
	camera = cameraRef;
	SPIdrawings = true;
	SR = SRRef;

}

void AutoSPICheck::Initialize()
{

	initFlag = true;
}

bool AutoSPICheck::CheckImages( int idSite )
{
	if( !ffCheckFile( wxString::Format(FILE_PRODUCTION_FOLDER, DB->ProductionDataS.ProductionName.ToAscii() ), wxString::Format( FILE_SITEREF, DB->ProductionDataS.ProductionName.ToAscii(), idSite ).ToAscii() ) )
		return false;
	if( !ffCheckFile( wxString::Format(FILE_PRODUCTION_FOLDER, DB->ProductionDataS.ProductionName.ToAscii() ), wxString::Format( FILE_SITE, DB->ProductionDataS.ProductionName.ToAscii(), idSite ).ToAscii() ) )
		return false;

	return true;
}

bool AutoSPICheck::Inspect( cv::Mat* frame, cv::Mat* frameHighExposure, const PointI& offset, bool suggestCorrections )
{

	bool SiteOK=true;
	bool Short = false;

	DB->Spots2Save=0;


	if( !initFlag || DB->pAUTOInspectionCurrentSiteStruct->PointsNum <= 0 )
		return false;

	if(frame->empty())
		return false;

	// load site image
	wxString fullpath( DIR_VISION );

	cv::Mat image_draw;
	frame->copyTo(image_draw);

	//////////////////////////////////////////////////////// save  picture
	fullpath.Clear();
	fullpath.Append( wxString::Format( FILE_PRODUCTION_FOLDER, DB->ProductionDataS.ProductionName.ToAscii()) );
	fullpath.Append( wxString::Format("Post_Printing_%d, ", DB->ProductionDataS.Counter ));
	fullpath.Append( wxString::Format( FILE_SITE, DB->ProductionDataS.ProductionName.ToAscii(), DB->pAUTOInspectionCurrentSiteStruct->IdSite) );
	cv::Mat imgToSave = frame->clone();
	wxString label = "Board: ";
	label.append(wxString::Format(wxT("%i"),DB->ProductionDataS.Counter));
	label.append(" Stroke: ");
	if(SR->GetSqueegeesCycle()){
		label.append("RtF ");
	}else{
		label.append("FtR ");
	}
	label.append(" Corrections X: ");
	label.append(wxString::Format(wxT("%1.2f"),DB->ProductionDataS.CorrectionX));
	label.append(" Y: ");
	label.append(wxString::Format(wxT("%1.2f"),DB->ProductionDataS.CorrectionY));
	label.append(" DY: ");
	label.append(wxString::Format(wxT("%1.2f"),DB->ProductionDataS.DeltaYFrontRear));
	label.append(" Theta: ");
	label.append(wxString::Format(wxT("%1.2f"),DB->ProductionDataS.CorrectionTheta));

	cv::putText(imgToSave, label.ToAscii(), cv::Point(20, imgToSave.rows -30),  cv::FONT_HERSHEY_SIMPLEX, 0.45, cv::Scalar(255,0,0) );
	cv::imwrite( fullpath.ToAscii(),  imgToSave );
	//////////////////////////////////////////////////////////

	cv::Mat original_thresh;
	frameHighExposure->copyTo(original_thresh);

	//////////////////////////////////////////////////////////////////////////////////////////
	///// FIND THE PASTE  	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////

	//alter the original HUE
	cv::Mat frame_HSV;
	cv::vector<cv::Mat> HSV_planes;
	cv::cvtColor(original_thresh, frame_HSV, CV_BGR2HSV);
	cv::split(frame_HSV, HSV_planes);
	//HSV_planes[0]=HSV_planes[0]*DB->pAUTOInspectionCurrentSiteStruct->BestHue; //HUE
	HSV_planes[0]=HSV_planes[0] + DB->pAUTOInspectionCurrentSiteStruct->BestHue; //HUE 18/06
	merge(HSV_planes, frame_HSV);
	cvtColor(frame_HSV, original_thresh, CV_HSV2BGR);


	vector<cv::Mat> layers;
	split(original_thresh, layers);
	vector<int> Areas_paste;
	vector<vector<cv::Point> > Contours_paste_raw;
	vector<vector<cv::Point> > Contours_paste;

	cv::Mat layer_clone  = cv::Mat().zeros(layers[0].rows, layers[0].cols, CV_8UC1);
	cv::Mat Good_Contours_paste_regions = cv::Mat().zeros(layers[0].rows, layers[0].cols, CV_8UC1);

	//////////////////////////////////////////////////////////////////////////////////////////
	///// CREATE PASTE MASK  	//////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//find the closest
	float minDistance = 99999;
	cv::Mat pasteMask = cv::Mat(layers[0].rows, layers[0].cols, CV_8UC1, cv::Scalar(0));
	for(int i =0; i< DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.size(); i++){
		for(int j = i+1; j< DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.size(); j++){
			float distanceValue = norm2(DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i], DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[j]);
			if( distanceValue < minDistance){
				minDistance = distanceValue;
			}
		}
		cv::fillConvexPoly(pasteMask, DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i], cv::Scalar(255) );
	}
	//cv::imshow("pasteMask no dilate", pasteMask);

	int iterations = minDistance/2 + 2;
	cv::dilate(pasteMask,pasteMask, cv::Mat(), cv::Point(-1,-1), iterations);

	switch (DB->pAUTOInspectionCurrentSiteStruct->BestChannel){
		case BLUE_CHANNEL:

			threshold(layers[0], layers[0], DB->pAUTOInspectionCurrentSiteStruct->PadThreshold, 255, CV_THRESH_BINARY);
			///imshow("blue thr ", layers[0]);
			medianBlur(layers[0], layers[0], 5);
			cv::dilate(layers[0],layers[0], cv::Mat());
			cv::bitwise_and(layers[0], pasteMask, layers[0]);

			layers[0].copyTo(layer_clone);
			cv::findContours( layer_clone, Contours_paste_raw, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
			for (int i = 0; i < Contours_paste_raw.size(); i++)
			{
				if ( cv::contourArea(Contours_paste_raw[i]) < MIN_AREA_SPI) continue;// remove smaller contours

				//discard every region close to borders
				bool exit_cycle = false;
				for (int j = 0; j < Contours_paste_raw[i].size(); j++){
					if(Contours_paste_raw[i][j].x<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].x>layer_clone.cols-BORDER_DISTANCE_POST_PRINTING)
					{
						exit_cycle=true;
						break;
					};
					if(Contours_paste_raw[i][j].y<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].y>layer_clone.rows-BORDER_DISTANCE_POST_PRINTING)
					{
						exit_cycle=true;
						break;
					};
				}

				if (exit_cycle){
					continue;
				}

				Contours_paste.push_back(Contours_paste_raw[i]);
				if( DB->WorkingModesS.DebugMode )
				{
					cv::drawContours(image_draw, Contours_paste_raw, i, CV_RGB(255,0,0));
				}
				cv::fillConvexPoly(Good_Contours_paste_regions, Contours_paste_raw[i], 255);
			}
			//cv::imshow("Good_Contours_paste_regions", Good_Contours_paste_regions);
			//cv::waitKey(10);
			break;
		case GREEN_CHANNEL:

			threshold(layers[1], layers[1], DB->pAUTOInspectionCurrentSiteStruct->PadThreshold, 255, CV_THRESH_BINARY);
			////imshow("green thr ", layers[1]);
			medianBlur(layers[1], layers[1], 5);
			cv::dilate(layers[2],layers[2], cv::Mat());
			cv::bitwise_and(layers[1], pasteMask, layers[1]);
			layers[1].copyTo(layer_clone);
			findContours( layer_clone, Contours_paste_raw, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

			for (int i = 0; i < Contours_paste_raw.size(); i++)
			{
				if ( cv::contourArea(Contours_paste_raw[i]) < MIN_AREA_SPI) continue;// remove smaller contours

				//discard every region close to borders
				bool exit_cycle = false;
				for (int j = 0; j < Contours_paste_raw[i].size(); j++){
					if(Contours_paste_raw[i][j].x<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].x>layer_clone.cols-BORDER_DISTANCE_POST_PRINTING)
					{
						exit_cycle=true;
						break;
					};
					if(Contours_paste_raw[i][j].y<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].y>layer_clone.rows-BORDER_DISTANCE_POST_PRINTING)
					{
						exit_cycle=true;
						break;
					};
				}

				if (exit_cycle){
					continue;
				}

				Contours_paste.push_back(Contours_paste_raw[i]);
				if( DB->WorkingModesS.DebugMode )
				{
					cv::drawContours(image_draw, Contours_paste_raw, i, CV_RGB(255,0,0));
				}
				cv::fillConvexPoly(Good_Contours_paste_regions, Contours_paste_raw[i], 255);
			}
			break;
		case RED_CHANNEL:

			threshold(layers[2], layers[2], DB->pAUTOInspectionCurrentSiteStruct->PadThreshold, 255, CV_THRESH_BINARY);
			////imshow("red thr ", layers[2]);
			medianBlur(layers[2], layers[2], 5);
			cv::dilate(layers[2],layers[2], cv::Mat());
			cv::bitwise_and(layers[2], pasteMask, layers[2]);

			layers[2].copyTo(layer_clone);
			findContours( layer_clone, Contours_paste_raw, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
			for (int i = 0; i < Contours_paste_raw.size(); i++)
			{
				if ( cv::contourArea(Contours_paste_raw[i]) < MIN_AREA_SPI) continue;// remove smaller contours

				//discard every region close to borders
				bool exit_cycle = false;
				for (int j = 0; j < Contours_paste_raw[i].size(); j++){
					if(Contours_paste_raw[i][j].x<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].x>layer_clone.cols-BORDER_DISTANCE_POST_PRINTING)
					{
						exit_cycle=true;
						break;
					};
					if(Contours_paste_raw[i][j].y<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].y>layer_clone.rows-BORDER_DISTANCE_POST_PRINTING)
					{
						exit_cycle=true;
						break;
					};
				}

				if (exit_cycle){
					continue;
				}

				Contours_paste.push_back(Contours_paste_raw[i]);
				if( DB->WorkingModesS.DebugMode )
				{
					cv::drawContours(image_draw, Contours_paste_raw, i, CV_RGB(255,0,0));
				}
				cv::drawContours(image_draw, Contours_paste_raw, i, CV_RGB(255,0,0));
				cv::fillConvexPoly(Good_Contours_paste_regions, Contours_paste_raw[i], 255);
			}
			break;
		case COMPOSITE_CHANNEL:
			cv::Mat plane1(CAM_H, CAM_W, CV_32F); //"redPlane"
				layers[0].convertTo(plane1, CV_32F);
				cv::Mat plane2(CAM_H, CAM_W, CV_32F); //"greenPlane"
				layers[1].convertTo(plane2,CV_32F);
				cv::Mat plane3(CAM_H, CAM_W, CV_32F); //"bluePlane"
				layers[2].convertTo(plane3,CV_32F);

				cv::Mat mul(CAM_H, CAM_W, CV_32F);
				mul = plane1.mul(plane3);
				mul = mul.mul(1/plane2);
				double min, max;
				cv::minMaxLoc(mul, &min, &max);
				mul = (mul-min)/(max-min) ;
				//cv::imshow("pre threshold", mul);
				//imshow("mul pre thr", mul);
				cv::threshold(mul, mul, DB->pAUTOInspectionCurrentSiteStruct->PadThreshold/255.0, 255, CV_THRESH_BINARY);
				//imshow("mul", mul);
				//cv::medianBlur(mul,mul, 3);
				//imshow("mul Median", mul);
				mul.convertTo(mul,CV_8UC1);
				cv::bitwise_and(mul, pasteMask, mul);
				//cv::imshow("past threshold", mul);
				findContours( mul, Contours_paste_raw, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
				for (int i = 0; i < Contours_paste_raw.size(); i++)
				{
					if ( cv::contourArea(Contours_paste_raw[i]) < MIN_AREA_SPI) continue;// remove smaller contours

					//discard every region close to borders
					bool exit_cycle = false;
					for (int j = 0; j < Contours_paste_raw[i].size(); j++){
						if(Contours_paste_raw[i][j].x<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].x>layer_clone.cols-BORDER_DISTANCE_POST_PRINTING)
						{
							exit_cycle=true;
							break;
						};
						if(Contours_paste_raw[i][j].y<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].y>layer_clone.rows-BORDER_DISTANCE_POST_PRINTING)
						{
							exit_cycle=true;
							break;
						};
					}

					if (exit_cycle){
						continue;
					}

					Contours_paste.push_back(Contours_paste_raw[i]);
					if( DB->WorkingModesS.DebugMode )
					{
						cv::drawContours(image_draw, Contours_paste_raw, i, CV_RGB(255,0,0));
					}
					//cv::drawContours(image_draw, Contours_paste_raw, i, CV_RGB(255,0,0));
					cv::fillConvexPoly(Good_Contours_paste_regions, Contours_paste_raw[i], 255);
				}
				break;
		}


	//////////////////////////////////////////////////////////////////////////////////////////
	/// FIND THE PADS USING THE HUE OR COLOR DIFFERENCE
	//////////////////////////////////////////////////////////////////////////////////////////


	/*switch (DB->pAUTOInspectionCurrentSiteStruct->BestChannel){
		case BLUE_CHANNEL:
			bitwise_and(bgr_planes[0], layers[0], bgr_planes[0]);
			break;
		case GREEN_CHANNEL:
			bitwise_and(bgr_planes[0], layers[1], bgr_planes[0]);
			break;
		case RED_CHANNEL:
			bitwise_and(bgr_planes[0], layers[2], bgr_planes[0]);
			break;
	}*/

	cv::Mat PadTHR(CAM_H, CAM_W , CV_8UC1);

	if(DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE != -1){

		vector<cv::Mat> hsv_planes;
		cv::Mat frame_HSV;
		cv::cvtColor(*frame, frame_HSV , CV_BGR2HSV);
		cv::split( frame_HSV, hsv_planes );

		//double treshold, up and down
		for (int i=0; i< hsv_planes[0].rows; i++) ///we use the hue criteria!
		{
				for (int j=0; j< hsv_planes[0].cols; j++)
				{
					int editValue= hsv_planes[0].at<uchar>(i,j);

					if((editValue> (DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE - DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth/2) )&&(editValue<DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE + DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth/2)) //check whether value is within range.
					{
						PadTHR.at<uchar>(i,j)=255;
					}
					else
					{
						PadTHR.at<uchar>(i,j)=0;
					}
				}
			}
		//extremely white regions do not have a yellow hue, we add them separately
		cv::cvtColor(*frame, original_thresh, CV_BGR2GRAY);
		cv::threshold(original_thresh,original_thresh, 245, 255, CV_THRESH_BINARY_INV);
		erode(original_thresh,original_thresh,cv::Mat());
		//remove the white spots
		cv::bitwise_and(original_thresh, PadTHR, PadTHR);

	}
	else if(DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads != -1){

			cv::Mat frame_copy = frame->clone();
			vector<cv::Mat> bgr_planes;
			cv::split( *frame, bgr_planes );
			cv::Mat BestChannelImg;
			switch (DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads){
				case BLUE_CHANNEL:
					BestChannelImg = bgr_planes[0].clone();
					//cout<<"best channel blue"<<endl;
					break;
				case GREEN_CHANNEL:
					BestChannelImg = bgr_planes[1].clone();
					//cout<<"best channel green"<<endl;
					break;
				case RED_CHANNEL:
					BestChannelImg = bgr_planes[2].clone();
					//cout<<"best channel red"<<endl;
					break;
			}
			//imshow("BestChannelImg",BestChannelImg);
			//cv::waitKey(100);
			//cout<<"central pad color"<< DB->pAUTOInspectionCurrentSiteStruct->CentralPadsColor<<endl;
			//cout<<"width /2"<< DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth/2<<endl;


			//double treshold, up and down
			for (int i=0; i< bgr_planes[0].rows; i++)
			{
					for (int j=0; j< bgr_planes[0].cols; j++)
					{
						int editValue=BestChannelImg.at<uchar>(i,j);

						if((editValue >= (DB->pAUTOInspectionCurrentSiteStruct->CentralPadsColor - DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth) )&&(editValue <= DB->pAUTOInspectionCurrentSiteStruct->CentralPadsColor + DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth)) //check whether value is within range.
						{
							PadTHR.at<uchar>(i,j)=255;
						}
						else
						{
							PadTHR.at<uchar>(i,j)=0;
						}
					}
				}

			cv::dilate(PadTHR,PadTHR,cv::Mat(), cv::Point(-1,-1),1); // hashtag ColorDilate
	}

	//cv::imshow("PadTHR ",PadTHR );//OK!



	//cv::imshow("PadTHR + white regions", PadTHR ); //OK!

	// outside the regions we found in the previous step, we must not find pads
	//cv::Mat PadTHR_inv = PadTHR.clone();
	//cv::bitwise_not(PadTHR_inv,PadTHR_inv);
	//cv::dilate( PadTHR_inv,PadTHR_inv,cv::Mat() );

	//cv::imshow("PadTHR shown in aux", PadTHR_inv ); //NO

	//cv::Mat White_regions_Mask = PadTHR_inv.clone();
	cv::Mat White_regions_Mask = PadTHR.clone();
	//cv::dilate(White_regions_Mask,White_regions_Mask, cv::Mat());
	//cv::imshow("white mask", White_regions_Mask );

	switch (DB->pAUTOInspectionCurrentSiteStruct->BestChannel){
		case BLUE_CHANNEL:
			bitwise_and(PadTHR, layers[0], PadTHR);
			break;
		case GREEN_CHANNEL:
			bitwise_and(PadTHR, layers[1], PadTHR);
			break;
		case RED_CHANNEL:
			bitwise_and(PadTHR, layers[2], PadTHR);
			break;
	}

	//extract the paste borders

	vector<vector<cv::Point> > contours;
	Contours_paste.clear();
	cv::Mat PadTHR_Copy = PadTHR.clone();
	//cv::findContours( PadTHR_Copy, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	cv::findContours( Good_Contours_paste_regions, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	int area_region;

	for (int i = 0; i < contours.size(); ++i)
	{
		// Check area
		area_region=cv::contourArea(contours[i]);
		if ( area_region < MIN_AREA_SPI) continue;
		bool exit_cycle = false;
		for (int j = 0; j < contours[i].size(); j++){
			if(contours[i][j].x<BORDER_DISTANCE_POST_PRINTING||contours[i][j].x>PadTHR.cols-BORDER_DISTANCE_POST_PRINTING)
			{
				exit_cycle=true;
				break;
			};
			if(contours[i][j].y<BORDER_DISTANCE_POST_PRINTING||contours[i][j].y>PadTHR.rows-BORDER_DISTANCE_POST_PRINTING)
			{
				exit_cycle=true;
				break;
			};
		}

		if (exit_cycle){
			continue;
		}

		Contours_paste.push_back(contours[i]);
	}

	if(DB->WorkingModesS.DebugMode){
		cv::drawContours(image_draw, Contours_paste, -1,CV_RGB(255,0,0) );
	}






	//these contours are the ones found during the teaching state
	vector<vector<cv::Point> > Contours;
	vector<cv::Point2f> Centroids;
	Contours=DB->pAUTOInspectionCurrentSiteStruct->Contours;
	Centroids = DB->pAUTOInspectionCurrentSiteStruct->Centroids;
	//shift the contours to the ligned coordinates!
	for (int i=0; i < Contours.size(); i++ ){
		Centroids[i].x -= offset.X;
		Centroids[i].y -= offset.Y;
			for(int j=0; j<Contours[i].size(); j++){
				Contours[i][j].x-=offset.X;
				Contours[i][j].y-=offset.Y;

				}
	}

	vector<vector<cv::Point> > Contours_mask;
	vector<cv::Point2f> Centroids_mask;
	Contours_mask = DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask;
	Centroids_mask = DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask;
	//correct the nask contours
	for (int i=0; i < Contours_mask.size(); i++ ){
		Centroids_mask[i].x -= offset.X;
		Centroids_mask[i].y -= offset.Y;
				for(int j=0; j<Contours_mask[i].size(); j++){
					Contours_mask[i][j].x -= offset.X;
					Contours_mask[i][j].y -= offset.Y;

					}
		}
	//cout<< "appena copiato i centroids, nome:"<<DB->pAUTOInspectionCurrentSiteStruct->Name <<endl;


	//this struct creates a simple couple region1, region2. basically is a vector
	connected_domains connected;


	cv::Mat mask; //here we have the regions of the mask AND the white
	cv::Mat mask_PCB; //here we have the regions of PCB AND the white
	float white_pixel;
	float percentage;
	float X;
	float Y;

	//clean the structure results
	DB->ClearResultStruct();

	int counter=0;
	vector<cv::Point2f> directions; //in this vector, there is the correction for each spot

	for (int siteNum = 0; siteNum < DB->pAUTOInspectionCurrentSiteStruct->PointsNum; siteNum++){


		if (DB->pAUTOInspectionCurrentSiteStruct->SpotEnable[siteNum]){ //if the spot is enabled, check

			//Those will be used for white identification
			vector<cv::Moments> mu_white;
			vector<cv::Point2f> Centroids_white;
			vector<vector<cv::Point> > Contours_white;
			vector<double>Area_white;

			white_pixel=0;
			percentage=0;
			X=0;
			Y=0;

			////////////////////////////////////////////////////////////////////////////////////////////////
			//this part compute if there are connected spots
			/////////////////////////////////////////////////////////////////////////////////////////////////
			DB->AUTOInspectionResults[counter].Connected = 0;
			int domain_num=-1;
			//for each site, find he paste domain where it is contained
			for (int i=0; i<Contours_paste.size(); i++){

				if(cv::pointPolygonTest( Contours_paste[i], Centroids[siteNum], false ) >=0){ //inside or on the edge
				domain_num=i;
				break;
				}
			}

			// and now let's find if in the same region there are other centroids
			if(domain_num!=-1){
				for(int i=0; i<DB->pAUTOInspectionCurrentSiteStruct->PointsNum; i++){
					if(i==siteNum || !DB->pAUTOInspectionCurrentSiteStruct->SpotEnable[i]) continue; // all centroids (enabled) except sitenum
					if(cv::pointPolygonTest( Contours_paste[domain_num], Centroids[i], false )>=0){ //inside or on the edge
						connected.domain_a.push_back(siteNum);
						connected.domain_b.push_back(i);
						DB->AUTOInspectionResults[counter].Connected =1;
						break; 	//shall we check every connection or one is sufficient?
					}
				}
			}
			//cout<< "calcolati i connectedDomains "<<DB->pAUTOInspectionCurrentSiteStruct->Name <<endl;

			//////////////////////////////////////////////////////////////////////////////////////////////////////
			//now  focus on white
			////////////////////////////////////////////////////////////////////////////////////////////////////////

			//here we load the associated mask regions on the selected siteNum
			vector<int> index;
			index.push_back(-1);
			for(int i=0; i<DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask.size();i++){

				if(DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.PCB[i]==siteNum){
						if(index.back()==-1){
							index.clear();
						}

				index.push_back(DB->pAUTOInspectionCurrentSiteStruct->Coupled_spots.Mask[i]);
				}


			}

			//something very suspicious
			if(index[0]==-1){
				continue;
				//cout<< "index -1 "<<DB->pAUTOInspectionCurrentSiteStruct->Name <<endl;
			}

			//mask of 0
			mask=cv::Mat::zeros(original_thresh.rows, original_thresh.cols , CV_8U);
			//1 where it must check (this mask uses contours of white spots on PCB)

			//1 where it must check (this mask uses contours of holes in mask)
			for (int mask_num=0; mask_num <index.size(); mask_num++){
				cv::fillConvexPoly(mask, Contours_mask[ index[mask_num] ], Contours_mask[ index[mask_num] ].size() , 255);
			}

			cv::bitwise_and(mask, White_regions_Mask, mask );
			//lets find the contours of the white part

			cv::Mat mask_copy = mask.clone();
			cv::findContours(mask_copy, Contours_white, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

			for (int mask_num=0; mask_num <index.size(); mask_num++){
				cv::drawContours(image_draw, Contours_mask,  index[mask_num], CV_RGB(0,255,0) );
			}

			//cout<< "creata la maschera bianca con la regione interessata "<<DB->pAUTOInspectionCurrentSiteStruct->Name <<endl;
			//draw contours of white regions (red)
			for (int i=0; i<Contours_white.size(); i++){

				//this part eliminates the contours completely inside the paste
				bool destroy=true;
				//bool destroy=false;
					for(int p=0; p<Contours_white[i].size(); p++){

						if(cv::pointPolygonTest (Contours[siteNum],Contours_white[i][p], true) <=1){ //true means it estimates the distance between the point and the contour
						destroy=false;
						break;
						}
					}
				if(destroy){
					cv::Mat destroy_mask(mask.rows, mask.cols, CV_8UC1, 255); //this mask is white everywhere
					cv::fillConvexPoly(destroy_mask, Contours_white[i], 0); //we create a black spot where there is the region to destroy
					cv::bitwise_and(mask, destroy_mask,mask);
					Contours_white.erase (Contours_white.begin()+i); //we destroy the selected contour
					i--;
					continue;
				}
				//end destroy part

				cv::drawContours(image_draw, Contours_white, i, CV_RGB(0,0,255) );

				mu_white.push_back( moments( Contours_white[i], false ) ); //moments of white spots
				Centroids_white.push_back( cv::Point2f( mu_white[i].m10/mu_white[i].m00 , mu_white[i].m01/mu_white[i].m00 ) ); //mass center
				Area_white.push_back(cv::contourArea(Contours_white[i]));
			}
			//cout<< "regioni non pertinenti distrutte "<<DB->pAUTOInspectionCurrentSiteStruct->Name <<endl;


			//cv::circle(image_draw, Centroids[siteNum], 5, cv::Scalar(0,255,0));




			int supposedCoveredArea=0;

			for(int i=0; i<index.size(); i++){
				supposedCoveredArea += DB->pAUTOInspectionCurrentSiteStruct->Area_Mask[ index[i] ];
			}

			if(Contours_white.empty()){
				white_pixel = 0;
			}
			else {
				for (int i=0; i<Contours_white.size(); i++){
					white_pixel += cv::contourArea(Contours_white[i]); //sum every white spots inside the mask region
				}
			}

			percentage = white_pixel / (double)(supposedCoveredArea)*100;
			//cout<<"valore senza correzione: "<<percentage;

			//Small spots corrections
			double CorrectionalFactor = MIN( (SPI_SMALL_AREA_FACTOR)/supposedCoveredArea, SPI_SMALL_AREA_MAX_CORR);
			//cout<<" CorrectionalFactor: "<<CorrectionalFactor ;

			double percentageEffective = MIN(percentage, SPI_SMALL_AREA_VALIDITY)/SPI_SMALL_AREA_VALIDITY *2/3;
			//cout<<" percentageEffective: "<<percentageEffective;
			double addFactor = MIN(SPI_SMALL_AREA_THRESHOLD*percentageEffective, 2*SPI_SMALL_AREA_THRESHOLD/3)*CorrectionalFactor ;
			//cout<<" addFactor: "<<addFactor ;
			percentage -= addFactor;

			//cout<<"   Corretto: "<<percentage<<endl;


			if (percentage>100)
				percentage = 100;
			if (percentage<=0)
				percentage = 0;

			//cout<< "calcolata la percentuale "<<DB->pAUTOInspectionCurrentSiteStruct->Name <<endl;
			//percentage = 100- percentage;
			/*if(percentage > 100- DB->pAUTOInspectionCurrentSiteStruct->Alarm){
				cout<<"sitenum: "<<siteNum;
				cout<<" site number: "<<counter<<endl;
				cout<<"whitepixels: "<<white_pixel<< " in "<< Contours_white.size()<< " spots";
				cout<<" Suupposed uncovered Area: "<<DB->pAUTOInspectionCurrentSiteStruct->Uncovered_Area[siteNum]<<endl;
			}*/

			//let's save the barycenter
			cv::Moments m = cv::moments(mask, false);
			if(m.m00==0){
				X=	-1;
				Y= 	-1;
			}
			else{
				X=	m.m10/m.m00;
				Y=  m.m01/m.m00;
			}

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//now check the estimated correction!
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//cout<< "stimo la correzine, inizio "<<DB->pAUTOInspectionCurrentSiteStruct->Name <<endl;
			cv::Point2f direction(0,0);

			if(suggestCorrections){
				for (int k=0; k<Centroids_white.size(); k++){ //for each white spot we compute the shift that should be applied (not depend on areA)


					if ( Area_white[k]!=0){ //some spots exist even if their area is null
							cv::Point2f direction_tmp;
							//TODO sostituire centroide con centroid_mask
							direction_tmp.x = Centroids[siteNum].x - Centroids_white[k].x ;
							direction_tmp.y = Centroids[siteNum].y - Centroids_white[k].y ;
							direction_tmp.x = direction_tmp.x/ (float)norm( Centroids[siteNum] - Centroids_white[k]);
							direction_tmp.y = direction_tmp.y/ (float)norm( Centroids[siteNum] - Centroids_white[k]);
							//direction_tmp is a versor

							cv::Mat line=cv::Mat::zeros(mask.rows, mask.cols, CV_8UC1); //create a empity matrix
							//fill this matrix with a line, same direction of direction_tmp
							cv::line(line, Centroids[siteNum],  Centroids_white[k] - 30*direction_tmp, cv::Scalar(255)); //draw a long line
							//cv::line(image_draw, Centroids[siteNum],  Centroids_white[k] - 30*direction_tmp, cv::Scalar(255)); //TODO da rimuovere
							//cv::imshow("line", line);
							//cv::waitKey(1000);
							cv::bitwise_and(mask, line, line); //in line there is th intersection between the line and the white region
							cv::Mat nonZeroCoordinates;
							cv::findNonZero(line, nonZeroCoordinates); //the picture is completely black, except the line

							cv::Point p1(0,0);
							cv::Point p2(0,0);
							if(!nonZeroCoordinates.empty()){ //first and last point are the extremes of the segment
								p1= nonZeroCoordinates.at<cv::Point>(0);
								p2= nonZeroCoordinates.at<cv::Point>(nonZeroCoordinates.rows -1);
								cv::line(image_draw, p1,  p2 , cv::Scalar(255)); //let's draw the line that should be covered to achieve complete covering
							}

							float correction=norm(p1 -p2); //this is the length
								direction.x = direction_tmp.x*correction; //the final correstion is the versor, multiplied the length of the line
								direction.y = direction_tmp.y*correction;

						}


				}
			}
			//direction here is the correction of a single spot
			//cout<< "correzione stimata! "<<DB->pAUTOInspectionCurrentSiteStruct->Name <<endl;
			directions.push_back(direction);
			//cout<< "dopo push back, dir size: "<< directions.size()<<endl;
			//cout<< "dopo push back! "<<DB->pAUTOInspectionCurrentSiteStruct->Name <<endl;



			DB->AUTOInspectionResults[counter].Percentage_covered = percentage;
			DB->AUTOInspectionResults[counter].White_pixels = white_pixel;
			DB->AUTOInspectionResults[counter].WhiteX = X;
			DB->AUTOInspectionResults[counter].WhiteY = Y;

			if(index.size()==1){ //centroids of the mask are shifted with the alignment, they are more accurate
				//cout<< "dentro if! "<<DB->pAUTOInspectionCurrentSiteStruct->Name <<endl;
				/*cout<< " connected domains " <<connected.domain_a.size(); OK
				cout<<"directions size: "<<directions.size();
				cout<<"Centroids_mask size: "<<Centroids_mask.size();
				cout<<"Centroids size: "<<Centroids.size();
				cout<<"contours_mask size: "<<Contours_mask.size();
				cout<<"Contours size: "<<Contours.size();
				cout<< "Index size unitario, Area size:"<<DB->pAUTOInspectionCurrentSiteStruct->Area.size() <<endl;
				cout<< "Index size unitario, Area_Mask size:"<<DB->pAUTOInspectionCurrentSiteStruct->Area_Mask.size() <<endl;
				cout<< "Index size unitario, Contours size:"<<DB->pAUTOInspectionCurrentSiteStruct->Contours.size() <<endl;
				cout<< "Index size unitario, Contours_Mask size:"<<DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask.size() <<endl;
				cout<< "Index size unitario, Spot enabled size:"<<DB->pAUTOInspectionCurrentSiteStruct->SpotEnable.size() <<endl;
				cout<< "Index size unitario, Centroids size:"<<DB->pAUTOInspectionCurrentSiteStruct->Centroids.size() <<endl;
				cout<< "Index size unitario, Centroids_Mask size:"<<DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.size() <<endl;*/
				DB->AUTOInspectionResults[counter].SiteX= DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[ index[0] ].x - offset.X;
				DB->AUTOInspectionResults[counter].SiteY = DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[ index[0] ].y - offset.Y;
			}
			else{
				DB->AUTOInspectionResults[counter].SiteX = DB->pAUTOInspectionCurrentSiteStruct->Centroids[siteNum].x -offset.X;
				DB->AUTOInspectionResults[counter].SiteY = DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[index[0]].y - offset.Y;

			}

			//results are calculated on enabled spots only... siteNum is different from spotNum
			DB->AUTOInspectionResults[counter].SpotNum = siteNum;


			//DB->SaveResult(counter);



			//draw a orange rectangle is the paste is insufficient
			if(percentage > 100- DB->pAUTOInspectionCurrentSiteStruct->Alarm){
				cv::Rect boundRect;
				SiteOK = false;
				if(index.size()==1)
					boundRect = cv::boundingRect( DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[index[0]] );
				else
					boundRect = cv::boundingRect( DB->pAUTOInspectionCurrentSiteStruct->Contours[siteNum] );

				cv::Point br(boundRect.br().x + SPI_RECTANGLE_OFFSET  -offset.X, boundRect.br().y + SPI_RECTANGLE_OFFSET -offset.Y);
				cv::Point tl(boundRect.tl().x - SPI_RECTANGLE_OFFSET  -offset.X, boundRect.tl().y - SPI_RECTANGLE_OFFSET -offset.Y);
				cv::Rect big_rec(tl,br);
				cv::rectangle( image_draw, big_rec, CV_RGB(0,0,255), SPI_RECTANGLE_THICKNESS );
			}
			if(DB->AUTOInspectionResults[counter].Connected==1){
				SiteOK = false;
				Short = true;
				cv::Rect boundRect = boundRect = cv::boundingRect( Contours_paste[domain_num] );
				cv::Point br(boundRect.br().x + 0.2*boundRect.width , boundRect.br().y + 0.2*boundRect.height );
				cv::Point tl(boundRect.tl().x - 0.2*boundRect.width , boundRect.tl().y - 0.2*boundRect.height );;
				cv::Rect big_rec(tl,br);
				cv::rectangle( image_draw, big_rec, CV_RGB(0,153,255), SPI_RECTANGLE_THICKNESS );
			}
			DB->Spots2Save++;
			counter++;


		}

	}

	if(suggestCorrections){
		//once the inspection of every point is over, we can compute the resulting vector
		cv::Point2f complessivo(0,0);
		int number=0;

		for (int t=1; t<directions.size(); t++ ){

		//if (directions[t].x!=0 ||directions[t].y!=0) //if they are both 0, should not apply correction
		if(true) //all are considered!
			{
				complessivo.x += directions[t].x;
				complessivo.y += directions[t].y;
				number++;}

			}

		complessivo.x = complessivo.x / number;
		complessivo.y = complessivo.y / number;

		DB->InspectionSiteSuggestedCorrection[ DB->SiteGetSelected() ].x = complessivo.x;
		DB->InspectionSiteSuggestedCorrection[ DB->SiteGetSelected() ].y = complessivo.y;
	}

	//In case of Errors, draw Contours
	if(Short){
		cv::drawContours(image_draw, Contours_paste, -1,CV_RGB(255,0,0) );
	}

	image_draw.copyTo(TemplateImg);



	return SiteOK;
}

void AutoSPICheck::EstimateCorrection(){

	//first part, angle estimation

	DB->estimated_rotation =0;
	for (int i=0; i< DB->SiteCount(); i++){ //for each site
		for (int j=i+1; j<  DB->SiteCount(); j++){
			cv::Point2f p1 (DB->AUTOInspectionSiteStruct[i].X , DB->AUTOInspectionSiteStruct[i].Y) ;
			cv::Point2f p2 (DB->AUTOInspectionSiteStruct[j].X , DB->AUTOInspectionSiteStruct[j].Y) ;

			//suggested correction is mm, Y and X are mm.

			cv::Point2f p3 (DB->AUTOInspectionSiteStruct[i].X + DB->InspectionSiteSuggestedCorrection[i].x * DB->MachineParamsS.DnXPixMm, DB->AUTOInspectionSiteStruct[i].Y +DB->InspectionSiteSuggestedCorrection[i].y * DB->MachineParamsS.DnYPixMm) ;
			cv::Point2f p4 (DB->AUTOInspectionSiteStruct[j].X + DB->InspectionSiteSuggestedCorrection[j].x * DB->MachineParamsS.DnXPixMm, DB->AUTOInspectionSiteStruct[j].Y +DB->InspectionSiteSuggestedCorrection[j].y * DB->MachineParamsS.DnYPixMm) ;

			cv::Point2f v1 = p1-p2;
			cv::Point2f v2 = p3-p4;

			float thetha = acos( (v1.x*v2.x + v1.y*v2.y)/(norm(v1)*norm(v2)) );
			float theta_degree=thetha * 180/3.141592653589793238462643383; //180 degree/pi

			DB->theta.push_back( theta_degree );
			DB->estimated_rotation +=  theta_degree;

			//cout<<theta_degree<<endl;
		}
	}

	DB->estimated_rotation = DB->estimated_rotation / DB->theta.size();

};

void AutoSPICheck::ShowResults( cv::Mat* image, bool drawSearchArea, const PointI& offset ){

	cv::Mat temp;
	cvtColor(*image, temp, CV_GRAY2BGR );

	vector<vector<cv::Point> > Contours;
	Contours=DB->pAUTOInspectionCurrentSiteStruct->Contours;

	for (int sitePointsNum = 0; sitePointsNum < DB->pAUTOInspectionCurrentSiteStruct->PointsNum; sitePointsNum++)
		{
			cv::drawContours(temp, Contours[sitePointsNum], sitePointsNum, CV_RGB(255,0,0) );

		}


}

int AutoSPICheck::whitePixels (cv::Mat Image){

	return cv::sum(Image)[0]/255; //255 because its the thresholded picture
}


double AutoSPICheck::MutualEntropy (cv::Mat* reference, cv::Mat* target)
{

	//if not, grayscale reference
	if (reference->channels()==3)
	{
		cvtColor(*reference,*reference,CV_BGR2GRAY);
	}
	//if not, grayscale target
	if (target->channels()==3)
	{
		cvtColor(*target,*target,CV_BGR2GRAY);
	}

	/// Set the ranges
	float range[] = { 0, 256 } ;
	const float* histRange = { range };
	//set the size
	const int histSize = 256;

	bool uniform = true; bool accumulate = false;

	//effettivamente non servono gli hist delle due variabili
	cv::Mat hist_REF;
	cv::Mat hist_TAR;
	cv::calcHist( reference, 1, 0, cv::Mat(), hist_REF, 1, &histSize, &histRange, true, false );
	cv::calcHist( target, 1, 0, cv::Mat(), hist_TAR, 1, &histSize, &histRange, true, false );
	//fine

	//coordinates hist bivariate
	int x=0, y=0, count=0;
	//bin width
	float bin_width;
	bin_width=range[1]/histSize;


	//check who's the smaller
	cv::Mat* smaller;
	if( reference->rows < target->rows)
		smaller=reference;
	else if ( reference->rows > target->rows)
		smaller=target;
	else if(reference->cols <= target->cols)
		smaller=reference;
	else
		smaller=target;


	//empity matrix histSize x histSize
	cv::Mat biv_hist(histSize,histSize,CV_32F,cv::Scalar::all(0));
	//for each row(i), for each column(j), evaluate the position
	for (int i=0; i< smaller->rows; i++)
	{
		for (int j=0; j< smaller->cols; j++)
		{
			//hist row (reference)
			x=floor((int)reference->at<uchar>(i,j)/bin_width);
			//hist col (target)
			y=floor((int)target->at<uchar>(i,j)/bin_width);

			biv_hist.at<float>(x,y) += 1;
			count++;

		}
	}
	//normalize the hist
	biv_hist = biv_hist/count;

	//now we calculate the joint entropy
	double joint_entropy=0;

	for (int i=0; i<histSize; i++)
		{
			for (int j=0; j<histSize; j++)
			{
				if(biv_hist.at<float>(i,j) != 0) //probability could be 0. 0*log(0) is 0
				joint_entropy += -1*biv_hist.at<float>(i,j)*log2(biv_hist.at<float>(i,j));
			}
		}


	return joint_entropy;
}

double  AutoSPICheck::Entropy (cv::Mat* image)
{
	//if not, grayscale
	if (image->channels()==3)
	{
		cvtColor(*image,*image,CV_BGR2GRAY);
	}
	    /// Establish the number of bins
	    int histSize = 256;
	    /// Set the ranges
	    float range[] = { 0, 256 } ;
	    const float* histRange = { range };
	    bool uniform = true; bool accumulate = false;
	    cv::Mat hist;

	    /// Compute the histograms:
	    cv::calcHist( image, 1, 0, cv::Mat(), hist, 1, &histSize, &histRange, true, false );
	    //images, n of images, channels, mask, hist, dim, histsize, histrange, uniform, accumulate

	    //normalize
	    hist /= image->total();

	    double entropy=0;

	    for (int i=0; i<histSize; i++)
	    	{
	    		if(hist.at<float>(i) != 0) //probability could be 0. 0*log(0) is 0
	    		entropy += -1*hist.at<float>(i)*log2(hist.at<float>(i));
	    	}


	    return entropy;
}

bool AutoSPICheck::Align (cv::Mat* reference, cv::Mat* target, float &x, float &y)
{
	float threshold=0.5;
		int MAX_ITERATIONS=15;
		double mutual_information[MAX_ITERATIONS];
		double mutual_information_dx_Plus[MAX_ITERATIONS];
		double mutual_information_dx_Minus[MAX_ITERATIONS];
		double mutual_information_dy_Plus[MAX_ITERATIONS];
		double mutual_information_dy_Minus[MAX_ITERATIONS];
		cv::Mat ref_tmp;
		cv::Mat tar_tmp;

		cv::Mat ref_actual;
		cv::Mat tar_actual;

		std::vector<int> x_shift;
		std::vector<int> y_shift;

		for (int i=1; i<MAX_ITERATIONS; i++)
		{


			ref_actual = Resize(reference,x, HORIZONTAL);
			ref_actual = Resize(&ref_actual,y, VERTICAL);

			tar_actual = Resize(target,-x, HORIZONTAL);
			tar_actual = Resize(&tar_actual,-y, VERTICAL);

			mutual_information[i]=Entropy(&ref_actual) +Entropy(&tar_actual)- MutualEntropy(&ref_actual,&tar_actual); //H(x) + H(y) - H(x,y)

			/* 	o-----------> x
			 *  |
			 *  |
			 *  |
			 *  y
			 *
			 *
			 * just in this case*/


			//move right target picture (destroy last column in target and destroy first column in ref)
			tar_tmp = this->Resize(&tar_actual,1, HORIZONTAL);
			ref_tmp = this->Resize(&ref_actual, -1, HORIZONTAL);

			mutual_information_dx_Plus[i] = Entropy(&tar_tmp) + Entropy(&ref_tmp)- MutualEntropy(&tar_tmp,&ref_tmp);

			//move left target picture (destroy last column in ref and destroy first column in tar)
			tar_tmp = this->Resize(&tar_actual,-1, HORIZONTAL);
			ref_tmp = this->Resize(&ref_actual, 1, HORIZONTAL);

			mutual_information_dx_Minus[i] = Entropy(&tar_tmp) + Entropy(&ref_tmp)- MutualEntropy(&tar_tmp,&ref_tmp);

			bool movedX =false;
			if(mutual_information_dx_Plus[i]>mutual_information[i]){
				x_shift.push_back(x);
				x--;
				movedX=true;
			}
			else if(mutual_information_dx_Minus[i]>mutual_information[i]){
				x_shift.push_back(x);
				x++;
				movedX=true;
			}

			//move down target picture (destroy last row in target and destroy first row in ref
			tar_tmp=this->Resize(&tar_actual, 1, VERTICAL);
			ref_tmp=this->Resize(&ref_actual, -1, VERTICAL);

			mutual_information_dy_Plus[i] = Entropy(&tar_tmp) + Entropy(&ref_tmp)- MutualEntropy(&tar_tmp,&ref_tmp);

			//move up target picture (destroy last row in ref and destroy first row in target)
			tar_tmp=this->Resize(&tar_actual, -1, VERTICAL);
			ref_tmp=this->Resize(&ref_actual, 1, VERTICAL);

			mutual_information_dy_Minus[i] = Entropy(&tar_tmp) + Entropy(&ref_tmp)- MutualEntropy(&tar_tmp,&ref_tmp);

			bool movedY =false;
			if(mutual_information_dy_Plus[i]>mutual_information[i]){
				y_shift.push_back(y);
				y--;
				movedY=true;
			}
			else if(mutual_information_dy_Minus[i]>mutual_information[i]){
				y_shift.push_back(y);
				y++;
				movedY=true;
			}
			//cout<< "Current: "<<mutual_information[i]<<" +x: "<<mutual_information_dx_Plus[i]<<" -x: "<<mutual_information_dx_Minus[i]<<" +y: "<<mutual_information_dy_Plus[i]<<endl;

			if(!movedX && !movedY){
				break;
			}
			/*if(i!=0)
			{
				if((mutual_information[i]-mutual_information[i-1])/mutual_information[i] < threshold)
					{break;}
			}*/
			//cv::imshow("difference",ref_actual-tar_actual);
			//cv::waitKey(5);
			//cout<< "mutua: "<< mutual_information[i] <<"     Mutua dx "<< mutual_information_dx[i]<< "     Mutua dy "<< mutual_information_dy[i]<<endl;
			//cout<< x<< "     "<<y<<endl;

		}
		//cropped pictures! now borders should match
		//ref_actual.copyTo(*reference);
		//tar_actual.copyTo(*target);
		return true;
}

bool AutoSPICheck::Align (cv::Mat* reference, wxString fullpath, float &x, float &y){
	cv::Mat target;
	target = cv::imread(fullpath.ToAscii(),CV_LOAD_IMAGE_GRAYSCALE );


	float threshold=0.5;
		int MAX_ITERATIONS=15;
		double mutual_information[MAX_ITERATIONS];
		double mutual_information_dx_Plus[MAX_ITERATIONS];
		double mutual_information_dx_Minus[MAX_ITERATIONS];
		double mutual_information_dy_Plus[MAX_ITERATIONS];
		double mutual_information_dy_Minus[MAX_ITERATIONS];
		cv::Mat ref_tmp;
		cv::Mat tar_tmp;

		cv::Mat ref_actual;
		cv::Mat tar_actual;

		std::vector<int> x_shift;
		std::vector<int> y_shift;

		for (int i=1; i<MAX_ITERATIONS; i++)
		{


			ref_actual = Resize(reference,x, HORIZONTAL);
			ref_actual = Resize(&ref_actual,y, VERTICAL);

			tar_actual = Resize(&target,-x, HORIZONTAL);
			tar_actual = Resize(&tar_actual,-y, VERTICAL);

			mutual_information[i]=Entropy(&ref_actual) +Entropy(&tar_actual)- MutualEntropy(&ref_actual,&tar_actual); //H(x) + H(y) - H(x,y)

			/* 	o-----------> x
			 *  |
			 *  |
			 *  |
			 *  y
			 *
			 *
			 * just in this case*/


			//move right target picture (destroy last column in target and destroy first column in ref)
			tar_tmp = this->Resize(&tar_actual,1, HORIZONTAL);
			ref_tmp = this->Resize(&ref_actual, -1, HORIZONTAL);

			mutual_information_dx_Plus[i] = Entropy(&tar_tmp) + Entropy(&ref_tmp)- MutualEntropy(&tar_tmp,&ref_tmp);

			//move left target picture (destroy last column in ref and destroy first column in tar)
			tar_tmp = this->Resize(&tar_actual,-1, HORIZONTAL);
			ref_tmp = this->Resize(&ref_actual, 1, HORIZONTAL);

			mutual_information_dx_Minus[i] = Entropy(&tar_tmp) + Entropy(&ref_tmp)- MutualEntropy(&tar_tmp,&ref_tmp);

			bool movedX =false;
			if(mutual_information_dx_Plus[i]>mutual_information[i]){
				x_shift.push_back(x);
				x--;
				movedX=true;
			}
			else if(mutual_information_dx_Minus[i]>mutual_information[i]){
				x_shift.push_back(x);
				x++;
				movedX=true;
			}

			//move down target picture (destroy last row in target and destroy first row in ref
			tar_tmp=this->Resize(&tar_actual, 1, VERTICAL);
			ref_tmp=this->Resize(&ref_actual, -1, VERTICAL);

			mutual_information_dy_Plus[i] = Entropy(&tar_tmp) + Entropy(&ref_tmp)- MutualEntropy(&tar_tmp,&ref_tmp);

			//move up target picture (destroy last row in ref and destroy first row in target)
			tar_tmp=this->Resize(&tar_actual, -1, VERTICAL);
			ref_tmp=this->Resize(&ref_actual, 1, VERTICAL);

			mutual_information_dy_Minus[i] = Entropy(&tar_tmp) + Entropy(&ref_tmp)- MutualEntropy(&tar_tmp,&ref_tmp);

			bool movedY =false;
			if(mutual_information_dy_Plus[i]>mutual_information[i]){
				y_shift.push_back(y);
				y--;
				movedY=true;
			}
			else if(mutual_information_dy_Minus[i]>mutual_information[i]){
				y_shift.push_back(y);
				y++;
				movedY=true;
			}
			//cout<< "Current: "<<mutual_information[i]<<" +x: "<<mutual_information_dx_Plus[i]<<" -x: "<<mutual_information_dx_Minus[i]<<" +y: "<<mutual_information_dy_Plus[i]<<endl;

			if(!movedX && !movedY){
				break;
			}
			/*if(i!=0)
			{
				if((mutual_information[i]-mutual_information[i-1])/mutual_information[i] < threshold)
					{break;}
			}*/
			//cv::imshow("difference",ref_actual-tar_actual);
			//cv::waitKey(5);
			//cout<< "mutua: "<< mutual_information[i] <<"     Mutua dx "<< mutual_information_dx[i]<< "     Mutua dy "<< mutual_information_dy[i]<<endl;
			//cout<< x<< "     "<<y<<endl;

		}
		//cropped pictures! now borders should match
		//ref_actual.copyTo(*reference);
		//tar_actual.copyTo(*target);
		return true;
}

coupled_spots AutoSPIProc::MatchRegions ( bool first_time )
{
	Contours_and_proprieties Region_PCB;
	Contours_and_proprieties Region_Mask;

	//sull'area (occhio agli ingrandimenti) e non sul numero di piazzole
	//FindRegions(reference,simple,false);
	for (int i=0; i<SR->DB->pAUTOInspectionCurrentSiteStruct->Area.size(); i++)
	{
		Region_PCB.Areas.push_back(SR->DB->pAUTOInspectionCurrentSiteStruct->Area[i]);
		Region_PCB.centroids.push_back(SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids[i]);
		Region_PCB.contours.push_back(SR->DB->pAUTOInspectionCurrentSiteStruct->Contours[i]);
	}

	for (int i=0; i<SR->DB->pAUTOInspectionCurrentSiteStruct->Area_Mask.size(); i++)
		{
			Region_Mask.Areas.push_back(SR->DB->pAUTOInspectionCurrentSiteStruct->Area_Mask[i]);
			Region_Mask.centroids.push_back(SR->DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i]);
			Region_Mask.contours.push_back(SR->DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i]);
		}

	coupled_spots coupled_regions;
	if(Region_PCB.Areas.size()==0 || Region_Mask.Areas.size()==0) return coupled_regions; //there aren't regions


	if(first_time){

		double max_allowable_distance=25;

		for(int i=0; i<Region_Mask.Areas.size(); i++) //for each region in the mask, associate a region in the pcb, use the distace between centroids
		{
			float min_distance=std::numeric_limits<float>::max();
			int index_PCB=-1;

			for (int j=0; j<Region_PCB.Areas.size(); j++)
			{
				float distance;
				distance=norm2(Region_Mask.centroids[i], Region_PCB.centroids[j]);

				if( distance  < min_distance &&  distance  < max_allowable_distance )
				{
					min_distance=distance;
					index_PCB=j;
				}

			}
			if(index_PCB != -1){
			coupled_regions.Mask.push_back(i);
			coupled_regions.PCB.push_back(index_PCB);
			}
		}
	}

	else{
		for(int i=0; i<Region_Mask.Areas.size(); i++){

			cv::Point center =Region_Mask.centroids[i];
			int index_PCB=-1;
			for (int j=0; j<Region_PCB.Areas.size(); j++){
				if(cv::pointPolygonTest(Region_PCB.contours[j], center, false)>=0){
					index_PCB=j;
					break;
				}
			}

			if(index_PCB != -1){
			coupled_regions.Mask.push_back(i);
			coupled_regions.PCB.push_back(index_PCB);
			}

		}
	}


	return coupled_regions;

}





cv::Mat AutoSPICheck::Resize (cv::Mat* image, double i, int direction){
	cv::Mat result;
	if(direction==HORIZONTAL){
		if(i>0)
		{
			result= image->colRange(0,image->cols-i);
			return result;
		}
		if(i<0)
		{
			result= image->colRange(abs(i),image->cols);
			return result;
		}


	}
	else
	{
		if(i>0)
			{
				result= image->rowRange(0,image->rows-i);
				return result;
			}
			if(i<0)
			{
				result= image->rowRange(abs(i),image->rows);
				return result;
			}
	}


	//if i was 0, no shift
	return  *image;
}

cv::Mat AutoSPICheck::RegionGrowingMean (cv::Mat* image, cv::Point seed, int connectivity, int Thr, int Npixels){


	int n=Npixels;
	cv::Mat mask = cv::Mat::zeros(image->rows, image->cols, CV_8UC1);

	cv::Mat checked = cv::Mat::zeros(image->rows, image->cols, CV_8UC1);


	seed.x=round(seed.x);
	seed.y=round(seed.y);
	vector<cv::Point> children;

	checked.at<uchar>(seed.x,seed.y)=1;


	//add first 4 points
	cv::Point punto((seed.x+1), seed.y);

	checked.at<uchar>((seed.x+1), seed.y)=1;
	children.push_back( punto );


	punto.x=(seed.x-1);
	children.push_back( punto );
	checked.at<uchar>((seed.x-1), seed.y)=1;


	punto.x=seed.x;
	punto.y=seed.y+1;
	children.push_back( punto );
	checked.at<uchar>((seed.x), seed.y+1)=1;

	punto.y=seed.y-1;
	children.push_back( punto );
	checked.at<uchar>((seed.x), seed.y-1)=1;

	cv::Mat tmp_mean;
	int counter=10;


	cv::Point currentpoint;

	int mean = image->at<uchar> (seed.x, seed.y);


	while(children.size()){
		//get the last element
		currentpoint=children.back();



		//remove the last element
		children.pop_back();

		bool cond_up = abs( mean - image->at<uchar>(currentpoint.x-n, currentpoint.y) )<Thr;
		bool cond_down = abs( mean - image->at<uchar>(currentpoint.x+n, currentpoint.y) )< Thr;
		bool cond_right = abs( mean - image->at<uchar>(currentpoint.x, currentpoint.y+n) )< Thr;
		bool cond_left = abs( mean - image->at<uchar>(currentpoint.x, currentpoint.y-n) )< Thr;

		//cout<< "image at "<< currentpoint.x << " , "<< currentpoint.y<< "    ";
		//cout<< (int)abs(( image->at<uchar>(currentpoint.x, currentpoint.y) ))<< "     "<< int(image->at<uchar>(currentpoint.x, currentpoint.y+n))<< endl;



		bool overshoot_up = currentpoint.x==0;
		bool overshoot_down = currentpoint.x==image->rows-n-1;
		bool overshoot_right = currentpoint.y==image->cols-1-n;
		bool overshoot_left = currentpoint.y==0;



		if(cond_up && cond_down && cond_right && cond_left){
			cv::Point point_up(currentpoint.x-1, currentpoint.y );
			cv::Point point_down(currentpoint.x+1, currentpoint.y);
			cv::Point point_right(currentpoint.x, currentpoint.y+1);
			cv::Point point_left(currentpoint.x, currentpoint.y-1);


			if( checked.at<uchar>(point_up.x, point_up.y)==0 && !overshoot_up){
				children.push_back(point_up);
				checked.at<uchar>(point_up.x, point_up.y)=1;

			}
			if( checked.at<uchar>(point_down.x, point_down.y)==0 && !overshoot_down){
				children.push_back(point_down);
				checked.at<uchar>(point_down.x, point_down.y)=1;

			}
			if( checked.at<uchar>(point_right.x, point_right.y)==0 && !overshoot_right){
				children.push_back(point_right);
				checked.at<uchar>(point_right.x, point_right.y)=1;

			}
			if( checked.at<uchar>(point_left.x, point_left.y)==0 && !overshoot_left){
				children.push_back(point_left);
				checked.at<uchar>(point_left.x, point_left.y)=1;
			}

			mask.at<uchar>(currentpoint.x, currentpoint.y)=255;
			//tmp_mean= mask.(*image);

			if (counter==10){
			cv::bitwise_and(mask, *image, tmp_mean);
			//imshow("bitwise or", tmp_mean);
			//cv::waitKey(10);

			mean= cv::sum(tmp_mean)[0]/(sum(mask)[0]/255);
			counter=0;}
			counter++;


		}

		//cv::imshow("mask", mask);
		//cv::waitKey(1);
		//cout<< *image<< endl;
		//cv::imshow("checked",checked);

	};
	return mask;

};


void AutoSPICheck::Merge4Images(cv::Mat* Xplus, cv::Mat* Xminus, cv::Mat* Yplus, cv::Mat* Yminus, cv::Mat* dest, float shift){

	float x=round(2*shift/DB->MachineParamsS.DnXPixMm);
	float y=0;
	int Nx =5;

	cv::Mat Xplus_color = Xplus->clone();
	cv::Mat Xminus_color = Xminus->clone();
	cv::Mat Yplus_color = Yplus->clone();
	cv::Mat Yminus_color = Yminus->clone();

	cv::cvtColor(*Xplus, *Xplus, CV_BGR2GRAY);
	cv::cvtColor(*Xminus, *Xminus, CV_BGR2GRAY);
	Align(Xplus, Xminus, x, y);
	//imshow()


	cv::Mat Xdx = Xminus_color.colRange( abs(x)/2 , abs(x) + Nx);
	cv::Mat Xsx = Xplus_color.colRange( Xplus->cols -abs(x) - Nx, Xplus->cols -abs(x)/2 ); // ci sta che queste immagini debbano essere accorciate lungo y
	Resize(&Xdx, -y, VERTICAL).copyTo(Xdx );
	Resize(&Xsx, y, VERTICAL).copyTo(Xsx );


	Resize(&Xplus_color, x, HORIZONTAL).copyTo(Xplus_color );
	Resize(&Xminus_color,-x, HORIZONTAL).copyTo(Xminus_color );

	Resize(&Xplus_color, y, VERTICAL).copyTo(Xplus_color );
	Resize(&Xminus_color,-y, VERTICAL).copyTo(Xminus_color );




	cv::Mat Xtot(Xplus_color.rows, Xplus_color.cols, CV_8UC3);

	for (int i=0; i< Xplus_color.rows; i++){
		for(int j=0; j< Xplus_color.cols; j++)
		{
			/*
			if(norm(Xplus.at<Vec3b>(i,j))> norm(Xminus.at<Vec3b>(i,j))){
				Xtot.at<Vec3b>(i,j)= Xminus_color.at<Vec3b>(i,j);
			}
			else{
				Xtot.at<Vec3b>(i,j)= Xplus_color.at<Vec3b>(i,j);
			}*/
			Xtot.at<cv::Vec3b>(i,j)= (Xminus_color.at<cv::Vec3b>(i,j)/2+ Xplus_color.at<cv::Vec3b>(i,j)/2);

		}
	}

	Xtot = Resize(&Xtot, Nx, HORIZONTAL);
	Xtot = Resize(&Xtot, -Nx, HORIZONTAL);
	//imshow("Xtot:", Xtot);
	//cv::waitKey(10);

	cv::hconcat(Xdx, Xtot, Xtot);
	cv::hconcat(Xtot, Xsx, Xtot);

	if(y<0){
		cv::Mat zeroPad = cv::Mat().zeros(abs(y), Xtot.cols, CV_8UC3);
		cv::vconcat(zeroPad, Xtot, Xtot);
	}
	else if (y>0){
		cv::Mat zeroPad = cv::Mat().zeros(abs(y), Xtot.cols, CV_8UC3);
		cv::vconcat(Xtot, zeroPad, Xtot);
	}
	//size now is camW*camH


	//cv::imshow("Xtot", Xtot);
	//cv::waitKey(10);
	//cout<< Xplus.size().height <<"   "<< Xplus.size().width<<endl;

	x=0;
	y=-round(2*shift/DB->MachineParamsS.DnYPixMm);;
	int Ny=5;

	cv::cvtColor(*Yplus, *Yplus, CV_BGR2GRAY);
	cv::cvtColor(*Yminus, *Yminus, CV_BGR2GRAY);
	Align(Yplus, Yminus, x, y);


	cv::Mat Yup = Yplus_color.rowRange( abs(y)/2 , abs(y) + Ny);
	cv::Mat Ydw = Yminus_color.rowRange( Yplus->rows - abs(y) -Ny , Yplus->rows -abs(y)/2);

	Resize(&Yup, x, HORIZONTAL).copyTo(Yup );
	Resize(&Ydw, -x, HORIZONTAL).copyTo(Ydw );

	Resize(&Yplus_color, x, HORIZONTAL).copyTo(Yplus_color );
	Resize(&Yminus_color,-x, HORIZONTAL).copyTo(Yminus_color );

	Resize(&Yplus_color, y, VERTICAL).copyTo(Yplus_color );
	Resize(&Yminus_color,-y, VERTICAL).copyTo(Yminus_color );


	cv::Mat Ytot(Yplus_color.rows, Yplus_color.cols, CV_8UC3);


		for (int i=0; i< Ytot.rows; i++){
			for(int j=0; j< Ytot.cols; j++)
			{
				//Ytot.at<uchar>(i,j)= (int)mean(Yplus.at<uchar>(i,j), Yminus.at<uchar>(i,j)).val[0];
				Ytot.at<cv::Vec3b>(i,j)= (Yminus_color.at<cv::Vec3b>(i,j)/2+Yplus_color.at<cv::Vec3b>(i,j)/2);
			}
		}

	Ytot = Resize(&Ytot, Ny, VERTICAL);
	Ytot = Resize(&Ytot, -Ny, VERTICAL);

	cv::vconcat(Yup, Ytot, Ytot);
	cv::vconcat(Ytot, Ydw, Ytot);
	if(x<0){
		cv::Mat zeroPad = cv::Mat().zeros(Ytot.rows, abs(x), CV_8UC3);
		cv::hconcat(zeroPad, Ytot, Ytot);
	}
	else if (x>0){
		cv::Mat zeroPad = cv::Mat().zeros(Ytot.rows, abs(x), CV_8UC3);
		cv::hconcat(Ytot, zeroPad, Ytot);
	}
	//size now is camW*camH

	//cv::imshow("Ytot", Ytot);
	//cv::waitKey(10);

	x=0;
	y=0;
	Align(&Ytot, &Xtot, x,y); // should be even

	Resize(&Ytot, x, HORIZONTAL).copyTo(Ytot );
	Resize(&Xtot,-x, HORIZONTAL).copyTo(Xtot );

	Resize(&Ytot, y, VERTICAL).copyTo(Ytot );
	Resize(&Xtot,-y, VERTICAL).copyTo(Xtot );

	cv::Mat Ttot(Ytot.rows, Ytot.cols, CV_8UC3);
	for (int i=0; i< Ttot.rows; i++){
				for(int j=0; j< Ttot.cols; j++)
				{
					Ttot.at<cv::Vec3b>(i,j)= Ytot.at<cv::Vec3b>(i,j)/2 + Xtot.at<cv::Vec3b>(i,j)/2;
				}
			}
	if(Ttot.size() != cv::Size(CAM_W,CAM_H)){
		resize(Ttot,Ttot,cv::Size(CAM_W,CAM_H));
	}


	/*cv::imshow("tot pre filtro", Ttot);
	cv::waitKey(10);
	cv::Mat filtered_picture(Ttot.rows, Ttot.cols, CV_8UC3);
	cv::bilateralFilter(Ttot,filtered_picture, 5, 80, 80);

	cv::imshow("tot post filtro", filtered_picture);
	cv::waitKey(10);

	filtered_picture.copyTo(*dest);*/
	Ttot.copyTo(*dest);
	Ttot.copyTo(camera->Working_frame);






}

bool AutoSPICheck::FindPaste(cv::Mat* frame, cv::Mat* frameHighExposure){



	if( !initFlag || DB->pAUTOInspectionCurrentSiteStruct->PointsNum <= 0 )
		return false;

	// load site image
	//wxString fullpath = wxString::Format(FILE_PRODUCTION_FOLDER, DB->ProductionDataS.ProductionName.ToAscii() );
	//fullpath.Append( wxString::Format( FILE_SITE, DB->ProductionDataS.ProductionName.ToAscii(), DB->pAUTOInspectionCurrentSiteStruct->IdSite ).ToAscii() );
	//cv::Mat Img_site;
	//Img_site= cv::imread( fullpath.ToAscii(), CV_LOAD_IMAGE_COLOR);
	//cv::Mat readedframe =  cv::imread("/home/dpelitti12/Pictures/Post_Printing_27, D11J-TOP_128_site.jpeg");
	//frame = &readedframe;

	wxString fullpath;
	fullpath.Append( wxString::Format( FILE_PRODUCTION_FOLDER, DB->ProductionDataS.ProductionName.ToAscii()) );
	fullpath.Append( wxString::Format("Post_Printing_%d, ", DB->ProductionDataS.Counter ));
	fullpath.Append( wxString::Format( FILE_SITE, DB->ProductionDataS.ProductionName.ToAscii(), DB->pAUTOInspectionCurrentSiteStruct->IdSite) );
	cv::imwrite( fullpath.ToAscii(),  *frame );

	cv::Mat image_draw;
	frame->copyTo(image_draw);

	cv::Mat original_thresh;
	frameHighExposure->copyTo(original_thresh);

	///////////////////////////////////////////////////////////////////////
	//// FIND THE HUE THAT MAXIMIZE THE COLOR DISTANCE		///////////////
	///////////////////////////////////////////////////////////////////////
	cv::Mat frame_HSV;
	cv::vector<cv::Mat> HSV_planes;

	if(DB->pAUTOInspectionCurrentSiteStruct->BestChannel==-1)	{

		cv::Mat frame_RGB;

		vector<double> meanT;
		vector<double> stdDevT;

		vector<cv::Vec3d> meanVec;
		vector<cv::Vec3d> stdDev;


		cvtColor(*frameHighExposure, frame_HSV, CV_BGR2HSV);
		split(frame_HSV, HSV_planes);
		cv::Mat hue_original = HSV_planes[0].clone();
		float max_variance=0;
		int n_points=100;


		for (int i=3; i<n_points-10; i++){

			HSV_planes[0]=hue_original*((float)i/(n_points/HUE_DENOMINATOR)); //hue
			merge(HSV_planes, frame_RGB);
			cvtColor(frame_RGB,frame_RGB, CV_HSV2BGR);

			meanT.clear();
			stdDevT.clear();
			meanStdDev(frame_RGB, meanT, stdDevT);

			if(stdDevT[0]>max_variance){
				max_variance= stdDevT[0];
				DB->pAUTOInspectionCurrentSiteStruct->BestChannel = BLUE_CHANNEL;
				DB->pAUTOInspectionCurrentSiteStruct->BestHue = i/(n_points/HUE_DENOMINATOR);
				//cout<<"max_variance blue "<< max_variance<< endl;

			}
			if(stdDevT[1]>max_variance){
				max_variance= stdDevT[1];
				DB->pAUTOInspectionCurrentSiteStruct->BestChannel=  GREEN_CHANNEL;
				DB->pAUTOInspectionCurrentSiteStruct->BestHue = i/(n_points/HUE_DENOMINATOR);
				//cout<<"max_variance green "<< max_variance<< endl;

			}
			if(stdDevT[2]>max_variance){
				max_variance= stdDevT[1];
				DB->pAUTOInspectionCurrentSiteStruct->BestChannel= RED_CHANNEL;
				DB->pAUTOInspectionCurrentSiteStruct->BestHue = i/(n_points/HUE_DENOMINATOR);
				//cout<<"max_variance red "<< max_variance<< endl;
			}

		}

	}

	//////////////////////////////////////////////////////////////////////////////////////////
	///// FIND THE PASTE  	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//alter the original HUE
	cvtColor(original_thresh, frame_HSV, CV_BGR2HSV);
	split(frame_HSV, HSV_planes);
	//HSV_planes[0]=HSV_planes[0]*DB->pAUTOInspectionCurrentSiteStruct->BestHue; //HUE
	HSV_planes[0]=HSV_planes[0] + DB->pAUTOInspectionCurrentSiteStruct->BestHue; //1806
	merge(HSV_planes, frame_HSV);
	cvtColor(frame_HSV, original_thresh, CV_HSV2BGR);


	vector<cv::Mat> layers;
	split(original_thresh, layers);
	int otsu_THR;
	vector<int> Areas_paste;
	vector<vector<cv::Point> > Contours_paste_raw;
	vector<vector<cv::Point> > Contours_paste;

	cv::Mat Good_Contours_paste_regions = cv::Mat(layers[0].rows, layers[0].cols, CV_8UC1, cv::Scalar(255));
	cv::Mat layer_clone;

	//////////////////////////////////////////////////////////////////////////////////////////
	///// CREATE PASTE MASK  	//////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//find the closest
	float minDistance = 99999;
	cv::Mat pasteMask = cv::Mat(layers[0].rows, layers[0].cols, CV_8UC1, cv::Scalar(0));
	for(int i =0; i< DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.size(); i++){
		for(int j = i+1; j< DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask.size(); j++){
			float distanceValue = norm2(DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[i], DB->pAUTOInspectionCurrentSiteStruct->Centroids_Mask[j]);
			if( distanceValue < minDistance){
				minDistance = distanceValue;
			}
		}
		cv::fillConvexPoly(pasteMask, DB->pAUTOInspectionCurrentSiteStruct->Contours_Mask[i], cv::Scalar(255) );
	}
	//cv::imshow("pasteMask no dilate", pasteMask);

	int iterations = minDistance/2 + 2;
	cv::dilate(pasteMask,pasteMask, cv::Mat(), cv::Point(-1,-1), iterations);
	//cv::imshow("pasteMask dilate", pasteMask);
	//cv::waitKey(0);



	switch (DB->pAUTOInspectionCurrentSiteStruct->BestChannel){
		case BLUE_CHANNEL:

			if(DB->pAUTOInspectionCurrentSiteStruct->PadThreshold ==-1){
				otsu_THR = cv::threshold(layers[0], cv::Mat(layers[1].rows, layers[1].cols, CV_8U), 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
				DB->pAUTOInspectionCurrentSiteStruct->PadThreshold = otsu_THR*1.2;
				threshold(layers[0], layers[0], otsu_THR*1.2, 255, CV_THRESH_BINARY);
			}else{
				threshold(layers[0], layers[0], DB->pAUTOInspectionCurrentSiteStruct->PadThreshold, 255, CV_THRESH_BINARY);
			}
			//imshow("blue thr ", layers[0]);
			medianBlur(layers[0], layers[0], 5);
			cv::dilate(layers[0],layers[0], cv::Mat());
			//cv::bitwise_and(layers[0], pasteMask ,layers[0]);


			layers[0].copyTo(layer_clone);
			cv::findContours( layer_clone, Contours_paste_raw, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
			for (int i = 0; i < Contours_paste_raw.size(); i++)
			{
				if ( cv::contourArea(Contours_paste_raw[i]) < MIN_AREA_SPI) continue;// remove smaller contours

				//discard every region close to borders
				bool exit_cycle = false;
				for (int j = 0; j < Contours_paste_raw[i].size(); j++){
					if(Contours_paste_raw[i][j].x<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].x>layer_clone.cols-BORDER_DISTANCE_POST_PRINTING)
					{
						exit_cycle=true;
						break;
					};
					if(Contours_paste_raw[i][j].y<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].y>layer_clone.rows-BORDER_DISTANCE_POST_PRINTING)
					{
						exit_cycle=true;
						break;
					};
				}

				if (exit_cycle){
					continue;
				}

				Contours_paste.push_back(Contours_paste_raw[i]);
				cv::drawContours(image_draw, Contours_paste_raw, i, CV_RGB(255,0,0));
				//fill the mask
				vector<cv::Point> tmp = Contours_paste_raw.at(i);
				const cv::Point* elementPoint[1] ={&tmp[0]};
				int n_points = (int)tmp.size();
				cv::fillPoly(Good_Contours_paste_regions, elementPoint, &n_points, 1 , cv::Scalar(0),8);

			}
			//cv::imshow("Good_Contours_paste_regions", Good_Contours_paste_regions);
			//cv::waitKey(10);
			break;
		case GREEN_CHANNEL:
			if(DB->pAUTOInspectionCurrentSiteStruct->PadThreshold ==-1){
				otsu_THR = cv::threshold(layers[1], cv::Mat(layers[1].rows, layers[1].cols, CV_8U), 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
				DB->pAUTOInspectionCurrentSiteStruct->PadThreshold = otsu_THR*1.2;
				threshold(layers[1], layers[1], otsu_THR*1.2, 255, CV_THRESH_BINARY);
			}else{
				threshold(layers[1], layers[1], DB->pAUTOInspectionCurrentSiteStruct->PadThreshold, 255, CV_THRESH_BINARY);
			}

			//imshow("green thr ", layers[1]);
			medianBlur(layers[1], layers[1], 5);
			cv::dilate(layers[1],layers[1], cv::Mat());
			//cv::bitwise_and(layers[1], pasteMask ,layers[1]);


			layers[1].copyTo(layer_clone);
			findContours( layer_clone, Contours_paste_raw, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
			for (int i = 0; i < Contours_paste_raw.size(); i++)
			{
				if ( cv::contourArea(Contours_paste_raw[i]) < MIN_AREA_SPI) continue;// remove smaller contours
					//discard every region close to borders
					bool exit_cycle = false;
					for (int j = 0; j < Contours_paste_raw[i].size(); j++){
						if(Contours_paste_raw[i][j].x<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].x>layer_clone.cols-BORDER_DISTANCE_POST_PRINTING)
						{
							exit_cycle=true;
							break;
						};
						if(Contours_paste_raw[i][j].y<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].y>layer_clone.rows-BORDER_DISTANCE_POST_PRINTING)
						{
							exit_cycle=true;
							break;
						};
					}

					if (exit_cycle){
						continue;
					}

				Contours_paste.push_back(Contours_paste_raw[i]);
				cv::drawContours(image_draw, Contours_paste_raw, i, CV_RGB(255,0,0));
				//fill the mask
				vector<cv::Point> tmp = Contours_paste_raw.at(i);
				const cv::Point* elementPoint[1] ={&tmp[0]};
				int n_points = (int)tmp.size();
				cv::fillPoly(Good_Contours_paste_regions, elementPoint, &n_points, 1 , cv::Scalar(0),8);
			}

			break;
		case RED_CHANNEL:
			if(DB->pAUTOInspectionCurrentSiteStruct->PadThreshold ==-1){
				otsu_THR = cv::threshold(layers[2], cv::Mat(layers[1].rows, layers[1].cols, CV_8U), 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
				DB->pAUTOInspectionCurrentSiteStruct->PadThreshold = otsu_THR*1.3;
				threshold(layers[2], layers[2], otsu_THR*1.3, 255, CV_THRESH_BINARY);
			}else{
				threshold(layers[2], layers[2], DB->pAUTOInspectionCurrentSiteStruct->PadThreshold, 255, CV_THRESH_BINARY);
			}
			//imshow("red thr ", layers[2]);
			medianBlur(layers[2], layers[2], 5);
			cv::dilate(layers[2],layers[2], cv::Mat());
			//cv::bitwise_and(layers[2], pasteMask ,layers[2]);

			layers[2].copyTo(layer_clone);
			findContours( layer_clone, Contours_paste_raw, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
			for (int i = 0; i < Contours_paste_raw.size(); i++)
				{
					if ( contourArea(Contours_paste_raw[i]) < MIN_AREA_SPI) continue;
					bool exit_cycle = false;
					for (int j = 0; j < Contours_paste_raw[i].size(); j++){
						if(Contours_paste_raw[i][j].x<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].x>layer_clone.cols-BORDER_DISTANCE_POST_PRINTING)
						{
							exit_cycle=true;
							break;
						};
						if(Contours_paste_raw[i][j].y<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].y>layer_clone.rows-BORDER_DISTANCE_POST_PRINTING)
						{
							exit_cycle=true;
							break;
						};
					}

					if (exit_cycle){
						continue;
					}

					Contours_paste.push_back(Contours_paste_raw[i]);
					cv::drawContours(image_draw, Contours_paste_raw, i, CV_RGB(255,0,0),1);
					vector<cv::Point> tmp = Contours_paste_raw.at(i);
					const cv::Point* elementPoint[1] ={&tmp[0]};
					int n_points = (int)tmp.size();
					cv::fillPoly(Good_Contours_paste_regions, elementPoint, &n_points, 1 , cv::Scalar(0),8);
				}
			break;
		case COMPOSITE_CHANNEL:
			cv::Mat plane1(CAM_H, CAM_W, CV_32F); //"redPlane"
				layers[0].convertTo(plane1, CV_32F);
				cv::Mat plane2(CAM_H, CAM_W, CV_32F); //"greenPlane"
				layers[1].convertTo(plane2,CV_32F);
				cv::Mat plane3(CAM_H, CAM_W, CV_32F); //"bluePlane"
				layers[2].convertTo(plane3,CV_32F);

				cv::Mat mul(CAM_H, CAM_W, CV_32F);
				mul = plane1.mul(plane3);
				mul = mul.mul(1/plane2);
				double min, max;
				cv::minMaxLoc(mul, &min, &max);
				mul = (mul-min)/(max-min) ;
				//imshow("mul pre thr", mul);
				cv::threshold(mul, mul, DB->pAUTOInspectionCurrentSiteStruct->PadThreshold/255.0, 255, CV_THRESH_BINARY);
				//imshow("mul", mul);
				//cv::medianBlur(mul,mul, 3);
				//imshow("mul Median", mul);
				mul.convertTo(mul,CV_8UC1);
				cv::bitwise_and(mul, pasteMask ,mul);
				findContours( mul, Contours_paste_raw, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
				for (int i = 0; i < Contours_paste_raw.size(); i++)
				{
					if ( cv::contourArea(Contours_paste_raw[i]) < MIN_AREA_SPI) continue;// remove smaller contours

					//discard every region close to borders
					bool exit_cycle = false;

					for (int j = 0; j < Contours_paste_raw[i].size(); j++){
						if(Contours_paste_raw[i][j].x<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].x>(CAM_W-BORDER_DISTANCE_POST_PRINTING))
						{
							exit_cycle=true;
							break;
						};
						if(Contours_paste_raw[i][j].y<BORDER_DISTANCE_POST_PRINTING||Contours_paste_raw[i][j].y>(CAM_H-BORDER_DISTANCE_POST_PRINTING))
						{
							exit_cycle=true;
							break;
						};
					}

					if (exit_cycle){
						continue;
					}

					Contours_paste.push_back(Contours_paste_raw[i]);
					if( DB->WorkingModesS.DebugMode )
					{
						cv::drawContours(image_draw, Contours_paste_raw, i, CV_RGB(255,0,0));
					}
					cv::drawContours(image_draw, Contours_paste_raw, i, CV_RGB(255,0,0));
					//cv::fillConvexPoly(Good_Contours_paste_regions, Contours_paste_raw[i], 255);
				}
				//imshow("image_draw", image_draw);
		}


	image_draw.copyTo(TemplateImg);
	//////////////////////////////////////////////////////////////////////////////////////////
	/// FIND THE PASTE USING THE HUE DIFFERENCE
	//////////////////////////////////////////////////////////////////////////////////////////
	/*
	if(DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE != -1){
		vector<cv::Mat> bgr_planes;
		cv::cvtColor(*frame, frame_HSV , CV_BGR2HSV);
		cv::split( frame_HSV, bgr_planes );



		cv::Mat PadTHR(bgr_planes[0].rows,bgr_planes[0].cols , CV_8UC1);
		//double treshold, up and down
		for (int i=0; i< bgr_planes[0].rows; i++)
		{
			for (int j=0; j< bgr_planes[0].cols; j++)
			{
				int editValue=bgr_planes[0].at<uchar>(i,j);

				if((editValue> (DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE - DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth/2) )&&(editValue<DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE + DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth/2)) //check whether value is within range.
				{
					PadTHR.at<uchar>(i,j)=255;
				}
				else
				{
					PadTHR.at<uchar>(i,j)=0;
				}
			}
		}

		//extremey white regions do not have a yellow hue, we add them separately
		cv::cvtColor(original_thresh, original_thresh, CV_BGR2GRAY);
		cv::threshold(original_thresh,original_thresh, 250, 255, CV_THRESH_BINARY_INV);
		erode(original_thresh,original_thresh,cv::Mat());
		cv::bitwise_and(original_thresh, PadTHR, PadTHR);

		cv::erode(PadTHR,PadTHR, cv::Mat());

		//dilate a little bit the region of interest (remember, the mask is white)
		cv::erode(Good_Contours_paste_regions,Good_Contours_paste_regions, cv::Mat());
		//cv::imshow("Good_Contours_paste_regions", Good_Contours_paste_regions);
		// outside the regions we found in the previous step, we must not find pads
		cv::bitwise_or(Good_Contours_paste_regions,PadTHR, PadTHR);



		//copy the PadTHR image into camera->working_frame to view it in the preview
		PadTHR.copyTo(camera->Pad_Mask_frame);


		switch (DB->pAUTOInspectionCurrentSiteStruct->BestChannel){
			case BLUE_CHANNEL:
				bitwise_and(PadTHR, layers[0], PadTHR);
				break;
			case GREEN_CHANNEL:
				bitwise_and(PadTHR, layers[1], PadTHR);
				break;
			case RED_CHANNEL:
				bitwise_and(PadTHR, layers[2], PadTHR);
				break;
		}

		//extract the paste borders
		cv::Mat Inverted_Mask = Good_Contours_paste_regions.clone();
		cv::bitwise_not(Inverted_Mask,Inverted_Mask);
		//cv::imshow("Inverted_Mask",Inverted_Mask);

		cv::Mat frame_copy= frame->clone();
		vector<vector<cv::Point> > contours;
		cv::findContours( PadTHR, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		int area_region;

		for (int i = 0; i < contours.size(); ++i)							{
								// Check area
							area_region=cv::contourArea(contours[i]);
							if ( area_region < MIN_AREA_SPI) continue;

							bool exit_cycle = false;
							for (int j = 0; j < contours[i].size(); j++){
								if(contours[i][j].x<BORDER_DISTANCE_POST_PRINTING||contours[i][j].x>frame_copy.cols-BORDER_DISTANCE_POST_PRINTING)
								{
									exit_cycle=true;
									break;
								};
								if(contours[i][j].y<BORDER_DISTANCE_POST_PRINTING||contours[i][j].y>frame_copy.rows-BORDER_DISTANCE_POST_PRINTING)
								{
									exit_cycle=true;
									break;
								};
							}

							if (exit_cycle){
								continue;
							}
							cv::drawContours(frame_copy, contours, i, CV_RGB(255,0,0) );

							}

		frame_copy.copyTo(TemplateImg);



	}*/






}

bool AutoSPICheck::FindUncoveredPads(cv::Mat* frame){

	if(frame->rows==0 || frame->cols==0){
		return false;
	}

	//we use the HUE
	if(DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE != -1){
		cv::Mat frame_copy = frame->clone();
		vector<cv::Mat> bgr_planes;
		cv::Mat frame_HSV;
		cv::cvtColor(*frame, frame_HSV , CV_BGR2HSV);
		cv::split( frame_HSV, bgr_planes );

		cv::Mat PadTHR(bgr_planes[0].rows,bgr_planes[0].cols , CV_8UC1);
		//double treshold, up and down
		for (int i=0; i< bgr_planes[0].rows; i++)
		{
				for (int j=0; j< bgr_planes[0].cols; j++)
				{
					int editValue=bgr_planes[0].at<uchar>(i,j);

					if((editValue> (DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE - DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth/2) )&&(editValue<DB->pAUTOInspectionCurrentSiteStruct->PasteCentralHUE + DB->pAUTOInspectionCurrentSiteStruct->PasteHUEWidth/2)) //check whether value is within range.
					{
						PadTHR.at<uchar>(i,j)=255;
					}
					else
					{
						PadTHR.at<uchar>(i,j)=0;
					}
				}
			}
		//cv::imshow("padThr", PadTHR);
		//cv::waitKey(100);
		PadTHR.copyTo(camera->Pad_Mask_frame);

		vector<vector<cv::Point> > contours;
		cv::findContours( PadTHR, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		int area_region;


		for (int i = 0; i < contours.size(); i++){
				// Check area
			//area_region=cv::contourArea(contours[i]);
			//if ( area_region < MIN_AREA_SPI) continue;

			bool exit_cycle = false;
			for (int j = 0; j < contours[i].size(); j++){
				if(contours[i][j].x<BORDER_DISTANCE_POST_PRINTING||contours[i][j].x>frame_copy.cols-BORDER_DISTANCE_POST_PRINTING)
				{
					exit_cycle=true;
					break;
				};
				if(contours[i][j].y<BORDER_DISTANCE_POST_PRINTING||contours[i][j].y>frame_copy.rows-BORDER_DISTANCE_POST_PRINTING)
				{
					exit_cycle=true;
					break;
				};
			}

			if (exit_cycle){
				continue;
			}
			cv::drawContours(frame_copy, contours, i, CV_RGB(0,0,255) );

		}


		frame_copy.copyTo(TemplateImg);
		return true;

	}//end HUE part
	else if(DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads != -1){

		cv::Mat frame_copy = frame->clone();
		vector<cv::Mat> bgr_planes;
		cv::split( *frame, bgr_planes );
		cv::Mat BestChannelImg;
		switch (DB->pAUTOInspectionCurrentSiteStruct->BestChannelPads){
			case BLUE_CHANNEL:
				BestChannelImg = bgr_planes[0].clone();
				//cout<<"best channel blue"<<endl;
				break;
			case GREEN_CHANNEL:
				BestChannelImg = bgr_planes[1].clone();
				//cout<<"best channel green"<<endl;
				break;
			case RED_CHANNEL:
				BestChannelImg = bgr_planes[2].clone();
				//cout<<"best channel red"<<endl;
				break;
		}
		//imshow("BestChannelImg",BestChannelImg);
		//cv::waitKey(100);
		//cout<<"central pad color"<< DB->pAUTOInspectionCurrentSiteStruct->CentralPadsColor<<endl;
		//cout<<"width /2"<< DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth/2<<endl;

		cv::Mat PadTHR(bgr_planes[0].rows,bgr_planes[0].cols , CV_8UC1);
		//double treshold, up and down
		for (int i=0; i< bgr_planes[0].rows; i++)
		{
				for (int j=0; j< bgr_planes[0].cols; j++)
				{
					int editValue=BestChannelImg.at<uchar>(i,j);

					if((editValue >= (DB->pAUTOInspectionCurrentSiteStruct->CentralPadsColor - DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth) )&&(editValue <= DB->pAUTOInspectionCurrentSiteStruct->CentralPadsColor + DB->pAUTOInspectionCurrentSiteStruct->PadsColorWidth)) //check whether value is within range.
					{
						PadTHR.at<uchar>(i,j)=255;
					}
					else
					{
						PadTHR.at<uchar>(i,j)=0;
					}
				}
			}
		//cv::imshow("padThr", PadTHR);
		//cv::waitKey(100);
		cv::dilate(PadTHR,PadTHR,cv::Mat(), cv::Point(-1,-1),1); // hashtag ColorDilate
		PadTHR.copyTo(camera->Pad_Mask_frame);

		vector<vector<cv::Point> > contours;
		cv::findContours( PadTHR, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
		int area_region;

		for (int i = 0; i < contours.size(); i++)							{
								// Check area
							//area_region=cv::contourArea(contours[i]);
							//if ( area_region < MIN_AREA_SPI) continue;

							bool exit_cycle = false;
							for (int j = 0; j < contours[i].size(); j++){
								if(contours[i][j].x<BORDER_DISTANCE_POST_PRINTING||contours[i][j].x>frame_copy.cols-BORDER_DISTANCE_POST_PRINTING)
								{
									exit_cycle=true;
									break;
								};
								if(contours[i][j].y<BORDER_DISTANCE_POST_PRINTING||contours[i][j].y>frame_copy.rows-BORDER_DISTANCE_POST_PRINTING)
								{
									exit_cycle=true;
									break;
								};
							}

							if (exit_cycle){
								continue;
							}
							cv::drawContours(frame_copy, contours, i, CV_RGB(0,0,255) );

							}
		//cv::imshow("frame_copy", frame_copy);
		//cv::waitKey(100);

		frame_copy.copyTo(TemplateImg);
		return true;

	}// end the color part




}

float AutoSPICheck::norm2 (cv::Point2f v1, cv::Point2f v2){
	float ret=sqrt( pow((v1.x-v2.x),2) + pow((v1.y-v2.y),2) );
	return ret;
}



