#!/bin/bash

echo Removeing orphaned images without tags...
docker images | grep "<none" | awk '{print $3}'| xargs docker rmi -f 
