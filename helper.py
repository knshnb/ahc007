import statistics
import os

os.system("g++ main.cpp -o hoge")
scores = []
for i in range(60, 70):
    in_file = f"in/{i:04}.txt"
    out_file = f"out/{i:04}.txt"
    os.system(f"time ./hoge < tools/{in_file} > tools/{out_file}")
    out = os.popen(f"cd tools && cargo run --release --bin vis {in_file} {out_file}")
    score = int(out.read().split()[-1]) / 1e8
    print(score)
    scores.append(score)

print(scores)
mean = statistics.mean(scores)
print("mean: ", mean)
print("sum: ", mean * 15)
