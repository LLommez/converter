Hello! My name is Lucca, and I will guide you on how to use the converter program. This program transforms .log files into .pqr files and also generates two additional files: charges_atoms.log, which contains atoms and their charges, and xyz.log, which contains the coordinates extracted from the .log file.

Important Note: If your .log file contains only coordinates, the charges_atoms.log file will be blank, and the .pqr file will not be generated. Therefore, it is essential that your .log file also includes the charges.

--Usage Instructions--
Download the Converter:
    Download the converter.zip file.

Extraction:
    Navigate to the directory where converter.zip is located and extract the contents. You will obtain a folder named converter.

Folder Structure:
    Inside the converter folder, you will find:
        inputs: To store your input files.
        instructions: Where you are reading these instructions.
        outputs: To store the generated files.

File Handling:
    After generating the files output.pqr, charges_atoms.log, and xyz.log, move them to the outputs folder or any other directory of your choice and/or rename them. This is necessary to avoid overwriting the files in future executions.

Test File:
    In the converter folder, there is a file named input.log used to calibrate the program. You can use it to test the program's functionality. You will also find an example of output.pqr, charges_atoms.log, and xyz.log in the outputs folder for reference.

---Running the Converter---
Open a terminal.
Navigate to the converter folder.
Ensure that the .log file you wish to convert is in the same directory as the converter executable.
Execute the command: ./converter <filename.log>
Replace <filename.log> with the name of your .log file.
For calibration:./converter input_calibration.log

After running the command, the generated files will be in the converter folder.

For any problems or errors, contact technical support at the email: profluccalommez@gmail.com.

Happy computing!
