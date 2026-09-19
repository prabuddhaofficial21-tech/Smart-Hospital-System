#include "hospital.h"

// Lookup Table Initializations
const float BASE_FEES[NUM_SPECIALTIES] = {1500.0, 2500.0, 4500.0, 5000.0};
const int CONSULT_TIMES[NUM_SPECIALTIES] = {15, 20, 30, 30};
const float WARD_RATES[NUM_WARDS] = {3000.0, 6000.0, 12000.0, 25000.0};
const int WARD_CAPACITIES[NUM_WARDS] = {20, 10, 10, 5};

const char* SPEC_NAMES[NUM_SPECIALTIES] = {"General Practice (OPD)", "Paediatrics", "Cardiology", "Neurology"};
const char* WARD_NAMES[NUM_WARDS] = {"General Ward", "Paediatric Ward", "Surgical Ward", "ICU"};

// Array Definitions
char p_names[MAX_PATIENTS][50];
int p_ages[MAX_PATIENTS], p_urgency[MAX_PATIENTS], p_spec[MAX_PATIENTS];
int p_ward[MAX_PATIENTS], p_days[MAX_PATIENTS];
float p_gross[MAX_PATIENTS], p_discount[MAX_PATIENTS], p_final[MAX_PATIENTS];

int patient_count = 0;
int spec_queue[NUM_SPECIALTIES] = {0};
int bedOccupancy[NUM_WARDS][20] = {0};
