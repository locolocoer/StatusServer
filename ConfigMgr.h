#pragma once
#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
class Section {
public:
	Section(boost::property_tree::ptree pt);
	Section() = default;
	std::map<std::string, std::string> _section_data;
	std::string operator[](const std::string& sec_key);
};

class ConfigMgr
{
public:
	Section operator[](const std::string& key);
	static ConfigMgr& Inst();
private:
	static ConfigMgr *inst;
	ConfigMgr();
	std::map<std::string, Section> _sections;
};

