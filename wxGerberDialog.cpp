#include "wxGerberDialog.h"
#include "wxPictureBox.h"
#include "images/png_images.h"
#include "Messages.h"
#include "GlobalDefs.h"
#include "GlobalUtils.h"
#include <wx/filedlg.h>
#include <wx/msgdlg.h>

//(*InternalHeaders(wxGerberDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/dcmemory.h>
#include <wx/image.h>

#include <gdk/gdk.h>
#include <gtk/gtk.h>

//(*IdInit(wxGerberDialog)
const long wxGerberDialog::ID_CUSTOM1 = wxNewId();
const long wxGerberDialog::ID_CHECKBOX3 = wxNewId();
const long wxGerberDialog::ID_BUTTON2 = wxNewId();
const long wxGerberDialog::ID_CHECKBOX2 = wxNewId();
const long wxGerberDialog::ID_BUTTON4 = wxNewId();
const long wxGerberDialog::ID_CHECKBOX4 = wxNewId();
const long wxGerberDialog::ID_BITMAPBUTTON1 = wxNewId();
const long wxGerberDialog::ID_BITMAPBUTTON2 = wxNewId();
const long wxGerberDialog::ID_BITMAPBUTTON3 = wxNewId();
const long wxGerberDialog::ID_BITMAPBUTTON4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxGerberDialog,wxDialog)
	//(*EventTable(wxGerberDialog)
	//*)
END_EVENT_TABLE()

wxGerberDialog::wxGerberDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(wxGerberDialog)
	wxBoxSizer* BoxSizer4;
	wxStaticBoxSizer* StaticBoxSizer2;
	wxBoxSizer* BoxSizer6;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;
	
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("id"));
	SetClientSize(wxSize(900,600));
	Move(wxDefaultPosition);
	SetMinSize(wxSize(900,600));
	SetMaxSize(wxSize(900,600));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	pcbImage = new wxPictureBox(this,ID_CUSTOM1,wxPoint(0,0),wxSize(600,600));
	FlexGridSizer1->Add(pcbImage, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Gerber Files"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	solderCheck = new wxCheckBox(this, ID_CHECKBOX3, _("Solder Mask Layer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	solderCheck->SetValue(false);
	solderCheck->Disable();
	BoxSizer2->Add(solderCheck, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	solderBtn = new wxButton(this, ID_BUTTON2, _("..."), wxDefaultPosition, wxSize(50,-1), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer2->Add(solderBtn, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
	mechCheck = new wxCheckBox(this, ID_CHECKBOX2, _("Mechanical Layer"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	mechCheck->SetValue(false);
	mechCheck->Disable();
	BoxSizer4->Add(mechCheck, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	mechBtn = new wxButton(this, ID_BUTTON4, _("..."), wxDefaultPosition, wxSize(50,-1), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	BoxSizer4->Add(mechBtn, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(BoxSizer4, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(-1,-1,0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	flip_Check = new wxCheckBox(this, ID_CHECKBOX4, _("Flip Gerber"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	flip_Check->SetValue(false);
	BoxSizer1->Add(flip_Check, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Rotate Gerber"));
	StaticBoxSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ccwRotBtn = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	ccwRotBtn->Disable();
	StaticBoxSizer2->Add(ccwRotBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	cwRotBtn = new wxBitmapButton(this, ID_BITMAPBUTTON2, wxNullBitmap, wxDefaultPosition, wxSize(44,44), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	cwRotBtn->Disable();
	StaticBoxSizer2->Add(cwRotBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(StaticBoxSizer2, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
	abortBtn = new wxBitmapButton(this, ID_BITMAPBUTTON3, wxNullBitmap, wxDefaultPosition, wxSize(50,50), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
	BoxSizer6->Add(abortBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	okBtn = new wxBitmapButton(this, ID_BITMAPBUTTON4, wxNullBitmap, wxDefaultPosition, wxSize(50,50), wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
	BoxSizer6->Add(okBtn, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer1->Add(BoxSizer6, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);
	
	Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxGerberDialog::OnsolderCheckClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxGerberDialog::OnsolderBtnClick);
	Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxGerberDialog::OnmechCheckClick);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxGerberDialog::OnmechBtnClick);
	Connect(ID_CHECKBOX4,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&wxGerberDialog::Onflip_CheckClick);
	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxGerberDialog::OnccwRotBtnClick);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxGerberDialog::OncwRotBtnClick);
	Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxGerberDialog::OnabortBtnClick);
	Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxGerberDialog::OnokBtnClick);
	//*)

	ccwRotBtn->SetBitmapLabel( wxMEMORY_BITMAP( turn_left_on ) );
	cwRotBtn->SetBitmapLabel( wxMEMORY_BITMAP( turn_right_on ) );
	abortBtn->SetBitmapLabel( wxMEMORY_BITMAP( abort_on ) );
	okBtn->SetBitmapLabel( wxMEMORY_BITMAP( ok_on ) );

	// create a top level libgerbv structure
	GdkColor darkGreenColor = {0, 0, 19000, 0};
	mainProject = gerbv_create_project();
	mainProject->background = darkGreenColor;

	//width = pcbImage->GetWidth();
	//height = pcbImage->GetHeight();
	width = 600;
	height = 600;
	//width = 312;
	//height = 374;
	rot = 0.0;
	layerFlip = 0;

    // make sure we change the render type to "cairo" instead of the GDK alternative
    screenRenderInfo.renderType = GERBV_RENDER_TYPE_CAIRO_HIGH_QUALITY;
    screenRenderInfo.displayHeight = height;
    screenRenderInfo.displayWidth = width;

    // Numero di livelli inseriti nel progetto
    gerberIndex = 0;
    solderIndex = -1;
    mechIndex = -1;
}

wxGerberDialog::~wxGerberDialog()
{
	//(*Destroy(wxGerberDialog)
	//*)

	// destroy the project, which will in turn destroy all child images
	gerbv_destroy_project (mainProject);

}

void wxGerberDialog::Init( SRMachine *SRRef )
{
	SR = SRRef;
}

void wxGerberDialog::cairoDraw(unsigned char *buffer, gerbv_project_t *gerber, gerbv_render_info_t *screenRenderInfo, double angle, int flip)
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

	gerbv_render_zoom_to_fit_display(gerber, screenRenderInfo);

	if( solderCheck->GetValue() )
	{
        cairo_push_group (cr);
		gerbv_render_layer_to_cairo_target (cr, mainProject->file[solderIndex], screenRenderInfo);
        cairo_pop_group_to_source (cr);
        cairo_paint_with_alpha (cr, 0.9);
	}
	if( mechCheck->GetValue() )
	{
        cairo_push_group (cr);
		gerbv_render_layer_to_cairo_target (cr, mainProject->file[mechIndex], screenRenderInfo);
        cairo_pop_group_to_source (cr);
        cairo_paint_with_alpha (cr, 1);
	}
	//gerbv_render_all_layers_to_cairo_target (gerber, cr, screenRenderInfo);

	//wxMessageBox( wxString::Format( "X:%5.3f Y:%5.3f", screenRenderInfo->scaleFactorX, screenRenderInfo->scaleFactorY ), MACHINE_NAME, wxOK | wxICON_INFORMATION, this );



	// Cleanup.
	cairo_destroy(cr);
	cairo_surface_destroy(surface);
}

void wxGerberDialog::gerberRedraw(double angle, int flip)
{
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
	pcbImage->SetImage( blankBmp );

	// Cleanup.
	delete wx_buffer;
	delete cairo_buffer;

	// export a rendered PNG image of the project, using the autoscale version to automatically center the image
	//gerbv_export_png_file_from_project_autoscaled (mainProject, 640, 480, "Panel of F10D.png");
}

void wxGerberDialog::OnsolderBtnClick(wxCommandEvent& event)
{
	wxFileDialog *openFileDialog = new wxFileDialog( this, MSG_SELECTGERBER, wxT(""), wxT(""), wxT("*.*"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if( openFileDialog->ShowModal() == wxID_OK )
	{
		char cstring[1024];
		// assuming you want UTF-8, change the wxConv* parameter as needed
		strncpy(cstring, (const char*)openFileDialog->GetPath().mb_str(wxConvUTF8), 1023);

		/*
		// parse a Gerber file and store it in the gerbv_project_t struct
		if( solderIndex != -1 )
		{
			gerbv_unload_layer(mainProject, solderIndex);
			solderIndex = -1;
		}
		*/
		gerbv_open_layer_from_filename( mainProject, cstring );

		solderIndex = gerberIndex;

		// make sure we parsed the file
		if( mainProject->file[solderIndex] == NULL )
			wxMessageBox( MSG_ERRORGERBER, MACHINE_NAME, wxOK | wxICON_ERROR, this );
		else
		{
			// change the color of the image
			GdkColor goldColor = {0, 56000, 51000, 2550};
			//GdkColor greenishColor = {0, 10000, 65000, 10000};
			mainProject->file[solderIndex]->color = goldColor;

			gerberIndex++;

			solderBtn->Enable( false );
			solderCheck->Enable( true );
			solderCheck->SetValue( true );

			gerberRedraw(rot, layerFlip);

			cwRotBtn->Enable(true);
			ccwRotBtn->Enable(true);
		}
	}

	delete openFileDialog;
}

void wxGerberDialog::OnmechBtnClick(wxCommandEvent& event)
{
	wxFileDialog *openFileDialog = new wxFileDialog( this, MSG_SELECTGERBER, wxT(""), wxT(""), wxT("*.*"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if( openFileDialog->ShowModal() == wxID_OK )
	{
		char cstring[1024];
		// assuming you want UTF-8, change the wxConv* parameter as needed
		strncpy(cstring, (const char*)openFileDialog->GetPath().mb_str(wxConvUTF8), 1023);

		gerbv_open_layer_from_filename( mainProject, cstring );

		mechIndex = gerberIndex;

		// make sure we parsed the file
		if( mainProject->file[mechIndex] == NULL )
			wxMessageBox( MSG_ERRORGERBER, MACHINE_NAME, wxOK | wxICON_ERROR, this );
		else
		{
			// change the color of the image
			GdkColor whiteColor = {0, 65000, 65000, 65000};
			mainProject->file[mechIndex]->color = whiteColor;

			gerberIndex++;

			mechBtn->Enable( false );
			mechCheck->Enable( true );
			mechCheck->SetValue( true );

			gerberRedraw(rot, layerFlip);

			cwRotBtn->Enable(true);
			ccwRotBtn->Enable(true);
		}
	}

	delete openFileDialog;
}

void wxGerberDialog::OnsolderCheckClick(wxCommandEvent& event)
{
	gerberRedraw(rot, layerFlip);
}

void wxGerberDialog::OnpadsCheckClick(wxCommandEvent& event)
{
	gerberRedraw(rot, layerFlip);
}

void wxGerberDialog::OnmechCheckClick(wxCommandEvent& event)
{
	gerberRedraw(rot, layerFlip);
}

void wxGerberDialog::OnccwRotBtnClick(wxCommandEvent& event)
{
	if( layerFlip )
		rot += M_PI / 2.0;
	else
		rot -= M_PI / 2.0;
	gerberRedraw(rot, layerFlip);
}

void wxGerberDialog::OncwRotBtnClick(wxCommandEvent& event)
{
	if( layerFlip )
		rot -= M_PI / 2.0;
	else
		rot += M_PI / 2.0;
	gerberRedraw(rot, layerFlip);
}

bool wxGerberDialog::SaveProject()
{
	char path[MAXNPATH];
	char fullpath[MAXNPATH];
	char fileNumber[2];
    //char* output = strrchr(mainProject->file[0]->fullPathname, '/');

    // check/create "gerber" directory
	if( !CheckDirectory( DIR_GERBER ) )
	{
		if( mkdir( DIR_GERBER, DIR_CREATION_FLAG ) )
		{
			wxMessageBox( MSG_ERRORDIRGERBER, MACHINE_NAME, wxOK | wxICON_ERROR, this );
			return false;
		}
	}

	// delete any file with the same name (if exist)
    strcpy(path,SR->DB->ProductionDataS.ProductionName);
    if( layer == TOP_LAYER )
        strcat(path,"-t");
    else
    	strcat(path,"-b");
	DeleteFiles( DIR_GERBER, path );

	strcpy(path,DIR_GERBER);
    strcat(path,"/");
    strcat(path,SR->DB->ProductionDataS.ProductionName);
    if( layer == TOP_LAYER )
        strcat(path,"-t.l");
    else
    	strcat(path,"-b.l");

    if( solderCheck->GetValue() )
    {
    	sprintf(fileNumber,"%d",solderIndex);
		strcpy(fullpath, path);
		strcat(fullpath, fileNumber);
		if( CopyFile( mainProject->file[solderIndex]->fullPathname, fullpath ) )
		{
			wxMessageBox( MSG_ERRORFILEGERBER, MACHINE_NAME, wxOK | wxICON_ERROR, this );
			return false;
		}
		if( layer == TOP_LAYER )
			SR->DB->ProductionDataS.TopGerberSolder = solderIndex + 1;
		else
			SR->DB->ProductionDataS.BotGerberSolder = solderIndex + 1;
    }
    if( mechCheck->GetValue() )
    {
    	sprintf(fileNumber,"%d",mechIndex);
		strcpy(fullpath, path);
		strcat(fullpath, fileNumber);
		if( CopyFile( mainProject->file[mechIndex]->fullPathname, fullpath ) )
		{
			wxMessageBox( MSG_ERRORFILEGERBER, MACHINE_NAME, wxOK | wxICON_ERROR, this );
			return false;
		}
		if( layer == TOP_LAYER )
			SR->DB->ProductionDataS.TopGerberMech = mechIndex + 1;
		else
			SR->DB->ProductionDataS.BotGerberMech = mechIndex + 1;
    }

    strcpy(path,DIR_GERBER);
    strcat(path,"/");
    strcat(path,SR->DB->ProductionDataS.ProductionName);
    if( layer == TOP_LAYER )
        strcat(path,"-t.png");
    else
        strcat(path,"-b.png");

    gerbv_export_png_file_from_project_autoscaled (mainProject, 100, 100, path);
    wxImage rotateImage;
    rotateImage.LoadFile(path, wxBITMAP_TYPE_PNG);

    if( layerFlip )
    {
		rotateImage = rotateImage.Mirror(true);
		rotateImage = rotateImage.Rotate(rot, wxPoint(50,50));
    }
    else
    	rotateImage = rotateImage.Rotate(-rot, wxPoint(50,50));

    rotateImage.SaveFile(path);

    return true;
}

void wxGerberDialog::OnokBtnClick(wxCommandEvent& event)
{
	if( SaveProject() )
		EndModal( GERBERDIALOG_OK );
	else
		EndModal( GERBERDIALOG_CANCEL );
}

void wxGerberDialog::OnabortBtnClick(wxCommandEvent& event)
{
	/*
	gerbv_render_size_t boundingbox;
	gerbv_render_get_boundingbox(mainProject, &boundingbox);

	double xdim, ydim;
	xdim = INCH_TO_MM*fabs(boundingbox.right-boundingbox.left);
	ydim = INCH_TO_MM*fabs(boundingbox.top-boundingbox.bottom);
	double Cx = fabs( xdim * cos(rot) + ydim * sin(rot) );
	double Cy = fabs( -xdim * sin(rot) + ydim * cos(rot) );
	wxMessageBox( wxString::Format( "X:%5.3f Y:%5.3f (%d %d)", Cx, Cy, myLRound( Cx ), myLRound( Cy ) ), MACHINE_NAME, wxOK | wxICON_INFORMATION, this );

	gerberRedraw(rot, layerFlip);
	*/


	EndModal( GERBERDIALOG_CANCEL );

}

void wxGerberDialog::Onflip_CheckClick(wxCommandEvent& event)
{
	if( flip_Check->GetValue() )
		layerFlip = 1;
	else
		layerFlip = 0;

	gerberRedraw(rot, layerFlip);
}
