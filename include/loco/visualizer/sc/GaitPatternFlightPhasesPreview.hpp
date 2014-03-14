/*
 * GaitPatternFlightPhasesPreview.hpp
 *
 *  Created on: Mar 14, 2014
 *      Author: gech
 */

#ifndef LOCO_GAITPATTERNFLIGHTPHASESPREVIEW_HPP_
#define LOCO_GAITPATTERNFLIGHTPHASESPREVIEW_HPP_

#include "loco/gait_pattern/GaitPatternFlightPhases.hpp"
#include <AppGUI/SubGLWindow.h>

namespace loco {

class GaitPatternFlightPhasesPreview : public SubGLWindow {
 public:
  GaitPatternFlightPhasesPreview(int posX, int posY, int sizeX, int sizeY);
  virtual ~GaitPatternFlightPhasesPreview();
  virtual void draw();

  void setGaitPattern(GaitPatternFlightPhases* gaitPattern);
 private:
  GaitPatternFlightPhases* gaitPattern_;

  double cursorPosition;
  int nrCycles;
  double maxXCoord;
  double maxYCoord;
  double labelsStart;
  double boxStart;
  double boxLength;

//  double getTrajMin(Trajectory1D traj);
//  double getTrajMax(Trajectory1D traj);
//  double getScaledY(double ymin, double ymax, double yval);
};

} /* namespace loco */

#endif /* LOCO_GAITPATTERNFLIGHTPHASESPREVIEW_HPP_ */
