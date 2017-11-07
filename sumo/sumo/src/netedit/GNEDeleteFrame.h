/****************************************************************************/
/// @file    GNEDeleteFrame.h
/// @author  Pablo Alvarez Lopex
/// @date    Dec 2016
/// @version $Id$
///
// The Widget for remove network-elements
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright (C) 2001-2016 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This file is part of SUMO.
//   SUMO is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef GNEDeleteFrame_h
#define GNEDeleteFrame_h

// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include "GNEFrame.h"

// ===========================================================================
// class declarations
// ===========================================================================
class GNEAttributeCarrier;
class GNENetElement;

// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class GNEDeleteFrame
 * The Widget for deleting elements
 */
class GNEDeleteFrame : public GNEFrame{
    /// @brief FOX-declaration
    FXDECLARE(GNEDeleteFrame)

public:

    /**@brief Constructor
     * @brief parent FXHorizontalFrame in which this GNEFrame is placed
     * @brief viewNet viewNet that uses this GNEFrame
     */
    GNEDeleteFrame(FXHorizontalFrame *horizontalFrameParent, GNEViewNet* viewNet);

    /// @brief Destructor
    ~GNEDeleteFrame();

    /// @brief show child of attributeCarrier (element) in frame
    void showAttributeCarrierChilds(GNEAttributeCarrier *ac);

    /// @brief remove attribute carrier (element)
    void removeAttributeCarrier(GNEAttributeCarrier *ac);

    /**@brief mark attribute carrier (element)
     * @note if ac == NULL current marked attribute carrier will be dismarked
     */
    void markAttributeCarrier(GNEAttributeCarrier *ac);

    /// @brief returns marked atrribute carrier
    GNEAttributeCarrier *getMarkedAttributeCarrier() const;


    long onCmdSelectItem(FXObject*, FXSelector, void*);

    long onCmdShowMenu(FXObject*, FXSelector, void*);

protected:
    /// @brief FOX needs this
    GNEDeleteFrame() {}

    // @brief create pop-up menu
    void createPopUpMenu();

private:
    /// @brief groupbox for current element
    FXGroupBox *myGroupBoxCurrentElement;

    /// @brief label for current element
    FXLabel *myCurrentElementLabel;

    /// @brief label for marked element
    FXLabel *myMarkedElementLabel;

    /// @brief groupbox options
    FXGroupBox *myGroupBoxOptions;
    
    /// @brief groupbox for tree list
    FXGroupBox *myGroupBoxTreeList;

    /// @brief groupbox for information
    FXGroupBox *myGroupBoxInformation;

    /// @brief Label for information 1
    FXLabel *myInformationLabel;

    /// @brief tree list to show the childs of the element to erase
    FXTreeList *myTreelist;

    /// @brief pointer to marked attributeCarrier(element)
    GNEAttributeCarrier *myMarkedAc;

    /// @brief current attribute carrier selected in three
    GNEAttributeCarrier *mySelectedAc;
};


#endif

/****************************************************************************/

