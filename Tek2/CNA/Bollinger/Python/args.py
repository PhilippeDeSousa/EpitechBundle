#!/usr/bin/env python3.6 
import sys
import numbers


def PrintUsage(str) : 
        print("Bollinger Bands\n\nUSAGE\t");
        print(str + " [-h] period standard_dev indexes_files index_number\n");
        print("\tperiod\t\tnumber of indexes for the moving average");
        print("\tstandard_dev\tstandard deviation coefficient to apply");
        print("\tindexes_file\tfile containing daily indexes");
        print("\tindex_number\tindex number to compute moving average and Bollinger bands\n");
        print("OPTIONS");
        print("\t-h\t\tprint the usage and quit");

def CheckArgs() : 
        if len(sys.argv) < 2 :
            sys.exit(84);
        if (sys.argv[1] == '-h') :
            if len(sys.argv) > 2 :
                sys.exit(84)
            else: 
                PrintUsage(sys.argv[0]);
                sys.exit(0);
        if len(sys.argv) != 5 :
                PrintUsage(sys.argv[0]);
                sys.exit(84);
        if sys.argv[1].isdigit() == False or sys.argv[4].isdigit() == False:
            sys.exit(84)
        try :
            float(sys.argv[2])
        except ValueError :
            sys.exit(84)