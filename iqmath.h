//---------------------------------------------------------------------------
//
// Name:        iqmath.h
// Author:      Gabriel Ferri
// Created:     23/06/2011
// Description: Definitions for the IQ math
//
//---------------------------------------------------------------------------
#ifndef __IQMATH_H
#define __IQMATH_H


	//---------------//
	//    IQ Math    //
	//---------------//

typedef   long    _iq;
typedef   long    _iq30;
typedef   long    _iq29;
typedef   long    _iq28;
typedef   long    _iq27;
typedef   long    _iq26;
typedef   long    _iq25;
typedef   long    _iq24;
typedef   long    _iq23;
typedef   long    _iq22;
typedef   long    _iq21;
typedef   long    _iq20;
typedef   long    _iq19;
typedef   long    _iq18;
typedef   long    _iq17;
typedef   long    _iq16;
typedef   long    _iq15;
typedef   long    _iq14;
typedef   long    _iq13;
typedef   long    _iq12;
typedef   long    _iq11;
typedef   long    _iq10;
typedef   long    _iq9;
typedef   long    _iq8;
typedef   long    _iq7;
typedef   long    _iq6;
typedef   long    _iq5;
typedef   long    _iq4;
typedef   long    _iq3;
typedef   long    _iq2;
typedef   long    _iq1;
//---------------------------------------------------------------------------
#define   _IQ30(A)      (long) ((A) * 1073741824.0L)
#define   _IQ29(A)      (long) ((A) * 536870912.0L)
#define   _IQ28(A)      (long) ((A) * 268435456.0L)
#define   _IQ27(A)      (long) ((A) * 134217728.0L)
#define   _IQ26(A)      (long) ((A) * 67108864.0L)
#define   _IQ25(A)      (long) ((A) * 33554432.0L)
#define   _IQ24(A)      (long) ((A) * 16777216.0L)
#define   _IQ23(A)      (long) ((A) * 8388608.0L)
#define   _IQ22(A)      (long) ((A) * 4194304.0L)
#define   _IQ21(A)      (long) ((A) * 2097152.0L)
#define   _IQ20(A)      (long) ((A) * 1048576.0L)
#define   _IQ19(A)      (long) ((A) * 524288.0L)
#define   _IQ18(A)      (long) ((A) * 262144.0L)
#define   _IQ17(A)      (long) ((A) * 131072.0L)
#define   _IQ16(A)      (long) ((A) * 65536.0L)
#define   _IQ15(A)      (long) ((A) * 32768.0L)
#define   _IQ14(A)      (long) ((A) * 16384.0L)
#define   _IQ13(A)      (long) ((A) * 8192.0L)
#define   _IQ12(A)      (long) ((A) * 4096.0L)
#define   _IQ11(A)      (long) ((A) * 2048.0L)
#define   _IQ10(A)      (long) ((A) * 1024.0L)
#define   _IQ9(A)       (long) ((A) * 512.0L)
#define   _IQ8(A)       (long) ((A) * 256.0L)
#define   _IQ7(A)       (long) ((A) * 128.0L)
#define   _IQ6(A)       (long) ((A) * 64.0L)
#define   _IQ5(A)       (long) ((A) * 32.0L)
#define   _IQ4(A)       (long) ((A) * 16.0L)
#define   _IQ3(A)       (long) ((A) * 8.0L)
#define   _IQ2(A)       (long) ((A) * 4.0L)
#define   _IQ1(A)       (long) ((A) * 2.0L)

#define   _IQ15ToF(A)   (double) ((A) / 32768.0L)
#define   _IQ24ToF(A)   (double) ((A) / 16777216.0L)

#endif
