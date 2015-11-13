#!/bin/bash
cat input.txt | mpiexec -np 2 ./temperature # alternativamente: -np NUMBER_PROCESS