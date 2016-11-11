#include "IDs.h"

IDs::IDs(): ID(-1) { }
IDs::~IDs() { }
int IDs::generate() {
	return ++ID;
}

int IDs::get_current_max() const { return ID; }
