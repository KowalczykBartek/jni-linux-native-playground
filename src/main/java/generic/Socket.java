package generic;

import java.util.Arrays;
import java.util.Objects;

/**
 * High level wrapper for JNI socket api.
 */
public class Socket {

    static {
        System.loadLibrary("socket");
    }

    private byte[] host;
    private int port;
    private int fd = 1;

    private Socket(String host, int port) {
        this.host = host.getBytes();
        this.port = port;
    }

    public static Socket of(String host, int port) {
        Socket socket = new Socket(host, port);
        int resp = socket.socket0();
        if (resp < 0) {
            throw new RuntimeException("Not able to create socket - no file descriptor returned.");
        }
        return socket;
    }

    /**
     * Connect to remote peer.
     * RuntimeException is thrown if connection cannot be established.
     */
    public void connect() {
        int res = connet0();
        if (res < 0) {
            throw new RuntimeException("Not able to connect to remote peer.");
        }
    }

    /**
     * Ask OS for corresponding file descriptor for this socket.
     *
     * @return result of socket() syscall.
     */
    private native int socket0();


    /*
     * Native section, 0 suffix means last, most internal method in the chain.
     */

    /**
     * call os's connect(fd) syscall to make tcp connection.
     *
     * @return result of connect() syscall
     */
    private native int connet0();
    public native byte[] read0();
    public native int write0(byte[] data);

    public int getPort() {
        return fd;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Socket socket = (Socket) o;
        return port == socket.port &&
                fd == socket.fd &&
                Arrays.equals(host, socket.host);
    }

    @Override
    public int hashCode() {
        int result = Objects.hash(port, fd);
        result = 31 * result + Arrays.hashCode(host);
        return result;
    }

    @Override
    public String toString() {
        return "generic.Socket{" +
                "host=" + Arrays.toString(host) +
                ", port=" + port +
                ", fd=" + fd +
                '}';
    }
}
