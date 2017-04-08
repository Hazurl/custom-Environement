#ifndef __BASH_VALUE__
#define __BASH_VALUE__

#include <list>
#include <string>
#include <stdexcept>
#include <initializer_list>
#include "../../lib/Logger/src/Logger.h"

namespace bash {
    class Value;
};

bash::Value operator+(bash::Value& v0, bash::Value& v1);
bash::Value operator-(bash::Value& v0, bash::Value& v1);
bash::Value operator*(bash::Value& v0, bash::Value& v1);
bash::Value operator/(bash::Value& v0, bash::Value& v1);

bash::Value operator+=(bash::Value& v0, bash::Value& v1);
bash::Value operator-=(bash::Value& v0, bash::Value& v1);
bash::Value operator*=(bash::Value& v0, bash::Value& v1);
bash::Value operator/=(bash::Value& v0, bash::Value& v1);

bash::Value operator++(bash::Value& v0);
bash::Value operator--(bash::Value& v0);

bool operator<(bash::Value& v0, bash::Value& v1);
bool operator>(bash::Value& v0, bash::Value& v1);
bool operator<=(bash::Value& v0, bash::Value& v1);
bool operator>=(bash::Value& v0, bash::Value& v1);
bool operator==(bash::Value& v0, bash::Value& v1);
bool operator!=(bash::Value& v0, bash::Value& v1);

namespace bash {

class Value {
public:
    enum class Type {
        STRING, NUMBER, ARRAY
    };

    Value ();
    Value (double n);
    Value (std::string s);
    Value (std::list<Value> a);
    Value (std::initializer_list<Value> l);
    ~Value();

    Type getType() { return type; }
    std::string to_string();

    Value& push_front(Value v);
    Value& push_back(Value v);

private:

    friend Value ( ::operator+) (Value& v0, Value& v1);
    friend Value ( ::operator-) (Value& v0, Value& v1);
    friend Value ( ::operator/) (Value& v0, Value& v1);
    friend Value ( ::operator*) (Value& v0, Value& v1);
    friend Value ( ::operator+=) (Value& v0, Value& v1);
    friend Value ( ::operator-=) (Value& v0, Value& v1);
    friend Value ( ::operator/=) (Value& v0, Value& v1);
    friend Value ( ::operator*=) (Value& v0, Value& v1);

    friend Value ( ::operator++) (Value& v0);
    friend Value ( ::operator--) (Value& v0);

    friend bool ( ::operator<) (Value& v0, Value& v1);
    friend bool ( ::operator>) (Value& v0, Value& v1);
    friend bool ( ::operator<=) (Value& v0, Value& v1);
    friend bool ( ::operator>=) (Value& v0, Value& v1);
    friend bool ( ::operator==) (Value& v0, Value& v1);
    friend bool ( ::operator!=) (Value& v0, Value& v1);

    Type type = Type::NUMBER;
    
    double number = 0;
    std::string str = "";
    std::list<Value> arr;
};

}; // namespace bash


#endif