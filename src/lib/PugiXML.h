/*
File: PugiXML.h
Author: Lars Vidar Magnusson
*/

#pragma once

class Engine;

class PugiXML {
private:
  
  static Log *log;

public:
  
  static void Initialize(Engine &engine);
  static pugi::xml_document *ParseDocument(const std::string &filename);

};
