#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os;

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

print bcolors.OKGREEN + "========> Validating [dataset.xml]" + bcolors.ENDC;
os.system("xmllint dataset.xml --schema ../resources/dataset.xsd | grep 'dataset\.xml'")


print bcolors.OKGREEN + "========> Validating [test.xml]" + bcolors.ENDC;
os.system("xmllint test.xml --schema ../resources/t2fit.xsd | grep 'test.xml'")
