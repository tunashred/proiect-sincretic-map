# Proiect sincretic MAP - Tower of Hanoi

We have three rods(A, B, C) and N disks. All the disks have various diameters and can slide onto any rod. The problem begins with all the disks stacked on rod **'A'** in order of increasing size from bottom to top. The goal of the problem is to move the entire stack to one of the other rods, having the following rules:
1. Only one disk may be moved at a time.
2. A disk may be placed only on top of a bigger disk.

# Local Build and Run
To build and run the project locally, follow these steps:
1. Build the Docker image:
```docker build -t hanoi -f Dockerfile .```
2. Run the Docker container:
```docker run hanoi:latest <optional: disk number, default is 3>```

# Docker Build Configuration
The file ```docker-build.yml``` is a ```GitHub Actions workflow``` for building and pushing a Docker image to ```Docker Hub``` when changes are made to the main branch. The workflow includes the following steps:
1. **Checkout**: Checks out the repository.
2. **Login to Docker Hub**: Logs in to ```Docker Hub``` using the specified credentials.
3. **Build with Makefile**: Executes the ```Makefile``` located at ```./src/makefile```.
4. **Set up Docker Buildx**: Sets up ```Docker Buildx```.
5. **Build and push**: Builds the ```Docker image``` using the specified ```Dockerfile```.

```
name: Docker Build

on:
    push:
        branches:
            - "main"

jobs:
    build:
        runs-on: ubuntu-latest
        steps:
        - name: Checkout
          uses: actions/checkout@v4
        - name: Login to Docker Hub
          uses: docker/login-action@v3
          with:
              username: ${{ secrets.DOCKERHUB_USERNAME }}
              password: ${{ secrets.DOCKERHUB_PASSWORD }}
        - name: Build with Makefile
          run: make -f ./src/makefile
        - name: Set up Docker Buildx
          uses: docker/setup-buildx-action@v3
        - name: Build and push
          uses: docker/build-push-action@v5
          with:
              context: .
              file: ./Dockerfile
              push: true
              tags: ${{ secrets.DOCKERHUB_USERNAME }}/proiect-sincretic:latest
```

# Dockerfile
The ```Dockerfile``` file is based on the ```busybox``` image.
1. Copies the compiled ```hanoi``` executable into the image.
2. Sets the executable permission.
3. Specifies the default command to run the program.
```
FROM busybox:latest

COPY src/hanoi .
RUN chmod +x hanoi

ENTRYPOINT ["./hanoi"]
CMD ["3"]
```

# Source Code
The ```source.c``` contains the C source code for solving the Tower of Hanoi problem. It defines a recursive function **'hanoi'** and it's called in **'main'** using the arguments passed through command line.
```
#include <stdio.h>
#include <stdlib.h>

void hanoi(int nr_discuri_pe_sursa, char sursa, char destinatie, char intermediar) {
    if(nr_discuri_pe_sursa == 0) {
        return;
    }

    hanoi(nr_discuri_pe_sursa - 1, sursa, intermediar, destinatie);
    printf("Muta discul #%d de pe '%c' pe '%c'.\n", nr_discuri_pe_sursa, sursa, destinatie);
    hanoi(nr_discuri_pe_sursa - 1, intermediar, destinatie, sursa);
}

int main(int argc, char *argv[]) {
    int nr_discuri = atoi(argv[1]);
    if(argv[2]) {
        nr_discuri = atoi(argv[2]);
    }
    hanoi(nr_discuri, 'A', 'C', 'B');

    return 0;
}
```

# Makefile
The ```makefile``` file includes the compilation rules for the source code and it creates the **'hanoi'** executable.
```
hanoi: source.o
	gcc -o hanoi source.o

source.o: src/source.c
	gcc -c src/source.c -o source.o
```
Preview:
```
$ make -f src/makefile
gcc -c src/source.c -o source.o
gcc -o hanoi source.o
```

Also, it contains a ```clean target``` which removes the generated files. 

```
.PHONY: clean
clean:
	rm -f hanoi source.o
```
Preview:
```
$ make clean
rm -f hanoi source.o
```
