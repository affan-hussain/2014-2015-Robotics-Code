/** @file init.c
 * @brief File for initialization code
 *
 * This file should contain the user initialize() function and any functions related to it.
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
 * Runs pre-initialization code. This function will be started in kernel mode one time while the
 * VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port
 * states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely
 * configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {
}

/*
 * Runs user initialization code. This function will be started in its own task with the default
 * priority and stack size once when the robot is starting up. It is possible that the VEXnet
 * communication link may not be fully established at this time, so reading from the VEX
 * Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global
 * variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks
 * will not start. An autonomous mode selection menu like the pre_auton() in other environments
 * can be implemented in this task if desired.
 */

// waits for button press from lcd
void waitForPress() {
	while (lcdReadButtons(uart1 ) == 0) {
		wait(5);
	}
}
// waits for button release from lcd
void waitForRelease() {
	while (lcdReadButtons(uart1 ) != 0) {
		wait(5);
	}
}

Encoder rightE; // right encoder object
Encoder leftE; // left encoder object
Encoder rightS; // right scissor encoder
Encoder leftS; //left scissor encoder

Gyro gDog;
int autoChoice = 1;

void initialize() {
	speakerInit();
	rightE = encoderInit(8, 9, false); //intialize right encoder
	leftE = encoderInit(4, 5, false); // intitalize left encoder
	rightS = encoderInit(11, 12, true);
	leftS = encoderInit(1, 2, false);
	pinMode(14, INPUT);
	gDog = gyroInit(2, 0);

	lcdInit(uart1 ); // initalize lcd
	lcdClear(uart1 ); // clear the lcd
	lcdSetBacklight(uart1, true);

	int But = 0;

	int Butalt = 0;
	int annoying = 0;
	//if (isOnline()) {

	lcdSetText(uart1, 1, " Click Left ");
	lcdSetText(uart1, 2, " Click Right");

	while (But != 2) {

		waitForPress();
		But = lcdReadButtons(uart1 );
		waitForRelease();

		if (annoying == 0) {
			lcdSetText(uart1, 1, "  Autonomous");
			lcdSetText(uart1, 2, "<    enter   >");
			Butalt = 4;
			annoying = 1;
		}
		////////////////////////////////////////////////////////////
		if (annoying == 1) {

			if (But == 4) {
				lcdSetText(uart1, 1, "  Alt. Auton");
				lcdSetText(uart1, 2, "<    enter   >");
				Butalt = 2;
				annoying = 2;
			}

			else if (But == 1) {
				lcdSetText(uart1, 1, "   Forward");
				lcdSetText(uart1, 2, "<    enter    >");
				Butalt = 5;
				annoying = 5;
			}

		}
		////////////////////////////////////////////////////
		else if (annoying == 2) {

			if (But == 4) {
				lcdSetText(uart1, 1, "  Cube Auton");
				lcdSetText(uart1, 2, "<    enter   >");
				Butalt = 3;
				annoying = 3;
			}

			else if (But == 1) {
				lcdSetText(uart1, 1, "  Autonomous");
				lcdSetText(uart1, 2, "<    enter    >");
				Butalt = 1;
				annoying = 1;
			}

		}
		///////////////////////////////////////////////
		else if (annoying == 3) {

			if (But == 4) {
				lcdSetText(uart1, 1, "    Skills");
				lcdSetText(uart1, 2, "<    enter   >");
				Butalt = 4;
				annoying = 4;
			}

			else if (But == 1) {
				lcdSetText(uart1, 1, "  Alt. Auton");
				lcdSetText(uart1, 2, "<    enter    >");
				Butalt = 2;
				annoying = 2;
			}

		}
		//////////////////////////////////////////////
		else if (annoying == 4) {

			if (But == 4) {
				lcdSetText(uart1, 1, "  Forward");
				lcdSetText(uart1, 2, "<    enter   >");
				Butalt = 5;
				annoying = 5;
			}

			else if (But == 1) {
				lcdSetText(uart1, 1, "  Cube Auton");
				lcdSetText(uart1, 2, "<    enter    >");
				Butalt = 3;
				annoying = 3;
			}

		}

		else if (annoying == 5) {
			if (But == 4) {
				lcdSetText(uart1, 1, "  Autonomous");
				lcdSetText(uart1, 2, "<    enter   >");
				Butalt = 1;
				annoying = 1;
			}

			else if (But == 1) {
				lcdSetText(uart1, 1, "    Skills");
				lcdSetText(uart1, 2, "<    enter    >");
				Butalt = 4;
				annoying = 4;
			}

		}
		////////////////////////////////////////////////////
	} //while loop end
	  //}

	if (Butalt == 1) {
		lcdSetText(uart1, 1, "You chose Auto");
		lcdSetText(uart1, 2, "Good choice");
		autoChoice = 1;
	} else if (Butalt == 2) {
		lcdSetText(uart1, 1, "You chose Alt.");
		lcdSetText(uart1, 2, "Good choice");
		autoChoice = 2;
	} else if (Butalt == 3) {
		lcdSetText(uart1, 1, "You chose Cube");
		lcdSetText(uart1, 2, "Good choice");
		autoChoice = 3;
	} else if (Butalt == 4) {
		lcdSetText(uart1, 1, "You chose Skills");
		lcdSetText(uart1, 2, "Good choice");
		autoChoice = 4;
	} else if (Butalt == 5) {
		lcdSetText(uart1, 1, "You chose Forward");
		lcdSetText(uart1, 2, "Good choice");
		autoChoice = 5;
	}

} //function end

