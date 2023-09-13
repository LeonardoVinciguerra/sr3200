#include "wxPinsDialog.h"
#include "wxPictureBox.h"
#include "images/png_images.h"
#include "Messages.h"
#include "GlobalDefs.h"
#include "GlobalUtils.h"
#include <wx/filedlg.h>
#include <wx/msgdlg.h>

//(*InternalHeaders(wxPinsDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/dcmemory.h>
#include <wx/image.h>

#include <gdk/gdk.h>
#include <gtk/gtk.h>

//(*IdInit(wxPinsDialog)
const long wxPinsDialog::ID_CUSTOM1 = wxNewId();
const long wxPinsDialog::ID_BUTTON1 = wxNewId();
const long wxPinsDialog::ID_BITMAPBUTTON3 = wxNewId();
const long wxPinsDialog::ID_BITMAPBUTTON4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxPinsDialog,wxDialog)
	//(*EventTable(wxPinsDialog)
	//*)
END_EVENT_TABLE()

wxPinsDialog::wxPinsDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxPinsDialog)
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
	SetClientSize(wxSize(820,700));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	pcbImage = new wxPictureBox(this,ID_CUSTOM1,wxDefaultPosition,wxSize(700,700));
	FlexGridSizer1->Add(pcbImage, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	resetBtn = new wxButton(this, ID_BUTTON1, _("RESET"), wxDefaultPosition, wxSize(-1,30), 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(resetBtn, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	abortBtn = new wxBitmapButton(this, ID_BITMAPBUTTON3, wxNullBitmap, wxDefaultPosition, wxSize(50,50), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
	BoxSizer6->Add(abortBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	okBtn = new wxBitmapButton(this, ID_BITMAPBUTTON4, wxNullBitmap, wxDefaultPosition, wxSize(50,50), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
	BoxSizer6->Add(okBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);
	
	pcbImage->Connect(wxEVT_ENTER_WINDOW,(wxObjectEventFunction)&wxPinsDialog::OnpcbImageMouseEnter,0,this);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxPinsDialog::OnresetBtnClick);
	Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxPinsDialog::OnabortBtnClick);
	Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxPinsDialog::OnokBtnClick);
	//*)

	abortBtn->SetBitmapLabel( wxMEMORY_BITMAP( abort_on ) );
	okBtn->SetBitmapLabel( wxMEMORY_BITMAP( ok_on ) );

	// create a top level libgerbv structure
	GdkColor darkGreenColor = {0, 0, 19000, 0};
	mainProject = gerbv_create_project();
	mainProject->background = darkGreenColor;

	//width = pcbImage->GetWidth();
	//height = pcbImage->GetHeight();
	width = 700;
	height = 700;
	//width = 312;
	//height = 374;
	rot = 0.0;
	layerFlip = 0;

	topPixelY = 0;
	leftPixelX = 0;

	numPins = 0;

    // make sure we change the render type to "cairo" instead of the GDK alternative
    screenRenderInfo.renderType = GERBV_RENDER_TYPE_CAIRO_HIGH_QUALITY;
    screenRenderInfo.displayHeight = height;
    screenRenderInfo.displayWidth = width;

    // Numero di livelli inseriti nel progetto
    gerberIndex = 0;

    pcbImage->ConnectMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &wxPinsDialog::ImageLeftClick ), this );
    isClickEnable = true;
}

wxPinsDialog::~wxPinsDialog()
{
	//(*Destroy(wxPinsDialog)
	//*)

	// destroy the project, which will in turn destroy all child images
	gerbv_destroy_project (mainProject);
}

void wxPinsDialog::Init( SRMachine *SRRef )
{
	SR = SRRef;

    // loads level from saved files and show on image
	char pathBase[MAXNPATH];
	char layerName[MAXNPATH];
	char fileNumber[2];

	gerberIndex = 0;

	strcpy(pathBase,DIR_GERBER);
    strcat(pathBase,"/");
    strcat(pathBase,SR->DB->ProductionDataS.ProductionName);
	strcat(pathBase,"-b.l");

	// Add active layers to project
	if( SR->DB->ProductionDataS.BotGerberSolder != 0 )
	{
		strcpy(layerName,pathBase);
    	sprintf(fileNumber,"%d",SR->DB->ProductionDataS.BotGerberSolder-1);
		strcat(layerName, fileNumber);
		gerbv_open_layer_from_filename( mainProject, layerName );
		// change the color of the layer
		GdkColor goldColor = {0, 56000, 51000, 2550};
		mainProject->file[gerberIndex]->color = goldColor;
		gerberIndex++;
	}
	if( SR->DB->ProductionDataS.BotGerberMech != 0 )
	{
		strcpy(layerName,pathBase);
    	sprintf(fileNumber,"%d",SR->DB->ProductionDataS.BotGerberMech-1);
		strcat(layerName, fileNumber);
		gerbv_open_layer_from_filename( mainProject, layerName );
		// change the color of the layer
		GdkColor whiteColor = {0, 65000, 65000, 65000};
		mainProject->file[gerberIndex]->color = whiteColor;
		gerberIndex++;
	}

	if( gerberRedraw(SR->DB->ProductionDataS.BotGerberRot, SR->DB->ProductionDataS.BotGerberFlip) )
		wxMessageBox( MSG_DIMENSIONWARNING, MACHINE_NAME, wxOK | wxICON_WARNING, this );

	// Recall pins positions
	if( SR->DB->ProductionDataS.PinsPointsNumber > 0 )
	{
		numPins = SR->DB->ProductionDataS.PinsPointsNumber;

		for( int i=0; i<numPins; i++ )
		{
			pinsCenter[i].x = SR->DB->PinsPointsS[i].X * screenRenderInfo.scaleFactorX / INCH_TO_MM + leftPixelX;
			pinsCenter[i].y = SR->DB->PinsPointsS[i].Y * screenRenderInfo.scaleFactorY / INCH_TO_MM + topPixelY;
		}

		gerberRedraw(SR->DB->ProductionDataS.BotGerberRot, SR->DB->ProductionDataS.BotGerberFlip);
	}
}

void wxPinsDialog::ImageLeftClick( wxMouseEvent& e )
{
	if( !isClickEnable )
		return;

	isClickEnable = false;

	// Cursor position
	int cursorX = e.GetPosition().x;
	int cursorY = e.GetPosition().y;

	//CHECK CONDITIONS!
	if(cursorX > maxXclickable || cursorX < minXclickable){
		isClickEnable = true;
		return;
	}
	if(cursorY > maxYclickable || cursorY < minYclickable){
		isClickEnable = true;
		return;
	}

	if( numPins < NUM_PINS_POINTS )
	{
		pinsCenter[numPins].x = cursorX+1;
		pinsCenter[numPins++].y = cursorY+1;
	}

	gerberRedraw(SR->DB->ProductionDataS.BotGerberRot, SR->DB->ProductionDataS.BotGerberFlip);

	//wxMessageBox( wxString::Format( "X:%d Y:%d", cursorX, cursorY ), MACHINE_NAME, wxOK | wxICON_INFORMATION, this );

	// Workplace position
	//int posX = (cursorX - WORKPLACE_IMG_DELTA)*(WORKPLACE_DIM/float(WORKPLACE_IMG_W - 1)) + WORKPLACE_X;
	//int posY = -cursorY*(WORKPLACE_DIM/float(WORKPLACE_IMG_H - 1)) + WORKPLACE_Y;

	isClickEnable = true;
}

void wxPinsDialog::cairoDraw(unsigned char *buffer, gerbv_project_t *gerber, gerbv_render_info_t *screenRenderInfo, double angle, int flip)
{
	int width = screenRenderInfo->displayWidth;
	int height = screenRenderInfo->displayHeight;

	cairo_t *cr;
	cairo_surface_t* surface;
	cairo_format_t format = CAIRO_FORMAT_RGB24;

	surface = cairo_image_surface_create_for_data(buffer, format, width, height, width*4);
	cr = cairo_create(surface);

	// White background.
	//cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	// Dark green background.
	cairo_set_source_rgb(cr, 0, 0.3, 0);
	cairo_paint (cr);
	//cairo_rectangle(cr, 0, 0, width, height);
	//cairo_fill(cr);

	if( flip )
	{
		cairo_matrix_t matrix;
		cairo_translate(cr,width/2,height/2); // translate origin to the center
		//flip around Y axis
		cairo_matrix_init_scale (&matrix, -1.0, 1.0);
		cairo_transform (cr, &matrix);
		cairo_translate(cr,-width/2,-height/2); // translate origin back
	}

	if( angle != 0.0 )
	{
		cairo_translate(cr,width/2,height/2); // translate origin to the center
		cairo_rotate (cr, angle);
		cairo_translate(cr,-width/2,-height/2); // translate origin back
	}

	//gerbv_render_zoom_to_fit_display(gerber, screenRenderInfo);
	gerbv_render_zoom_to_fit_display_nobound(gerber, screenRenderInfo);

	if( SR->DB->ProductionDataS.BotGerberSolder != 0 )
	{
        cairo_push_group (cr);
		gerbv_render_layer_to_cairo_target (cr, mainProject->file[SR->DB->ProductionDataS.BotGerberSolder-1], screenRenderInfo);
        cairo_pop_group_to_source (cr);
        cairo_paint_with_alpha (cr, 0.9);
	}
	if( SR->DB->ProductionDataS.BotGerberMech != 0 )
	{
        cairo_push_group (cr);
		gerbv_render_layer_to_cairo_target (cr, mainProject->file[SR->DB->ProductionDataS.BotGerberMech-1], screenRenderInfo);
        cairo_pop_group_to_source (cr);
        cairo_paint_with_alpha (cr, 1);
	}

	// Cleanup.
	cairo_destroy(cr);
	cairo_surface_destroy(surface);
}

int wxPinsDialog::gerberRedraw(double angle, int flip)
{
	int dimensionsOut = 0;

	wxBitmap blankBmp( width, height );
	wxMemoryDC dc;
	dc.SelectObject( blankBmp );
	dc.SetBackground( this->GetBackgroundColour() );
	dc.Clear();

    unsigned char *cairo_buffer = new unsigned char[width*height*4];
    unsigned char* wx_buffer = new unsigned char[width*height*4];

    cairoDraw(cairo_buffer, mainProject, &screenRenderInfo, angle, flip);
    cairoToWxImageFormat(cairo_buffer, wx_buffer, screenRenderInfo.displayWidth, screenRenderInfo.displayHeight);

	// Blit final image to the screen.
	wxBitmap m_bitmap(wxImage(width, height, wx_buffer, true));

	dc.DrawBitmap(m_bitmap, 0, 0, true);

	// Check differences between gerber outside dimensions and dimensions written on program data
	gerbv_render_size_t boundingbox;
	gerbv_render_get_boundingbox(mainProject, &boundingbox);
	double xdim, ydim;
	xdim = INCH_TO_MM*fabs(boundingbox.right-boundingbox.left);
	ydim = INCH_TO_MM*fabs(boundingbox.top-boundingbox.bottom);
	double Cx = fabs( xdim * cos(SR->DB->ProductionDataS.BotGerberRot) + ydim * sin(SR->DB->ProductionDataS.BotGerberRot) );
	double Cy = fabs( -xdim * sin(SR->DB->ProductionDataS.BotGerberRot) + ydim * cos(SR->DB->ProductionDataS.BotGerberRot) );
	double diffX = fabs(SR->DB->ProductionDataS.PCBX - Cx);
	double diffY = fabs(SR->DB->ProductionDataS.PCBY - Cy);
	if( (diffX > MAX_GERBER_DIFF) || (diffY > MAX_GERBER_DIFF) )
		dimensionsOut = 1;

	//wxMessageBox( wxString::Format( "scaleX:%5.3f scaleY:%5.3f\nlowerLeftX:%5.3f lowerLeftX:%5.3f", screenRenderInfo.scaleFactorX, screenRenderInfo.scaleFactorY, screenRenderInfo.lowerLeftX, screenRenderInfo.lowerLeftY ), MACHINE_NAME, wxOK | wxICON_INFORMATION, this );

	// if not a squared pcb...
	if( Cx != Cy )
	{
		// Draw rectangles in the outside of pcb borders
		dc.SetPen( wxPen( this->GetBackgroundColour(), 1 ) );

		if( Cx >= Cy )
		{
			// pcb with a top and bottom clear space on the window image
			topPixelY = ( height - myLRound( Cy / INCH_TO_MM * screenRenderInfo.scaleFactorY) )/2 ;
			int bottomPixelY = height - topPixelY;
			//wxMessageBox( wxString::Format( "top:%d bottom:%d", topPixelY, bottomPixelY ), MACHINE_NAME, wxOK | wxICON_INFORMATION, this );
			dc.DrawRectangle( 0, 0, width, topPixelY );
			dc.DrawRectangle( 0, bottomPixelY, width, height-bottomPixelY );
			//draw red lines to identify clickable region
			wxBrush brush( wxColour( 255, 0, 0 ) );
			dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
			dc.SetBrush(brush);
			wxPoint p1Top(0, myLRound(18/ INCH_TO_MM * screenRenderInfo.scaleFactorX) + topPixelY) ;
			wxPoint p2Top( m_bitmap.GetWidth() , myLRound(PIN_PLACEMENT_SECURITY_DISTANCE/ INCH_TO_MM * screenRenderInfo.scaleFactorX)  +topPixelY) ;

			wxPoint p1Bot(0, m_bitmap.GetHeight() - myLRound(PIN_PLACEMENT_SECURITY_DISTANCE/ INCH_TO_MM * screenRenderInfo.scaleFactorX) -topPixelY) ;
			wxPoint p2Bot( m_bitmap.GetWidth() , m_bitmap.GetHeight() - myLRound(PIN_PLACEMENT_SECURITY_DISTANCE/ INCH_TO_MM * screenRenderInfo.scaleFactorX)  -topPixelY) ;
			dc.DrawLine(p1Top, p2Top);
			dc.DrawLine(p1Bot, p2Bot);
			minXclickable = 0;
			maxXclickable = m_bitmap.GetWidth();
			minYclickable = topPixelY;
			maxYclickable = m_bitmap.GetHeight() - topPixelY;
			minYWarning = p1Top.y;
			maxYWarning = p1Bot.y;

		}
		else
		{
			// pcb with a left and right clear space on the window image
			leftPixelX = ( width - myLRound( Cx / INCH_TO_MM * screenRenderInfo.scaleFactorX) )/2 ;
			int rightPixelX = width - leftPixelX;
			dc.DrawRectangle( 0, 0, leftPixelX, height );
			dc.DrawRectangle( rightPixelX, 0, width-rightPixelX, height );
			//draw red lines to identify clickable region
			wxBrush brush( wxColour( 255, 0, 0 ) );
			dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
			dc.SetBrush(brush);
			wxPoint p1Top(leftPixelX, myLRound(PIN_PLACEMENT_SECURITY_DISTANCE/ INCH_TO_MM * screenRenderInfo.scaleFactorX) ) ;
			wxPoint p2Top( m_bitmap.GetWidth() -leftPixelX, myLRound(PIN_PLACEMENT_SECURITY_DISTANCE/ INCH_TO_MM * screenRenderInfo.scaleFactorX) ) ;

			wxPoint p1Bot(leftPixelX, m_bitmap.GetHeight() - myLRound(PIN_PLACEMENT_SECURITY_DISTANCE/ INCH_TO_MM * screenRenderInfo.scaleFactorX) ) ;
			wxPoint p2Bot( m_bitmap.GetWidth() -leftPixelX , m_bitmap.GetHeight() - myLRound(PIN_PLACEMENT_SECURITY_DISTANCE/ INCH_TO_MM * screenRenderInfo.scaleFactorX) ) ;
			dc.DrawLine(p1Top, p2Top);
			dc.DrawLine(p1Bot, p2Bot);
			minXclickable = leftPixelX;
			maxXclickable = m_bitmap.GetWidth() - leftPixelX ;
			minYclickable = 0;
			maxYclickable = m_bitmap.GetHeight();
			minYWarning = p1Top.y;
			maxYWarning = p1Bot.y;
		}
	}







	// Draw pins
	if( numPins > 0 )
	{
		wxBrush brush( wxColour( 255, 0, 0 ) );
		dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
		dc.SetBrush(brush);
		for( int i=0; i<numPins; i++ ){
			if(pinsCenter[i].y < minYWarning || pinsCenter[i].y > maxYWarning){
				dc.SetPen( wxPen( wxColour( 255, 0, 0 ) ) );
				dc.SetBrush(wxBrush(wxColour( 255, 0, 0 )));
			}
			else{
				dc.SetPen( wxPen( wxColour( 0, 0, 255 ) ) );
				dc.SetBrush(wxBrush(wxColour( 0, 0, 255 )));
			}
				dc.DrawCircle( pinsCenter[i], PINS_RADIUS );
		}


	}

	pcbImage->SetImage( blankBmp );

	// Cleanup.
	delete wx_buffer;
	delete cairo_buffer;

	// export a rendered PNG image of the project, using the autoscale version to automatically center the image
	//gerbv_export_png_file_from_project_autoscaled (mainProject, 640, 480, "Panel of F10D.png");

	return dimensionsOut;
}

void wxPinsDialog::OnabortBtnClick(wxCommandEvent& event)
{
	EndModal( PINSDIALOG_CANCEL );
}

void wxPinsDialog::OnokBtnClick(wxCommandEvent& event)
{
	SortFiducials();
	// Save pins positions
	if( numPins > 0 )
	{
		SR->DB->ProductionDataS.PinsPointsNumber = numPins;

		for( int i=0; i<numPins; i++ )
		{
			SR->DB->PinsPointsS[i].X = (pinsCenter[i].x - leftPixelX) / screenRenderInfo.scaleFactorX * INCH_TO_MM;
			SR->DB->PinsPointsS[i].Y = (pinsCenter[i].y - topPixelY) / screenRenderInfo.scaleFactorY * INCH_TO_MM;

			//wxMessageBox( wxString::Format( "X:%5.3f Y:%5.3f", SR->DB->PinsPointsS[i].X, SR->DB->PinsPointsS[i].Y ), MACHINE_NAME, wxOK | wxICON_INFORMATION, this );
		}
	}
	else
	{
		SR->DB->ProductionDataS.PinsPointsNumber = 0;

		for( int i=0; i<NUM_PINS_POINTS; i++ )
		{
			SR->DB->PinsPointsS[i].X = 0.0;
			SR->DB->PinsPointsS[i].Y = 0.0;
		}
	}

	EndModal( PINSDIALOG_OK );
}

void wxPinsDialog::OnpcbImageMouseEnter(wxMouseEvent& event)
{
	pcbImage->SetCursor( wxCURSOR_CROSS );
}

void wxPinsDialog::OnresetBtnClick(wxCommandEvent& event)
{
	if( wxMessageBox( MSG_RESETPINSPOS, MACHINE_NAME, wxYES_NO | wxICON_QUESTION, this ) == wxYES )
	{
		numPins = 0;

		for( int i=0; i<NUM_PINS_POINTS; i++ )
		{
			pinsCenter[i].x = 0;
			pinsCenter[i].y = 0;
		}

		gerberRedraw(SR->DB->ProductionDataS.BotGerberRot, SR->DB->ProductionDataS.BotGerberFlip);
	}
}

int wxPinsDialog::SortFiducials(){

	struct PinsLines{
		std::vector<int> x;
		std::vector<int> y;
	};

	PinsLines pinsLines[10];
	int linesNumber=0;

	std::vector<cv::Point> myPoints;
	for(int i =0; i<numPins; i++){
		myPoints.push_back( cv::Point(pinsCenter[i].x, pinsCenter[i].y) );
		cout<<"rowPinCenter valuex:"<<pinsCenter[i].x<<"y:"<<pinsCenter[i].y<<endl;

	}
	std::vector<int> minY;

	numPins = 0;

	for( int i=0; myPoints.size() != 0; i++ ){
		int YCoord = myPoints[0].y;
		minY.push_back(myPoints[0].y);
		pinsLines[linesNumber].x.push_back(myPoints[0].x);
		pinsLines[linesNumber].y.push_back(myPoints[0].y);
		myPoints.erase(myPoints.begin());
		for( int j = 0; j < myPoints.size(); j++){

			if( abs(myPoints[j].y  - YCoord) < PIN_SORTING_THRESHOLD ){
				pinsLines[linesNumber].x.push_back(myPoints[j].x);
				pinsLines[linesNumber].y.push_back(myPoints[j].y);
				if(myPoints[j].y < minY.at(i)){
					minY.at(i) = myPoints[j].y;
				}
				myPoints.erase(myPoints.begin()+j);
				j--;
			}

		}
		linesNumber++;
		cout<<"size: "<<myPoints.size()<<endl;
	}

	//sort each struct based on its minY
	for(int i=0; i<linesNumber; i++){
		int minLocalY = minY[i];
		int minIndex = -1;
		for(int j=i; j<linesNumber; j++){
			if(minY[j]< minLocalY){
				minLocalY = minY[j];
				minIndex = j;
			}
		}
		if(minIndex != -1){
			int tmp = minY[i];
			minY[i] = minY[minIndex];
			minY[minIndex] = tmp;

			std::vector<int> tmpX = pinsLines[i].x;
			std::vector<int> tmpY = pinsLines[i].y;
			pinsLines[i].x = pinsLines[minIndex].x;
			pinsLines[i].y = pinsLines[minIndex].y;
			pinsLines[minIndex].x = tmpX;
			pinsLines[minIndex].y = tmpY;
		}

		//sort in each line
		for(int k=0; k<pinsLines[i].x.size(); k++){
			int minX = pinsLines[i].x[k];
			int minXInedx = -1;
			for(int l=k; l<pinsLines[i].x.size(); l++){
				if(pinsLines[i].x[l]< minX){
					minX = pinsLines[i].x[l];
					minXInedx = l;
				}
			}
			if(minXInedx != -1){
				int xtmp = pinsLines[i].x[minXInedx];
				int ytmp = pinsLines[i].y[minXInedx];
				pinsLines[i].x[minXInedx] = pinsLines[i].x[k];
				pinsLines[i].y[minXInedx] = pinsLines[i].y[k];
				pinsLines[i].x[k] = xtmp;
				pinsLines[i].y[k] = ytmp;
			}
			pinsCenter[numPins].x = pinsLines[i].x[k];
			pinsCenter[numPins++].y = pinsLines[i].y[k];
			cout<<"iteration:"<<i<<" iteration k: "<<k<<" valuex:"<<pinsLines[i].x[k]<<"y:"<<pinsLines[i].y[k]<<endl;
		}
	}

	return SR_OK;
}
