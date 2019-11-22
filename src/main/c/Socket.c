#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header
#include "Socket.h"   // Generated
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr

JNIEXPORT jint JNICALL Java_Socket_socket0(JNIEnv *env, jobject obj) {
	int socket_desc;
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);

	if (socket_desc == -1)
	{
		printf("[NATIVE] Could not create socket\n");
		return socket_desc;
	}

    printf("[NATIVE] socket's fd received %d \n", socket_desc);

	jclass class_socket = (*env)->GetObjectClass(env, obj);
    jfieldID fid = (*env)->GetFieldID(env, class_socket, "fd","I");
    (*env)->SetIntField(env, obj ,fid, socket_desc);

	return 0;
}

JNIEXPORT jint JNICALL Java_Socket_connet0(JNIEnv *env, jobject obj) {

	/* get the class */
	jclass class_socket = (*env)->GetObjectClass(env, obj);

	jfieldID portId = (*env)->GetFieldID(env, class_socket, "port", "I");
	jint port = (*env)->GetIntField(env, obj, portId);

	jfieldID fdiD = (*env)->GetFieldID(env, class_socket, "fd", "I");
	jint socketFd = (*env)->GetIntField(env, obj, fdiD);

	// get field
	jfieldID byteArrayField = (*env)->GetFieldID(env, class_socket, "host", "[B");
	jbyteArray byteArray = (*env)->GetObjectField(env, obj, byteArrayField);

	jbyte *host = (*env)->GetByteArrayElements(env, byteArray, 0);
	jint hostPathLen = (*env)->GetArrayLength(env, byteArray);

	printf("[NATIVE] connecting to %d %d %s \n", port, hostPathLen, host);

	// connet socket
	struct sockaddr_in server;
	server.sin_addr.s_addr = inet_addr(host);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	//Connect to remote server
	if (connect(socketFd , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		printf("[NATIVE] connect error\n");
		return -1;
	}

	return 0;
}

JNIEXPORT jbyteArray JNICALL Java_Socket_read0(JNIEnv *env, jobject obj) {

	jclass class_socket = (*env)->GetObjectClass(env, obj);
	jfieldID fdiD = (*env)->GetFieldID(env, class_socket, "fd", "I");
	jint socketFd = (*env)->GetIntField(env, obj, fdiD);

    char onStackData[2000];
    int recvData = recv(socketFd, onStackData , 2000 , 0);
    if(recvData < 0)
	{
		printf("[NATIVE]recv failed\n");
	}


    jbyteArray data = (*env)->NewByteArray(env, recvData);
    if (data == NULL) {
        return NULL; //  out of memory error thrown
    }

    // creat bytes from byteUrl
    jbyte *bytes = (*env)->GetByteArrayElements(env, data, 0);
    int i;
    for (i = 0; i < recvData; i++) {
        bytes[i] = onStackData[i];
    }

    // move from the temp structure to the java structure
    (*env)->SetByteArrayRegion(env, data, 0, recvData, bytes);

    return data;

}