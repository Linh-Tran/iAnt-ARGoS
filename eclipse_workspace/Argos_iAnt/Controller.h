#ifndef CONTROLLER_H_
#define CONTROLLER_H_

/* iAnt Library: objects implementing the iAnt CPFA algorithms. (extension/modularization) */
#include "NavigationData.h"
#include "FoodData.h"

/* Base class for Argos3 controller objects. (inheritance) */
#include <argos3/core/control_interface/ci_controller.h>

/* Argos3 objects for robot components: actuators and sensors. (plug-ins) */
#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_proximity_sensor.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_motor_ground_sensor.h>
#include <argos3/plugins/robots/foot-bot/control_interface/ci_footbot_light_sensor.h>

/* Argos3 libray: random number generator, log printout to Argos GUI, etc. (plug-ins)*/
#include <argos3/core/utility/math/rng.h>
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
	NavigationData    navData;   // Navigation data container object.
	/* TODO move foodData into the navigationData object.. maybe.. think about it.. */
	FoodData          foodData;  // Food source data container object.

	/* CPFA variables,
     * NOTE: until my understanding improves, below comments may not be accurate. */
	Real           travelProbability;           // %-chance of traveling, from [0.0, 1.0]
	Real           searchProbability;           // %-chance of searching, from [0.0, 1.0]
	CRadians       uninformedSearchCorrelation; // radian angle turned during searching [0.0, 4.0PI]
	Real           informedSearchDecay;         // %-rate that informed search decays [0.0, 5.0]
	Real           siteFidelityRate;            // %-chance that robot remembers a site [0.0, 20.0]
	Real           pheromoneRate;               // %-chance of laying a pheromone [0.0, 20.0]
	Real           pheromoneDecayRate;          // %-rate that pheromones decay [0.0, 10.0]
	CRandom::CRNG *RNG;                         // random number generator used for random walking, etc.

	/* Primary state definitions for the CPFA. */
	enum state {
        SET_SEARCH_LOCATION = 0,
        TRAVEL_TO_SEARCH_SITE,
        PERFORM_INFORMED_WALK,
        PERFORM_UNINFORMED_WALK,
        SENSE_LOCAL_RESOURCE_DENSITY,
        TRAVEL_TO_NEST
	} state;

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

    /* Just a thought, but you may make these private and add
	 * a function "changeState()" which calls the appropriate
	 * function from the list below... */
	/* CPFA state machine implementation functions */
	void SetSearchLocation();
	void TravelToSearchSite();
	void PerformInformedWalk();
	void PerformUninformedWalk();
	void SenseLocalResourceDensity();
	void TravelToNest();

}; /* Controller */

#endif /* CONTROLLER_H_ */
