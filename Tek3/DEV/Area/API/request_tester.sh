#!/usr/bin/env bash

curl --header "Content-Type: application/json" \
	--request POST \
	--data '{}' \
	http://localhost:8080/signup

curl --header "Content-Type: application/json" \
	--request POST \
	--data '{"username":"username", "password": "password" ,"email": "email@gmail.com"}' \
	http://localhost:8080/signup

curl --header "Content-Type: application/json" \
    --request POST \
    --data '{"username":"username","password":"password", "email": "email@gmail.com"}' \
    http://localhost:8080/login

curl --header "Content-Type: application/json" \
	--request POST \
	--data '{"id": "0"}' \
	http://localhost:8080/delete
