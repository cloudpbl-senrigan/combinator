Requirements
----
* g++
* ninja  
  On ubuntu, you can install ninja using `apt` as 
  ```
$ sudo apt-get install ninja-build
```



Install
----

```
$ cd tools/gyp
$ python setup.py install # if you use system-wide python, sudo is needed
$ cd ../../third_party/
$ cd mysql-connector-c++-1.1.4
$ cmake . && make -j5 && sudo make install
$ cd ../yaml-cpp-0.5.1
$ cmake . && make -j5 && sudo make install
$ cd ../google-glog
$ ./configure && make -j5 && sudo make install
$ cd ../../
```

How to build
----

```
$ gyp -f ninja --depth . build/combinator.gyp # generate build.ninja
$ ninja -C out/Release
```

How to Execute
----
w/o logging
```
$ ./out/Release/SenriganCombinator
```

w/ logging
```
$ mkdir log
$ GLOG_log_dir=./log ./out/Release/SenriganCombinator
```
