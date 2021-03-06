/*****************************************************************************************
* Software License Agreement (BSD License)
*
* Copyright (c) 2014, Christian Gehring, Péter Fankhauser, C. Dario Bellicoso, Stelian Coros
* All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of Autonomous Systems Lab nor ETH Zurich
*     nor the names of its contributors may be used to endorse or
*     promote products derived from this software without specific
*     prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*/
/*
 * LegBase.hpp
 *
 *  Created on: Feb 25, 2014
 *      Author: gech
 */

#ifndef LOCO_LEGBASE_HPP_
#define LOCO_LEGBASE_HPP_

//#include "loco/common/LegLink.hpp"

#include "loco/common/LegStateLiftOff.hpp"
#include "loco/common/LegStateTouchDown.hpp"

#include "loco/common/TypeDefs.hpp"

#include "loco/common/LegPropertiesBase.hpp"

//#include "loco/common/LegLinkGroup.hpp"

#include "loco/state_switcher/StateSwitcher.hpp"

#include <Eigen/Core>

#include <string>
#include <iostream>



namespace loco {

class LegLink;
class LegLinkGroup;

//! Base class for a leg
/*! This should be used only as a data container
 *
 */
class LegBase {
 public:
  static constexpr int nJoints_ = 3;
  static constexpr int nDofContactPoint_ = 3;
  typedef Eigen::Array<double, nJoints_, 1> JointPositions;
  typedef Eigen::Array<double, nJoints_, 1> JointVelocities;
  typedef Eigen::Array<unsigned char, nJoints_, 1> JointControlModes;
  typedef Eigen::Array<double, nJoints_, 1> JointTorques;
  typedef Eigen::Matrix<double, nDofContactPoint_, nJoints_> TranslationJacobian;

 public:
  LegBase();
  LegBase(const std::string& name, LegLinkGroup* links);
  virtual ~LegBase();

  virtual const std::string& getName() const ;

  /*!@returns list of links.
   */
  LegLinkGroup* getLinks();

  /*! @returns the stance phase. The phase is -1 if the leg is in swing mode,
   * otherwise it is between 0 (start) and 1 (end).
   */
  virtual double getStancePhase() const;

  /*! @returns the swing phase. The phase is -1 if the leg is in stance mode,
   * otherwise it is between 0 (start) and 1 (end).
   */
  virtual double getSwingPhase() const;

  /*! @returns the duration of the stance phase in seconds.
   * The leg should be grounded during the stance phase.
   */
  virtual double getStanceDuration() const;

  /*! @returns the duration of the swing phase in seconds.
   * The leg should be in the air during the swing phase.
   */
  virtual double getSwingDuration() const;

  /*! @returns true if the leg is in contact with the ground according to sensor measurements.
   */
  virtual bool isGrounded() const;

  /*! @returns true if the leg was in contact with the ground according to sensor measurements
   * during the previous control update.
   */
  virtual bool wasGrounded() const;

  /*! @returns true if the leg should be in contact with the ground
   *  according to the plan (timing).
   */
  virtual bool shouldBeGrounded() const;

  /*! @returns true if the leg is grounded according to sensor measurements and should be grounded
   *  according to the plan (timing).
   *  @see isGrounded, shouldBeGrounded
   */
  virtual bool isAndShouldBeGrounded() const;

  /*! @returns true if the leg is slipping, i.e it is grounded according to sensor measurements,
   * but the foot still moves.
   */
  virtual bool isSlipping() const;

  /*! @returns true if this leg is supposed to be used as a support leg.
   * This means that this leg is grounded and can be safely used to control the pose of the torso.
   */
  virtual bool isSupportLeg() const;

  /*! @returns true if the leg is supposed to be grounded, but lost contact according to sensor measurements.
   */
  virtual bool isLosingContact() const;

  /*! @returns the load factor between 0 and 1, which indicates how much the leg can/should be loaded.
   *  If it is one, the leg can/should be fully loaded.
   *  If it is zero, the leg cannot/shouldn't be loaded at all.
   */
  virtual double getDesiredLoadFactor() const;

  virtual void setIsLosingContact(bool isLosingContact);

  virtual void setStancePhase(double phase);
  virtual void setSwingPhase(double phase);

  virtual void setStanceDuration(double duration);
  virtual void setSwingDuration(double duration);

  virtual void setIsGrounded(bool isGrounded);
  virtual void setWasGrounded(bool wasGrounded);
  virtual void setShouldBeGrounded(bool shouldBeGrounded);
  virtual void setIsSlipping(bool isSlipping);

  virtual void setIsSupportLeg(bool isSupportLeg);

  virtual bool didTouchDownAtLeastOnceDuringStance() const;
  virtual void setDidTouchDownAtLeastOnceDuringStance(bool didTouchDownAtLeastOnceDuringStance);


  /*!
   * Change how much a leg should be loaded.
   * @param loadFactor sets the factor how much the leg should be loaded
   *        (related to the unconstrained case without user specified load
   *        factors), value in the interval [0, 1] where 0: unloaded
   *        and 1: completely loaded.
   */
  virtual void setDesiredLoadFactor(double loadFactor);

  LegStateTouchDown* getStateTouchDown();
  const LegStateTouchDown& getStateTouchDown() const;

  LegStateLiftOff* getStateLiftOff();
  const LegStateLiftOff& getStateLiftOff() const;

  virtual const Position& getPositionWorldToFootInWorldFrame() const = 0;
  virtual const Position& getPositionWorldToHipInWorldFrame() const  = 0;

  virtual const Position& getPositionWorldToFootInBaseFrame() const = 0;
  virtual const Position& getPositionWorldToHipInBaseFrame() const  = 0;

  virtual const Position& getPositionBaseToFootInBaseFrame() const = 0;
  virtual const Position& getPositionBaseToHipInBaseFrame() const = 0;

  virtual const LinearVelocity& getLinearVelocityFootInWorldFrame() const  = 0;
  virtual const LinearVelocity& getLinearVelocityHipInWorldFrame() const  = 0;
  virtual JointPositions getJointPositionsFromPositionBaseToFootInBaseFrame(const Position& positionBaseToFootInBaseFrame) = 0;

  virtual const TranslationJacobian& getTranslationJacobianFromBaseToFootInBaseFrame() const = 0;


  virtual const Force& getFootContactForceInWorldFrame() const = 0;
  virtual const Vector& getFootContactNormalInWorldFrame() const = 0;

  friend std::ostream& operator << (std::ostream& out, const LegBase& leg);

  virtual void setDesiredJointControlModes(const JointControlModes& jointControlMode);
  virtual void setDesiredJointPositions(const JointPositions& jointPositions);
  virtual void setDesiredJointTorques(const JointTorques& jointTorques);
  virtual void setMeasuredJointPositions(const JointPositions& jointPositions);
  virtual void setMeasuredJointVelocities(const JointVelocities& jointVelocities);
  virtual void setMeasuredJointTorques(const JointTorques& jointTorques);

  virtual const JointControlModes& getDesiredJointControlModes() const;
  virtual const JointPositions& getDesiredJointPositions() const;
  virtual const JointPositions& getMeasuredJointPositions() const;
  virtual const JointVelocities& getMeasuredJointVelocities() const;
  virtual const JointTorques& getDesiredJointTorques() const;
  virtual const JointTorques& getMeasuredJointTorques() const;

  virtual bool initialize(double dt) = 0;
  virtual bool advance(double dt) = 0;

  virtual LegPropertiesBase& getProperties() = 0;
  virtual const LegPropertiesBase& getProperties() const = 0;
  virtual int getId() const = 0;

  const Position& getDesiredWorldToFootPositionInWorldFrame() const;
  void setDesireWorldToFootPositionInWorldFrame(const Position& position);

	void setPreviousStancePhase(double previousStancePhase);
	double getPreviousStancePhase() const;

	void setPreviousSwingPhase(double previousSwingPhase);
	double getPreviousSwingPhase() const;

	virtual StateSwitcher* getStateSwitcher() const;


	void setIsInStandConfiguration(bool isInStandConfiguration);
	bool isInStandConfiguration() const;

protected:
	/*! This is the name of the leg.
	 */
  std::string name_;

  /*! This is a list of links.
   */
  LegLinkGroup* links_;

  /*! The stance phase is -1 if the leg is in swing mode,
   * otherwise it is between 0 (start) and 1 (end).
   */
  double stancePhase_;

  /*! The stance phase during the previous control update.
   */
  double previousStancePhase_;

  /*! The swing phase is -1 if the leg is in stance mode,
   * otherwise it is between 0 (start) and 1 (end).
   */
  double swingPhase_;

  /*! The swing phase during the previous control update.
   */
  double previousSwingPhase_;

  /*! The duration of the stance phase in seconds.
   * The leg should be grounded during the stance phase.
   */
  double stanceDuration_;

  /*! The duration of the swing phase in seconds.
   * The leg should be in the air during the swing phase.
   */
  double swingDuration_;

  /*! Indicates if the leg is in contact with the ground according to sensor measurements.
   */
  bool isGrounded_;

  /*! Indicates if the leg was in contact with the ground according to sensor measurements
   * during the previous control update.
   */
  bool wasGrounded_;

  /*! Indicates if the leg should be in contact with the ground according to the plan (timing).
   */
  bool shouldBeGrounded_;

  /*! Indicates if the leg is slipping, i.e. it is in contact with the ground according to sensor measurements,
   * but its foot is moving.
   */
  bool isSlipping_;

  /*! Indicates if this leg is supposed to be used as a support leg.
   * This means that this leg is grounded and can be safely used
   * to control the pose of the torso.
   */
  bool isSupportLeg_;

  /*! Indicates if the leg is supposed to be grounded, but lost contact according to sensor measurements.
   */
  bool isLosingContact_;

  /*! Indicates if the leg touched-down at least once during the current stance phase.
   */
  bool didTouchDownAtLeastOnceDuringStance_;

  /*! This leg should be loaded only by this factor, which is between 0 and 1.
   *  If it is 1, the leg can/should be fully loaded.
   *  If it is 0, the leg cannot/shouldn't be loaded at all.
   */
  double loadFactor_;

  /*! This is the state of the leg at touch-down event.
   */
  LegStateTouchDown stateTouchDown_;

  /*! This is the state of the leg at lift-off event.
   */
  LegStateLiftOff stateLiftOff_;

  /*! These are the control modes of all joints.
   */
  JointControlModes desiredJointControlModes_;

  /*! These are the desired joint angles.
   */
  JointPositions desiredJointPositions_;

  /*! These are the measured joint angles.
    */
  JointPositions measuredJointPositions_;

  /*! These are the measured joint velocities.
    */
  JointVelocities measuredJointVelocities_;

  /*! These are the desired joint torques.
    */
  JointTorques desiredJointTorques_;

  /*! These are the measured joint torques.
    */
  JointTorques measuredJointTorques_;

  /*! This is the desired foot position expressed in world frame.
   */
  Position positionWorldToDesiredFootInWorldFrame_;

  /*! Reference to the state switcher.
   */
  StateSwitcher* stateSwitcher_;

  bool isInStandConfiguration_;

};

} /* namespace loco */

#endif /* LOCO_LEGBASE_HPP_ */
