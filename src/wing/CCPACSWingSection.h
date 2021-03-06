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
* @brief  Implementation of CPACS wing section handling routines.
*/

#ifndef CCPACSWINGSECTION_H
#define CCPACSWINGSECTION_H

#include "tigl_internal.h"
#include "tixi.h"
#include "CCPACSWingSectionElements.h"
#include "CTiglTransformation.h"
#include <string>

namespace tigl
{

class CCPACSWingSection
{

public:
    // Constructor
    TIGL_EXPORT CCPACSWingSection();

    // Virtual Destructor
    TIGL_EXPORT virtual ~CCPACSWingSection(void);

    // Read CPACS section elements
    TIGL_EXPORT void ReadCPACS(TixiDocumentHandle tixiHandle, const std::string& sectionXPath);

    // Get element count for this section
    TIGL_EXPORT int GetSectionElementCount(void) const;

    // Get the UID of this WingSection
    TIGL_EXPORT const std::string& GetUID(void) const;

    // Get element for a given index
    TIGL_EXPORT CCPACSWingSectionElement& GetSectionElement(int index) const;

    // Gets the section transformation
    TIGL_EXPORT CTiglTransformation GetSectionTransformation(void) const;

protected:
    // Cleanup routine
    void Cleanup(void);

    // Build transformation matrix for the section
    void BuildMatrix(void);

    // Update internal section data
    void Update(void);

private:
    // Copy constructor
    CCPACSWingSection(const CCPACSWingSection& );

    // Assignment operator
    void operator=(const CCPACSWingSection& );

private:
    std::string               name;           /**< Section name             */
    std::string               uID;              /**< Section uid                */
    CTiglTransformation       transformation; /**< Section transfromation   */
    CTiglPoint                translation;    /**< Section translation      */
    CTiglPoint                scaling;        /**< Section scaling          */
    CTiglPoint                rotation;       /**< Section rotation         */
    CCPACSWingSectionElements elements;       /**< Section elements         */

};

} // end namespace tigl

#endif // CCPACSWINGSECTION_H
