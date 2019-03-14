#! /bin/bash

ID=$(docker ps -aqf "name=dev_dashboard_2018_node_app")
docker exec -it ${ID} ip addr
