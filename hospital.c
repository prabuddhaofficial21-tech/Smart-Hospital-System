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

void initializeSystem(void) {
    loadBedsFromFile();
}

void displayMenu(void) {
    printf("\n");
    printf("\n");
    printf("=========================================================\n");
    printf("       SMART HOSPITAL & RESOURCE ALLOCATION SYSTEM\n");
    printf("=========================================================\n");
    printf("  [1] Register New Patient\n");
    printf("  [2] View Bed Occupancy Matrix\n");
    printf("  [3] View Emergency Triage Queue\n");
    printf("  [4] Generate Performance Reports\n");
    printf("  [5] Save System Data & Exit\n");
    printf("---------------------------------------------------------\n");
    printf("  > Please select an option (1-5): ");
}

void registerPatient(void) {
    if (patient_count >= MAX_PATIENTS) {
        printf("\n  [!] System is currently at maximum patient capacity.\n");
        return;
    }
    int i = patient_count;

    printf("\n=========================================================\n");
    printf("                  PATIENT REGISTRATION\n");
    printf("=========================================================\n");

    printf("  > Full Name: ");
    scanf(" %[^\n]s", p_names[i]);

    printf("  > Age (Years): ");
    scanf("%d", &p_ages[i]);

    printf("\n  --- Triage Assessment ---\n");
    printf("  [1] Normal\n  [2] Urgent\n  [3] Critical\n");
    printf("  > Select Urgency Level (1-3): ");
    scanf("%d", &p_urgency[i]);

    printf("\n  --- Department Routing ---\n");
    printf("  [1] General Practice (OPD)\n  [2] Paediatrics\n");
    printf("  [3] Cardiology\n  [4] Neurology\n");
    printf("  > Select Specialty ID (1-4): ");
    scanf("%d", &p_spec[i]);

    printf("\n  --- Ward Admission ---\n");
    int isAdmitted;
    printf("  > Does the patient require ward admission? (1=Yes, 0=No): ");
    scanf("%d", &isAdmitted);

    int allocated_bed = -1;
    if (isAdmitted == 1) {
        printf("  [1] General Ward\n  [2] Paediatric Ward\n");
        printf("  [3] Surgical Ward\n  [4] ICU\n");
        printf("  > Select Ward ID (1-4): ");
        scanf("%d", &p_ward[i]);
        printf("  > Estimated Days Admitted: ");
        scanf("%d", &p_days[i]);

        int w_idx = p_ward[i] - 1;
        for (int b = 0; b < WARD_CAPACITIES[w_idx]; b++) {
            if (bedOccupancy[w_idx][b] == 0) {
                bedOccupancy[w_idx][b] = 1;
                allocated_bed = b + 1;
                break;
            }
        }
        if (allocated_bed == -1) {
            printf("\n  [!] Warning: No beds currently available in %s.\n", WARD_NAMES[w_idx]);
        } else {
            printf("\n  [+] Successfully allocated Bed #%02d in %s.\n", allocated_bed, WARD_NAMES[w_idx]);
        }
    } else {
        p_ward[i] = 0;
        p_days[i] = 0;
    }

    int s_idx = p_spec[i] - 1;
    float base_fee = BASE_FEES[s_idx];
    float surcharge = 0.0;
    int surcharge_pct = 0;

    if (p_urgency[i] == 2) { surcharge = base_fee * 0.20; surcharge_pct = 20; }
    else if (p_urgency[i] == 3) { surcharge = base_fee * 0.50; surcharge_pct = 50; }

    float ward_cost = (p_ward[i] > 0) ? (p_days[i] * WARD_RATES[p_ward[i] - 1]) : 0.0;
    p_gross[i] = base_fee + surcharge + ward_cost;


