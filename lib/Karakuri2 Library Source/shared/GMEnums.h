//
//  GMEnums.h
//  Game Framework
//
//  Created by numata on Jan 09, 2011.
//  Copyright 2011 Sazameki and Satoshi Numata, Ph.D. All rights reserved.
//

#ifndef __GM_CONTAINMENT_TYPE_H__
#define __GM_CONTAINMENT_TYPE_H__


/*!
    @enum       GMContainmentType
    @group      Math
    @constant   GMContainmentTypeContains
    @constant   GMContainmentTypeDisjoint
    @constant   GMContainmentTypeIntersects
 */
enum GMContainmentType {
    GMContainmentTypeContains,
    GMContainmentTypeDisjoint,
    GMContainmentTypeIntersects,
};

/*!
    @enum       GMPlaneIntersectionType
    @group      Math
    @constant   GMPlaneIntersectionTypeFront
    @constant   GMPlaneIntersectionTypeBack
    @constant   GMPlaneIntersectionTypeIntersecting
 */
enum GMPlaneIntersectionType {
    GMPlaneIntersectionTypeFront,
    GMPlaneIntersectionTypeBack,
    GMPlaneIntersectionTypeIntersecting,
};

#endif  //#ifndef __GM_CONTAINMENT_TYPE_H__

