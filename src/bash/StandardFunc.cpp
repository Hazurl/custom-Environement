#include "StandardFunc.h"

using namespace bash;

using namespace haz;

/* Namspace that contains all the standards functions of the custom bash
 *
 * Prototype for all function are : 
 *      (Context&) -> void
 * In C++ :
 *      void (*) (Context&)
 */

void std_bash_func::print (Context& ctx) {
    ctx.print(ctx.getParam(1));
}
