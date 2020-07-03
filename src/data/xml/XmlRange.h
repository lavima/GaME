#pragma once

template<typename I> class XmlRange {
private:

    I begin_;
    I end_;

public:

    XmlRange(I begin, I end) : begin_(begin), end_(end) {}

    I begin() { return begin_; }
    I end() { return end_; }

};