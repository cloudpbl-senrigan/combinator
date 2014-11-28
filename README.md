Install
----

```
$ cd tools/gyp
$ python setup.py install # if you use system-wide python, sudo is needed
$ cd ../../
$ cd third_party/mysql-connector-c++-1.1.4
$ cmake . && make -j5 && sudo make install
$ cd ../../third_party/yaml-cpp-0.5.1
$ cmake . && make -j5 && sudo make install
$ cd ../../
```

How to build
----

```
$ gyp -f ninja --depth . build/combinator.gyp # generate build.ninja
$ ninja -C out/Release
```
