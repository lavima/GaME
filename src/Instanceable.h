/*
File: Instanceable.h
Author: Lars Vidar Magnusson
*/

#pragma once

class __Instanceable {
private:

    static uint64_t instanceCounter;
    uint_fast64_t instanceId;

    string typeName;
    uint_fast64_t typeHash;

protected:

    __Instanceable(const string &typeName);

public:

    const string &GetTypeName() const;

    bool operator==(const __Instanceable &other);

};
