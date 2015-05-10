/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

/* MOTOR SETUP
 *
 *
 *
 *
 * Motor 1  - front right drive
 * Motor 2  - rear right drive
 * Motor 3' - scissor lift motors front left  ---
 * Motor 4  - Intake
 * Motor 5  - scissor rear right ---
 * ------------------------------------- seperation
 * Motor 6  - rear left drive
 * Motor 7' - scissor rear right
 * Motor 8  - Intake
 * Motor 9  - scissor front right  -----
 * Motor 10 -  front left drive
 *
 * ' = plugged into power expander
 *
 *
 *
 */

//function to use PID loop to raise or lower the left



void operatorControl() {

	while (1) {


		//int rightEE = encoderGet(gDog);
		int leftEE = gyroGet(gDog);

		printf("%d \n\r", leftEE);

		// rightp = analogRead(2); // right potentiometer
		//leftp = analogRead(3); // left potentiometer

		//Chanells 2 and 3 on joystick
		int CH2 = joystickGetAnalog(1, 2);
		int CH3 = joystickGetAnalog(1, 3);
		int CH2Alt = joystickGetAnalog(2, 2);
		int CH3Alt = joystickGetAnalog(2, 3);
		// Buttons on joystick
		bool Btn5U = joystickGetDigital(2, 5, JOY_UP);
		bool Btn5D = joystickGetDigital(2, 5, JOY_DOWN);
		bool Btn6U = joystickGetDigital(2, 6, JOY_UP);
		bool Btn6D = joystickGetDigital(2, 6, JOY_DOWN);
		bool Btn7U = joystickGetDigital(2, 7, JOY_UP);
		bool Btn7D = joystickGetDigital(2, 7, JOY_DOWN);
		//bool Btn7R = joystickGetDigital(1, 7, JOY_RIGHT);
		//bool Btn7L = joystickGetDigital(1, 7, JOY_LEFT);
	//	bool Btn8U = joystickGetDigital(1, 8, JOY_UP);
	//	bool Btn8D = joystickGetDigital(1, 8, JOY_DOWN);
		bool Btn8U2 = joystickGetDigital(2, 8, JOY_UP);
		bool Btn8D2 = joystickGetDigital(2, 8, JOY_DOWN);
		bool Btn8R = joystickGetDigital(1, 8, JOY_RIGHT);
		//	bool Btn8L = joystickGetDigital(1,8,JOY_LEFT);

		//Drive control
		motorSet(1, CH2); //right
		motorSet(2, -CH2); //right
		motorSet(6, -CH3); // rear left
		motorSet(10, -CH3); // frontl left


		motorSet(3,CH3Alt);
		motorSet(5,-CH2Alt);
		motorSet(7,-CH3Alt);
		motorSet(9,CH2Alt);
		//Scissor Lift
/*
		if (Btn6D) //down
		{
			motorSet(3, -127);
			motorSet(7, 127);
			motorSet(5, 127);
			motorSet(9, -127);

		} else if (Btn6U) //up
		{
			motorSet(7, -127);
			motorSet(9, 127);
			motorSet(3, 127);
			motorSet(5, -127);

		} else if (Btn8U2) {
			motorSet(9, 127);
			motorSet(5, -127);
		} else if (Btn8D2) {
			motorSet(9, -127);
			motorSet(5, 127);
		}
		else if(Btn7U){
			motorSet(7, -127);
			motorSet(3, 127);
		}
		else if(Btn7D){
			motorSet(7, 127);
			motorSet(3, -127);
		}
		else{
			motorSet(3, 0);
			motorSet(7, 0);
			motorSet(5, 0);
			motorSet(9, 0);
		}
		*/

		//intake
		if (Btn5U) {
			motorSet(4, 127);
			motorSet(8, -127);
		} else if (Btn5D) {
			motorSet(4, -127);
			motorSet(8, 127);
		} else {
			motorSet(4, 0);
			motorSet(8, 0);
		}
		/*
		 if (Btn7U) {
		 encoderReset(rightS);
		 encoderReset(leftS);
		 encoderReset(rightE);
		 encoderReset(leftE);
		 gyroReset(gDog);

		 if (Btn8D) //up
		 {
		 motorSet(7, 127);
		 motorSet(5, 127);
		 } else if (Btn8U) //down
		 {
		 motorSet(7, -127);
		 motorSet(5, -127);
		 } else //dont move
		 {
		 motorSet(7, 0);
		 motorSet(5, 0);
		 }

		 }

		 */

		/*
		 * 22- start
		 * 26 - pictures of irwin and asmit
		 * 42 - looks nice
		 * 45 - autonomous
		 * 59 - 62 - recent device changes
		 *
		 *
		 */

	} //while loop end bracket

} //function end bracket
