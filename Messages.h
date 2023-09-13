//---------------------------------------------------------------------------
//
// Name:        Messages.h
// Author:      Daniele Belloni
// Created:     16/10/2007
// Description: Definitions for the SR3200 messages
//
//---------------------------------------------------------------------------
#ifndef __MESSAGES_H
#define __MESSAGES_H

// Main machine
#define MSG_BADDBVERSION		_("DB version not supported !")
#define MSG_DBUPDATE			_("Updating database... ")
#define MSG_DBUPDATEERROR		_("Unable to update database !")
#define MSG_DBUPDATEOK			_("Database successfully updated !")

#define MSG_ORIGINOSET			_("Origins not setted !")
#define MSG_ORIGIALREADYSET		_("Origins already setted !")
#define MSG_MACHINENOTACTIVATED	_("Machine not activated !")
#define MSG_MACHINEDISABLED		_("Machine successfully disabled !")
#define MSG_MACHINESAFEMODE		_("Machine in Safe-Mode !")
#define MSG_ERROROCCURRED		_("ERROR occurred !")
#define MSG_ASKABORT			_("Abort procedure ?")
#define MSG_ABORTEDBYUSER		_("Procedure terminated by user !")
#define MSG_WAITWORKING			_("Please wait, working...")
#define MSG_WAITVIDEO			_("Please wait, video init...")
#define MSG_VIDEOINITEND		_("Video initialized !")
#define TOO_ON					_("SR3200 activation")
#define TOO_OFF					_("SR3200 deactivation")
#define TOO_ORIGINS				_("Origin search")
#define TOO_HOME				_("Motors start position")
#define TOO_MENU				_("Back to main menu")
#define TOO_ALARMGREEN			_("Alarm light green")
#define TOO_ALARMRED			_("Alarm light red")
#define TOO_BUZZER				_("Buzzer")
#define TOO_CAMERALEDUP			_("Camera led up")
#define TOO_CAMERALEDDOWN		_("Camera led down")
#define TOO_FRAMELOCK			_("Frame lock")
#define TOO_FRONTSQUEEGEES		_("Front squeegees")
#define TOO_REARSQUEEGEES		_("Rear squeegees")
#define TOO_VACUUMPLATE			_("Vacuum plate")
#define TOO_AUXVIDEO			_("Switch aux video mode")
#define TOO_MOTORHOME			_("Move current motor in start position")
#define TOO_MOTOREND			_("Move current motor in end position")
#define MSG_SEMAPHOREREDUCTION  _("Semaphore reduction command failed !")

// Others
#define MSG_PCBZEROHEIGHT		_("PCB thickness setted to zero. Continue anyway ?")
#define MSG_ROTDONE				_("Rotational correction done: R=%3.2f deg")
#define MSG_ROTCHECKDETECTED	_("Rotational offset detected: R=%3.3f deg")
#define MSG_TRASLDONE			_("Translational correction done: X=%3.2f mm Y=%3.2f mm")
#define MSG_NOTIFYMOTORRESET	_("Move motors to start position to continue !")
#define MSG_ASKMOTORRESET		_("Reset motors position ?")
#define TOO_IMMEDIATESTOP		_("Immediate STOP")
#define MSG_HWTALERT			_("ATTENTION! Movement and security controls are not performed on Hardware Test !")
#define MSG_COVEROPEN			_("ATTENTION! The cover is open!\nContinue the cycle anyway ?")
#define MSG_BOARDPRESENT 		_("WARNING! A board is loaded!")
#define MSG_RACKINLOADINGPOS	_("WARNING! Rack in loading position!\nMove to working position?")
#define MSG_LOADING				_("Loading board...")
#define MSG_UNLOADING			_("Unloading board...")
#define MSG_LOADERROR			_("Board loading failed !")
#define MSG_UNLOADERROR			_("Board unloading failed !")
#define MSG_CONVEYORSTOOLDSTART	_("Adjust conveyors to last production (%s) position?")
#define MSG_CAMERAZEROFOUND     _("Camera Zero found, corrections: %3.2f %3.2f")
#define MSG_CAMERAZERONOTFOUND  _("Camera Zero not  found, please teach")
#define MSG_CAMERAZEROOUTBONDS  _("Camera Zero outside bonds")
#define MSG_CONVEYORSTOSTART	_("Adjust conveyors to selected production position?")
#define MSG_REMOVERACK			_("ATTENTION! Remove rack if placed into loader !")
#define MSG_TOOMANYBOARDS		_("ATTENTION! Too many boards to produce !\nBoards number setted to max value...")
#define MSG_ERRORDIRLOGS		_("Error creating logs directory !")
#define MSG_CLEANING			_("Cleaning stencil...")
#define MSG_CLEANINGERROR		_("Cleaning cycle failed !")
#define MSG_CLEANINGENDED		_("Cleaning cycle complete !")
#define MSG_REMEMBERSQUEGEES	_("Please remember to remove squeegees!")

// Inspection sites
#define MSG_ASKREMOVESITE		_("Are you sure to delete selected inspection site ?")
#define MSG_ASKREMOVEAREA		_("Are you sure to delete selected area ?")
#define TOO_ADDSITE				_("Add inspection site")
#define TOO_REMOVESITE			_("Remove inspection site")
#define TOO_SELECTTHR			_("Threshold selection")
#define TOO_TEACHSPI			_("Teach inspection site")

// InspectionPanel
#define MSG_MAXSITEREACHED		_("Maximum number of inspection points reached !")
//Inspection
#define MSG_SPI_REFIMG_ERR		_("SPI reference image match error !")
#define MSG_SPI_REFIMG_POS_ERR	_("SPI reference image position error !")

// File
#define MSG_FILEOPENERROR		_("Unable to open selected file !")
#define MSG_FILEOBSOLETE		_("Selected file is obsolete !")
#define MSG_FILECORRUPTED		_("Selected file is corrupted or not valid !")

// Database
#define MSG_DBBACKUPOK			_("Database backup complete !")
#define MSG_DBBACKUPERROR		_("Unable to create database backup ! (%d)")
#define MSG_DBRESTORE			_("Select a database to restore:")
#define MSG_DBRESTOREAKS		_("Are you sure to restore selected backup ?")
#define MSG_DBRESTOREOK			_("Database correctly restored !")
#define MSG_DBRESTOREERROR		_("Unable to restore database ! (%d)")

// SW Update
#define MSG_SWUPDATE			_("Select an update file")
#define MSG_SWUPDATEEAKS		_("Are you sure you want to update current software ?")

// Language
#define MSG_LANGREBOOT			_("Restart machine to apply changes !")
#define MSG_LANGERROR			_("Unable to use selected language !")

// Fiducials
#define MSG_FIDUCIALMANUAL		_("Teach fiducial manually !")
#define MSG_FIDNOTFOUND			_("Fiducial not found !")
#define MSG_FIDNOTFOUND_CHECK	_("Fiducial not found (Check)!")
#define MSG_TRASLATION_CHECK	_("Translation check detected: X=%3.3f Y=%3.3f")
#define MSG_FIDFOUND_CIRCLE		_("Fiducial found: X=%3.2f Y=%3.2f R=%3.2f")
#define MSG_FIDFOUND_RECT		_("Fiducial found: X=%3.2f Y=%3.2f x=%3.2f y=%3.2f")
#define MSG_FIDFOUND_TEMPLATE	_("Template found: X=%3.2f Y=%3.2f s=%3.2f") //s=%3.2f"
#define MSG_FIDFOUNDMAN			_("Fiducial found manually: X=%d Y=%d")
#define MSG_FIDMANUALTEACH		_("Fiducial manual teaching...")
#define MSG_SEARCHFIDROT1		_("First rotation fiducial search...")
#define MSG_SEARCHFIDROT2		_("Second rotation fiducial search...")
#define MSG_SEARCHFIDTRA		_("Translation fiducial search...")
#define MSG_SEARCHFIDROT1FRAME	_("Frame first rotation fiducial search...")
#define MSG_SEARCHFIDROT2FRAME	_("Frame second rotation fiducial search...")
#define MSG_SEARCHFIDTRAFRAME	_("Frame translation fiducial search...")
#define MSG_CLICKFIDUCIAL		_("Click inside fiducial...")
#define MSG_NOTEMPLATEIMAGE		_("Template image not founded!\nPlease start a new alignment!")
#define MSG_SETTEMPLATE			_("Select template image...")
#define MSG_FIDUCIALSEARCH		_("Searching fiducial...")

// Serial port
#define MSG_SPORTOPENOKSTEPPER			_("Stepper modules serial port successfully open !")
#define MSG_SPORTOPENERRORSTEPPER		_("Stepper modules serial port open error !")
#define MSG_SPORTCLOSEERRORSTEPPER		_("Stepper modules serial port close error !")
#define MSG_SPORTOPENOKBRUSHLESS		_("Brushless modules serial port successfully open !")
#define MSG_SPORTOPENERRORBRUSHLESS		_("Brushless modules serial port open error !")
#define MSG_SPORTCLOSEERRORBRUSHLESS	_("Brushless modules serial port close error !")

// Video
#define MSG_VIDEOERROR			_("Unable to initialize video device !!!\n\nApplication will be terminated !!!")
#define MSG_ACQUIRING			_("Acquiring...")

// Inputs / Outputs
#define MSG_INPUTSERROR			_("Inputs read error !")
#define MSG_INPUTSECURITYSERROR	_("Security input sensor activated !\nCheck for a board locked between conveyors !")
#define MSG_INPUTSECURITYSERROR2	_("Security input sensor NOT activated !\nWas the board correctly unloaded?")
#define MSG_DISABLESECURITYSERROR	_("Warning, are you sure to disable this check? Boards stuck between conveyors can be broken")
#define MSG_AIRPRESSUREERROR	_("Air pressure sensor not activated !")
#define MSG_CAMSECURITYERROR	_("Camera security sensor not activated !")
#define MSG_ZSECURITYERROR		_("Plate security sensor not activated !")
#define MSG_SEMAPHOREERROR		_("Alarm light activation error !")
#define MSG_BUZZERERROR			_("Buzzer activation error !")
#define MSG_FRAMELOCKERROR		_("Frame lock activation error !")
#define MSG_CAMERAVIEWERROR		_("Camera led activation error !")
#define MSG_SQUEEGEESACTERROR	_("Squeegees activation error !")
#define MSG_VACUUMERROR			_("Vacuum activation error !")
#define MSG_BOARDLOCKERROR		_("Board lock activation error !")
#define MSG_CONVPISTONERROR		_("Conveyor ejector activation error !")
#define MSG_CAMPISTONERROR		_("Camera piston activation error !")
#define MSG_LOADERPISTONERROR	_("Loader piston activation error !")
#define MSG_CLEANPISTONERROR	_("Cleaning system piston activation error !")
#define MSG_CLEANVACUUMERROR	_("Cleaning system vacuum activation error !")
#define MSG_CLEANACTIVATEERROR	_("Cleaning system activation error !")

// Motors
#define MSG_MOTORINITENDED		_("Motors successfully initializated !")
#define MSG_MOTORINITERROR		_("Motors initialization error !")
#define MSG_MOTORLIMITSWTCERROR	_("Limit switch activated !")
#define MSG_MOTORLIMERROR		_("Motor limit reached !")
#define MSG_MOTORCOMMERROR		_("Serial communication error !")
#define MSG_MOTORSTARTPOS		_("Motors start position reached !")
#define MSG_MOTORDRIVERERROR	_("Motor driver error !")
#define MSG_MOTORMOVEERROR		_("Motor move error !")
#define MSG_MOTORWAITERROR		_("Motor wait error !")
#define MSG_MOTORENABLE			_("Enabling motors")
#define MSG_TABLE1				_("Table 1")
#define MSG_TABLE2				_("Table 2")
#define MSG_TABLE3				_("Table 3")
#define MSG_CAMERAX				_("Camera X")
#define MSG_CAMERAY				_("Camera Y")
#define MSG_PLATE				_("Plate")
#define MSG_SQUEEGEES			_("Squeegees")
#define MSG_LOADER				_("Loader")
#define MSG_LCONVWIDTH			_("Left Conveyor Width")
#define MSG_LCONVFEED			_("Left Conveyor Feed")
#define MSG_CCONVWIDTH			_("Center Conveyor Width")
#define MSG_CCONVFEED			_("Center Conveyor Feed")
#define MSG_MOTORSSTARTWAIT		_("Moving motors to start positions...")
#define MSG_CLEANER				_("Cleaning System")

// Motors movement error
#define MSG_TABLEERROR			_("Table motors error !")
#define MSG_CAMERAERROR			_("Camera motors error !")
#define MSG_CAMERAXERROR		_("Camera X motors error !")
#define MSG_CAMERAYERROR		_("Camera Y motors error !")
#define MSG_PLATEERROR			_("Plate motor error !")
#define MSG_SQUEEGEESERROR		_("Squeegees motor error !")
#define MSG_LOADERERROR			_("Loader motor error !")
#define MSG_CONVWIDTHERROR		_("Conveyor width motor error !")
#define MSG_CONVWIDTHMIN		_("Conveyor width exceeds minimum size. Please check PCB Y size")
#define MSG_CONVFEEDERROR		_("Conveyor feeding motor error !")
#define MSG_CLEANERERROR		_("Cleaning system motor error !")
#define MSG_CONVPUSHERROR		_("Conveyor push motor error !")

// Enable/disable motors error
#define MSG_TABLEINITERROR		_("Table motors enable error !")
#define MSG_CAMERAINITERROR		_("Camera motors enable error !")
#define MSG_PLATEINITERROR		_("Plate motor enable error !")
#define MSG_SQUEEGEESINITERROR	_("Squeegees motor enable error !")
#define MSG_LOADERINITERROR		_("Loader motor enable error !")
#define MSG_LCONVWINITERROR		_("Left conveyor width motor enable error !")
#define MSG_LCONVFINITERROR		_("Left conveyor feeding motor enable error !")
#define MSG_LCONVPINITERROR		_("Left conveyor ejector motor enable error !")
#define MSG_CCONVWINITERROR		_("Center conveyor width motor enable error !")
#define MSG_CCONVFINITERROR		_("Center conveyor feeding motor enable error !")
#define MSG_CLEANERINITERROR	_("Cleaning System motor enable error !")

#define MSG_TABLEDISERROR		_("Table motor %d disable error !")
#define MSG_CAMERADISERROR		_("Camera motor %c disable error !")
#define MSG_PLATEDISERROR		_("Plate motor disable error !")
#define MSG_SQUEEGEESDISERROR	_("Squeegees motor disable error !")
#define MSG_LOADERDISERROR		_("Loader motor disable error !")
#define MSG_LCONVWDISERROR		_("Left conveyor width motor disable error !")
#define MSG_LCONVFDISERROR		_("Left conveyor feeding motor disable error !")
#define MSG_CCONVWDISERROR		_("Center conveyor width motor disable error !")
#define MSG_CCONVFDISERROR		_("Center conveyor feeding motor disable error !")

// Moltimode activation errors
#define MSG_TABLEMMERROR		_("Table motors multimode enable error !")
#define MSG_LCONVMMERROR		_("Left conveyor motors multimode enable error !")
#define MSG_CCONVMMERROR		_("Center conveyor motors multimode enable error !")

// Origin
#define MSG_ASKORIGINSEARCH		_("Start origins search ?")
#define MSG_ORIGINSEARCH		_("Origins search...")
#define MSG_ORIGINSEARCHENDED	_("Origins search complete !")

// SMAlignment
#define MSG_ALIGNABORTED		_("Alignment procedure aborted !")
#define MSG_ALIGNENDED			_("Alignment procedure complete !")
#define MSG_ALIGNFRAME			_("Align frame manually !")
#define MSG_ALIGNBOARDTEACH		_("Start board position teaching...")
#define MSG_ALIGNLOWEDGE		_("Center the camera X axis on the low PCB edge...")
#define MSG_ALIGNLEFTEDGE		_("Center the camera Y axis on the left PCB edge...")
#define MSG_ALIGNSTART			_("Start board alignment teaching...")
#define MSG_ALIGNMOVE1FID		_("Move camera on first point (rotation) !")
#define MSG_ALIGNMOVE2FID		_("Move camera on second point (rotation) !")
#define MSG_ALIGNMOVE3FID		_("Move camera on third point (translation) !")
#define MSG_ALIGNMOVENEXTPOINT	_("Move camera on next point !")
#define MSG_ALIGNVERIFY			_("Alignment verify...")
#define MSG_ALIGNVERIFYVISIONQ	_("Check alignment with camera ?")
#define MSG_ALIGNVERIFYVISION	_("Check alignment with camera...")
#define MSG_FIDUCIALTEACHSTART	_("Start fiducial teaching...")
#define MSG_ALIGNFIDENDED		_("Alignment fiducial teaching procedure complete !")
#define MSG_ALIGNFIDENDEDNEXT1	_("Select Printing menu to start production !")
#define MSG_ASKSQUEEGEESZTEACH	_("Teach squeegees zero position ?\nAnswering No the old value will be used.")
#define MSG_ASKSQUEEGEESMTEACH	_("Teach squeegees movement ?\nAnswering No the old value will be used.")
#define MSG_ALIGNSAMEPOINT		_("Attention second point (rotation) too close to first point (rotation) !\nPlease choose a different point !")

// SMPrinting
#define MSG_PRINTINGABORTED		_("Printing procedure aborted !")
#define MSG_PRINTINGENDED		_("Printing cycle complete !")
#define MSG_PRINTINGVERIFY		_("Check alignment...")
#define MSG_PRINTING			_("Printing in progress...")
#define MSG_PRINTINGNOPOINT		_("Some verify points have not been teached !\nPlease teach them manually !")
#define MSG_PRINTINGRECOVERYERR _("Squeegees recovery movement out of range - Please check it !")
#define MSG_PRINTINGZEROBOARD	_("Loader board number set to zero. Start a single cycle printing ?")
#define MSG_PRINTINGLEFT		_("Printing cycles remaining: %d")
#define MSG_WARNINGDOUBLEPRNT	_("Do you want to move the loader in the next position?")

// SMVerify
#define MSG_VERIFYABORTED		_("Verify procedure aborted !")
#define MSG_VERIFYENDED			_("Verify procedure complete !")
#define MSG_NOVERIFYPOINTS		_("There aren't points to verify !")
#define MSG_VERIFYPOINT			_("Verifying point %d...")

// SMInspection
#define MSG_NOSITESTOTEACH		_("There aren't sites to teach !")
#define MSG_NOCORRECTIONMASK	_("Correction mask not present, please teach")
#define MSG_SUCCESSFULLYSAVED 	_("Correction Mask successfully saved")
#define MSG_INSPECTINGSITE		_("Inspecting site %d / %d")
#define MSG_INSPECTIONABORTED	_("Inspection procedure aborted !")
#define MSG_INSPECTIONENDED		_("Inspection procedure complete !")
#define MSG_INSP_TECH_ENDED		_("Inspection teaching procedure complete !")
#define MSG_ASK_ADD_SITE		_("Add a new inspection site ?")
#define MSG_ESTIMATED_CORR		_("Estimated correction: %f degree. Apply changes?")

// SMPins
#define MSG_PINSNOPOINT			_("No pins placement points teached !")
#define MSG_PINSABORTED			_("Pins placement procedure aborted !")
#define MSG_PINSENDED			_("Pins placement procedure complete !")
#define MSG_PINSPOINT			_("Pin placement point %d...")
#define MSG_PINSCOVER			_("Close cover to continue procedure !")

// SMPasteConditioning
#define MSG_PASTEABORTED		_("Paste conditioning procedure aborted !")
#define MSG_PASTEENDED			_("Paste conditioning procedure complete !")
#define MSG_PASTECYCLE			_("Paste conditioning cycle %d / %d")
#define MSG_PASTEASKPAPER		_("Place the paste on the stencil. Place a paper on PCB surface. Confirm to Start")
#define MSG_PASTEREMOVEPAPER	_("Remove paper from PCB surface...")

// SMPlateMovement
#define MSG_PLATEMOVEABORTED	_("Plate height procedure aborted !")
#define MSG_PLATEMOVEENDED		_("Plate height procedure complete !")
#define MSG_PLATEMOVESTART		_("Move plate to reach the working position...")

// SMCameraFocus
#define MSG_CAMERAFOCUSABORTED	_("Camera focus procedure aborted !")
#define MSG_CAMERAFOCUSENDED	_("Camera focus procedure complete !")
#define MSG_CAMERAFOCUSSTART	_("Move plate and camera to reach the focal height...")

// SMCameraScale
#define MSG_CAMERASCALEABORTED	_("Camera scale procedure aborted !")
#define MSG_CAMERASCALEENDED	_("Camera scale procedure complete !")
#define MSG_CAMERASCALESTART	_("Align calibration board to camera axes...")
#define MSG_CAMERASCALEXAXIS	_("Teach X axis scale...")
#define MSG_CAMERASCALEYAXIS	_("Teach Y axis scale...")
#define MSG_CAMERASCALEXAXISMM	_("Insert distance in mm (X axis):")
#define MSG_CAMERASCALEYAXISMM	_("Insert distance in mm (Y axis):")

// SMCameraOffset
#define MSG_CAMERAOFFSETABORTED	_("Camera offset procedure aborted !")
#define MSG_CAMERAOFFSETENDED	_("Camera offset procedure complete !")
#define MSG_PRINTMANUALLY		_("Print manually...")
#define MSG_SEARCHTPOINT		_("Search point: %d")
#define MSG_BGAPARMADJ			_("Adjust vision centering parameters...")
#define MSG_BGACAMCENTERFIRST	_("Center camera on first offset pattern !")
#define MSG_BGAMANUALSEARCH		_("Offset pattern manual teaching...")
#define MSG_BGAFOUND			_("Offset pattern found: X=%3.2f Y=%3.2f")
#define MSG_BGAFOUNDMAN			_("Offset pattern found manually: X=%d Y=%d")
#define MSG_BGANOTFOUND			_("Offset pattern not found !")
#define MSG_BGAMANUAL			_("Teach offset pattern manually !")
#define MSG_BGAASKMANUAL		_("Teach offset pattern manually ?\nChoose NO to search again in automatic mode !")
#define MSG_CAMERAOFFSETMANUAL	_("Some points need manual teaching !")
#define MSG_WRONGFRAMEPOSITION	_("Wrong frame position! Camera can't reach all the offset points !\nMove the frame on the left and align it again !")
#define MSG_RESETCHECKMAP		_("Reset check mapping values ?")
#define MSG_UPDATEMAP			_("Update offset mapping values ?")
#define MSG_CORRECTOFFSETMAP	_("Correct the Offset map? Cannot be undone ")

#define MSG_CAMERAZEROENDED		_("Camera Zero procedure complete !")
#define MSG_CAMERAZEROABORTED	_("Camera Zero procedure aborted !")

// SMConveyorEdge
#define MSG_CONVEDGEABORTED		_("Conveyor edge procedure aborted !")
#define MSG_CONVEDGEENDED		_("Conveyor edge procedure complete !")
#define MSG_CONVEDGESTART		_("Move camera to the center of the top edge of fixed conveyor...")

//BoardPanel
#define MSG_DELETE_RESULT		_("Delete selected Board?")

// ProductionDataPanel
#define MSG_SQUEEGEESZERO		_("Teach squeegees zero position...")
#define MSG_SQUEEGEESMOVE		_("Teach squeegees movement...")
#define MSG_SQUEEGEESZEROABORTED	_("Squeegees zero position procedure aborted !")
#define MSG_SQUEEGEESMOVEABORTED	_("Squeegees movement procedure aborted !")
#define MSG_SQUEEGEESZEROENDED	_("Squeegees zero position procedure complete !")
#define MSG_SQUEEGEESMOVEENDED	_("Squeegees movement procedure complete !")
#define MSG_ASKCOUNTERRESET		_("Are you sure to reset the production counter ?")
#define MSG_NEWPRODUCTIONNAME	_("Insert new production name :")
#define MSG_EXSISTINGNAME		_("Name already exist !")
#define MSG_ASKPRODUCTIONDELETE	_("Are you sure to delete selected production ?")
#define MSG_ASKSAVERECORDS		_("Delete related results?")
#define MSG_LOADERZERO			_("Teach loader start position...")
#define MSG_LOADERZEROENDED		_("Loader start position procedure complete !")
#define MSG_LOADERZEROABORTED	_("Loader start position procedure aborted !")
#define MSG_LOADERZEROPOS		_("Move loader to old start position ?")
#define MSG_CONVEYOROK			_("Conveyors correctly setted !")
#define MSG_CONVEYORWAIT		_("Waiting for conveyors movement...")
#define MSG_LOADERWAIT			_("Waiting for loader movement...")
#define TOO_NEWPRODUCTION		_("Add a new production")
#define TOO_EDITPRODUCTION		_("Edit production name")
#define TOO_DELETEPRODUCTION	_("Delete production")
#define TOO_TEACHSQUEEGEESZERO	_("Teach squeegees zero position")
#define TOO_TEACHSQUEEGEESMOVE	_("Teach squeegees movement")
#define TOO_COUNTERRESET		_("Reset production counter")
#define TOO_OK					_("OK")
#define TOO_CANCEL				_("Cancel")
#define TOO_MOVELOADERZERO		_("Move loader to start position")
#define TOO_TEACHLOADERZERO		_("Teach loader start position")
#define TOO_CONVEYORADJUST		_("Conveyors to PCB's Y dimension")
#define TOO_TOPGERBERSEL		_("Select top layer gerber files")
#define TOO_BOTGERBERSEL		_("Select bottom layer gerber files")
#define TOO_GERBERDIM			_("Import dimensions from gerber files")

// ProductionPanel
#define TOO_FIDUCIALMODIFY		_("Modify fiducial parameters")
#define TOO_RACKMOVEUP			_("Move to next board")
#define TOO_RACKMOVEDN			_("Move to previous board")
#define TOO_RACKMOVEPOS			_("Move to board in position...")
#define MSG_MANUALCLEAN			_("You may clean the stencil    ")

// PinsPanel
#define MSG_BOARDNOTALIGNED		_("Alignment procedure not yet completed !")
#define TOO_PINSSELECT			_("Select pins positions")

// Password
#define MSG_ENTERPASSWORDHWT	_("Enter password HWT")
#define MSG_ENTERPASSWORDL1		_("Enter password Level 1")
#define MSG_ENTERPASSWORDL2		_("Enter password Level 2")

// Bootloader
#define MSG_DEACTIVATETOUPDATE	_("Deactivate machine to update boards firmwares !")
#define MSG_FIRMWARESELECT		_("Select a firmware file !")
#define MSG_DRIVERNOTCONN		_("Selected driver not connected !")
#define MSG_DRIVERSUSPENDALL	_("Suspend all drivers...")
#define MSG_DRIVERSUSPENDERROR	_("Unable to suspend driver %d !")
#define MSG_DRIVERSUSPEND		_("Suspended driver %d !")
#define MSG_DRIVERRESET			_("Reset selected driver...")
#define MSG_DRIVERRESETERROR	_("Unable to reset selected driver !")
#define MSG_DRIVERNOTFOUND		_("Target device not found !")
#define MSG_DRIVERCOMMERROR		_("Communication error !")
#define MSG_FIRMWAREPARSE		_("Parse firmware...")
#define MSG_TRANSFERDATA		_("Transferring data...")
#define MSG_TRANSFERDATAENDED	_("Data transfer successfully completed !")
#define MSG_DRIVERSELECT		_("Select a driver !")

// OffDialog
#define TOO_STANDBY				_("Standby: deactivate machine motors and outputs")
#define TOO_SHUTDOWN			_("Shutdown: turn off the machine")

// OffsetMapsDialog
#define MSG_SAVE				_("Data as changed!\nDo you want to save data?")

// Gerber
#define MSG_SELECTGERBER		_("Select a gerber file")
#define MSG_ERRORGERBER			_("Not a valid gerber file !")
#define MSG_ERRORFILEGERBER		_("Error copying gerber files !")
#define MSG_ERRORDIRGERBER		_("Error creating gerber directory !")
#define MSG_ERRORLOADGERBER		_("Gerber files not found !")
#define MSG_ERRORSELGERBER		_("Gerber files not selected !")

// PinsDialog
#define MSG_DIMENSIONWARNING	_("Warning ! Gerber dimensions and program data dimensions\nare different of more than 2 mm !")
#define MSG_RESETPINSPOS		_("Reset all pins positions ?")

#endif
