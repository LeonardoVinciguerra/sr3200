# these are the headers for your project

#########################################################################
# APPLICATION SECTION
#########################################################################
# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = wxsr3050 wxsr3100

# the application source, library search path, and link libraries

noinst_HEADERS = BrushlessModule.h BrushlessModuleDefs.h SRDB200.h \
	StepperModuleDefs.h iqmath.h v4l2.h wxAuxVideo.h wxControlPanel.h wxDatasette.h \
	wxMainVideo.h wxMainWin.h wxStatusPanel.h
wxsr3050_SOURCES = BrushlessModule.cpp FindCircle.cpp FindOffsetPattern.cpp \
	FindRectangle.cpp FindTemplate.cpp GlobalUtils.cpp Motor.cpp MotorModule.cpp \
	SMAlignment.cpp SMBase.cpp SMCameraFocus.cpp SMCameraOffset.cpp SMCameraScale.cpp \
	SMDemomode.cpp SMHardwareTest.cpp SMPlateMovement.cpp SMPrinting.cpp SMVerify.cpp \
	SMVision.cpp SRDatabase.cpp SRDatabaseUpdate.cpp SRDatabaseUpdate_100_101.cpp \
	SRMachine.cpp SRMachineCamera.cpp SRMachinePlate.cpp SRMachineSlide.cpp \
	SRMachineSqueegees.cpp SRMachineTable.cpp SRMachineUpdateDriver.cpp SerialCom.cpp SmartLog.cpp \
	StepperModule.cpp VideoDevice.cpp hough.cpp v4l2.cpp wxAdvancedParamsPanel.cpp \
	wxAlignmentTypeDialog.cpp wxAuxVideo.cpp wxCalibrationPanel.cpp wxCameraControl.cpp \
	wxCommInterface.cpp wxControlPanel.cpp wxDatasette.cpp wxGeneralParamsPanel.cpp \
	wxHardwareTestPanel.cpp wxMainVideo.cpp wxMainWin.cpp wxMotorsDataPanel.cpp \
	wxMyComboValidator.cpp wxMyEntryDialog.cpp wxMySerialPort.cpp wxMySpinValidator.cpp \
	wxMyTextValidator.cpp wxOffDialog.cpp wxOffsetMapsDialog.cpp wxPictureBox.cpp \
	wxProductionDataPanel.cpp wxProductionPanel.cpp wxSR3050App.cpp wxStatusPanel.cpp wxSwUpdate.cpp \
	wxTranslationHelper.cpp wxVisionPanel.cpp wxZipFiles.cpp
wxsr3050_LDFLAGS = $(WX_LIBS)
