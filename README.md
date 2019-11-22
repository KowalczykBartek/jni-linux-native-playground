I always wanted to make some JNI !

in native-playground/src/main/c :
```
gcc -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/darwin" -dynamiclib -o libsocket.dylib Socket.c
```

and as VM argument

```
-Djava.library.path=.../native-playground/src/main/java
```