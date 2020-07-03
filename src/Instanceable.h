/*
File: Instanceable.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Instanceable {
private:

    static uint64_t instance_counter_;
    static unordered_map<uint_fast64_t, string> hash_typename_;

    uint_fast64_t instance_id_;

    uint_fast64_t type_hash_;

protected:

    Instanceable(const string &type_name);

public:

    const string &GetTypeName() const;

    bool operator==(const Instanceable &other);

};
