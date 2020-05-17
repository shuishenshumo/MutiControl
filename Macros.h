//=============================================================================
// $URL: http://svn/svn/VAPSXT178/branches/XT/4.0/VAPSXT_DIR/src/Examples/MultiDocOGL/Macros.h $
//
// Version: $Revision: 31572 $
//
// Last Revision $Author: sparadis $
//
// Last Revision $Date: 2013-03-20 15:48:06 -0400 (Wed, 20 Mar 2013) $
//
// IMPORTANT NOTICE: This software program ("Software") including the source
// code is a confidential and/or proprietary product of Presagis Canada Inc.
// and/or its subsidiaries and affiliated companies. ("Presagis") and is
// protected by copyright laws. The use of the Software is subject to the terms
// of the Presagis Software License Agreement.
//
// (c) Copyright 2003 - 2008, All Rights Reserved.
//
// AVIS IMPORTANT: Ce logiciel incluant le code source est de l'information
// confidentielle et/ou propriete de Presagis Canada Inc. et/ou ses filiales et
// compagnies affiliees ("Presagis") et est protege par les lois sur le droit
// d'auteur. L'utilisation de ce logiciel est sujet aux termes d'une licence de
// Presagis.
//
// (c) Copyright 2003 - 2008, Tous Droits Reserves.
//
//=============================================================================

#ifndef _MACROS_H_
#define _MACROS_H_

#define _USE_MATH_DEFINES

//=============================================================================
//                         I N C L U D E  F I L E S
//=============================================================================

#include <math.h>

#define RAD_TO_DEG(AngleRad) ((AngleRad) * (180.0/M_PI))
#define DEG_TO_RAD(AngleDeg) ((AngleDeg) * (M_PI/180.0))

#define IN_INTERVAL(Valeur, BorneMin, BorneMax) (((Valeur) >= (BorneMin)) && ((Valeur) <= (BorneMax)))

#endif

// End of File
