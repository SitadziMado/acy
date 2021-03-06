#include "ControlPins.h"


ControlPins::ControlPins()
{
	pinMode((int)pins::encoderB, INPUT);
	pinMode((int)pins::forRev1, INPUT);
	pinMode((int)pins::forRev2, INPUT);
	pinMode((int)pins::handDrive1, INPUT);
	pinMode((int)pins::handDrive2, INPUT);
	pinMode((int)pins::emergency, INPUT);
	pinMode((int)pins::knife, INPUT);
	pinMode((int)pins::handAuto, INPUT);

	pinMode((int)pins::gearForv, OUTPUT);
	pinMode((int)pins::gearRev, OUTPUT);
	pinMode((int)pins::gearSpeed, OUTPUT);
	pinMode((int)pins::sound, OUTPUT);
}

///
/// Clear variables, casts after stop()
///
void ControlPins::Reset()
{
	knifeSwitch = false;
	length = 0;
	parts = 0;
	encoderLength = 0;
	encoderParts = 0;
}

///
/// Initialize variables
///
void ControlPins::Start(long newlength, int newparts, int& encoderCounter)
{
	length = newlength;
	parts = newparts;
	runOn = true;
	encoderLength = encoderCounter; // set init conter to current length
	RunGear();
}


///
/// Just stop the process, calls when has cut all parts
///
void ControlPins::Stop()
{
	//length = 0;
	//parts = 0;
	runOn = false;
	gearSpeed = true;
}

///
/// Runing gear whith current setups for vector and speed
///
void ControlPins::RunGear()
{
	if (!ifAuto)
	{
		if (handDrive1)
		{
			if (forRev1) digitalWrite((int)pins::gearForv, HIGH);
			else digitalWrite((int)pins::gearRev, HIGH);
		}
		if (handDrive2)
		{
			if (forRev2) digitalWrite((int)pins::gearForv, HIGH);
			else digitalWrite((int)pins::gearRev, HIGH);
		}
	}
	else digitalWrite((int)pins::gearForv, HIGH); // Auto
	if (gearSpeed) digitalWrite((int)pins::gearSpeed, HIGH);
	else digitalWrite((int)pins::gearSpeed, LOW);

	if (sound) digitalWrite((int)pins::sound, HIGH);
	else digitalWrite((int)pins::sound, LOW);
}

///
/// Stops gear
///
void ControlPins::StopGear()
{
	digitalWrite((int)pins::gearForv, LOW);
	digitalWrite((int)pins::gearRev, LOW);
	digitalWrite((int)pins::gearSpeed, LOW);
	if (sound) digitalWrite((int)pins::sound, HIGH);
	else digitalWrite((int)pins::sound, LOW);
}

///
///Returns array of bool states of pins
///
bool* ControlPins::ScanPins()
{
	bool scan[5];
	for (int i = 0; i < 5; i++) scan[i] = true;
	return  scan;
}

///
/// update states for all pins and do doings
///
void ControlPins::UpdateInputs(int& encoderCounter)
{
	knife      = !ReadPin((int)pins::knife);
	forRev1    = ReadPin((int)pins::forRev1);
	forRev2    = ReadPin((int)pins::forRev2);
	handDrive1 = !ReadPin((int)pins::handDrive1);
	handDrive2 = !ReadPin((int)pins::handDrive2);
	emergency  = ReadPin((int)pins::emergency);
	ifAuto     = !ReadPin((int)pins::handAuto);

	encoderCounterRef = encoderCounter;

	// TODO: notifications
	if (emergency) 
	{
		sound = false;
		StopGear();
	}

	if (knife) 
	{
		StopGear();
	}

	if (runOn && ifAuto) AutoMod(encoderCounter);
	else if (!ifAuto) HandMode(encoderCounter);

}

///
/// When emploee controls the process himself
///
void ControlPins::HandMode(int& encoderCounter)
{
	if (knife) encoderLength = encoderCounter;
	if (handDrive1 && handDrive2) // if both then stop
		StopGear(); 
	else if (handDrive1 || handDrive2) // if presed move then move 
		RunGear(); 
	else StopGear(); 									// if not move then stop								
}

///
/// When controller controls the process
///
void ControlPins::AutoMod(int& encoderCounter)
{
	// Knife's up/down motions
	if (knife && knifeSwitch)
	{
		knifeSwitch = false;
		encoderParts++; // + 1 part
		sound = false;
		if (parts != encoderParts) RunGear();
		encoderLength = encoderCounter;
	}
	// end knife
	if (!knifeSwitch)
		if (encoderCounter - encoderLength >= length) // It's time to cut
		{
			sound = true;
			StopGear();						// stop gear
			knifeSwitch = true;				// wait for cut
		}
	if (parts == encoderParts) Stop(); // If all parts done stop process
}

ControlPins::~ControlPins()
{
}
