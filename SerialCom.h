//---------------------------------------------------------------------------
//
// Name:        SerialCom.h
// Author:      Gabriel Ferri
// Created:     07/05/2008
// Description: SerialCom functions declaration
//
//---------------------------------------------------------------------------
#ifndef __SERIALCOM_H
#define __SERIALCOM_H

#include "wxCommInterface.h"

int TWSBus1_Send( wxCommInterface* commInt, unsigned char NSlave, unsigned char Cmd, unsigned char* TxBuf, unsigned short TxLen, unsigned char* RxBuf,  unsigned short* RxLen );
int TWSBus1_Send( wxCommInterface* commInt, unsigned char NSlave, unsigned char Cmd, unsigned char* TxBuf, unsigned short TxLen );
int TWSBus1_Send_Command( wxCommInterface* commInt, unsigned char NSlave, unsigned char Cmd, unsigned char* RxData, bool activated = true );
int TWSBus1_Send_Command( wxCommInterface* commInt, unsigned char NSlave, unsigned char Cmd, unsigned short TxData, unsigned char* RxData, bool activated = true );


#endif	// __SERIALCOMM_H
