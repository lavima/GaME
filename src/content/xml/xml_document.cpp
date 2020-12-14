#include <string>
#include <memory>

#include <pugixml.hpp>

#include "../../global.h"
#include "xml_range.h"
#include "xml_attribute.h"
#include "xml_node.h"
#include "xml_document.h"

namespace game::content::xml {

    using namespace pugi;

    XmlDocument::XmlDocument() : internal_(std::unique_ptr<xml_document>(new xml_document())) {}
    XmlDocument::~XmlDocument() {}

    XmlDocument::XmlDocument(XmlDocument& other) {
        internal_.reset(other.internal_.release());
    }

    bool XmlDocument::Load(const std::string& filename) {

        xml_parse_result result = internal_->load_file(filename.c_str());
        if (!result)
            return false;

        return true;

    }

    bool XmlDocument::Save(const std::string& filename) {
        return internal_->save_file(filename.c_str());
    }

    void XmlDocument::Unload() {
        internal_.reset();
    }

    XmlNode XmlDocument::GetDocumentElement() {
        return XmlNode(internal_->document_element());
    }

}
