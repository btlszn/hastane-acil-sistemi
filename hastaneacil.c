#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_MEDICATIONS 5 // Her hasta i�in en fazla 5 ila�
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
    char prescription_id[20]; // Re�ete ID
    Medication medications[MAX_MEDICATIONS];
    int medication_count;
} HL7_Patient;

HL7_Patient patients[MAX_PATIENTS];
int patient_count = 0;
int prescription_counter = 1000;

void generate_hl7_id(char *buffer, int id) {
    sprintf(buffer, "hasta-%04d", id); // %04d ile 4 haneli say�
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

    printf("Hasta Ad�: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Ya�: ");
    scanf("%d", &p.age);
    getchar();

    printf("Cinsiyet (Erkek/Kad�n): ");
    fgets(p.gender, sizeof(p.gender), stdin);
    p.gender[strcspn(p.gender, "\n")] = 0;

    printf("Hastal�k Durumu: ");
    fgets(p.condition, sizeof(p.condition), stdin);
    p.condition[strcspn(p.condition, "\n")] = 0;

    printf("�ncelik (1-5): ");
    scanf("%d", &p.priority);
    getchar();

    generate_prescription_id(p.prescription_id); // Re�ete numaras� �ret

    p.medication_count = 0;
    printf("Hasta ba�ar�yla eklendi! Hasta ID: %s, Re�ete No: %s\n", p.patient_id, p.prescription_id);

    patients[patient_count++] = p;
}

void add_medication() {
    char patient_id[20];
    printf("�la� eklemek istedi�iniz hasta ID'sini girin: ");
    scanf("%s", patient_id);
    getchar();

    for (int i = 0; i < patient_count; i++) {
        if (strcmp(patients[i].patient_id, patient_id) == 0) {
            if (patients[i].medication_count >= MAX_MEDICATIONS) {
                printf("Bu hastaya daha fazla ila� eklenemez!\n");
                return;
            }

            Medication med;
            printf("�la� Ad�: ");
            fgets(med.name, sizeof(med.name), stdin);
            med.name[strcspn(med.name, "\n")] = 0;

            printf("Dozaj (Say� olarak girin): ");
            scanf("%d", &med.dose);
            getchar();

            printf("Doz Birimi (mg/ml vb.): ");
            fgets(med.unit, sizeof(med.unit), stdin);
            med.unit[strcspn(med.unit, "\n")] = 0;

            patients[i].medications[patients[i].medication_count++] = med;
            printf("�la� eklendi: %s - %d %s\n", med.name, med.dose, med.unit);
            return;
        }
    }
    printf("Hasta bulunamad�!\n");
}

void list_patients() {
    printf("\nHastalar Listesi:\n");
    for (int i = 0; i < patient_count; i++) {
        printf("\nID: %s | Ad: %s | Ya�: %d | Cinsiyet: %s | Durum: %s | �ncelik: %d | Re�ete No: %s\n",
               patients[i].patient_id, patients[i].name, patients[i].age, patients[i].gender,
               patients[i].condition, patients[i].priority, patients[i].prescription_id);

        if (patients[i].medication_count > 0) {
            printf(" Re�ete ��eri�i:\n");
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
    printf(" Acil servis hastas� i�leniyor: %s | �ncelik: %d | Re�ete No: %s\n",
           treated_patient.name, treated_patient.priority, treated_patient.prescription_id);

    for (int i = highest_priority_index; i < patient_count - 1; i++) {
        patients[i] = patients[i + 1];
    }
    patient_count--;
}

int main() {
    int choice;
    do {
        printf("\nHastane Y�netim Sistemi\n");
        printf("1. Hasta Ekle\n");
        printf("2. Hastalar� Listele\n");
        printf("3. �la� Ekle\n");
        printf("4. Acil Servis Hastas�n� ��le\n");
        printf("0. ��k��\n");
        printf("Se�iminiz: ");
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
                printf("��k�� yap�l�yor...\n");
                break;
            default:
                printf("Ge�ersiz se�im!\n");
        }
    } while (choice != 0);

    return 0;
}
