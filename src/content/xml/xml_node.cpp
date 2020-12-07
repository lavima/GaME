#include <string>
#include <memory>

#include <pugixml.hpp>

#include "../../global.h"
#include "xml_range.h"
#include "xml_attribute.h"
#include "xml_node.h"

namespace game::content::xml {

    using namespace pugi;

    XmlNode::XmlNode() : internal_(xml_node()) {}
    XmlNode::XmlNode(pugi::xml_node node) : internal_(node) {}

    const std::string XmlNode::GetName() const { return std::string(internal_.name()); }
    void XmlNode::SetName(const std::string& name) { internal_.set_name(name.c_str()); }

    const std::string XmlNode::GetValue() const { return std::string(internal_.child_value()); }
    void XmlNode::SetValue(const std::string& value) { internal_.first_child().set_value(value.c_str()); }

    XmlNode XmlNode::AddChild() {
        return XmlNode(internal_.append_child());
    }

    XmlNode XmlNode::AddChild(const std::string& name) {
        return XmlNode(internal_.append_child(name.c_str()));
    }

    bool XmlNode::HasChild(const std::string& name) {
        return !internal_.child(name.c_str()).empty();
    }

    XmlNode XmlNode::GetChild(const std::string& name) {
        return XmlNode(internal_.child(name.c_str()));
    }

    XmlRange<XmlNode::Iterator> XmlNode::GetChildren() {
        return XmlRange<XmlNode::Iterator>(XmlNode::Iterator(internal_.first_child()), XmlNode::Iterator(xml_node()));
    }

    XmlRange<XmlNode::NamedIterator> XmlNode::GetChildren(const std::string& name) {
        return XmlRange<XmlNode::NamedIterator>(XmlNode::NamedIterator(internal_.child(name.c_str()), name), XmlNode::NamedIterator(xml_node(), name));
    }

    XmlAttribute XmlNode::AddAttribute(const std::string& name) {
        return XmlAttribute(internal_.append_attribute(name.c_str()));
    }

    XmlAttribute XmlNode::GetAttribute(const std::string& name) {
        return XmlAttribute(internal_.attribute(name.c_str()));
    }

    XmlRange<XmlAttribute::Iterator> XmlNode::GetAttributes() {
        return XmlRange<XmlAttribute::Iterator>(XmlAttribute::Iterator(internal_.first_attribute()), XmlAttribute::Iterator(xml_attribute()));
    }

    bool XmlNode::operator!() const {
        return internal_.empty();
    }

    XmlNode::operator bool() const {
        return !internal_.empty();
    }


    XmlNode::Iterator::Iterator(pugi::xml_node node) : node_(node) {}

    XmlNode::Iterator XmlNode::Iterator::operator++() {
        node_ = node_.next_sibling();
        return *this;
    }

    bool XmlNode::Iterator::operator!=(const Iterator& other) const {
        return node_!=other.node_;
    }

    const XmlNode XmlNode::Iterator::operator*() const {
        return XmlNode(node_);
    }

    XmlNode::NamedIterator::NamedIterator(pugi::xml_node node_, const std::string& name) : node_(node_), name_(name) {}

    XmlNode::NamedIterator XmlNode::NamedIterator::operator++() {
        node_ = node_.next_sibling(name_.c_str());
        return *this;
    }

    bool XmlNode::NamedIterator::operator!=(const NamedIterator& other) const {
        return node_!=other.node_;
    }

    const XmlNode XmlNode::NamedIterator::operator*() const {
        return XmlNode(node_);
    }

}
