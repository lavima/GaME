#include "../../GaME.h"

using namespace pugi;

XmlDocument::XmlDocument() : internal_(unique_ptr<xml_document>(new xml_document())) {}

XmlDocument::XmlDocument(XmlDocument& other) {
    internal_.reset(other.internal_.release());
}

bool XmlDocument::Load(const string& filename) {
   
    xml_parse_result result = internal_->load_file(filename.c_str());
    if (!result)
        return false;

    return true;

}

bool XmlDocument::Save(const string& filename) {
    return internal_->save_file(filename.c_str());
}

XmlNode XmlDocument::GetDocumentElement() {
    return XmlNode(internal_->document_element());
}
