#include <stdio.h>

void hanoi(int nr_discuri_pe_sursa, char sursa, char destinatie, char intermediar) {
    if(nr_discuri_pe_sursa == 0) {
        return;
    }

    hanoi(nr_discuri_pe_sursa - 1, sursa, intermediar, destinatie);

    printf("Muta discul #%d de pe '%c' pe '%c'.\n", nr_discuri_pe_sursa, sursa, destinatie);

    hanoi(nr_discuri_pe_sursa - 1, intermediar, destinatie, sursa);
}

int main() {
    hanoi(2, 'A', 'B', 'C');

    return 0;
}
