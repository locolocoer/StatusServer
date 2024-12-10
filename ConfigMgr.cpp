#include "ConfigMgr.h"
#include <iostream>
Section ConfigMgr::operator[](const std::string& key)
{
	return _sections[key];
}
ConfigMgr& ConfigMgr::Inst()
{
	if (inst == nullptr) {
		inst = new ConfigMgr();
	}
	return *inst;
}
ConfigMgr::ConfigMgr()
{
	auto currentPath = boost::filesystem::current_path();
	auto iniPath = currentPath / "config.ini";
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(iniPath.string(), pt);
	for (const auto &sec : pt) {
		_sections[sec.first] = Section(sec.second);
	}
	for (const auto& sec : _sections) {
		std::cout << "[" << sec.first << "]" << std::endl;
		for (const auto& data : sec.second._section_data) {
			std::cout << data.first << ":" << data.second << std::endl;
		}
	}
}

Section::Section(boost::property_tree::ptree pt)
{
	for (const auto& data : pt) {
		_section_data[data.first] = data.second.get_value<std::string>();
	}
}

std::string Section::operator[](const std::string& sec_key)
{
	return _section_data[sec_key];
}


ConfigMgr* ConfigMgr::inst = nullptr;