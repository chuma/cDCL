// ==============================
// Fichier:			TDCLCommLayer.cp
// Projet:			Desktop Connection Library
//
// Cr�� le:			23/08/2000
// Tabulation:		4 espaces
//
// ***** BEGIN LICENSE BLOCK *****
// Version: MPL 1.1
//
// The contents of this file are subject to the Mozilla Public License Version
// 1.1 (the "License"); you may not use this file except in compliance with
// the License. You may obtain a copy of the License at
// http://www.mozilla.org/MPL/
//
// Software distributed under the License is distributed on an "AS IS" basis,
// WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
// for the specific language governing rights and limitations under the
// License.
//
// The Original Code is TDCLCommLayer.cp.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2000-2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLCommLayer.cp,v 1.3 2004/11/24 14:08:53 paul Exp $
// ===========

#include <DCL/Communication_Layers/TDCLCommLayer.h>

// ANSI C
#include <stdlib.h>

// DCL
#include <DCL/Exceptions/Errors/TDCLBadStateError.h>
#include <DCL/Server/TDCLServer.h>

// ------------------------------------------------------------------------- //
//  *�TDCLCommLayer( Boolean, KUInt32 )
// ------------------------------------------------------------------------- //
TDCLCommLayer::TDCLCommLayer(
					Boolean	inFlushAvailable /* = false */,
					KUInt32	inMaxPipeCount /* = kDefaultPipeCount */
				)
	:
		mFlushAvailable( inFlushAvailable ),
		mMaxPipeCount( inMaxPipeCount ),
		mServer( nil )
{
	// D�fense de stationner.
}

// ------------------------------------------------------------------------- //
//  *�Idle( void )
// ------------------------------------------------------------------------- //
void
TDCLCommLayer::Idle( void )
{
	// Sortie de v�hicules.
}

// ------------------------------------------------------------------------- //
//  *�StartListening( TDCLServer* )
// ------------------------------------------------------------------------- //
void
TDCLCommLayer::StartListening( TDCLServer* inServer )
{
	// Exception si on est d�j� en train d'�couter.
	if (mServer)
	{
		throw DCLBadStateError;
	}
	
	// On note le serveur.
	mServer = inServer;
	
	// Ensuite, on appelle la m�thode qui fait vraiment le travail.
	DoStartListening();
	
	// Ay�, on �coute.
	inServer->WaitingConnection( this );
}

// ------------------------------------------------------------------------- //
//  *�StopListening( void )
// ------------------------------------------------------------------------- //
void
TDCLCommLayer::StopListening( void )
{
	// On ne fait rien si on n'est pas en train d'�couter.
	if (mServer)
	{
		try {
			// On appelle la m�thode qui fait vraiment le travail.
			DoStopListening();
		} catch ( ... ) {
			// Silence!
		}

		// On n'a plus besoin de r�f�rence sur le serveur.
		mServer = nil;	
	}
}

// ======================================================================== //
// > X..., c'est un millefeuille avec une couche de cr�me patissi�re, une   //
// > de sauce tomate et une de cr�me d'anchois... Mais c'est vrai que       //
// > c'est un syst�me ouvert: tu peux y rajouter des p�pites de chocolat... //
// -+- Ol in Guide du linuxien pervers - "Remettez m'en une couche !" -+-   //
// ======================================================================== //
