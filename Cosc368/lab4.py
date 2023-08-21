from math import log2


filename = "logWidths.txt"
output_filename = "summary.csv"
ID_sig_figs = 2
mean_time_sig_figs = 3

def Get_ID(dist, width):
    return log2(dist / width + 1)

with open(filename, "r") as f:
    lines = f.readlines()


mean_data = {}

# get mean data
for line in lines:
    name, dist, width, index, time_taken = line.split()
    dist = int(dist)
    width = int(width)
    time_taken = float(time_taken)
    index = int(index)
    if index < 2:   # ignore first two clicks
        continue    # to avoid outliers
    if (dist, width) not in mean_data:
        mean_data[(dist, width)] = []   # create list because i accidentally did too many trials
    mean_data[(dist, width)].append(time_taken)

for key in mean_data:
    mean_data[key] = sum(mean_data[key]) / len(mean_data[key]) / 1000 # convert to seconds

# print results

print(f"have {len(mean_data)} data points")
for key, value in mean_data.items():
    print(f"{key} {round(value, 3)}s")


# get ID and mean time

ID_data = {}

for key, value in mean_data.items():
    dist, width = key
    ID = Get_ID(dist, width)
    if ID not in ID_data:
        ID_data[ID] = []
    ID_data[ID].append(value)

for key in ID_data:
    ID_data[key] = sum(ID_data[key]) / len(ID_data[key])


# print ID and mean time

print(f"have {len(ID_data)} data points")
for key, value in ID_data.items():
    print(f"{round(key, 2)} {round(value, 3)}s")

# log results

with open(output_filename, "w+") as f:
    f.write(f"ID,Mean Time\n")
    for key, value in ID_data.items():
        f.write(f"{round(key, ID_sig_figs)},{round(value, mean_time_sig_figs)}\n")