#!/bin/python3
import sys
import statistics as stats

# open files

# anaylze file

explored_data = []
created_data = []
max_depth_data = []

def analyze_file(filename):
    f = open(filename)

    lines = f.readlines()

    e_i = 0
    c_i = 0
    d_i = 0

    for line in lines:
        if line.startswith("explored"):
            num = int(line.split(' ')[1]) / 1000000
            if len(explored_data) <= e_i:
                explored_data.append([num])
            else:
                explored_data[e_i].append(num)
            e_i += 1
        elif line.startswith("created"):
            num = int(line.split(' ')[1]) / 1000000
            if len(created_data) <= c_i:
                created_data.append([num])
            else:
                created_data[c_i].append(num)
            c_i += 1
        elif line.startswith("max depth"):
            num = int(line.split(' ')[2])
            if len(max_depth_data) <= d_i:
                max_depth_data.append([num])
            else:
                max_depth_data[d_i].append(num)
            d_i += 1

    f.close()

def get_stats(i):
    stat = [0]*6
    stat[0] = stats.mean(explored_data[i])
    stat[2] = stats.mean(created_data[i])
    stat[4] = stats.mean(max_depth_data[i])
    if len(explored_data[i]) != 1:
        stat[1] = stats.stdev(explored_data[i])
        stat[3] = stats.stdev(created_data[i])
        stat[5] = stats.stdev(max_depth_data[i])

    return tuple(stat)

def main(args):
    for f in args:
        analyze_file(f)

    print("explore,explore stdev,create,create stdev,depth,depth stdev")

    #print(explored_data)
    #print(created_data)
    #print(max_depth_data)
    for i in range(len(explored_data)):
        i_stat = get_stats(i)
        print("{},{},{},{},{},{}".format(i_stat[0],i_stat[1],i_stat[2],i_stat[3],i_stat[4],i_stat[5]))

main(sys.argv[1:])
