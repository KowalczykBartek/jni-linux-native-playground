/**
 * Java binding for tun/tap linux interface.
 */
public class TunTap {

    static {
        System.loadLibrary("tuntap");
    }
    private int fd; //tun/tap is represented by ordinary file descriptor

    public void setFd(int fd) {
        this.fd = fd;
    }

    public int tun_alloc() {
        int tunfd = tun_alloc0();
        if(tunfd < 0) {
            throw new RuntimeException("Cannot create TUN/TAP interface - make sure you start app as root.") ;
        }
        this.fd = tunfd;
        return fd;
    }

    private native int tun_alloc0();
    public native byte[] read0();

    //fixme toString
    //fixme hashCode
    //fixme equals
}
