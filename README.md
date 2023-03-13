1. Clone the repository
```
git clone git@github.com:Faramax/sdb_reconnect_mt.git
cd sdb_reconnect_mt
git submodule init
git submodule update
```

2. Build a7 software. For this you need to have installed sysroot /opt/st/skrm/3.1-snapshot
After that deploy the software to your board.
```
mkdir build
mkdir build/a7
cd build/a7
cmake  -GNinja -DCMAKE_TOOLCHAIN_FILE=../../arm-tools/a7-toolchain.cmake -DCMAKE_SDK_PATH=/opt/st/skrm/3.1-snapshot ../../
cmake --build .
scp sw/mpu/manual_test/sdb_reconnect/sdb_reconnect_manual_test root@myir:
cd ../../
```

3. Build m4 software. For this you need to unarchive the toolchain. It's included in the test. After that deploy the firmware to your board.
```
7z x arm-tools/gcc-arm-none-eabi/gcc-arm-none-eabi-10-2020-q4-major.7z -aos -oarm-tools/gcc
mkdir build/m4
cd build/m4
cmake -GNinja -DCMAKE_TOOLCHAIN_FILE=../../arm-tools/m4-toolchain.cmake ../../
cmake --build .
scp sw/mcu/manual_tests/sdb_reconnect_test/mt_sdb_reconnect.elf root@myir:/lib/firmware
```

4. Start the test
```
ssh root@myir
echo -n mt_sdb_reconnect.elf > /sys/class/remoteproc/remoteproc0/firmware
echo start > /sys/class/remoteproc/remoteproc0/state
./sdb_reconnect_manual_test
```
