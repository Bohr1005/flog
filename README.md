### flog
flog(flash logger) is a logging library I use in my high-frequency trading system, it's a lightweight and high-performance logging library that supports asynchronous logging to the console or files.I separated it from my high-frequency trading system and partially open-sourced

### Run example
```shell
bazel run log_cout
[10:18:55.691850716 log_cout.cpp:8 INFO] hello world
```

### benchmark
It performs significantly better than spdlog on device with Intel(R) Core(TM) i7-8550U CPU @ 1.80GHz

write 1,000,000 items to file

```shell
bazel run bm_logger --cxxopt="-O3"
benchmark file elapse:0.0595878 avg:1.67819e+07/sec
```