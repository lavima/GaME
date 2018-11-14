/*
File: PugiXML.h
Author: Lars Vidar Magnusson
*/

#pragma once

class PugiXML {
private:
  
  static Log *log;

public:
  
  static void Initialize(Engine &engine);
  static pugi::xml_document *ParseDocument(const std::string &filename);

};
