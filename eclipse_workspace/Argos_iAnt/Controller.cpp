#include "Controller.h"

/* Construct the Controller object and set all default values to NULL.
 * Variables will be initialized by the Init() function. */
Controller::Controller() :
	steeringActuator(NULL),
	proximitySensor(NULL),
	groundSensor(NULL),
	lightSensor(NULL)
{}

/* Deconstruct the Controller object (deallocate memory, etc).
 * Currently not necessary and included for future expansion. */
Controller::~Controller() {
	// does nothing... for now
}

/* Inherited function of the CCI_Controller class.
 * Set default values for all components and variables from the XML file. */
void Controller::Init(TConfigurationNode& node) {
	/* Initialize ARGoS sensors and actuators from these categories in the XML file. */
	steeringActuator = GetActuator<CCI_DifferentialSteeringActuator>("differential_steering");
	proximitySensor  = GetSensor<CCI_FootBotProximitySensor>("footbot_proximity");
	groundSensor     = GetSensor<CCI_FootBotMotorGroundSensor>("footbot_motor_ground");
	lightSensor      = GetSensor<CCI_FootBotLightSensor>("footbot_light");

	/* Initialize default iAnt object values from the <params> tag located inside of
	 * the <controllers> tag inside of the Argos3 XML file. */
	CPFA_data.Init(GetNode(node, "CPFA"));
	navData.Init(GetNode(node, "navigation"));
	foodData.Init(GetNode(node, "food"));
}

/* Inherited function of the CCI_Controller class.
 * Perform control logic for a single step (frame) of simulation time. */
void Controller::ControlStep() {
}

/* Inherited function of the CCI_Controller class.
 * Reset all variables to their default pre-run values.
 * Sensors/Actuators are reset by Argos outside of this class. */
void Controller::Reset() {
	CPFA_data.Reset();
	navData.Reset();
	foodData.Reset();
}

/* Inherited function of the CCI_Controller class.
 * Memory deallocation and clean up. Currently not needed and here for future expansion. */
void Controller::Destroy() {
	// do nothing... for now
}
