// (C) Copyright 2002-2012 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include <AcDbGeoCoordinateSystem.h>
#include <AcDbGeoTypes.h>
#include <AcDbGeoPositionMarker.h>
#include <AcDbGeoMap.h>
#include <AcDbGeomRef.h>
#include <dbmain.h>
#include <dbGeoData.h>
#include <tchar.h>

//-----------------------------------------------------------------------------
#define szRDS _RXST("ak")

void ModifyTTCoordinates();

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CModifyTTCoords_TESTApp : public AcRxArxApp {

public:
	CModifyTTCoords_TESTApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		ModifyTTCoordinates();

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}
	
	// The ACED_ARXCOMMAND_ENTRY_AUTO macro can be applied to any static member 
	// function of the CModifyTTCoords_TESTApp class.
	// The function should take no arguments and return nothing.
	//
	// NOTE: ACED_ARXCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid and
	// have arguments to define context and command mechanism.
	
	// ACED_ARXCOMMAND_ENTRY_AUTO(classname, group, globCmd, locCmd, cmdFlags, UIContext)
	// ACED_ARXCOMMAND_ENTRYBYID_AUTO(classname, group, globCmd, locCmdId, cmdFlags, UIContext)
	// only differs that it creates a localized name using a string in the resource file
	//   locCmdId - resource ID for localized command

	// Modal Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CModifyTTCoords_TESTApp, akMyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL)
	static void akMyGroupMyCommand () {
		// Put your command code here

	}

	// Modal Command with pickfirst selection
	// ACED_ARXCOMMAND_ENTRY_AUTO(CModifyTTCoords_TESTApp, akMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET)
	static void akMyGroupMyPickFirst () {
		ads_name result ;
		int iRet =acedSSGet (ACRX_T("_I"), NULL, NULL, NULL, result) ;
		if ( iRet == RTNORM )
		{
			// There are selected entities
			// Put your command using pickfirst set code here
		}
		else
		{
			// There are no selected entities
			// Put your command code here
		}
	}

	// Application Session Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CModifyTTCoords_TESTApp, akMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION)
	static void akMyGroupMySessionCmd () {
		// Put your command code here
	}

	// The ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO macros can be applied to any static member 
	// function of the CModifyTTCoords_TESTApp class.
	// The function may or may not take arguments and have to return RTNORM, RTERROR, RTCAN, RTFAIL, RTREJ to AutoCAD, but use
	// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal to return
	// a value to the Lisp interpreter.
	//
	// NOTE: ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid.
	
	//- ACED_ADSFUNCTION_ENTRY_AUTO(classname, name, regFunc) - this example
	//- ACED_ADSSYMBOL_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file
	//- ACED_ADSCOMMAND_ENTRY_AUTO(classname, name, regFunc) - a Lisp command (prefix C:)
	//- ACED_ADSCOMMAND_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file

	// Lisp Function is similar to ARX Command but it creates a lisp 
	// callable function. Many return types are supported not just string
	// or integer.
	// ACED_ADSFUNCTION_ENTRY_AUTO(CModifyTTCoords_TESTApp, MyLispFunction, false)
	static int ads_MyLispFunction () {
		//struct resbuf *args =acedGetArgs () ;
		
		// Put your command code here

		//acutRelRb (args) ;
		
		// Return a value to the AutoCAD Lisp Interpreter
		// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal

		return (RTNORM) ;
	}
	
} ;

void ModifyTTCoordinates()
{
	const AcString csId(L"UTM84-43N");

	Acad::ErrorStatus es;

	AcDbDatabase *pDb = acdbHostApplicationServices()->workingDatabase();

	double pi = 3.14159265359;

	AcDbBlockTable *pBlockTable;
	acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pBlockTable, AcDb::kForRead);
	AcDbBlockTableRecord *pBlockTableRecord;
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForRead);
	pBlockTable->close();

	AcDbBlockTableRecordIterator *pBlockIterator;
	pBlockTableRecord->newIterator(pBlockIterator);
	for (; !pBlockIterator->done(); pBlockIterator->step())
	{
		AcDbEntity *pEnt;
		pBlockIterator->getEntity(pEnt, AcDb::kForWrite);

		AcGeMatrix3d m;

		m.setToRotation((7.433333333 * (pi / 180)), AcGeVector3d::kZAxis, AcGePoint3d::kOrigin);

		pEnt->transformBy(m);

		pEnt->close();
	}

	delete pBlockIterator;
	pBlockTableRecord->close();

	acdbHostApplicationServices()->workingDatabase()->getSymbolTable(pBlockTable, AcDb::kForRead);
	pBlockTable->getAt(ACDB_MODEL_SPACE, pBlockTableRecord, AcDb::kForRead);
	pBlockTable->close();

	pBlockTableRecord->newIterator(pBlockIterator);
	for (; !pBlockIterator->done(); pBlockIterator->step())
	{
		AcDbEntity *pEnt;
		pBlockIterator->getEntity(pEnt, AcDb::kForWrite);

		AcGeMatrix3d m;

		AcGeVector3d v(62083862.12500000039999, 47610445.749999, 6000.0);

		m.setTranslation(v);

		pEnt->transformBy(m);

		pEnt->close();
	}

	delete pBlockIterator;
	pBlockTableRecord->close();

	AcDbGeoCoordinateSystem* pGeoCS;

	AcDbGeoCoordinateSystem::create(csId, pGeoCS);

	if (NULL == pGeoCS)
		return;

	AcString xmlStr;

	es = pGeoCS->getXmlRepresentation(xmlStr);

	acutPrintf(_T("\ncrsName: %s"), xmlStr.kACharPtr());

	if (xmlStr.isEmpty())
		return;

	AcDbObjectId geoId;

	AcDbObjectPointer<AcDbGeoData> pGeoData;

	acdbGetGeoDataObjId(pDb, geoId);

	if (geoId.isNull())
	{
		pGeoData.create();

		pGeoData->setBlockTableRecordId(acdbSymUtil()->blockModelSpaceId(pDb));

		pGeoData->postToDb(geoId);
	}

	else
	{
		pGeoData.open(geoId, AcDb::kForWrite);
	}

	if (NULL == pGeoData.object())
		return;

	es = pGeoData->setCoordinateSystem(xmlStr);

	es = pGeoData->setCoordinateType(AcDbGeoData::kCoordTypLocal);

	es = pGeoData->setHorizontalUnits(AcDb::kUnitsInches);

	es = pGeoData->setVerticalUnits(AcDb::kUnitsInches);

	es = pGeoData->setDesignPoint(AcGePoint3d::kOrigin);

	es = pGeoData->setUpDirection(AcGeVector3d::kZAxis);

	//AcGePoint3d refPtInUTM84, refPtInLatLong(38.2172641, -84.8720050, 0.0);
	AcGePoint3d refPtInUTM84, refPtInLatLong(38.2160096, -84.8714267, 0.0);

	pGeoData->transformFromLonLatAlt(refPtInLatLong, refPtInUTM84);

	pGeoData->setReferencePoint(refPtInUTM84);

	pGeoData->setNorthDirectionVector(AcGeVector2d::kYAxis);

	delete pGeoCS;

	pGeoData.close();
}

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CModifyTTCoords_TESTApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CModifyTTCoords_TESTApp, akMyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CModifyTTCoords_TESTApp, akMyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CModifyTTCoords_TESTApp, akMyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION, NULL)
ACED_ADSSYMBOL_ENTRY_AUTO(CModifyTTCoords_TESTApp, MyLispFunction, false)
