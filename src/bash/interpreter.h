#ifndef __BASH_INTERPRETER__
#define __BASH_INTERPRETER__

namespace bash {

#define INTERACTIVE_PREFIXE "~> "

class Interpreter {
public: 
                Interpreter                 ();
                ~Interpreter                ();

    void        interactive                 ();
    void        runTest                     ();
};

}; // namespace bash

#endif