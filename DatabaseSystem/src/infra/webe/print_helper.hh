#ifndef INFRA_WEBE_PRINT_HEADER_HH
#define INFRA_WEBE_PRINT_HEADER_HH

#include "common.hh"
#include "types.hh"
#include "infra/moer/system.hh"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>

void print_header(std::ostream& aOutput, std::string aHeaderName, int aWidth = 80);

void print_sep(std::ostream& aOutput, int aTot = 80);

double round(double d);

std::string fFormatNumber(int number);

std::string getEnumAsString(int aValue, bool aFlag);

void print_bulk_load_insert_result(const string_vt& aRelationNames, const double_vt& aMeasurementData, const bool aFlag, const std::string aTestType = "Unknown");

void print_scan_result(const size_t aAttrNo, const double_vt& aMeasurementData, const std::string aTestType = "Unknown");

void print_projection_result(const size_t aAttrNo, const double_vt& aMeasurementData, const std::string aTestType = "Unknown");

#endif