const int StepperPin1 = A2;
const int StepperPin2 = A4;
const int EncoderPin1 = 6;
const int EncoderPin2 = 8;

const int DaylightPin = A6; // defaults to INPUT mode

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
