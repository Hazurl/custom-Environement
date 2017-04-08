#include "Value.h"

using namespace bash;

Value::Value () {}
Value::Value (double n) : type(Type::NUMBER), number(n) {}
Value::Value (std::string s) : type(Type::STRING), str(s) {}
Value::Value (std::list<Value> a) : type(Type::ARRAY), arr(a) {}
Value::Value (std::initializer_list<Value> l) : type(Type::ARRAY), arr(l) {}

Value::~Value() {}

std::string Value::to_string() const {
    if (type == Type::NUMBER) {
        std::string s = std::to_string (number);
        int offset = 1; 
        if (s.find_last_not_of('0') == s.find('.')) 
            offset = 0; 
        s.erase(s.find_last_not_of('0') + offset, std::string::npos); 
        return s; 
    } else if (type == Type::STRING)
        return str;
    else { // array
        std::string ret = "[";
        bool first = true;

        for (auto& v : arr) {
            if (!first)
                ret += ", ";
            else
                first = false;
            ret += v.to_string();
        }

        return ret + "]";
    }
}

bool Value::to_bool() const {
    if (type == Type::NUMBER)
        return number != 0;
    if (type == Type::STRING)
        return str != "";
    if (type == Type::ARRAY)
        return !arr.empty();

    return false;
}

Value& Value::push_front(Value v) {
    if (type != Type::ARRAY)
        throw std::runtime_error("Cannot push, if it's not an array");
    arr.push_front(v);
    return *this;
}

Value& Value::push_back(Value v) {
    if (type != Type::ARRAY)
        throw std::runtime_error("Cannot push, if it's not an array");
    arr.push_back(v);
    return *this;
}

///////////////////////////////////////////////////
//                   OPERATOR                    //
///////////////////////////////////////////////////

Value operator+(Value const& v0, Value const& v1) {
    if (v0.type == Value::Type::NUMBER && v1.type == Value::Type::NUMBER)
        return Value(v0.number + v1.number);

    else if (v0.type == Value::Type::ARRAY && v1.type == Value::Type::ARRAY) {
        Value v(v0);
        for (auto& _v : v1.arr)
            v.push_back(_v);
        return v;
    }

    return Value(v0.to_string() + v1.to_string());
}

Value operator-(Value const& v0, Value const& v1) {
    if (v0.type == Value::Type::NUMBER && v1.type == Value::Type::NUMBER)
        return Value(v0.number - v1.number);

    return Value("");
}

Value operator-(Value const& v0) {
    if (v0.type == Value::Type::NUMBER)
        return Value(-v0.number);

    return Value("");
}

Value operator/(Value const& v0, Value const& v1) {
    if (v0.type == Value::Type::NUMBER && v1.type == Value::Type::NUMBER) {
        if (v1.number != 0)
            return Value(v0.number / v1.number);
        else 
            throw std::runtime_error("Division by 0");
    }

    return Value("");
}

Value operator*(Value const& v0, Value const& v1) {
    if (v0.type == Value::Type::NUMBER && v1.type == Value::Type::NUMBER)
        return Value(v0.number * v1.number);

    return Value("");
}

Value operator+=(Value& v0, Value const& v1) {
    return v0 = v0 + v1;
}

Value operator-=(Value& v0, Value const& v1) {
    return v0 = v0 - v1;
}

Value operator/=(Value& v0, Value const& v1) {
    return v0 = v0 / v1;
}

Value operator*=(Value& v0, Value const& v1) {
    return v0 = v0 * v1;
}

Value operator++(Value& v0) {
    auto v = Value(1);
    return v0 += v;
}

Value operator--(Value& v0) {
    auto v = Value(1);
    return v0 -= v;
}

bool operator<(Value const& v0, Value const& v1) {
    if (v0.type == Value::Type::NUMBER && v1.type == Value::Type::NUMBER)
        return v0.number < v1.number;
    return false;
}

bool operator>(Value const& v0, Value const& v1) {
    if (v0.type == Value::Type::NUMBER && v1.type == Value::Type::NUMBER)
        return v0.number > v1.number;
    return false;
}

bool operator<=(Value const& v0, Value const& v1) {
    return !(v0 > v1);
}

bool operator>=(Value const& v0, Value const& v1) {
    return !(v0 < v1);
}

bool operator==(Value const& v0, Value const& v1) {
    if (v0.type == Value::Type::NUMBER && v1.type == Value::Type::NUMBER)
        return v0.number == v1.number;

    if (v0.type == Value::Type::STRING && v1.type == Value::Type::STRING)
        return v0.str == v1.str;

    if (v0.type == Value::Type::ARRAY && v1.type == Value::Type::ARRAY) {
        if (v1.arr.size() != v0.arr.size())
            return false;

        auto i1 = v1.arr.begin();
        for (auto i0 = v0.arr.begin(); i0 != v0.arr.end(); ++i0, ++i1)
             if (*i0 != *i1)
                return false;
        return true;
    }

    return false;
}

bool operator!=(Value const& v0, Value const& v1) {
    return !(v0 == v1);
}

