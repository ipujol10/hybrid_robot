//
// Created by woombat on 2/23/22.
//

#include "PID_controller.hpp"

PID::PID( const std::string &name,Float64 target = M_PI/2, Float64 KP=0.2,Float64 KI=0.0,Float64 KD=0.0,Float64 sample_time = 0.05 ,ros::Time current_time = ros::Time{0.0}){
    P = KP;
    I = KI;
    D = KD;

    SampleTime = sample_time;
    CurrentTime = current_time;
    LastTime = CurrentTime;
    SetPoint = target;
    clear();


}


void PID::clear() {
    //Clears PID computations and coefficients
//    SetPoint = 0.0;

    PTerm = 0.0;
    ITerm = 0.0;
    DTerm = 0.0;
    LastError = 0.0;

    // Windup Guard
    Float64 int_error = 0.0;
//    windup_guard = 20.0;

    Output = 0.0;
}


Float64 PID::update(Float64 feedback_value, ros::Time current_time, bool limit, Float64 upper, Float64 lower) {
    //Calculates PID value for given reference feedback

    /*..math::
     * u(t) = K_p e(t) + K_i \int_{0}^{t} e(t)dt + K_d {de}/{dt}
    */
    Float64 error = SetPoint - feedback_value;

    CurrentTime = current_time;

    ros::Duration delta_time = CurrentTime - LastTime;
    Float64 delta_error = error - LastError;

    if (delta_time >= ros::Duration{SampleTime})
    {PTerm = P * error;
    ITerm += error * delta_time.toSec();
}

    if (ITerm < -windup_guard){
    ITerm = -windup_guard;
}
    else if(ITerm > windup_guard){
        ITerm =windup_guard;
        }


    DTerm = 0.0;
    if (delta_time.toSec() > 0){
        DTerm = delta_error / delta_time.toSec();
    }

    //Remember last time and last error for next calculation
    LastTime = CurrentTime;
    LastError = error;

    Output = PTerm + (I * ITerm) + (D * DTerm);

    if (limit) {
      Output = range_limiter(Output, upper, lower);
    }

    return Output;
}


void PID::setKp(Float64 proportional_gain) {
    //Determines how aggressively the PID reacts to the current error with setting Proportional Gain"""
   P = proportional_gain;
}
void PID::setKi(Float64 integral_gain) {
    //Determines how aggressively the PID reacts to the current error with setting Integral Gain"""
   I = integral_gain;
}
void PID::setKd(Float64 derivative_gain){
   //Determines how aggressively the PID reacts to the current error with setting Derivative Gain"""
   D = derivative_gain;
}



void PID::setWindup(Float64 windup) {
/*Integral windup, also known as integrator windup or reset windup,
*refers to the situation in a PID feedback controller where
*a large change in setpoint occurs (say a positive change)
*and the integral terms accumulates a significant error
*        during the rise (windup), thus overshooting and continuing
* to increase as this accumulated error is unwound
* (offset by errors in the other direction).
* The specific problem is the excess overshooting.
*/
    windup_guard = windup;
}

void PID::setTarget(Float64 target = M_PI/2){

    SetPoint = target;

}
void PID::setSampleTime(Float64 sample_t) {
/* PID that should be updated at a regular interval.
*  Based on a pre-determined sample time, the PID decides if it should compute or return immediately.
*/
    SampleTime = sample_t;
}

Float64 PID::get_target() const {
  return SetPoint;
}


int mainPID(){

    PID pid = PID("pid",0.2,0.001,0.01,0.5);
    pid.setWindup(20.0);
    pid.setTarget(M_PI/2);

    Float64 vel = pid.update(M_PI,ros::Time());
    return 0;
}

Float64 PID::range_limiter(Float64 input, Float64 upper, Float64 lower) {
  if (input < lower) return lower;
  if (input > upper) return upper;
  return input;
}