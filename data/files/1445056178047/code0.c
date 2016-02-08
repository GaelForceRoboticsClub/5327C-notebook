#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  transmission,   sensorDigitalOut)
#pragma config(Sensor, dgtl2,  angle,          sensorDigitalOut)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port2,           LTO,           tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           LTI,           tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           LB,            tmotorVex393TurboSpeed_MC29, openLoop, reversed, encoderPort, I2C_1)
#pragma config(Motor,  port5,           LRI,           tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           LRF,           tmotorVex393TurboSpeed_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port7,           RB,            tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           RTI,           tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           RTO,           tmotorVex393TurboSpeed_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)
#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
int RT1;
int RT2;
int LS = -127;
int buttonToggleState1 = 0;
int buttonPressed1 = 0;
int buttonToggleState2 = 0;
int buttonPressed2 = 0;
int buttonPressed3 = 0;
const unsigned int TrueSpeed[128] =
{
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0, 21, 21, 21, 22, 22, 22, 23, 24, 24,
	25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
	28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
	33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
	37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
	41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
	46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
	52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
	71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
	80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
	88, 89, 89, 90, 90,127,127,127
};

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Functions
//
/////////////////////////////////////////////////////////////////////////////////////////

void dc_six_drive()
{
	RT1 = vexRT[Ch3];
	RT2 = vexRT[Ch2];
	if(RT2 > 0)
	{
		motor[LB] = TrueSpeed[RT2];
		motor[LTI] = TrueSpeed[RT2];
		motor[LTO] = TrueSpeed[RT2];
	}
	else if(RT2 < 0)
	{
		RT2 = RT2 * -1;
		motor[LB] = -TrueSpeed[RT2];
		motor[LTI] = -TrueSpeed[RT2];
		motor[LTO] = -TrueSpeed[RT2];
	}

	if(RT1 > 0)
	{
		motor[RB] = TrueSpeed[RT1];
		motor[RTI] = TrueSpeed[RT1];
		motor[RTO] = TrueSpeed[RT1];
	}
	else if(RT1 < 0)
	{
		RT1 = RT1 * -1;
		motor[RB] = -TrueSpeed[RT1];
		motor[RTI] = -TrueSpeed[RT1];
		motor[RTO] = -TrueSpeed[RT1];
	}
}

void dc_two_drive()
{
	RT1 = vexRT[Ch3];
	RT2 = vexRT[Ch2];
	if(RT2 > 0)
	{
		motor[LB] = TrueSpeed[RT2];
	}
	else if(RT2 < 0)
	{
		RT2 = RT2 * -1;
		motor[LB] = -TrueSpeed[RT2];
	}

	if(RT1 > 0)
	{
		motor[RB] = TrueSpeed[RT1];
	}
	else if(RT1 < 0)
	{
		RT1 = RT1 * -1;
		motor[RB] = -TrueSpeed[RT1];
	}
}

void dc_fw_stop()
{
	buttonPressed3 = 0;
	motor[LRF] = -80;
	motor[LTI] = -80;
	motor[LTO] = -80;
	motor[RTI] = -80;
	motor[RTO] = -80;
	wait1Msec(500);
	motor[LRF] = -30;
	motor[LTI] = -30;
	motor[LTO] = -30;
	motor[RTI] = -30;
	motor[RTO] = -30;
	wait1Msec(500);
	motor[LRF] = 0;
	motor[LTI] = 0;
	motor[LTO] = 0;
	motor[RTI] = 0;
	motor[RTO] = 0;
}

void dc_transmission_toggle()
{
	if(vexRT[Btn7U] == 1)
	{
		if(!buttonPressed1)
		{
			buttonToggleState1 = 1 - buttonToggleState1;
			buttonPressed1 = 1;
		}
	}
	else
	{
		buttonPressed1 = 0;
	}
	if(buttonToggleState1)
	{
		SensorValue[transmission] = 1;
	}
	else
	{
		SensorValue[transmission] = 0;
	}
}

void dc_angle_toggle()
{
	if(vexRT[Btn8U] == 1)
	{
		if(!buttonPressed2)
		{
			buttonToggleState2 = 1 - buttonToggleState2;
			buttonPressed2 = 1;
		}
	}
	else
	{
		buttonPressed2 = 0;
	}

	if(buttonToggleState2)
	{
		SensorValue[angle] = 1;
	}
	else
	{
		SensorValue[angle] = 0;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	// .....................................................................................
	// Insert user code here.
	// .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	while (true)
	{
		dc_transmission_toggle();
		dc_angle_toggle();

		//Intake
		if(vexRT[Btn6U] == 1)
		{
			motor[LRI] = 127;
		}
		else if(vexRT[Btn6D] == 1)
		{
			motor[LRI] = -127;
		}
		else
		{
			motor[LRI] = 0;
		}

		//Transmission
		if(SensorValue[transmission] == 0) //shifted out to flywheel
		{
			dc_two_drive();
			if(vexRT[Btn8D] == 1)
			{
				motor[LB] = 15;
				motor[RB] = 15;

			}
			if(vexRT[Btn5U] == 1)
			{
				buttonPressed3 = 1;
			}

			if(buttonPressed3 == 1)
			{
				if(vexRT[Btn7L] == 1)
				{
					LS = -127;
				}
				if(vexRT[Btn7D] == 1)
				{
					LS = -100;
				}
				if(vexRT[Btn7R] == 1)
				{
					LS = -80;
				}
				motor[LRF] = LS;
				motor[LTI] = LS;
				motor[LTO] = LS;
				motor[RTI] = LS;
				motor[RTO] = LS;

				if(vexRT[Btn5D] == 1)
				{
					dc_fw_stop();
				}
			}
		}

		if(SensorValue[transmission] == 1) //shifted in to base
		{
			dc_six_drive();
			if(vexRT[Btn5U] == 1)
			{
				motor[LRF] = -50;
			}
			if(vexRT[Btn5D] == 1)
			{
				motor[LRF] = 0;
			}
		}


	}

}
