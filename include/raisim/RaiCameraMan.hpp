//
// Created by jhwangbo on 22.01.19.
//

#ifndef RAISIMOGREVISUALIZER_RAICAMERAMAN_HPP
#define RAISIMOGREVISUALIZER_RAICAMERAMAN_HPP

#include "OgreBitesPrerequisites.h"
#include "OgreCamera.h"
#include "OgreSceneNode.h"
#include "OgreFrameListener.h"

#include "OgreInput.h"

/** \addtogroup Optional
*  @{
*/
/** \addtogroup Bites
*  @{
*/
namespace raisim
{

using namespace OgreBites;

enum CameraStyle   /// enumerator values for different styles of camera movement
{
  CS_FREELOOK,
  CS_ORBIT,
  CS_MANUAL
};

/**
Utility class for controlling the camera in samples.
*/
class _OgreBitesExport CameraMan : public InputListener
{
 public:
  CameraMan(Ogre::SceneNode* cam);

  /**
  Swaps the camera on our camera man for another camera.
  */
  void setCamera(Ogre::SceneNode* cam);

  Ogre::SceneNode* getCamera()
  {
    return mCamera;
  }

  /**
  Sets the target we will revolve around. Only applies for orbit style.
  */
  virtual void setTarget(Ogre::SceneNode* target);

  Ogre::SceneNode* getTarget()
  {
    return mTarget;
  }

  /**
  Sets the spatial offset from the target. Only applies for orbit style.
  */
  void setYawPitchDist(Ogre::Radian yaw, Ogre::Radian pitch, Ogre::Real dist, bool trackObjectsYaw = false);

  /**
  Sets the camera's top speed. Only applies for free-look style.
  */
  void setTopSpeed(Ogre::Real topSpeed)
  {
    mTopSpeed = topSpeed;
  }

  Ogre::Real getTopSpeed()
  {
    return mTopSpeed;
  }

  /**
  Sets the movement style of our camera man.
  */
  virtual void setStyle(CameraStyle style);

  CameraStyle getStyle()
  {
    return mStyle;
  }

  /**
  Manually stops the camera when in free-look mode.
  */
  void manualStop();

  void frameRendered(const Ogre::FrameEvent& evt);

  /**
  Processes key presses for free-look style movement.
  */
  bool keyPressed(const KeyboardEvent& evt);

  /**
  Processes key releases for free-look style movement.
  */
  bool keyReleased(const KeyboardEvent& evt);

  /**
  Processes mouse movement differently for each style.
  */
  bool mouseMoved(const MouseMotionEvent& evt, bool midMousePressed);

  bool mouseWheelRolled(const MouseWheelEvent& evt);

  /**
  Processes mouse presses. Only applies for orbit style.
  Left button is for orbiting, and right button is for zooming.
  */
  bool mousePressed(const MouseButtonEvent& evt);

  /**
  Processes mouse releases. Only applies for orbit style.
  Left button is for orbiting, and right button is for zooming.
  */
  bool mouseReleased(const MouseButtonEvent& evt);

  /**
   * fix the yaw axis to be Vector3::UNIT_Y of the parent node (tabletop mode)
   *
   * otherwise the yaw axis can change freely
   */
  void setFixedYaw(bool fixed)
  {
    mYawSpace = fixed ? Ogre::Node::TS_PARENT : Ogre::Node::TS_LOCAL;
  }
  void update();

  void setPivotOffset(const Ogre::Vector3& offset);
 protected:
  Ogre::Real getDistToTarget();
  Ogre::Real dist_;
  Ogre::Node::TransformSpace mYawSpace;
  Ogre::SceneNode* mCamera;
  CameraStyle mStyle;
  Ogre::SceneNode* mTarget;
  bool mOrbiting;
  bool mMoving;
  Ogre::Real mTopSpeed;
  Ogre::Vector3 mVelocity;
  bool mGoingForward;
  bool mGoingBack;
  bool mGoingLeft;
  bool mGoingRight;
  bool mGoingUp;
  bool mGoingDown;
  bool mFastMove;
  Ogre::Vector3 mOffset;
};
}
/** @} */
/** @} */

#endif //RAISIMOGREVISUALIZER_RAICAMERAMAN_HPP
