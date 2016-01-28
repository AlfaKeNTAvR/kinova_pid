/***************************************************************************//**
* \file pid_header.h
*
* \brief Simple PID controller with dynamic reconfigure and diagnostics
* \author Andy Zelenak
* \date March 8, 2015
*
* \section license License (BSD-3)
* Copyright (c) 2015, Andy Zelenak\n
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
* - Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
* - Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
* - Neither the name of Willow Garage, Inc. nor the names of its contributors
* may be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

#pragma once

//#include "pid/plant_msg.h"
//#include "pid/controller_msg.h"

#include <diagnostic_updater/diagnostic_updater.h>
#include <diagnostic_updater/update_functions.h>
#include "ros/ros.h"
#include <std_msgs/Float64.h>
#include <std_msgs/Bool.h>

#include "math.h"
#include <stdio.h>
#include <string>
#include <iostream>

// Primary PID controller input & output variables
double plant_state;          // current output of plant
double control_effort;       // output of pid controller
double setpoint = 0;         // desired output of plant
bool pid_enabled = true;         // PID is enabled to run

ros::Time prev_time;
ros::Duration delta_t;

double error_integral = 0.0;
double proportional;         // proportional term of output
double integral;             // integral term of output
double derivative;           // derivative term of output

double Kp, Ki, Kd;   // PID loop parameters
double rate; // Control loop rate in Hz.

// Cutoff frequency for the derivative calculation in Hz.
// Negative -> Has not been set by the user yet, so use a default.
double cutoff_frequency = -1; 

// Upper and lower saturation limits
double upper_limit =  1000.0;
double lower_limit = -1000.0; 
double windup_limit = 1000.0; // Anti-windup term. Limits the absolute value of the integral term.

std::vector<double> error(3);
std::vector<double> filtered_error(3);
std::vector<double> error_deriv(3);
std::vector<double> filtered_error_deriv(3);
int loop_counter = 0; // Counts # of times through the control loop. Used to start taking a derivative after 2 rounds

// Topic and node names and message objects
ros::Publisher control_effort_pub;

std::string topic_from_controller;
std::string topic_from_plant;
std::string setpoint_topic;
std::string node_name = "pid_node";

std_msgs::Float64 control_msg;
std_msgs::Float64 state_msg;

// Diagnostic objects
double min_input_rate = 1;
double max_input_rate = 200;
int measurements_received = 0;


class PidControllerDiags
{
public:
  PidControllerDiags();
  const diagnostic_updater::FrequencyStatusParam fparam;
  diagnostic_updater::FrequencyStatus freq_status;
  diagnostic_updater::Updater diag_updater;
};

PidControllerDiags::PidControllerDiags() :
  fparam(diagnostic_updater::FrequencyStatusParam(&min_input_rate, &max_input_rate)),
  freq_status(fparam)
{
}

PidControllerDiags *diags;
