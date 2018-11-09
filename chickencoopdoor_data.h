const int StepperPin1 = A0;
const int StepperPin2 = A1;
const int MotorControlPin1 = A2;
const int MotorControlPin2 = A3;

const int DaylightPin = A4; // defaults to INPUT mode

struct LightData  {
	int lightLevel;
	bool isConsistent;
};

// classify resistance value ranges for photo sensor
// based on return value of analogRead()
const int NightMin = 0;
const int NightMax = 300;
const int DayMin = 600;
const int DayMax = 1023;
