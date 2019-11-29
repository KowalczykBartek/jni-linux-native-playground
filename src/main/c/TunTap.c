#include <jni.h>
#include "TunTap.h"
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

JNIEXPORT jint JNICALL Java_TunTap_tun_1alloc0(JNIEnv *env, jobject obj) {
    char tun_name[] = "tun0";
    int tun_fd = tun_alloc(tun_name, IFF_TUN);
    return tun_fd;
}

JNIEXPORT jbyteArray JNICALL Java_TunTap_read0(JNIEnv *env, jobject obj){
    jclass class_tuntap = (*env)->GetObjectClass(env, obj);
    jfieldID fdId = (*env)->GetFieldID(env, class_tuntap, "fd", "I");
    jint tuntapFd = (*env)->GetIntField(env, obj, fdId);

    unsigned char buffer[2000];
    int nread;

    nread = read(tuntapFd, buffer,sizeof(buffer));

    if(nread < 0) {
        return NULL;
    }

    jbyteArray data = (*env)->NewByteArray(env, nread);
    if (data == NULL) {
        return NULL;
    }

    jbyte *bytes = (*env)->GetByteArrayElements(env, data, 0);
    int i;
    for (i = 0; i < nread; i++) {
        bytes[i] = buffer[i];
    }

    (*env)->SetByteArrayRegion(env, data, 0, nread, bytes);

    return data;
}

/*
* create tun/tap interface based on received params
* ref https://backreference.org/2010/03/26/tuntap-interface-tutorial/
*/
int tun_alloc(char *dev, int flags) {
    struct ifreq ifr;
    int fd, err;
    char *clonedev = "/dev/net/tun";

    if( (fd = open(clonedev, O_RDWR)) < 0 ) {
        return fd;
    }

    memset(&ifr, 0, sizeof(ifr));

    ifr.ifr_flags = flags;

    if (*dev) {
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    }

    if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ) {
        close(fd);
        return err;
    }

    strcpy(dev, ifr.ifr_name);
    return fd;
}