#ifndef __BASH_VALUE__
#define __BASH_VALUE__

#include <deque>
#include <string>
#include <stdexcept>
#include <initializer_list>
#include <logger.h>

using namespace haz;

namespace bash {
    class Value;
};

bash::Value operator+(bash::Value const& v0, bash::Value const& v1);
bash::Value operator-(bash::Value const& v0, bash::Value const& v1);
bash::Value operator-(bash::Value const& v0);
bash::Value operator*(bash::Value const& v0, bash::Value const& v1);
bash::Value operator/(bash::Value const& v0, bash::Value const& v1);

bash::Value operator+=(bash::Value& v0, bash::Value const& v1);
bash::Value operator-=(bash::Value& v0, bash::Value const& v1);
bash::Value operator*=(bash::Value& v0, bash::Value const& v1);
bash::Value operator/=(bash::Value& v0, bash::Value const& v1);

bash::Value operator++(bash::Value& v0);
bash::Value operator--(bash::Value& v0);

bool operator<(bash::Value const& v0, bash::Value const& v1);
bool operator>(bash::Value const& v0, bash::Value const& v1);
bool operator<=(bash::Value const& v0, bash::Value const& v1);
bool operator>=(bash::Value const& v0, bash::Value const& v1);
bool operator==(bash::Value const& v0, bash::Value const& v1);
bool operator!=(bash::Value const& v0, bash::Value const& v1);

namespace bash {

class Value {
public:
    enum class Type {
        STRING, NUMBER, ARRAY, VOID
    };

    Value ();
    Value (double n);
    Value (std::string s);
    Value (std::deque<Value> a);
    Value (std::initializer_list<Value> l);
    ~Value();

    Type getType() { return type; }
    std::string to_string(bool showType = false) const;
    bool to_bool() const;

    Value& push_front(Value v);
    Value& push_back(Value v);
    Value& clearArray();
    Value& at(Value const& v);
    void setAt(Value const& key_v, Value v);

private:
    Logger* logger = &Logger::get("#.Value");

    friend Value ( ::operator+) (Value const& v0, Value const& v1);
    friend Value ( ::operator-) (Value const& v0, Value const& v1);
    friend Value ( ::operator-) (Value const& v0);
    friend Value ( ::operator/) (Value const& v0, Value const& v1);
    friend Value ( ::operator*) (Value const& v0, Value const& v1);
    friend Value ( ::operator+=) (Value& v0, Value const& v1);
    friend Value ( ::operator-=) (Value& v0, Value const& v1);
    friend Value ( ::operator/=) (Value& v0, Value const& v1);
    friend Value ( ::operator*=) (Value& v0, Value const& v1);

    friend Value ( ::operator++) (Value& v0);
    friend Value ( ::operator--) (Value& v0);

    friend bool ( ::operator<) (Value const& v0, Value const& v1);
    friend bool ( ::operator>) (Value const& v0, Value const& v1);
    friend bool ( ::operator<=) (Value const& v0, Value const& v1);
    friend bool ( ::operator>=) (Value const& v0, Value const& v1);
    friend bool ( ::operator==) (Value const& v0, Value const& v1);
    friend bool ( ::operator!=) (Value const& v0, Value const& v1);

    Type type = Type::VOID;
    
    double number = 0;
    std::string str = "";
    std::deque<Value> arr;
};

}; // namespace bash


#endif