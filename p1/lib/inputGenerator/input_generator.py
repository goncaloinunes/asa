import sys
import random
import pathlib
import os
import subprocess
import io
from timeit import default_timer as timer
import csv


DOCS_FOLDER = r"../../docs/analysis/"
EXECUTABLE_PATH = r"../../project"
INPUT_FOLDER = r"generatedInputs/"
FILENAME = "input"
MINIMUM_INPUT_SIZE = 1000
MAXIMUN_INPUT_SIZE = 50_000
STEP = 1000
INPUTS_PER_SIZE = 1

RANGE_RANDOM_NUMBER = 2_048


def generateInputs(problem):

    os.system("rm -r " + INPUT_FOLDER + "*")

    print("Generating Inputs...")

    for i in range(MINIMUM_INPUT_SIZE, MAXIMUN_INPUT_SIZE+1, STEP):
        for j in range(INPUTS_PER_SIZE):
             with open(INPUT_FOLDER + FILENAME  + "_" + str(problem) + "_" + str(i) + "_" + str(j), "w") as file:
                 file.write(f"{problem}\n")
                 for w in range(i):
                     number = random.randint(-RANGE_RANDOM_NUMBER, RANGE_RANDOM_NUMBER)
                     file.write(f"{number} ")

    print("Generation completed!")


def calculateTime():

    header = ['Input Size', 'Time']
    data = []


    for file in sorted([(os.path.getctime(INPUT_FOLDER + str(x)),x) for x in os.listdir(INPUT_FOLDER)]):
        filename = str(file[1])
        print(filename)
        
        input_size = filename.split("_")[2]
        start = timer()
        os.system(EXECUTABLE_PATH + " < " + INPUT_FOLDER + filename + r" > /dev/null")
        end = timer()
        
        elaped_time = (end- start)

        data.append([input_size, elaped_time])

        print(f"{elaped_time} seconds\n")


    with open(DOCS_FOLDER + 'perfomance.csv', 'w', encoding='UTF8', newline='') as file:
        writer = csv.writer(file)

        # write the header
        writer.writerow(header)

        # write multiple rows
        writer.writerows(data)


        
        




def main():
    pathlib.Path(INPUT_FOLDER).mkdir(parents=True, exist_ok=True)
    pathlib.Path(DOCS_FOLDER).mkdir(parents=True, exist_ok=True)

    if(len(sys.argv) > 1):
        if(type(sys.argv[1] == int)):
            problem = sys.argv[1]
            generateInputs(problem)
            calculateTime()
    

        

if __name__ == "__main__":
    main()