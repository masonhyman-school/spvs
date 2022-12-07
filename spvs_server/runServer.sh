#!/bin/bash
cd ../spvs_cli/;
make clean;
make;
cd ../spvs_server/;
node app.js
