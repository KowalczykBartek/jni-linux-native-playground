#include <jni.h>        // JNI header provided by JDK
#include <stdio.h>      // C Standard IO Header
#include "Socket.h"   // Generated
#include <string.h>
#include <stdlib.h>

JNIEXPORT jint JNICALL Java_Socket_socket(JNIEnv *env, jobject obj) {
   printf("creating socket \n");
   return 0;
}

JNIEXPORT jint JNICALL Java_Socket_connet(JNIEnv *env, jobject obj) {

	/* get the class */
	jclass class_socket = (*env)->GetObjectClass(env, obj);

	jfieldID portId = (*env)->GetFieldID(env, class_socket, "port", "I");
	jint port = (*env)->GetIntField(env, obj, portId);

	// get field
	jfieldID byteArrayField = (*env)->GetFieldID(env, class_socket, "host", "[B");
	jbyteArray byteArray = (*env)->GetObjectField(env, obj, byteArrayField);

	jbyte *host = (*env)->GetByteArrayElements(env, byteArray, 0);
	jint host_path_len = (*env)->GetArrayLength(env, byteArray);

	printf("connecting to %d %d %s \n", port, host_path_len, host);

	return 0;
}