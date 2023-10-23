### flog
flog(flash logger) is a logging library I use in my high-frequency trading system, it's a lightweight and high-performance logging library that supports asynchronous logging to the console or files.I separated it from my high-frequency trading system and partially open-sourced

### why is the performance excellent?
+ Using a lock-free circular queue to store logs, and ensuring that the elements in the queue are arranged continuously in memory.

+ The size of each log is aligned with cache size.

+ Each log is directly emplaced at the end of the queue in binary without copy or memory allocation.



### run example
```shell
bazel run log_cout
[10:18:55.691850716 log_cout.cpp:8 INFO] hello world
```

### benchmark
It performs significantly better than spdlog on device with Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz

write 1,000,000 items of size 50 bytes each to file

```shell
bazel run bm_logger --cxxopt="-O3"
benchmark file elapse:0.05896 avg:1.69607e+07/sec
```