#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_MEDICATIONS 5 // Her hasta için en fazla 5 ilaç
#define PRESCRIPTION_PREFIX "RX-"

typedef struct {
    char name[50];
    int dose;
    char unit[10];
} Medication;

typedef struct {
    char message_type[10];
    char patient_id[20];
    char name[50];
    int age;
    char gender[10];
    char condition[100];
    int priority;
    char prescription_id[20]; // Reçete ID
    Medication medications[MAX_MEDICATIONS];
    int medication_count;
} HL7_Patient;

HL7_Patient patients[MAX_PATIENTS];
int patient_count = 0;
int prescription_counter = 1000;

void generate_hl7_id(char *buffer, int id) {
    sprintf(buffer, "hasta-%04d", id); // %04d ile 4 haneli sayý
}

void generate_prescription_id(char *buffer) {
    sprintf(buffer, "%s%d", PRESCRIPTION_PREFIX, prescription_counter++);
}

void add_patient() {
    if (patient_count >= MAX_PATIENTS) {
        printf("Hasta kapasitesi doldu!\n");
        return;
    }

    HL7_Patient p;
    strcpy(p.message_type, "ADT^A01");
    generate_hl7_id(p.patient_id, patient_count + 1);

    printf("Hasta Adý: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Yaþ: ");
    scanf("%d", &p.age);
    getchar();

    printf("Cinsiyet (Erkek/Kadýn): ");
    fgets(p.gender, sizeof(p.gender), stdin);
    p.gender[strcspn(p.gender, "\n")] = 0;

    printf("Hastalýk Durumu: ");
    fgets(p.condition, sizeof(p.condition), stdin);
    p.condition[strcspn(p.condition, "\n")] = 0;

    printf("Öncelik (1-5): ");
    scanf("%d", &p.priority);
    getchar();

    generate_prescription_id(p.prescription_id); // Reçete numarasý üret

    p.medication_count = 0;
    printf("Hasta baþarýyla eklendi! Hasta ID: %s, Reçete No: %s\n", p.patient_id, p.prescription_id);

    patients[patient_count++] = p;
}

void add_medication() {
    char patient_id[20];
    printf("Ýlaç eklemek istediðiniz hasta ID'sini girin: ");
    scanf("%s", patient_id);
    getchar();

    for (int i = 0; i < patient_count; i++) {
        if (strcmp(patients[i].patient_id, patient_id) == 0) {
            if (patients[i].medication_count >= MAX_MEDICATIONS) {
                printf("Bu hastaya daha fazla ilaç eklenemez!\n");
                return;
            }

            Medication med;
            printf("Ýlaç Adý: ");
            fgets(med.name, sizeof(med.name), stdin);
            med.name[strcspn(med.name, "\n")] = 0;

            printf("Dozaj (Sayý olarak girin): ");
            scanf("%d", &med.dose);
            getchar();

            printf("Doz Birimi (mg/ml vb.): ");
            fgets(med.unit, sizeof(med.unit), stdin);
            med.unit[strcspn(med.unit, "\n")] = 0;

            patients[i].medications[patients[i].medication_count++] = med;
            printf("Ýlaç eklendi: %s - %d %s\n", med.name, med.dose, med.unit);
            return;
        }
    }
    printf("Hasta bulunamadý!\n");
}

void list_patients() {
    printf("\nHastalar Listesi:\n");
    for (int i = 0; i < patient_count; i++) {
        printf("\nID: %s | Ad: %s | Yaþ: %d | Cinsiyet: %s | Durum: %s | Öncelik: %d | Reçete No: %s\n",
               patients[i].patient_id, patients[i].name, patients[i].age, patients[i].gender,
               patients[i].condition, patients[i].priority, patients[i].prescription_id);

        if (patients[i].medication_count > 0) {
            printf(" Reçete Ýçeriði:\n");
            for (int j = 0; j < patients[i].medication_count; j++) {
                printf("    - %s (%d %s)\n",
                       patients[i].medications[j].name,
                       patients[i].medications[j].dose,
                       patients[i].medications[j].unit);
            }
        }
    }
}

void process_emergency() {
    if (patient_count == 0) {
        printf("Acil serviste bekleyen hasta yok!\n");
        return;
    }

    int highest_priority_index = 0;
    for (int i = 1; i < patient_count; i++) {
        if (patients[i].priority < patients[highest_priority_index].priority) {
            highest_priority_index = i;
        }
    }

    HL7_Patient treated_patient = patients[highest_priority_index];
    printf(" Acil servis hastasý iþleniyor: %s | Öncelik: %d | Reçete No: %s\n",
           treated_patient.name, treated_patient.priority, treated_patient.prescription_id);

    for (int i = highest_priority_index; i < patient_count - 1; i++) {
        patients[i] = patients[i + 1];
    }
    patient_count--;
}

int main() {
    int choice;
    do {
        printf("\nHastane Yönetim Sistemi\n");
        printf("1. Hasta Ekle\n");
        printf("2. Hastalarý Listele\n");
        printf("3. Ýlaç Ekle\n");
        printf("4. Acil Servis Hastasýný Ýþle\n");
        printf("0. Çýkýþ\n");
        printf("Seçiminiz: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                add_patient();
                break;
            case 2:
                list_patients();
                break;
            case 3:
                add_medication();
                break;
            case 4:
                process_emergency();
                break;
            case 0:
                printf("Çýkýþ yapýlýyor...\n");
                break;
            default:
                printf("Geçersiz seçim!\n");
        }
    } while (choice != 0);

    return 0;
}
