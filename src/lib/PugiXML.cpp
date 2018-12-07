/*
File: PugiXML.cpp
Author: Lars Vidar Magnusson
*/

#include "../GaME.h"

using namespace pugi;

Log *PugiXML::log = nullptr;

void PugiXML::Initialize(Engine &engine) {

    log = &engine.GetLog();

}

pugi::xml_document *PugiXML::ParseDocument(const string &filename) {

    xml_document *doc = new xml_document();
    xml_parse_result result = doc->load_file(filename.c_str());
    if (!result) {
        log->AddEvent(EVENT_ERROR, "Could not load XML file %s", filename);
        return nullptr;    
    }

    return doc;

}
