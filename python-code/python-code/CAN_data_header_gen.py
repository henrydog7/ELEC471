#!/usr/bin/env python3
# Automatic generation of CAN data header file from Simulink exported xlsx file
# This script reads an xlsx file exported from Simulink containing CAN message data
# For each sheet in the xlsx file, it generates a 2D array of CAN_Data structs in CAN_data.h 

import pandas as pd
import numbers


""" User Configurable Parameters """
fileName = "brakelight_example_sldvdata.xlsx"   # Input file name exported from Simulink


dfs = pd.read_excel(fileName, sheet_name=None)
dfs = {name.replace(" ", "_"): sheet for name, sheet in dfs.items()}
sheet_names = list(dfs.keys())
print("Found sheets: ")
print(sheet_names, "\n")


# === For each sheet in the xlsx file, write data to CAN_data.h ===
with open("CAN_data.h", "w") as f:
    f.write("#ifndef CAN_DATA_H\n#define CAN_DATA_H\n\n")
    f.write("#include <stdint.h>\n\n")
    
    unique_cols = set()
    for df in dfs.values():
        df.columns = [col.replace(" ", "_") if isinstance(col, str) else col for col in df.columns]
        unique_cols.update(df.columns.to_list())

    unique_cols.discard("time")
    
    f.write("enum class CAN_MsgType {\n")
    for col in sorted(unique_cols):
        f.write(f"    {col},\n")
    f.write("};\n\n")
    f.write("typedef struct {\n    float time;\n    CAN_MsgType msgType;\n    float data;\n} CAN_Data;\n\n")

    for sheet_name, df in dfs.items():
        df = df.copy()
        # df = df.iloc[4:].reset_index(drop=True)
        
        first_valid_row = 0
        for i, row in df.iterrows():
            if all(isinstance(v, numbers.Number) and not pd.isna(v) for v in row):
                first_valid_row = i
                break
        
        print(f"[{sheet_name}] First valid numeric row found at index {first_valid_row}")
        df = df.loc[first_valid_row:].reset_index(drop=True)
        
        columns = [col for col in df.columns if col != "time"]
        num_cols = len(columns)
        num_rows = len(df)
        
        f.write("const CAN_Data data_{}[{}][{}]".format(sheet_name, num_rows, num_cols))
        f.write(" = {\n")
        for _, row in df.iterrows():
            f.write("    { ")
            ts = row['time']
            for col in columns:
                msg_type = col
                data_value = row[col]
                f.write("{{{:.5f}, CAN_MsgType::{}, {:.5f}}}, ".format(ts, msg_type, data_value))
            f.write("},\n")

        f.write("};\n\n")
    
    f.write("// Helper macros for cycling through data arrays\n")
    f.write("#define NUM_ROWS(arr)  (sizeof(arr) / sizeof((arr)[0]))\n")
    f.write("#define NUM_COLS(arr)  (sizeof((arr)[0]) / sizeof((arr)[0][0]))\n\n")
    f.write("\n\n")
    f.write("#endif // CAN_DATA_H\n")

print("\nWrote CAN data to CAN_data.h")
