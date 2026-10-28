#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_COURSES 10
#define MIN_COURSES 5

static void clear_line(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }
}

static void print_scale(void) {
    printf("Dunii durem: 90-100=A(4), 80-89=B(3), 70-79=C(2), 60-69=D(1), 0-59=F(0)\n");
    printf("GPA = niit (kredit * grade point) / niit kredit\n\n");
}

static const char *get_letter(double score) {
    if (score >= 90 && score <= 100) return "A";
    else if (score >= 80 && score < 90) return "B";
    else if (score >= 70 && score < 80) return "C";
    else if (score >= 60 && score < 70) return "D";
    else return "F";
}

static double get_point(double score) {
    if (score >= 90 && score <= 100) return 4.0;
    else if (score >= 80 && score < 90) return 3.0;
    else if (score >= 70 && score < 80) return 2.0;
    else if (score >= 60 && score < 70) return 1.0;
    else return 0.0;
}

int main(void) {
    setlocale(LC_ALL, "");
    char subject[MAX_COURSES][50];
    char letter[MAX_COURSES][2];
    double score[MAX_COURSES], point[MAX_COURSES];
    int credit[MAX_COURSES];
    int n = 0, i, j, total_credits = 0;
    double weighted_sum = 0.0, gpa;

    printf("GOLCH DUN (GPA) TOOTSOOL\n");
    print_scale();

    do {
        printf("Hicheeliin too (5-10) oruulna uu: ");
        if (scanf("%d", &n) != 1) {
            clear_line();
            n = 0;
        }
        if (n < MIN_COURSES || n > MAX_COURSES)
            printf("Aldaa: 5-aas 10 hoorond too oruulna uu.\n");
    } while (n < MIN_COURSES || n > MAX_COURSES);

    clear_line();
    for (i = 0; i < n; i++) {
        printf("%d-r hicheeliin ner (zaigui): ", i + 1);
        if (scanf("%49s", subject[i]) != 1) {
            strcpy(subject[i], "Hicheel");
        }

        do {
            printf("Onoo (0-100) oruulna uu: ");
            if (scanf("%lf", &score[i]) != 1) {
                clear_line();
                score[i] = -1;
            }
            if (score[i] < 0 || score[i] > 100)
                printf("Aldaa: onoo 0-100 hoorond baih yostoi.\n");
        } while (score[i] < 0 || score[i] > 100);

        do {
            printf("Kredit (1-6) oruulna uu: ");
            if (scanf("%d", &credit[i]) != 1) {
                clear_line();
                credit[i] = 0;
            }
            if (credit[i] < 1 || credit[i] > 6)
                printf("Aldaa: kredit 1-6 hoorond baih yostoi.\n");
        } while (credit[i] < 1 || credit[i] > 6);

        strcpy(letter[i], get_letter(score[i]));
        point[i] = get_point(score[i]);
        total_credits += credit[i];
        weighted_sum += point[i] * credit[i];
        clear_line();
    }

    gpa = weighted_sum / total_credits;
    printf("\nDUNGIIN HUUDAS\n");
    printf("%-4s | %-18s | %6s | %-5s | %6s | %5s\n", "No", "Hicheel", "Onoo", "Useg", "Kredit", "Point");
    printf("---------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-4d | %-18s | %6.2f | %-5s | %6d | %5.2f\n",
               i + 1, subject[i], score[i], letter[i], credit[i], point[i]);
    }
    printf("Niit kredit: %d\n", total_credits);
    printf("Credit-weighted GPA: %.2f\n", gpa);
    if (gpa >= 3.5 && gpa <= 4.0) printf("GPA angilal: Mash sain\n");
    else if (gpa >= 3.0 && gpa < 3.5) printf("GPA angilal: Sain\n");
    else if (gpa >= 2.0 && gpa < 3.0) printf("GPA angilal: Dund\n");
    else printf("GPA angilal: Sain bolgoh shaardlagatai\n");

    /* Sort all course details together by numeric score, descending. */
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (score[j] > score[i]) {
                double temp_score = score[i]; score[i] = score[j]; score[j] = temp_score;
                double temp_point = point[i]; point[i] = point[j]; point[j] = temp_point;
                int temp_credit = credit[i]; credit[i] = credit[j]; credit[j] = temp_credit;
                char temp_letter[2]; strcpy(temp_letter, letter[i]); strcpy(letter[i], letter[j]); strcpy(letter[j], temp_letter);
                char temp_subject[50]; strcpy(temp_subject, subject[i]); strcpy(subject[i], subject[j]); strcpy(subject[j], temp_subject);
            }
        }
    }

    printf("\nHAMGIIN UNDUR 3 DUN (onoogoor)\n");
    printf("%-18s | %6s | %-5s\n", "Hicheel", "Onoo", "Useg");
    printf("-------------------------------------\n");
    for (i = 0; i < 3; i++) {
        printf("%-18s | %6.2f | %-5s\n", subject[i], score[i], letter[i]);
    }
    return 0;
}
