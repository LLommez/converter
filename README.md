Hello! My name is Lucca, and I'll guide you through using the "converter" program. This program converts .log outputs (from Gaussian) and .molden.input outputs (from Orca) into .pqr files, as well as generating two additional files: charges_atoms.log, which contains atoms and their charges, and xyz.log, which contains coordinates extracted from the files.

Important Note (1): If your .log file contains only coordinates, the charges_atoms.log file will be blank, and the .pqr file will not be generated. Therefore, it is essential that your .log file also includes charges.

Important Note (2): If your .molden.input file contains only coordinates, the charges in the charges_atoms.log file will be calculated classically at runtime. Therefore, it is recommended that your .log file also includes charges calculated in MP2 by Orca itself to get the best out of the converter.

Important Note (3): When using Orca to calculate MP2 (or any other calculation), you must include the following lines in your input file before the calculation:

```
    %output
        Print[P_Molden] 1
    end
```

This will ensure the file is output in the .molden.input format.

---

--Usage Instructions--

Download the Converter:
   Download the file converter.zip.

Extraction:
   Navigate to the directory where converter.zip is located and extract its contents. You will obtain a folder named "converter."

Folder Structure:
   Inside the "converter" folder, you will find:
   - inputs: to store your input files.
   - instructions: where you’re reading these instructions.
   - outputs: to store the generated files.

Test File:
   In the converter folder, there is a file called "calibration_gauss.log" and "calibration.molden.input" used to calibrate the program. You can use them to test the program's functionality. You'll also find an example of output.pqr, charges_atoms.log, and xyz.log in the outputs folder for reference.

---

--Running the Converter--

1. Open a terminal.
2. Navigate to the "converter" folder.
3. Ensure that the file you want to convert is in the same directory as the converter executable.
4. Run the command: ./converter
5. Select your file (it will list all files in the directory).
6. Choose the input type (Gaussian or Orca).
7. Your .pqr will be generated.

After running the command, the generated files will be in the "converter" folder.

For any issues or errors, please contact technical support at: profluccalommez@gmail.com.

Happy calculations! :D
