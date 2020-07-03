#include "../../GaME.h"

using namespace pugi;

XmlAttribute::XmlAttribute() {}

XmlAttribute::XmlAttribute(pugi::xml_attribute attribute) : internal_(attribute) {}

const string XmlAttribute::GetName() { return string(internal_.name()); }

void XmlAttribute::SetName(const string& name) { internal_.set_name(name.c_str()); }

const string XmlAttribute::GetValue() { return string(internal_.value()); }

void XmlAttribute::SetValue(const string& value) { internal_.set_value(value.c_str()); }

bool XmlAttribute::operator!() {
    return internal_.empty();
}


XmlAttribute::Iterator::Iterator(xml_attribute attribute) : attribute_(attribute) {}

XmlAttribute::Iterator XmlAttribute::Iterator::operator++() {
    attribute_ = attribute_.next_attribute();
    return *this;
}
bool XmlAttribute::Iterator::operator!=(const Iterator& other) const {
    return attribute_ != other.attribute_;
}
const XmlAttribute XmlAttribute::Iterator::operator*() const {
    return XmlAttribute(attribute_);
}