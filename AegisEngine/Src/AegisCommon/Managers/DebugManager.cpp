#include "DebugManager.h"

DebugManager::DebugManager(): 
	Singleton()
{

	//necesito el scene manager para debugear lineas
}

DebugManager::~DebugManager()
{
}

void DebugManager::log(const std::string& msg) {
	std::cout<<"DEBUG: " << msg << std::endl;
}

void DebugManager::logWarning(const std::string& msg) {
	std::cout <<"WARNING: " << msg << std::endl;
}
void DebugManager::logError(const std::string& msg) {
	std::cout <<"ERROR: " << msg << std::endl;
}

bool DebugManager::init() {

	return true;
}
