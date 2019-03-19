#! /bin/bash

conan_update() {
    conan remote add $1 https://api.bintray.com/conan/$1/public-conan ||
        conan remote update $1 https://api.bintray.com/conan/$1/public-conan
}

add_repo() {
    conan_update conan-center
    conan_update epitech
    conan_update bincrafters
}

mkdir build; cd build && conan install --build=missing .. || add_repo && cmake .. -G "Unix Makefiles" && cmake –build . && make
