#!/bin/bash
cat input.txt | mpiexec -np 5 ./temperature # alternativamente: -np NUMBER_PROCESS