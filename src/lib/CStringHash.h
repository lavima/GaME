/*
File: CStringHash.h
Author: Lars Vidar Magnusson
*/

#pragma once

struct CStringHash {

  inline size_t operator()(const char* s) const {

    unsigned long hash = 0;
    for (; *s; ++s)
      hash = 5 * hash + *s;
    return size_t(hash);

  }

};

struct CStringCompare {

  inline bool operator()(const char *s1, const char *s2) const {
    return !strcmp(s1, s2);
  }

};