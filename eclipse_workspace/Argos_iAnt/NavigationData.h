#ifndef NAVIGATIONDATA_H_
#define NAVIGATIONDATA_H_

/* Access XML loading functionality. */
#include <argos3/core/utility/configuration/argos_configuration.h>

using namespace argos;

class NavigationData {

public:

	NavigationData();
	~NavigationData();

	void Init(TConfigurationNode& node) {}
	void Reset() {}

};

#endif /* NAVIGATIONDATA_H_ */
