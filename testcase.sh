# no output if no A/B pair, or only has reverse AB pair
./assembly_line 7 2 1 1 A 0 
./assembly_line 7 2 1 1 B 0
./assembly_line 7 2 1 2 B 0 A 1
## simulate 6 cycles, 2 pipeline stages, 2 workers at A at pos0 and B at pos1
# c0 workerA grab, c2 workerA put, c3 workerB grab, c5 workerB put, c6 sees a output drained out, so finished product count = 0 or 1
./assembly_line 6 2 1 2 A 0 B 1
./assembly_line 7 2 1 2 A 0 B 1
# then start the pipeline
# c2 workerA grab, c4 workerA put, c5 workerB grab, c7 workerB put, c8 sees a output drained out, so finished product count = 1 or 2
./assembly_line 7 2 1 2 A 0 B 1
./assembly_line 8 2 1 2 A 0 B 1

## simulate 11 cycles, 4 pipeline stages, 4 workers, workerA pos 0/1, workerB pos 1/2
# c0 A0 grab                   pipe
# c1 
# c2 A1 grab, A0 put+grab
# c3 
# c4 B0 grab, A1 put+grab, A0 put+grab
# c5 
# c6 B0 put+grab
# c7 
# c8 B1 put Out1
# c9 
# c10 Out2
./assembly_line 11 4 1 3 A 0 A 1 B 2

## simulate 12 cycles, 4 pipeline stages, 4 workers, workerA pos 0/1, workerB pos 1/2
# start time 4pipe+2+workerA+workerB=8 cycles, then a workerA/B pair is 1/2 IPC, 12-8=4 output product
./assembly_line 12 4 1 4 A 0 A 1 B 2 B 1

## simulate 11 cycles, 4 pipeline stages, 6 workers, workerA pos 0/1/1, workerB pos 1/2/2
# start time 4pipe+2+workerA+workerB=8 cycles, then a workerA/B pair is 1/2 IPC, (12-8)*1.5=6 output product
./assembly_line 12 4 2 6 A 0 A 1 B 2 B 1 A 1 B 2 

##output product = ceil( (cycle - 4 - num_of_pipe) * min(input_rate, num_of_AB_pairs * worker_throughput) )
