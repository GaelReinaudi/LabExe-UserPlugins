/*------------------------------------------------------------------------------*
 * File Name: OriginClient.cpp													*
 * Creation:  LY 4/7/2004														*
 * Purpose: Implementation of utility functions to access Origin Automation		*
 *			server																*
 * Copyright (C) OriginLab Corp.												*
 * All Rights Reserved															*
 *------------------------------------------------------------------------------*/

#include "StdAfx.h"
#include ".\originclient.h"

#pragma comment(lib, "comsupp.lib")

COriginClient::COriginClient(int nOption)
{
	//Initialize COM
	CoInitialize(NULL);
	
	//Create instance of Origin
	HRESULT hr = 0;
	switch( nOption )
	{
		case USE_EXIST_FIRST:
			hr = m_pOApp.CreateInstance( __uuidof(ApplicationSI) );
			break;

		case ALWAYS_CREATE_NEW:
		default:
			hr = m_pOApp.CreateInstance( __uuidof(Application) );
			break;
	}
}

COriginClient::~COriginClient(void)
{
	//Release the created instance of Origin
	if( m_pOApp != NULL )
        m_pOApp.Release();		

	//Uninit COM
	CoUninitialize();
}


BOOL COriginClient::IsValid()
{
	return (m_pOApp != NULL);
}

BOOL COriginClient::GetWorksheet(LPCSTR lpszWks, _variant_t& val)
{
	BOOL bRet = FALSE;
	if( m_pOApp == NULL )
		return bRet;

	try
	{
		val = m_pOApp->GetWorksheet( _bstr_t(lpszWks) );
		bRet = TRUE;
	}
	catch(...)
	{
		TRACE("ERROR during Origin access");
		bRet = FALSE;
	}	

	return bRet;
}

BOOL COriginClient::SetWorksheet(LPCSTR lpszWks, _variant_t val, int nRowStart)
{
	BOOL bRet = FALSE;
	if( m_pOApp == NULL )
		return bRet;

	_variant_t valRowStart;
	valRowStart.vt = VT_I4;
	valRowStart.intVal = nRowStart;

	try
	{
		bRet = m_pOApp->PutWorksheet( _bstr_t(lpszWks), val, valRowStart );			
	}
	catch(...)
	{
		TRACE("ERROR during Origin access");
	}

	return bRet;
}

