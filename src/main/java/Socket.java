public class Socket
{
	static {
		System.loadLibrary("socket");
	}

	private byte[] host;
	private int port;

	public Socket(String host, int port) {
		this.host = host.getBytes();
		this.port = port;
	}

	public native int socket();
	public native int connet();
}
