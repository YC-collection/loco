/*
 * TorsoControlDynamicGaitFreePlane.hpp
 *
 *  Created on: Sep 11, 2014
 *      Author: Dario Bellicoso
 */

#ifndef LOCO_TORSOCONTROLDYNAMICGAITFREEPLANE_HPP_
#define LOCO_TORSOCONTROLDYNAMICGAITFREEPLANE_HPP_


#include "loco/torso_control/TorsoControlDynamicGait.hpp"
#include "loco/dynamic_systems_utils/FirstOrderFilter.hpp"

namespace loco {

  class TorsoControlDynamicGaitFreePlane: public TorsoControlDynamicGait {
   public:
    enum AdaptToTerrain {CompleteAdaption, SaturatedLinearAdaption};
    TorsoControlDynamicGaitFreePlane(LegGroup* legs, TorsoBase* torso, loco::TerrainModelBase* terrain);
    virtual ~TorsoControlDynamicGaitFreePlane();

    virtual bool initialize(double dt);
    virtual bool advance(double dt);

   protected:

    double desiredTorsoCoMHeightAboveGroundInWorldFrameOffset_;

    double maxDesiredPitchRadians_;
    double desiredPitchSlope_;
    double maxDesiredRollRadians_;
    double desiredRollSlope_;
    AdaptToTerrain adaptToTerrain_;
    FirstOrderFilter* firstOrderFilter_;

    template <typename T> int sgn(T val);

    void getDesiredBasePitchFromTerrainPitch(const double terrainPitch, double& desiredBasePitch);
    void getDesiredBaseRollFromTerrainRoll(const double terrainRoll, double& desiredBaseRoll);

    double heightOffsetFilterAdvance(double dt);

  };

} /* namespace loco */


#endif /* LOCO_TORSOCONTROLDYNAMICGAITFREEPLANE_HPP_ */