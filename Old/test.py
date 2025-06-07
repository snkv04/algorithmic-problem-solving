



# # generate_gdb_script.py

# combinations = [
#     [1, 2, 3, 6, 5, 4],
#     [1, 6, 5, 4, 3, 2]
#     # Add more combinations as needed
# ]

# with open("dynamic_gdb_script.txt", "w") as script_file:
#     script_file.write("target your_executable\n")
#     script_file.write("break phase_6\n")
#     script_file.write("break explode_bomb\n")
#     script_file.write("run\n")

#     for combo in combinations:
#         args_str = " ".join(map(str, combo))
#         script_file.write(f"set args {args_str}\n")
#         script_file.write("c\n")
#         script_file.write("if $_breakpoint == 2\n")
#         script_file.write("  c\n")
#         script_file.write("end\n")

# print("Dynamic GDB script generated: dynamic_gdb_script.txt")


f = open("texttext.txt", "w")
for i in range(1000000): f.write(f"{i} ")
f.write("\n")
f.close()