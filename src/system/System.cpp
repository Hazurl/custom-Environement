#include "System.h"

using namespace haz;

System::System() {}
System::~System() {}

bash::Interpreter& System::getCmd() { return cmd; }