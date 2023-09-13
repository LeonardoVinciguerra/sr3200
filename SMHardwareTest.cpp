//---------------------------------------------------------------------------
//
// Name:        SMHardwareTest.cpp
// Author:      Gabriel Ferri
// Created:     20/05/2008 11.23
// Description: HardwareTest - State Machine functions implementation
//
//---------------------------------------------------------------------------

#include "SMBase.h"
#include "wxHardwareTestPanel.h"
#include "Messages.h"

//----------------------------------------------------------------------------------
// SMHardwareTestInitialize
// Inizializza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMHardwareTestInitialize()
{
	mainVideo->ConnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	camera->SetMainMode( MAIN_CAMERA_CUR );
	camera->SetAuxMode( AUX_CAMPOSITION );
	camera->StartCapture();

	isAuxVideoClickEnable = true;
	controlPanel->SetState( PANEL_MOVE_PLATE | PANEL_MOVE_CAMERA |PANEL_MOVE_SQUEEGEES | PANEL_MOVE_TABLE,
							PANEL_OUTPUT_LOCK | PANEL_OUTPUT_FRONT_S | PANEL_OUTPUT_REAR_S | PANEL_OUTPUT_ALARM_G | PANEL_OUTPUT_ALARM_Y | PANEL_OUTPUT_ALARM_R | PANEL_OUTPUT_BUZZER | PANEL_OUTPUT_LED_UP | PANEL_OUTPUT_LED_DOWN |
							PANEL_OUTPUT_BOARD_LOCK | PANEL_OUTPUT_CONV_PIST | PANEL_OUTPUT_CAM_PIST | PANEL_OUTPUT_LOAD_PIST | PANEL_OUTPUT_CLEAN_LOCK |PANEL_OUTPUT_CLEAN_ACT | PANEL_OUTPUT_CLEAN_VAC | PANEL_OUTPUT_CLEAN_FEED );

	return SR_OK;
}

//----------------------------------------------------------------------------------
// SMHardwareTestFinalize
// Finalizza la macchina a stati
//----------------------------------------------------------------------------------
int SMBase::SMHardwareTestFinalize()
{
	mainVideo->DisconnectAuxVideoMouseEvent( wxEVT_LEFT_DOWN, wxStaticCastEvent( wxMouseEventFunction, &SMBase::SMAuxVideoLeftClick ), this );
	camera->StopCapture();

	isAuxVideoClickEnable = false;

	return SR_OK;
}
