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
GENERATOR = r"randGeneoTree"
MINIMUM_INPUT_SIZE = 0
MAXIMUN_INPUT_SIZE = 4_000_000
STEP = 80_000
INPUTS_PER_SIZE = 1
PROBABILITY = 0.5



def generateInputs():

    if(not os.path.isfile(GENERATOR)):
        if(not os.path.isfile(f"{GENERATOR}.cpp")):
            print("[ERROR] randGeneoTree generator not found!")
            return
        os.system(f"g++ {GENERATOR}.cpp -o {GENERATOR}")

    print("Generating Inputs...")

    for i in range(MINIMUM_INPUT_SIZE, MAXIMUN_INPUT_SIZE+1, STEP):
        print(f"Generating input of size {i} ...")
        filename = INPUT_FOLDER + FILENAME  + "_" + str(i)
        os.system(f"./{GENERATOR} {i} {PROBABILITY} >> {filename}")
        print("Completed!\n")
                 

    print("All Generations completed!\n\n")


def calculateTime():

    header = ['Input Size', 'Time']
    data = []


    for file in sorted([(os.path.getctime(INPUT_FOLDER + str(x)),x) for x in os.listdir(INPUT_FOLDER)]):
        filename = str(file[1])
        print(filename)
        
        input_size = filename.split("_")[1]
        start = timer()
        os.system(EXECUTABLE_PATH + " < " + INPUT_FOLDER + filename + r" > /dev/null")
        end = timer()
        
        elaped_time = (end- start)

        data.append([input_size, elaped_time])

        print(f"{elaped_time} seconds\n")


    with open(DOCS_FOLDER + f"perfomance.csv", 'w', encoding='UTF8', newline='') as file:
        writer = csv.writer(file)

        # write the header
        writer.writerow(header)

        # write multiple rows
        writer.writerows(data)


        
def main():

    pathlib.Path(DOCS_FOLDER).mkdir(parents=True, exist_ok=True)

    if(os.path.isdir(INPUT_FOLDER)):
        calculateTime()
        return
    
    pathlib.Path(INPUT_FOLDER).mkdir(parents=True, exist_ok=True)

    generateInputs()
    calculateTime()
    
    

        

if __name__ == "__main__":
    main()