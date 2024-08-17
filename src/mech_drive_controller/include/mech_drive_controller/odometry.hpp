// Copyright 2020 PAL Robotics S.L.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*
 * Author: Luca Marchionni
 * Author: Bence Magyar
 * Author: Enrique Fernández
 * Author: Paul Mathieu
 */

#ifndef MECH_DRIVE_CONTROLLER__ODOMETRY_HPP_
#define MECH_DRIVE_CONTROLLER__ODOMETRY_HPP_

#include <cmath>

#include "mech_drive_controller/rolling_mean_accumulator.hpp"
#include "rclcpp/time.hpp"


namespace mech_drive_controller
{
class Odometry
{
public:
  explicit Odometry(size_t velocity_rolling_window_size = 10);

  void init(const rclcpp::Time & time);
  bool update(double front_left_pos, double front_right_pos, double back_left_pos, double back_right_pos, const rclcpp::Time & time);
  void updateOpenLoop(double linear_x, double linear_y, double angular, const rclcpp::Time & time);
  void resetOdometry();

  double getX() const { return x_; }
  double getY() const { return y_; }
  double getHeading() const { return heading_; }
  double getLinear_x() const { return linear_x_; }
  double getLinear_y() const { return linear_y_; }
  double getAngular() const { return angular_; }
  double getOld() const {return front_left_wheel_old_pos_; }

  void setWheelParams(double wheel_separation_length, double wheel_seperation_width, double left_wheel_radius, double right_wheel_radius);
  void setVelocityRollingWindowSize(size_t velocity_rolling_window_size);

private:
  using RollingMeanAccumulator = mech_drive_controller::RollingMeanAccumulator<double>;

  void integrateRungeKutta2(double linear_x, double linear_y, double angular);
  void integrateExact(double linear_x, double linear_y, double angular);
  void resetAccumulators();

  // Current timestamp:
  rclcpp::Time timestamp_;

  // Current pose:
  double x_;        //   [m]
  double y_;        //   [m]
  double heading_;  // [rad]

  // Current velocity:
  double linear_x_;   //   [m/s]
  double linear_y_;
  double angular_;  // [rad/s]

  // Wheel kinematic parameters [m]:
  double wheel_separation_length_;
  double wheel_separation_width_;
  double left_wheel_radius_;
  double right_wheel_radius_;

  // Previous wheel position/state [rad]:
  double front_left_wheel_old_pos_;
  double front_right_wheel_old_pos_;
  double back_left_wheel_old_pos_;
  double back_right_wheel_old_pos_;

  //loggers
  double calc_x;
  double calc_y;
  double calc_ang;

  // Rolling mean accumulators for the linear and angular velocities:
  size_t velocity_rolling_window_size_;
  RollingMeanAccumulator linear_accumulator_x;
  RollingMeanAccumulator linear_accumulator_y;
  RollingMeanAccumulator angular_accumulator_;
};

}  // namespace mech_drive_controller

#endif  // MECH_DRIVE_CONTROLLER__ODOMETRY_HPP_
