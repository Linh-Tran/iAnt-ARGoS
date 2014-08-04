#ifndef CONTROLLER_H_
#define CONTROLLER_H_

/* iAnt Class Library: Custom objects implementing the iAnt CPFA algorithms. (extension/modularization) */
#include "CPFA.h"
#include "NavigationData.h"
#include "FoodData.h"

/* Base class for Argos3 controller objects. (inheritance) */
#include <argos3/core/control_interface/ci_controller.h>

/* Argos3 objects for robot components: actuators and sensors. (plug-ins) */
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_motor_ground_sensor.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_light_sensor.h>
#include <argos3/core/utility/logging/argos_log.h>

/* Access the Argos3 classes/objects and save some typing. */
using namespace argos;

/* The controller class for iAnt robots. This is the "brain" for individual robot behavior,
 * and it implements the iAnt CPFA using the iAnt class library. */
class Controller : public CCI_Controller {

private:

	/* robot actuator and sensor components */
	CCI_DifferentialSteeringActuator *steeringActuator; // controls the robot's motor speeds
	CCI_FootBotProximitySensor       *proximitySensor;  // detects nearby objects to prevent collision
	CCI_FootBotMotorGroundSensor     *groundSensor;     // detects food items & nest (color changes)
	CCI_FootBotLightSensor           *lightSensor;      // detects nest-light for navigation control

	/* TODO make sure that each of these custom objects has an Init() function
	 * that will tie them into the ARGoS framework. */
	/* get rid of CPFA */ CPFA              CPFA_data; // CPFA data container.
	NavigationData    navData;   // Navigation data container object.
	FoodData          foodData;  // Food source data container.

	/* Primary state definitions for the CPFA. */
	enum STATE {
        SET_SEARCH_LOCATION = 0,
        TRAVEL_TO_SEARCH_SITE,
        PERFORM_INFORMED_WALK,
        PERFORM_UNINFORMED_WALK,
        SENSE_LOCAL_RESOURCE_DENSITY,
        TRAVEL_TO_NEST
	};

public:

	/* Constructor function. */
	Controller();

	/* Destructor function. */
	~Controller();

    /* Initializes the controller.
     * You should always perform all your memory allocation and configuration in this method,
     * and not in the constructor.
     * @param node The XML tree associated to this controller.
     * @see Reset()
     * @see Destroy() */
	void Init(TConfigurationNode& node);

	/* Executes a control step.
     * The logic of your controller goes here. */
    void ControlStep();

    /* Resets the state of the controller to what it was right after Init() was executed.
     * Note that the state of the robot, as well as the state of sensors and actuators
     * is automatically reset by ARGoS outside this class.
     * @see Init()
     * @see Destroy() */
    void Reset();

    /* You should perform memory deallocation and clean up in this function.
     * @see Init()
     * @see Reset() */
    void Destroy();

}; /* Controller */

#endif /* CONTROLLER_H_ */
