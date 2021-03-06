/* 
* Copyright (C) 2007-2013 German Aerospace Center (DLR/SC)
*
* Created: 2010-08-13 Markus Litz <Markus.Litz@dlr.de>
* Changed: $Id$ 
*
* Version: $Revision$
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
/**
* @file
* @brief  Implementation of CPACS fuselage handling routines.
*/

#ifndef CCPACSFUSELAGE_H
#define CCPACSFUSELAGE_H

#include <string>

#include "tigl_config.h"
#include "tigl_internal.h"
#include "tixi.h"
#include "CTiglTransformation.h"
#include "CCPACSFuselageSections.h"
#include "CCPACSFuselageSegments.h"
#include "CCPACSFuselagePositionings.h"
#include "CTiglAbstractPhysicalComponent.h"
#include "CCPACSGuideCurve.h"

#include "TopoDS_Shape.hxx"
#include "TopoDS_Compound.hxx"
#include "BRep_Builder.hxx"


namespace tigl
{

class CCPACSConfiguration;
class CTiglAbstractSegment;

class CCPACSFuselage : public CTiglAbstractPhysicalComponent
{

public:
    // Constructor
    TIGL_EXPORT CCPACSFuselage(CCPACSConfiguration* config);

    // Virtual Destructor
    TIGL_EXPORT virtual ~CCPACSFuselage(void);

    // Invalidates internal state
    TIGL_EXPORT void Invalidate(void);

    // Read CPACS fuselage elements
    TIGL_EXPORT void ReadCPACS(TixiDocumentHandle tixiHandle, const std::string& fuselageXPath);

    // Returns the name of the fuselage
    TIGL_EXPORT std::string GetName(void) const;

    // Returns the parent configuration
    TIGL_EXPORT CCPACSConfiguration & GetConfiguration(void) const;

    // Get section count
    TIGL_EXPORT int GetSectionCount(void) const;

    // Returns the section for a given index
    TIGL_EXPORT CCPACSFuselageSection& GetSection(int index) const;

    // Get segment count
    TIGL_EXPORT int GetSegmentCount(void) const;

    // Returns the segment for a given index
    TIGL_EXPORT CTiglAbstractSegment & GetSegment(const int index);

    // Returns the segment for a given UID
    TIGL_EXPORT CTiglAbstractSegment & GetSegment(std::string uid);

    // Gets the fuselage transformation
    TIGL_EXPORT CTiglTransformation GetFuselageTransformation(void);

    // Get the positioning transformation for a given section index
    TIGL_EXPORT CTiglTransformation GetPositioningTransformation(const std::string& sectionUID);

    // Gets a point on the given fuselage segment in dependence of a parameters eta and zeta with
    // 0.0 <= eta <= 1.0 and 0.0 <= zeta <= 1.0. For eta = 0.0 the point lies on the start
    // profile of the segment, for eta = 1.0 on the end profile of the segment. For zeta = 0.0
    // the point is the start point of the profile wire, for zeta = 1.0 the last profile wire point.
    TIGL_EXPORT gp_Pnt GetPoint(int segmentIndex, double eta, double zeta);

    // Gets the volume of this fuselage
    TIGL_EXPORT double GetVolume();

    // get the Transformation object
    TIGL_EXPORT CTiglTransformation GetTransformation(void);

    // sets a Transformation object
    TIGL_EXPORT void Translate(CTiglPoint trans);

    // Gets the surfade area of this wing
    TIGL_EXPORT double GetSurfaceArea();

    // Returns the circumference of the segment "segmentIndex" at a given eta
    TIGL_EXPORT double GetCircumference(int segmentIndex, double eta);

    // Returns the Component Type TIGL_COMPONENT_FUSELAGE
    TIGL_EXPORT TiglGeometricComponentType GetComponentType(void) {return TIGL_COMPONENT_FUSELAGE | TIGL_COMPONENT_PHYSICAL;}

    // Returns the point where the distance between the selected fuselage and the ground is at minimum.
    // The Fuselage could be turned with a given angle at at given axis, specified by a point and a direction.
    TIGL_EXPORT gp_Pnt GetMinumumDistanceToGround(gp_Ax1 RAxis, double angle);

    TIGL_EXPORT void SetSymmetryAxis(const std::string& axis);

    // Get the guide curve with a given UID
    TIGL_EXPORT CCPACSGuideCurve& GetGuideCurve(std::string uid);

protected:
    // Cleanup routine
    void Cleanup(void);

    // Build transformation matrix for the fuselage
    void BuildMatrix(void);

    // Update internal fuselage data
    void Update(void);
        
    // Adds all segments of this fuselage to one shape
    PNamedShape BuildLoft(void);

private:
    // get short name for loft
    std::string GetShortShapeName(void);

    // Copy constructor
    CCPACSFuselage(const CCPACSFuselage & );

    // Assignment operator
    void operator=(const CCPACSFuselage & );

private:
    std::string                name;                 /**< Fuselage name           */
    CCPACSFuselageSections     sections;             /**< Fuselage sections       */
    CCPACSFuselageSegments     segments;             /**< Fuselage segments       */
    CCPACSFuselagePositionings positionings;         /**< Fuselage positionings   */
    CCPACSConfiguration*       configuration;        /**< Parent configuration    */
    FusedElementsContainerType fusedElements;        /**< Stores already fused segments */

    TopoDS_Compound            aCompound;
    BRep_Builder               aBuilder;
    double                     myVolume;             /**< Volume of this fuselage              */
};

} // end namespace tigl

#endif // CCPACSFUSELAGE_H
