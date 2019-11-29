I always wanted to make some JNI !

## socket example

```
gcc -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" -shared -o src/main/c/libsocket.so src/main/c/Socket.c
./gradlew socketExample

sudo $JAVA_HOME/bin/java -Djava.library.path=./src/main/c -jar build/libs/native-playground-socket-1.0-SNAPSHOT.jar
```

## tun/tap example
In order to run tun/tap example you need to perform following steps (you need linux :/ ):
```
gcc -fPIC -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/linux" -shared -o src/main/c/libtuntap.so src/main/c/TunTap.c

./gradlew tuntapExample

#yeah, you need sudo, setcap didn't work for me :) but you can try to do that.
sudo $JAVA_HOME/bin/java -Djava.library.path=./src/main/c -jar build/libs/native-playground-tuntap-1.0-SNAPSHOT.jar

sudo ip addr add 192.168.0.1/24 dev tun0
sudo ip link set up dev tun0
```

## rescue
because we are working around virtual interfaces, it is possible that we will left mess there :D 
this is set of quite helpful commands (at least for me):

```
sudo ifconfig tun0 down
sudo ip link delete tun0
```