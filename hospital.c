#include "hospital.h"

// Lookup Table Initializations
const float BASE_FEES[NUM_SPECIALTIES] = {1500.0, 2500.0, 4500.0, 5000.0};
const int CONSULT_TIMES[NUM_SPECIALTIES] = {15, 20, 30, 30};
const float WARD_RATES[NUM_WARDS] = {3000.0, 6000.0, 12000.0, 25000.0};
const int WARD_CAPACITIES[NUM_WARDS] = {20, 10, 10, 5};

const char* SPEC_NAMES[NUM_SPECIALTIES] = {"General Practice (OPD)", "Paediatrics", "Cardiology", "Neurology"};
const char* WARD_NAMES[NUM_WARDS] = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU"};

