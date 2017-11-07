/****************************************************************************/
/// @file    NBSign.cpp
/// @author  Daniel Krajzewicz
/// @author  Michael Behrisch
/// @author  Jakob Erdmann
/// @date    Nov 2012
/// @version $Id$
///
// A class representing a street sign
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.dlr.de/
// Copyright (C) 2012-2016 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This file is part of SUMO.
//   SUMO is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/


// ===========================================================================
// included modules
// ===========================================================================
#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif

#include <cassert>
#include <utils/common/RGBColor.h>
#include <utils/common/ToString.h>
#include <utils/iodevices/OutputDevice.h>
#include "NBEdge.h"
#include "NBSign.h"

#ifdef CHECK_MEMORY_LEAKS
#include <foreign/nvwa/debug_new.h>
#endif // CHECK_MEMORY_LEAKS


// ===========================================================================
// static members
// ===========================================================================
StringBijection<NBSign::SignType>::Entry signTypeStringsInitializer[] = {
    {"speed limit",       NBSign::SIGN_TYPE_SPEED},
    {"yield",             NBSign::SIGN_TYPE_YIELD},
    {"stop",              NBSign::SIGN_TYPE_STOP},
    {"allway_stop",       NBSign::SIGN_TYPE_ALLWAY_STOP},
    {"on ramp",           NBSign::SIGN_TYPE_ON_RAMP},
    {"priority",          NBSign::SIGN_TYPE_PRIORITY},
    {"right before left", NBSign::SIGN_TYPE_RIGHT_BEFORE_LEFT},
    {"roundabout",        NBSign::SIGN_TYPE_ROUNDABOUT},
    {"rail crossing",     NBSign::SIGN_TYPE_RAIL_CROSSING},
    {"slope",             NBSign::SIGN_TYPE_SLOPE},
    {"city limits",       NBSign::SIGN_TYPE_CITY},
    {"info",              NBSign::SIGN_TYPE_INFO},
};

StringBijection<NBSign::SignType> NBSign::SignTypeStrings(
    signTypeStringsInitializer, NBSign::SIGN_TYPE_INFO);


// ===========================================================================
// member method definitions
// ===========================================================================

NBSign::NBSign(SignType type, SUMOReal offset, const std::string label) :
    myType(type),
    myOffset(offset),
    myLabel(label) {
}


NBSign::~NBSign() {}


void
NBSign::writeAsPOI(OutputDevice& into, const NBEdge* edge) const {
    PositionVector shp = edge->getLanes()[0].shape;
    try {
        shp.move2side(3);
    } catch (InvalidArgument&) {
        // we do not write anything, maybe we should
    }
    Position pos = shp.positionAtOffset(myOffset);
    into.openTag(SUMO_TAG_POI);
    into.writeAttr(SUMO_ATTR_ID, edge->getID() + "." + toString(myOffset));
    into.writeAttr(SUMO_ATTR_TYPE, SignTypeStrings.getString(myType));
    switch (myType) { /// XXX @todo add default colors
        case SIGN_TYPE_SPEED:
        case SIGN_TYPE_SLOPE:
        case SIGN_TYPE_CITY:
        case SIGN_TYPE_INFO:
            into.writeAttr(SUMO_ATTR_COLOR, RGBColor::GREY);
            break;
        case SIGN_TYPE_YIELD:
        case SIGN_TYPE_STOP:
        case SIGN_TYPE_ALLWAY_STOP:
        case SIGN_TYPE_ON_RAMP:
        case SIGN_TYPE_RAIL_CROSSING:
            into.writeAttr(SUMO_ATTR_COLOR, RGBColor::RED);
            break;
        case SIGN_TYPE_PRIORITY:
            into.writeAttr(SUMO_ATTR_COLOR, RGBColor::YELLOW);
            break;
        case SIGN_TYPE_RIGHT_BEFORE_LEFT:
            into.writeAttr(SUMO_ATTR_COLOR, RGBColor(255, 153, 0, 255));
            break;
        case SIGN_TYPE_ROUNDABOUT:
            into.writeAttr(SUMO_ATTR_COLOR, RGBColor::BLUE);
            break;
    }
    into.writeAttr(SUMO_ATTR_X, pos.x());
    into.writeAttr(SUMO_ATTR_Y, pos.y());
    into.writeAttr(SUMO_ATTR_ANGLE, 0); // XXX use road angle?
    // @todo add image resources and default images for all signs
    //into.writeAttr(SUMO_ATTR_IMGFILE, p->getImgFile());
    //into.writeAttr(SUMO_ATTR_WIDTH, p->getWidth());
    //into.writeAttr(SUMO_ATTR_HEIGHT, p->getHeight());
    into.closeTag();
}


/****************************************************************************/

